#include "connection.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>
#include <QSettings>
#include <QProcess>
#include <QVariant>
#include <windows.h> 

// Le QSqlDatabase n'est plus nécessaire ici car il est géré par le nom "qt_sql_default_connection"
// ou directement dans la méthode.

// --- 1. Implémentation du Singleton et du Destructeur ---

// Le constructeur est vide car l'initialisation se fait via createconnect()
Connection::Connection()
{
}

// Implémentation de l'instance Singleton
Connection& Connection::getInstance()
{
    // Crée l'instance unique la première fois qu'elle est appelée
    static Connection instance;
    return instance;
}

// Le destructeur ferme la connexion
Connection::~Connection()
{
    // La connexion est retirée si elle est nommée "qt_sql_default_connection"
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        if(db.isOpen()) {
            db.close();
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
            qDebug() << "Connexion fermée et retirée.";
        }
    }
}

// --- 2. Fonction Utilitaire : Lecture du Registre ---

// Fonction pour obtenir le nom exact du driver Oracle depuis le registre Windows
QStringList Connection::getOracleDriversFromRegistry()
{
    QStringList drivers;
    
    QStringList registryPaths = {
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\ODBC\\ODBCINST.INI",       // 64-bit
        "HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\ODBC\\ODBCINST.INI" // 32-bit
    };
    
    for (const QString &registryPath : registryPaths) {
        QSettings settings(registryPath, QSettings::NativeFormat);
        QStringList allSections = settings.childGroups();
        
        for (const QString &section : allSections) {
            if (section.contains("Oracle", Qt::CaseInsensitive)) {
                settings.beginGroup(section);
                if (settings.contains("Driver") || settings.contains("Setup")) {
                    if (!drivers.contains(section)) {
                        drivers.append(section);
                        qDebug() << "Driver Oracle trouvé dans le registre:" << section;
                    }
                }
                settings.endGroup();
            }
        }
    }
    return drivers;
}

// --- 3. Gestion du Schéma (FINANCES_HISTORIQUE) ---

bool Connection::initializeHistoriqueTable()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Base de données non connectée lors de l'initialisation de l'historique.";
        return false;
    }

    QSqlQuery query(db);

    // Vérifie si la table existe
    query.prepare("SELECT COUNT(*) FROM USER_TABLES WHERE TABLE_NAME = 'FINANCES_HISTORIQUE'");
    bool tableExists = false;
    if (query.exec() && query.next()) {
        tableExists = (query.value(0).toInt() > 0);
    }
    
    // Crée la table si elle n'existe pas (Ajout de PROJET_ID pour une meilleure cohérence)
    if (!tableExists) {
        QString createTableSQL =
            "CREATE TABLE FINANCES_HISTORIQUE ("
            "ID NUMBER PRIMARY KEY, "
            "REVENU NUMBER(10,2), "
            "DEPENSE NUMBER(10,2), "
            "BENEFICES NUMBER(10,2), "
            "TVA NUMBER(10,2), "
            "DELAI DATE, "
            "MODEPAIMENT VARCHAR2(50), "
            "STATUT VARCHAR2(50), "
            "PROJET_ID VARCHAR2(50), " // <-- Colonne importante pour la finance
            "DATE_SUPPRESSION TIMESTAMP DEFAULT CURRENT_TIMESTAMP, "
            "ROWID_ORIGINAL VARCHAR2(50))";

        if (!query.exec(createTableSQL)) {
            qDebug() << "Erreur lors de la création de la table FINANCES_HISTORIQUE:" << query.lastError().text();
        } else {
            qDebug() << "Table FINANCES_HISTORIQUE créée avec succès";
        }
    }

    // Vérifie et crée la séquence si nécessaire
    query.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
    bool sequenceExists = false;
    if (query.exec() && query.next()) {
        sequenceExists = (query.value(0).toInt() > 0);
    }

    if (!sequenceExists) {
        QString createSeqSQL = "CREATE SEQUENCE SEQ_FINANCES_HISTORIQUE START WITH 1 INCREMENT BY 1";
        if (!query.exec(createSeqSQL)) {
            qDebug() << "Erreur lors de la création de la séquence:" << query.lastError().text();
        } else {
            qDebug() << "Séquence SEQ_FINANCES_HISTORIQUE créée avec succès";
        }
    }

    return true;
}

