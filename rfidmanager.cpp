#include "rfidmanager.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTimer>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QApplication>  // ⭐ AJOUTEZ CETTE LIGNE ⭐


RFIDManager::RFIDManager(QObject *parent)
    : QObject(parent)
    , serialPort(nullptr)
    , isScanInCooldown(false)
{
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::readyRead, this, &RFIDManager::readSerialData);
    // ⭐ AJOUTEZ CE CODE APRÈS LA CONNEXION DU PORT SÉRIE ⭐
    scanCooldownTimer = new QTimer(this);
    scanCooldownTimer->setSingleShot(true);
    connect(scanCooldownTimer, &QTimer::timeout, this, [this]() {
        isScanInCooldown = false;
        qDebug() << "🔄 Prêt pour un nouveau scan";
    });
}

RFIDManager::~RFIDManager()
{
    stopRFID();

    // ⭐ AJOUTEZ CE CODE SI NÉCESSAIRE (Qt gère normalement la destruction) ⭐
    if (scanCooldownTimer && scanCooldownTimer->isActive()) {
        scanCooldownTimer->stop();
    }
}

bool RFIDManager::startRFID()
{
    // Essayer plusieurs ports COM
    QStringList portNames = {"COM3", "COM6", "COM4", "COM5", "COM7", "COM8", "COM9", "COM10"};

    foreach (const QString &portName, portNames) {
        qDebug() << "🔄 Tentative de connexion à" << portName << "...";

        serialPort->setPortName(portName);
        serialPort->setBaudRate(QSerialPort::Baud9600);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);

        if (serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "🎉✅ CONNECTÉ À" << portName << "- ARDUINO DÉTECTÉ!";
            serialPort->clear();
            emit arduinoConnected(true);
            return true;
        } else {
            qDebug() << "💥 ERREUR" << portName << ":" << serialPort->errorString();
        }
    }

    qDebug() << "❌ Aucun port COM disponible";
    emit arduinoConnected(false);
    emit errorOccurred("Aucun port COM disponible pour la connexion Arduino");
    return false;
}

void RFIDManager::stopRFID()
{
    if (serialPort && serialPort->isOpen()) {
        serialPort->close();
        qDebug() << "🔴 RFID déconnecté";
        emit arduinoConnected(false);
    }
}

bool RFIDManager::checkEmployeeUID(const QString &uid, QString &nom, QString &prenom, QString &role)
{
    // Nettoyer l'UID
    QString cleanedUID = uid;
    cleanupUID(cleanedUID);

    if (cleanedUID.isEmpty()) {
        qDebug() << "❌ UID vide après nettoyage";
        return false;
    }

    qDebug() << "🔍 Recherche employé avec UID:" << cleanedUID;

    // Vérification de la base de données
    QSqlQuery query;

    // Version 1: Vérifier d'abord si la colonne RFID_UID existe
    // Version 2: Utiliser une requête plus simple
    query.prepare("SELECT NOM, PRENOM, ROLE, STATUT FROM EMPLOYE WHERE RFID_UID = :uid");
    query.bindValue(":uid", cleanedUID);

    if (!query.exec()) {
        qDebug() << "❌ Erreur d'exécution de la requête:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString statut = query.value(3).toString();

        // Vérifier si l'employé est actif
        if (statut.toUpper() != "ACTIF") {
            qDebug() << "❌ Employé trouvé mais statut inactif:" << statut;
            return false;
        }

        nom = query.value(0).toString();
        prenom = query.value(1).toString();
        role = query.value(2).toString();

        qDebug() << "✅ Employé trouvé:" << nom << prenom << "-" << role << "- Statut:" << statut;
        return true;
    } else {
        qDebug() << "❌ Aucun employé trouvé avec UID:" << cleanedUID;
        return false;
    }
}

bool RFIDManager::associateCardToEmployee(int employeId, const QString &rfidUID)
{
    if (employeId <= 0 || rfidUID.isEmpty()) {
        qDebug() << "❌ Paramètres invalides";
        sendToArduino("DENIED");
        return false;
    }

    // Nettoyer l'UID
    QString cleanedUID = rfidUID;
    cleanupUID(cleanedUID);

    if (cleanedUID.isEmpty()) {
        qDebug() << "❌ UID invalide après nettoyage";
        sendToArduino("DENIED");
        return false;
    }

    qDebug() << "🔗 Association carte" << cleanedUID << "à employé ID:" << employeId;

    // Vérifier si l'employé existe
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT NOM, PRENOM, STATUT FROM EMPLOYE WHERE ID = :id");
    checkQuery.bindValue(":id", employeId);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "❌ Employé non trouvé ID:" << employeId;
        sendToArduino("DENIED");
        return false;
    }

    QString nom = checkQuery.value(0).toString();
    QString prenom = checkQuery.value(1).toString();
    QString statut = checkQuery.value(2).toString();

    if (statut.toUpper() != "ACTIF") {
        qDebug() << "❌ Employé inactif:" << nom << prenom << "- Statut:" << statut;
        sendToArduino("DENIED");
        return false;
    }

    // Vérifier si la carte est déjà associée à un autre employé
    QSqlQuery checkRFIDQuery;
    checkRFIDQuery.prepare("SELECT ID, NOM, PRENOM FROM EMPLOYE WHERE RFID_UID = :rfid AND ID != :id");
    checkRFIDQuery.bindValue(":rfid", cleanedUID);
    checkRFIDQuery.bindValue(":id", employeId);

    if (checkRFIDQuery.exec() && checkRFIDQuery.next()) {
        int existingId = checkRFIDQuery.value(0).toInt();
        QString existingNom = checkRFIDQuery.value(1).toString();
        QString existingPrenom = checkRFIDQuery.value(2).toString();

        qDebug() << "❌ Carte déjà associée à l'employé ID:" << existingId
                 << "(" << existingNom << existingPrenom << ")";
        sendToArduino("DENIED");
        return false;
    }

    // Mettre à jour l'employé avec le RFID_UID
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE EMPLOYE SET RFID_UID = :rfid WHERE ID = :id");
    updateQuery.bindValue(":rfid", cleanedUID);
    updateQuery.bindValue(":id", employeId);

    if (updateQuery.exec()) {
        int rowsAffected = updateQuery.numRowsAffected();
        qDebug() << "📊 Lignes affectées par UPDATE:" << rowsAffected;

        if (rowsAffected > 0) {
            qDebug() << "✅ Carte" << cleanedUID << "associée à l'employé" << employeId
                     << "(" << nom << prenom << ")";
            sendToArduino("ASSOCIATED");
            return true;
        } else {
            qDebug() << "⚠️ Aucune ligne mise à jour (l'UID était peut-être déjà identique)";

            // Vérifier si l'UID était déjà le même
            QSqlQuery verifyQuery;
            verifyQuery.prepare("SELECT RFID_UID FROM EMPLOYE WHERE ID = :id");
            verifyQuery.bindValue(":id", employeId);

            if (verifyQuery.exec() && verifyQuery.next()) {
                QString currentUID = verifyQuery.value(0).toString();
                if (currentUID == cleanedUID) {
                    qDebug() << "ℹ️ L'employé avait déjà cet UID";
                    sendToArduino("ASSOCIATED");
                    return true;
                }
            }

            sendToArduino("DENIED");
            return false;
        }
    } else {
        qDebug() << "❌ Erreur SQL lors de l'UPDATE:" << updateQuery.lastError().text();
        sendToArduino("DENIED");
        return false;
    }
}

void RFIDManager::sendToArduino(const QString &command)
{
    if (serialPort && serialPort->isOpen()) {
        QString fullCommand = command + "\n";
        qint64 bytesWritten = serialPort->write(fullCommand.toUtf8());
        serialPort->flush();

        qDebug() << "📤 Commande envoyée à Arduino:" << command
                 << "(bytes:" << bytesWritten << ")";
    } else {
        qDebug() << "❌ Impossible d'envoyer à Arduino - port fermé";
    }
}

void RFIDManager::cleanupUID(QString &uid)
{
    // Supprimer tous les caractères non hexadécimaux
    uid = uid.remove(QRegularExpression("[^A-Fa-f0-9]")).toUpper();
}