// --- 4. Méthode Principale de Connexion (createconnect) ---

bool Connection::createconnect()
{
    // Utiliser les identifiants spécifiques de votre premier fichier
    QString dsn = "PROJET2A"; // DSN du second fichier
    QString username = "maryem"; // User du second fichier
    QString password = "123456"; // Password du second fichier
    QString serviceName = "XE"; // Service du second fichier

    // Tentative de connexion 1 : Utilisation des identifiants du premier fichier
    QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC", "qt_sql_default_connection_temp1");
    db1.setDatabaseName("Projetbase"); // DSN du premier fichier
    db1.setUserName("C##Oussema");      // User du premier fichier
    db1.setPassword("esprit18");        // Password du premier fichier
    
    bool test = false;
    QString lastError;

    qDebug() << "Tentative 1: Identifiants 'Projetbase' / 'C##Oussema'";
    if (db1.open()) {
        test = true;
        qDebug() << "✓ Connexion établie avec succès (Mode 1)";
        // Renommer la connexion pour qu'elle devienne la connexion par défaut
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection_temp1");
        db.setDatabaseName("qt_sql_default_connection");
        QSqlDatabase::removeDatabase("qt_sql_default_connection_temp1");
    } else {
        lastError = db1.lastError().text();
        qDebug() << "✗ Échec (Mode 1):" << lastError;
        QSqlDatabase::removeDatabase("qt_sql_default_connection_temp1");

        // Tentative de connexion 2 : Utilisation du code multi-tentatives (second fichier)
        QSqlDatabase db2 = QSqlDatabase::addDatabase("QODBC", "qt_sql_default_connection");
        QStringList oracleDrivers = getOracleDriversFromRegistry();

        // STRATÉGIE A: DSN simple (PROJET2A)
        db2.setDatabaseName(dsn);
        db2.setUserName(username);
        db2.setPassword(password);
        
        qDebug() << "Tentative 2: DSN simple - " << dsn;
        if (db2.open()) {
            test = true;
            qDebug() << "✓ Connexion réussie (Mode 2A): DSN simple.";
        } else {
            // STRATÉGIE B: DSN avec driver spécifié
            QSqlDatabase::removeDatabase("qt_sql_default_connection");
            db2 = QSqlDatabase::addDatabase("QODBC", "qt_sql_default_connection");

            if (!oracleDrivers.isEmpty()) {
                for (const QString &driver : oracleDrivers) {
                    QString connStr = QString("Driver={%1};DSN=%2;Uid=%3;Pwd=%4;")
                                            .arg(driver).arg(dsn).arg(username).arg(password);
                    
                    db2.setDatabaseName(connStr);
                    if (db2.open()) {
                        test = true;
                        qDebug() << "✓ Connexion réussie (Mode 2B): driver explicite" << driver;
                        break;
                    } else {
                        lastError = db2.lastError().text();
                        QSqlDatabase::removeDatabase("qt_sql_default_connection");
                        db2 = QSqlDatabase::addDatabase("QODBC", "qt_sql_default_connection");
                    }
                }
            }
        }
    }

    // Si la connexion réussit, initialiser le schéma spécifique
    if (test) {
        initializeHistoriqueTable();
    } else {
        qDebug() << "\n=== DIAGNOSTIC FINAL D'ÉCHEC GLOBAL ===";
        qDebug() << "Aucune des méthodes n'a réussi à se connecter.";
        qDebug() << "Dernière erreur capturée:" << lastError;
        qDebug() << "Vérifiez les DSN: 'Projetbase' (User: C##Oussema) et 'PROJET2A' (User: maryem).";
        qDebug() << "=======================================\n";
    }

    return test;
}