void RFIDManager::readSerialData()
{
    static QByteArray buffer;

    if (!serialPort || !serialPort->isOpen()) {
        return;
    }

    // Lire toutes les données disponibles
    buffer.append(serialPort->readAll());

    //qDebug() << "📦 Données brutes reçues. Taille buffer:" << buffer.size();

    // Traiter toutes les lignes complètes
    while (true) {
        int lineEnd = buffer.indexOf('\n');
        if (lineEnd == -1) {
            // Pas de ligne complète, attendre plus de données
            break;
        }

        // Extraire la ligne complète
        QByteArray lineData = buffer.left(lineEnd);

        // Retirer \r si présent
        if (lineData.endsWith('\r')) {
            lineData.chop(1);
        }

        // Retirer la ligne traitée du buffer
        buffer = buffer.mid(lineEnd + 1);

        // Convertir en QString et nettoyer
        QString line = QString::fromUtf8(lineData).trimmed();

        if (!line.isEmpty()) {
            qDebug() << "📨 LIGNE REÇUE:" << line;
            emit arduinoMessageReceived(line);
            processReceivedLine(line);
        }
    }

    // Nettoyer le buffer s'il devient trop gros
    if (buffer.size() > 1024) {
        qDebug() << "⚠️ Buffer trop grand, nettoyage:" << buffer.size() << "octets";
        buffer.clear();
    }
}

void RFIDManager::processReceivedLine(const QString &line)
{
    QString trimmedLine = line.trimmed();

    if (trimmedLine.isEmpty()) {
        return;
    }

    // Vérifier si c'est une ligne RFID
    if (trimmedLine.startsWith("UID:") ||
        trimmedLine.startsWith("RFID:") ||
        trimmedLine.contains("UID:", Qt::CaseInsensitive)) {
        processRFIDLine(trimmedLine);
    }
    else if (trimmedLine.startsWith("DEBUG:") ||
             trimmedLine.startsWith("ARDUINO:") ||
             trimmedLine.startsWith("ERROR:")) {
        qDebug() << "🔧 Message Arduino:" << trimmedLine;
    }
    else {
        // Si c'est juste un UID simple (sans préfixe)
        QString possibleUID = trimmedLine;
        cleanupUID(possibleUID);

        if (possibleUID.length() >= 4 && possibleUID.length() <= 16) {
            qDebug() << "🎫 UID détecté (format simple):" << possibleUID;
            processRFIDLine("UID:" + possibleUID);
        } else {
            qDebug() << "📝 Message standard:" << trimmedLine;
        }
    }
}


void RFIDManager::processRFIDLine(const QString &line)
{
    // Anti-rebond
    if (isScanInCooldown) {
        qDebug() << "⏳ Scan ignoré (anti-rebond)";
        return;
    }
    isScanInCooldown = true;
    scanCooldownTimer->start(2000);

    QString uid;
    QString originalLine = line;

    // Extraire l'UID
    if (line.startsWith("UID:")) {
        uid = line.mid(4).trimmed();
    }
    else if (line.startsWith("RFID:DETECTED:")) {
        uid = line.mid(14).trimmed();
    }
    else if (line.startsWith("RFID:")) {
        uid = line.mid(5).trimmed();
    }
    else if (line.contains("UID:")) {
        int start = line.indexOf("UID:") + 4;
        uid = line.mid(start).trimmed();
    }
    else {
        uid = line.trimmed();
    }

    // Nettoyer UID
    cleanupUID(uid);

    if (uid.isEmpty() || uid.length() < 4) {
        qDebug() << "❌ UID invalide:" << uid;
        return;
    }

    qDebug() << "✅ UID VALIDE DÉTECTÉ:" << uid << "(longueur:" << uid.length() << ")";

    lastUID = uid;

    emit cardScanned(uid);

    QString nom, prenom, role;

    if (checkEmployeeUID(uid, nom, prenom, role)) {

        // Récupérer ID employé
        QSqlQuery idQuery;
        idQuery.prepare("SELECT ID FROM EMPLOYE WHERE RFID_UID = :uid");
        idQuery.bindValue(":uid", uid);

        QString employeeId = "N/A";
        if (idQuery.exec() && idQuery.next()) {
            employeeId = idQuery.value(0).toString();
        }

        qDebug() << "🎉 ACCÈS AUTORISÉ pour" << prenom << nom << "(" << role << ") - ID:" << employeeId;

        // 1️⃣ Envoyer GRANTED
        sendToArduino("GRANTED");

        // 2️⃣ Envoyer le nom + ID
        QString employeeInfo = prenom + " " + nom + "|" + employeeId;
        employeeInfo = employeeInfo.simplified();

        QTimer::singleShot(100, this, [this, employeeInfo]() {
            sendToArduino(employeeInfo);
            qDebug() << "📤 Infos employé envoyées:" << employeeInfo;
        });

        // 🚫 SUPPRIMÉ : "BIENVENUE:xxx"

    } else {

        qDebug() << "❌ ACCÈS REFUSÉ - Carte non autorisée";

        sendToArduino("DENIED");

        // 🚫 SUPPRIMÉ : "Carte Inconnue"
    }
}


// === FONCTION D'AUTHENTIFICATION RFID POUR EMPLOYE ===
bool authenticateEmployeWithRFID(QString &nom, QString &prenom, QString &role)
{
    qDebug() << "=== DÉMARRAGE AUTHENTIFICATION RFID EMPLOYE ===";

    RFIDManager rfid;

    if (!rfid.startRFID()) {
        QMessageBox::critical(nullptr, "ERREUR RFID",
                              "IMPOSSIBLE DE SE CONNECTER À L'ARDUINO!\n\n"
                              "Vérifiez que:\n"
                              "1. L'Arduino est branché sur USB\n"
                              "2. Le module RFID est connecté à l'Arduino\n"
                              "3. Le câble USB fonctionne\n"
                              "4. Aucun autre programme n'utilise le port COM");
        return false;
    }

    QDialog waitDialog;
    waitDialog.setWindowTitle("Authentification Employé - RFID");
    waitDialog.setFixedSize(450, 220);
    waitDialog.setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    QVBoxLayout *layout = new QVBoxLayout(&waitDialog);

    // Titre
    QLabel *titleLabel = new QLabel("🔑 AUTHENTIFICATION EMPLOYÉ");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #00BFFF; margin-bottom: 10px;");
    layout->addWidget(titleLabel);

    // Instructions
    QLabel *instructionLabel = new QLabel("🎫 APPROCHEZ VOTRE BADGE RFID\n\n"
                                          "Le système est prêt à lire votre carte...");
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setStyleSheet("font-size: 14px; color: #FFFFFF; margin: 15px;");
    layout->addWidget(instructionLabel);

    // Label pour afficher l'UID détecté
    QLabel *uidLabel = new QLabel("UID détecté: ---");
    uidLabel->setAlignment(Qt::AlignCenter);
    uidLabel->setStyleSheet("font-size: 12px; color: #FFFF00; font-family: monospace;");
    layout->addWidget(uidLabel);

    // Bouton Annuler
    QPushButton *cancelButton = new QPushButton("Annuler l'authentification");
    cancelButton->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #FF6B6B, stop:1 #EE5A52);"
        "    border: 2px solid #FF4757;"
        "    color: white;"
        "    border-radius: 8px;"
        "    font-weight: bold;"
        "    padding: 10px;"
        "    margin: 10px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #FF7979, stop:1 #FF6B6B);"
        "    border: 2px solid #FF3838;"
        "}"
        "QPushButton:pressed {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "    stop:0 #EE5A52, stop:1 #EA2027);"
        "}"
        );
    layout->addWidget(cancelButton);

    bool authenticated = false;

    // Connecter le signal cardScanned
    QObject::connect(&rfid, &RFIDManager::cardScanned,
                     [&](const QString &uid) {
                         qDebug() << "🔍 Carte détectée, vérification UID:" << uid;

                         // Mettre à jour l'affichage
                         uidLabel->setText("UID détecté: " + uid);
                         uidLabel->setStyleSheet("font-size: 12px; color: #00FF00; font-family: monospace; font-weight: bold;");

                         QApplication::processEvents();

                         QString empNom, empPrenom, empRole;
                         if (rfid.checkEmployeeUID(uid, empNom, empPrenom, empRole)) {
                             authenticated = true;
                             nom = empNom;
                             prenom = empPrenom;
                             role = empRole;

                             qDebug() << "🎉 AUTHENTIFICATION RÉUSSIE! Employé:"
                                      << prenom << nom << "- Rôle:" << role;

                             // Envoyer message de bienvenue à l'Arduino
                             QString welcomeMsg = "BIENVENUE " + prenom;
                             rfid.sendToArduino(welcomeMsg);

                             // Mettre à jour l'interface
                             instructionLabel->setText("✅ AUTHENTIFICATION RÉUSSIE!\n\n"
                                                       "Bienvenue " + prenom + " " + nom + "\n"
                                                                              "Rôle: " + role);
                             instructionLabel->setStyleSheet("font-size: 14px; color: #00FF00; font-weight: bold;");

                             // Attendre 2 secondes pour afficher le message
                             QTimer::singleShot(2000, &waitDialog, [&]() {
                                 waitDialog.accept();
                             });
                         } else {
                             qDebug() << "❌ Carte non reconnue ou employé inactif";

                             // Envoyer message de refus à l'Arduino
                             rfid.sendToArduino("REFUSEE");

                             // Mettre à jour l'interface
                             instructionLabel->setText("❌ ACCÈS REFUSÉ\n\n"
                                                       "Carte non autorisée\n"
                                                       "UID: " + uid);
                             instructionLabel->setStyleSheet("font-size: 14px; color: #FF0000; font-weight: bold;");
                             uidLabel->setStyleSheet("font-size: 12px; color: #FF0000; font-family: monospace; font-weight: bold;");

                             // Réinitialiser après 3 secondes
                             QTimer::singleShot(3000, &waitDialog, [&]() {
                                 instructionLabel->setText("🎫 APPROCHEZ VOTRE BADGE RFID\n\n"
                                                           "Le système est prêt à lire votre carte...");
                                 instructionLabel->setStyleSheet("font-size: 14px; color: #FFFFFF;");
                                 uidLabel->setText("UID détecté: ---");
                                 uidLabel->setStyleSheet("font-size: 12px; color: #FFFF00; font-family: monospace;");
                             });
                         }
                     });

    // Connecter le bouton Annuler
    QObject::connect(cancelButton, &QPushButton::clicked, [&]() {
        qDebug() << "❌ Authentification annulée par l'utilisateur";
        waitDialog.reject();
    });

    // Style de la boîte de dialogue
    waitDialog.setStyleSheet(
        "QDialog {"
        "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,"
        "    stop:0 #1a1a2e, stop:0.5 #16213e, stop:1 #0f3460);"
        "    border: 3px solid #00BFFF;"
        "    border-radius: 12px;"
        "}"
        "QLabel {"
        "    color: #FFFFFF;"
        "}"
        );

    qDebug() << "⏳ En attente d'une carte RFID...";

    // Exécuter la boîte de dialogue
    int result = waitDialog.exec();

    if (authenticated) {
        qDebug() << "🕒 Nettoyage final...";
        // Petite pause pour laisser l'Arduino afficher le message
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < 1000) {
            QCoreApplication::processEvents();
        }
    }

    rfid.stopRFID();
    qDebug() << "🔴 Connexion RFID fermée";

    return authenticated;
}
void RFIDManager::displayOnLCD(const QString &message1, const QString &message2)
{
    if (!serialPort || !serialPort->isOpen()) {
        qDebug() << "❌ Port non ouvert pour affichage LCD";
        return;
    }

    QString command;
    if (message2.isEmpty()) {
        command = "DISPLAY:" + message1;
    } else {
        command = "DISPLAY:" + message1 + "\\" + message2;
    }

    sendToArduino(command);
    qDebug() << "📺 Message LCD envoyé:" << command;
}
