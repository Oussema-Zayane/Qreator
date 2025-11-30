#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "client.h"
#include "employe.h"
#include "projet.h"
#include "finance.h"
#include "alerteretarddialog.h"
#include "historiquedialog.h"
// ... autres includes
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QSqlQuery>
#include <QHeaderView>
#include <QRegularExpressionValidator>
#include <QButtonGroup>
#include <QTableWidget>
#include <QFileDialog>    // AJOUTEZ CETTE LIGNE
#include <QDir>           // AJOUTEZ CETTE LIGNE
#include <QDebug>






MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentClientId(-1)
    , currentEmployeId(-1)
    , currentProjetId(-1)
    , currentFinanceId(-1)
    , currentEquipementId(-1)
    , currentMailingId(-1)
    , emailManager(new EmailSMTPManager(this))  // Initialisation directe
    , completionModel(new QStringListModel(this))
    , chatbotDialog(new ChatbotDialog(this))  // AJOUTE CETTE LIGNE
    , progressBarActifs(nullptr)  // INITIALISATION
    , progressBarNouveaux(nullptr) // INITIALISATION
    , labelStatsDetails(nullptr)   // INITIALISATION






{
    ui->setupUi(this);
    appliquerStyleModerne();
    creerIndicateursCirculaires();
    ajouterBoutonStatut();
    creerStatistiquesCirculaires();
    mettreAJourStatistiquesCirculaires();







    // Ajouter à la statusbar


    currentClientId = -1;
    currentEmployeId = -1;
    currentProjetId = -1;
    currentFinanceId = -1;
    currentEquipementId = -1;
    currentMailingId = -1;

    EmailSMTPManager *smtp = new EmailSMTPManager(this);

    emailManager->configurerSMTP(
        "oussamazayane2005@gmail.com",   // Ton Gmail
        "efhm hspd yewe dzew"            // Mot de passe d’application Google
        );

    smtp->envoyerEmail(
        "oussamazayane2005@gmail.com",
        "Bienvenue !",
        "<h2>Bonjour !</h2><p>Ceci est un email envoyé depuis Qt 😊</p>"
        );

    connect(smtp, &EmailSMTPManager::emailEnvoye, [](QString dest, bool ok, QString details){
        qDebug() << "Résultat =>" << dest << ok << details;
    });

    QPushButton *envoyerEmailBtn = new QPushButton("📧 Envoyer Email", this);
    envoyerEmailBtn->setObjectName("envoyerEmailClientBtn");
    envoyerEmailBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #17A2B8;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #138496;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #117A8B;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #BDC3C7;"
        "    color: #7F8C8D;"
        "}"
        );
    envoyerEmailBtn->setEnabled(false);

    // AJOUTER LE BOUTON DANS L'INTERFACE
    // Cherche le layout horizontal qui contient les boutons clients
    QHBoxLayout *boutonsLayout = nullptr;

    QLayout *layout = ui->groupBox->layout();
    if (layout) {
        for (int i = 0; i < layout->count(); ++i) {
            QLayoutItem *item = layout->itemAt(i);
            if (item && item->layout()) {
                QHBoxLayout *hbox = qobject_cast<QHBoxLayout*>(item->layout());
                if (hbox) {
                    for (int j = 0; j < hbox->count(); ++j) {
                        QWidget *widget = hbox->itemAt(j)->widget();
                        if (widget && widget->objectName().contains("addClientBtn")) {
                            boutonsLayout = hbox;
                            break;
                        }
                    }
                    if (boutonsLayout) break;
                }
            }
        }
    }

    // Ajouter le bouton
    if (boutonsLayout) {
        boutonsLayout->insertWidget(1, envoyerEmailBtn);
    } else {
        QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (mainLayout) {
            mainLayout->insertWidget(2, envoyerEmailBtn);
        }
    }


    // === BOUTON CHATBOT ===
    QPushButton *chatbotBtn = new QPushButton("💬 Assistant", this);
    chatbotBtn->setObjectName("chatbotBtn");
    chatbotBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #9B59B6;"
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #8E44AD;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #7D3C98;"
        "}"
        );

    // Ajouter le bouton dans le layout
    if (boutonsLayout) {
        boutonsLayout->insertWidget(2, chatbotBtn);  // Après le bouton email
    } else {
        QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (mainLayout) {
            mainLayout->insertWidget(3, chatbotBtn);
        }
    }

    // Connexion
    connect(chatbotBtn, &QPushButton::clicked, this, &MainWindow::on_chatbotBtn_clicked);

    // Initialiser le dialog chatbot
    chatbotDialog = new ChatbotDialog(this);

    // CONNEXIONS
    connect(envoyerEmailBtn, &QPushButton::clicked, this, &MainWindow::on_envoyerEmailClientBtn_clicked);
    connect(emailManager, &EmailSMTPManager::progressionEnvoi,this, &MainWindow::onProgression);

    qDebug() << "✅ Bouton 'Envoyer Email' ajouté dynamiquement";


    qDebug() << "Nombre de pages dans stackedWidget:" << ui->stackedWidget->count();
    initialiserInterfaceMailing();
    ui->stackedWidget->setCurrentWidget(ui->clientsPage);



    // Configuration de la navigation
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->clientsBtn);
    buttonGroup->addButton(ui->employesBtn);
    buttonGroup->addButton(ui->projetsBtn);
    buttonGroup->addButton(ui->financesBtn);
    buttonGroup->addButton(ui->equipementsBtn);
    buttonGroup->setExclusive(true);

    // Connexions pour la navigation
    connect(ui->clientsBtn, &QPushButton::clicked, this, &MainWindow::on_clientsBtn_clicked);
    connect(ui->employesBtn, &QPushButton::clicked, this, &MainWindow::on_employesBtn_clicked);
    connect(ui->projetsBtn, &QPushButton::clicked, this, &MainWindow::on_projetsBtn_clicked);
    connect(ui->financesBtn, &QPushButton::clicked, this, &MainWindow::on_financesBtn_clicked);
    connect(ui->equipementsBtn, &QPushButton::clicked, this, &MainWindow::on_equipementsBtn_clicked);



    // Configuration initiale pour toutes les gestions
    setWindowTitle("Smart Studio - Gestion Complète");

    // Configuration des tables
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->employeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->projetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->projetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->financeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->financeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Configuration des validateurs de saisie pour clients
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-ZÀ-ÿ]+([ '-][a-zA-ZÀ-ÿ]+)*$"), this);
    ui->clientNameEdit->setValidator(nameValidator);

    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"), this);
    ui->clientEmailEdit->setValidator(emailValidator);

    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(QRegularExpression("^(0[1-9])(?:[ _.-]?([0-9]{2})){4}$"), this);
    ui->clientPhoneEdit->setValidator(phoneValidator);

    // Validateurs pour employés
    ui->employeNameEdit->setValidator(nameValidator);
    ui->employeEmailEdit->setValidator(emailValidator);
    ui->employePhoneEdit->setValidator(phoneValidator);

    // Initialiser l'affichage
    refreshClientTable();
    refreshEmployeTable();
    refreshProjetTable();
    refreshFinanceTable();
    refreshEquipementTable();

    // Connecter les signaux et slots pour la gestion clients
    connect(ui->addClientBtn, &QPushButton::clicked, this, &MainWindow::on_addClientBtn_clicked);
    connect(ui->deleteClientBtn, &QPushButton::clicked, this, &MainWindow::on_deleteClientBtn_clicked);
    connect(ui->editClientBtn, &QPushButton::clicked, this, &MainWindow::on_editClientBtn_clicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_textChanged);
    connect(ui->clientTable, &QTableWidget::itemClicked, this, &MainWindow::on_clientTable_itemClicked);
    connect(ui->clearFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearFormBtn_clicked);
    connect(ui->refreshTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshTableBtn_clicked);
    connect(ui->exportPdfBtn, &QPushButton::clicked, this, &MainWindow::on_exportPdfBtn_clicked);
    connect(ui->activeClientsOnly, &QCheckBox::toggled, this, &MainWindow::on_activeClientsOnly_toggled);

    // Connecter les signaux et slots pour la gestion employés
    connect(ui->addEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_addEmployeBtn_clicked);
    connect(ui->deleteEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_deleteEmployeBtn_clicked);
    connect(ui->editEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_editEmployeBtn_clicked);
    connect(ui->searchEmployeLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchEmployeLineEdit_textChanged);
    connect(ui->employeTable, &QTableWidget::itemClicked, this, &MainWindow::on_employeTable_itemClicked);
    connect(ui->clearEmployeFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearEmployeFormBtn_clicked);
    connect(ui->refreshEmployeTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshEmployeTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion projets
    connect(ui->addProjetBtn, &QPushButton::clicked, this, &MainWindow::on_addProjetBtn_clicked);
    connect(ui->deleteProjetBtn, &QPushButton::clicked, this, &MainWindow::on_deleteProjetBtn_clicked);
    connect(ui->editProjetBtn, &QPushButton::clicked, this, &MainWindow::on_editProjetBtn_clicked);
    connect(ui->searchProjetLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchProjetLineEdit_textChanged);
    connect(ui->projetTable, &QTableWidget::itemClicked, this, &MainWindow::on_projetTable_itemClicked);
    connect(ui->clearProjetFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearProjetFormBtn_clicked);
    connect(ui->refreshProjetTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshProjetTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion finances
    connect(ui->addFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_addFinanceBtn_clicked);
    connect(ui->deleteFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_deleteFinanceBtn_clicked);
    connect(ui->editFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_editFinanceBtn_clicked);
    connect(ui->searchFinanceLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchFinanceLineEdit_textChanged);
    connect(ui->financeTable, &QTableWidget::itemClicked, this, &MainWindow::on_financeTable_itemClicked);
    connect(ui->clearFinanceFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearFinanceFormBtn_clicked);
    connect(ui->refreshFinanceTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshFinanceTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion equipement

    connect(ui->addEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_addEquipementBtn_clicked);
    connect(ui->deleteEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_deleteEquipementBtn_clicked);
    connect(ui->editEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_editEquipementBtn_clicked);
    connect(ui->searchEquipementLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchEquipementLineEdit_textChanged);
    connect(ui->equipementTable, &QTableWidget::itemClicked, this, &MainWindow::on_equipementTable_itemClicked);
    connect(ui->clearEquipementFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearEquipementFormBtn_clicked);
    connect(ui->refreshEquipementTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshEquipementTableBtn_clicked);

    // Afficher la page clients par défaut
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}



// ============================================================================
// MÉTHODES DE NAVIGATION
// ============================================================================


void MainWindow::on_clientsBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
    refreshClientTable();
}

void MainWindow::on_employesBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(1);
    refreshEmployeTable();
}

void MainWindow::on_projetsBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    refreshProjetTable();
}

void MainWindow::on_financesBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(3);
    refreshFinanceTable();
}


// ============================================================================
// GESTION CLIENTS
// ============================================================================

void MainWindow::updateClientStats()
{
    QSqlQuery query;
    int totalClients = 0;
    int activeClients = 0;
    int newThisMonth = 0;

    // Calculs des données de base
    query.exec("SELECT COUNT(*) FROM client");
    if (query.next()) {
        totalClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) {
        activeClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE MONTH(date_ajout) = MONTH(CURRENT_DATE) AND YEAR(date_ajout) = YEAR(CURRENT_DATE)");
    if (query.next()) {
        newThisMonth = query.value(0).toInt();
    }

    // Calculs des pourcentages
    double activePercentage = 0.0;
    double monthlyGrowthPercentage = 0.0;

    if (totalClients > 0) {
        activePercentage = (activeClients * 100.0) / totalClients;
        monthlyGrowthPercentage = (newThisMonth * 100.0) / totalClients;
    }

    // Formatage des textes avec pourcentages
    ui->totalClientsLabel->setText(QString::number(totalClients));

    QString activeText = QString("%1\n%2% Actifs")
                             .arg(activeClients)
                             .arg(activePercentage, 0, 'f', 1);
    ui->activeClientsLabel->setText(activeText);

    QString monthlyText = QString("%1\n%2% Ce mois")
                              .arg(newThisMonth)
                              .arg(monthlyGrowthPercentage, 0, 'f', 1);
    ui->newThisMonthLabel->setText(monthlyText);

    // Indicateur de performance
    QString performanceText;
    if (activePercentage >= 80.0 && monthlyGrowthPercentage >= 10.0) {
        performanceText = "🚀 Excellente performance";
    } else if (activePercentage >= 60.0 && monthlyGrowthPercentage >= 5.0) {
        performanceText = "📈 Bonne performance";
    } else if (activePercentage >= 40.0) {
        performanceText = "📊 Performance stable";
    } else {
        performanceText = "⚠️ Amélioration nécessaire";
    }

    statusBar()->showMessage(performanceText);
}




void MainWindow::clearClientForm()
{
    ui->clientNameEdit->clear();
    ui->clientEmailEdit->clear();
    ui->clientPhoneEdit->clear();
    currentClientId = -1;
    ui->addClientBtn->setEnabled(true);
    ui->editClientBtn->setEnabled(false);
    ui->selectedClientIdLabel->setText("Aucun");
}

bool MainWindow::validateClientForm()
{
    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    // Vérification des champs vides avec messages spécifiques
    if(nomPrenom.isEmpty()) {
        showValidationError("Le nom et prénom sont obligatoires");
        ui->clientNameEdit->setFocus();
        return false;
    }

    if(email.isEmpty()) {
        showValidationError("L'adresse email est obligatoire");
        ui->clientEmailEdit->setFocus();
        return false;
    }

    if(telephone.isEmpty()) {
        showValidationError("Le numéro de téléphone est obligatoire");
        ui->clientPhoneEdit->setFocus();
        return false;
    }

    // Validation du nom/prénom
    if(!Client::validerNomPrenom(nomPrenom)) {
        showValidationError("Le nom doit contenir uniquement des lettres, espaces, apostrophes ou tirets, et avoir au moins 2 caractères");
        ui->clientNameEdit->setFocus();
        return false;
    }

    // Validation de l'email
    if(!Client::validerEmail(email)) {
        showValidationError("L'adresse email n'est pas valide (exemple: utilisateur@domaine.com)");
        ui->clientEmailEdit->setFocus();
        return false;
    }

    // Validation du téléphone
    if(!Client::validerTelephone(telephone)) {
        showValidationError("Le numéro de téléphone n'est pas valide (format français: 0X XX XX XX XX)");
        ui->clientPhoneEdit->setFocus();
        return false;
    }

    qDebug() << "✅ Formulaire client validé avec succès";
    return true;
}


void MainWindow::on_addClientBtn_clicked()
{
    qDebug() << "=== TENTATIVE AJOUT CLIENT ===";

    if(!validateClientForm()) {
        return;
    }

    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    // Générer un ID unique
    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    QSqlQuery query;

    // SOLUTION: Utiliser SYSDATE pour Oracle et le bon nom de colonne STATUT
    query.prepare("INSERT INTO client (ID, NOM_PRENOM, EMAIL, TELEPHONE, DATE_AJOUT, STATUT) "
                  "VALUES (:id, :nom_prenom, :email, :telephone, SYSDATE, :statut)");

    query.bindValue(":id", id);
    query.bindValue(":nom_prenom", nomPrenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":statut", "Actif");

    if(query.exec()) {
        qDebug() << "✅ Client ajouté avec ID:" << id;
        QMessageBox::information(this, "Succès", "Client ajouté avec succès");
        refreshClientTable();
        clearClientForm();
    } else {
        QString error = query.lastError().text();
        qDebug() << "❌ Erreur SQL:" << error;
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout:\n" + error);
    }
}

void MainWindow::on_deleteClientBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->clientTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client à supprimer");
        return;
    }

    int row = ui->clientTable->currentRow();
    int id = ui->clientTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce client?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Client client;
        bool test = client.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Client supprimé avec succès");
            refreshClientTable();  // Mise à jour des stats
            clearClientForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du client");
        }
    }
}

void MainWindow::on_editClientBtn_clicked()
{
    if(currentClientId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client à modifier");
        return;
    }

    if(!validateClientForm()) {
        return;
    }

    // Récupération des données
    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    Client client;
    bool test = client.modifier(currentClientId, nomPrenom, email, telephone);

    if(test) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès");
        refreshClientTable();  // Mise à jour des stats
        clearClientForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client. Vérifiez que les données sont valides.");
    }
}



void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshClientTable();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, nom_prenom, email, telephone, date_ajout, statut FROM client "
                  "WHERE nom_prenom LIKE :search OR email LIKE :search OR telephone LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->clientTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->clientTable->insertRow(row);
            ui->clientTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->clientTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->clientTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->clientTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->clientTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->clientTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            row++;
        }
    }
}

void MainWindow::on_clientTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int row = item->row();

    // Récupérer les informations du client (EXISTANT)
    currentClientId = ui->clientTable->item(row, 0)->text().toInt();
    QString nomPrenom = ui->clientTable->item(row, 1)->text();

    // Mettre à jour le label (EXISTANT)
    ui->selectedClientIdLabel->setText(QString::number(currentClientId));

    // Activer le bouton modifier (EXISTANT)
    ui->editClientBtn->setEnabled(true);

    // ACTIVER LE BOUTON ENVOYER EMAIL (NOUVEAU)
    QPushButton *envoyerEmailBtn = findChild<QPushButton*>("envoyerEmailClientBtn");
    if (envoyerEmailBtn) {
        envoyerEmailBtn->setEnabled(true);
    }
    mettreAJourBoutonStatut();
}


void MainWindow::envoyerEmailClient(const QString &nomPrenom, const QString &email)
{
    // Vérifier que l'email est valide
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide",
                             QString("L'email de %1 n'est pas valide:\n%2").arg(nomPrenom).arg(email));
        return;
    }

    // Demander confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirmation d'envoi",
        QString("Voulez-vous envoyer un email RÉEL à :\n\n"
                "👤 %1\n"
                "📧 %2\n\n"
                "Cet email sera envoyé via EmailJS.").arg(nomPrenom).arg(email),  // ← CORRIGÉ
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        // Générer le sujet et message
        QString prenom = nomPrenom.split(" ").first();
        QString sujet = QString("Smart Studio - Offre spéciale pour %1").arg(prenom);
        QString message = genererMessageReel(prenom);

        qDebug() << "🚀 ENVOI RÉEL EmailJS demandé pour:" << email;

        // Envoyer l'email RÉEL via EmailJS  // ← CORRIGÉ
        QVector<QString> destinataires = {email};
        emailManager->envoyerEmailMultiple(destinataires, sujet, message);

        QMessageBox::information(this, "Envoi démarré",
                                 QString("L'email a été envoyé à :\n\n"
                                         "👤 %1\n"
                                         "📧 %2\n\n"
                                         "Vous recevrez une confirmation quand l'envoi sera terminé.").arg(nomPrenom).arg(email));
    }
}

void MainWindow::on_clearFormBtn_clicked()
{
    clearClientForm();
}

void MainWindow::on_refreshTableBtn_clicked()
{
    refreshClientTable();
}

void MainWindow::on_exportPdfBtn_clicked()
{
    // Vérifier s'il y a des clients à exporter
    QSqlQuery countQuery("SELECT COUNT(*) FROM client");
    if (countQuery.next() && countQuery.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Export PDF", "Aucun client à exporter.");
        return;
    }

    // Demander où sauvegarder le fichier
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Exporter les clients en PDF",
        QDir::homePath() + "/clients_smart_studio.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty()) {
        return;
    }

    // Vérifier l'extension .pdf
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) {
        fileName += ".pdf";
    }

    // Exporter en PDF
    PdfExporter exporter;
    bool success = exporter.exportClientsToPdf(fileName);

    if (success) {
        QMessageBox::information(this, "Export PDF",
                                 "✅ Export réussi!\nFichier sauvegardé: " + fileName);
    } else {
        QMessageBox::critical(this, "Export PDF",
                              "❌ Erreur lors de l'export PDF.");
    }
}



void MainWindow::on_activeClientsOnly_toggled(bool checked)
{
    refreshClientTable();
}

// ============================================================================
// GESTION EMPLOYÉS
// ============================================================================

void MainWindow::refreshEmployeTable()
{
    Employe e;
    QSqlQueryModel *model = e.afficher();

    if (model) {
        // Vider le tableau existant
        ui->employeTable->setRowCount(0);

        // Définir les en-têtes de colonnes
        QStringList headers;
        headers << "ID" << "Nom" << "Prénom" << "Email" << "Téléphone"
                << "Poste" << "Salaire" << "Date Embauche" << "Statut";
        ui->employeTable->setColumnCount(headers.size());
        ui->employeTable->setHorizontalHeaderLabels(headers);

        // Remplir le tableau avec les données
        for (int row = 0; row < model->rowCount(); ++row) {
            ui->employeTable->insertRow(row);

            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->employeTable->setItem(row, col, item);
            }
        }

        // Ajuster la taille des colonnes
        ui->employeTable->resizeColumnsToContents();

        // Libérer la mémoire du modèle
        delete model;
    }
}
void MainWindow::loadEmployees()
{
    refreshEmployeTable();  // Simplement appeler refreshEmployeTable
}

void MainWindow::clearEmployeForm()
{
    ui->employeNameEdit->clear();
    ui->employeEmailEdit->clear();
    ui->employePhoneEdit->clear();
    ui->employePosteEdit->clear();
    ui->employeSalaireEdit->clear();
    currentEmployeId = -1;
    ui->addEmployeBtn->setEnabled(true);
    ui->editEmployeBtn->setEnabled(false);
    ui->selectedEmployeIdLabel->setText("Aucun");
}

bool MainWindow::validateEmployeForm()
{
    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    QString salaire = ui->employeSalaireEdit->text().trimmed();

    // Vérification des champs vides
    if(nomPrenom.isEmpty() || email.isEmpty() || telephone.isEmpty() || poste.isEmpty() || salaire.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    // Validation du nom/prénom (plus permissif)
    if(nomPrenom.length() < 2) {
        showValidationError("Le nom doit contenir au moins 2 caractères");
        ui->employeNameEdit->setFocus();
        return false;
    }

    // Validation de l'email
    if(!Employe::validerEmail(email)) {
        showValidationError("L'adresse email n'est pas valide (exemple: utilisateur@domaine.com)");
        ui->employeEmailEdit->setFocus();
        return false;
    }

    // Validation du téléphone (plus permissif)
    QString phoneClean = telephone;
    phoneClean = phoneClean.remove(" ").remove(".").remove("-").remove("(").remove(")");

    if(phoneClean.length() < 10 || !phoneClean.startsWith("0")) {
        showValidationError("Le numéro de téléphone doit contenir 10 chiffres et commencer par 0");
        ui->employePhoneEdit->setFocus();
        return false;
    }

    // Validation du salaire
    bool ok;
    double salaireValue = salaire.toDouble(&ok);
    if(!ok || salaireValue <= 0) {
        showValidationError("Le salaire doit être un nombre positif");
        ui->employeSalaireEdit->setFocus();
        return false;
    }

    return true;
}

void MainWindow::on_addEmployeBtn_clicked()
{
    if(!validateEmployeForm()) {
        return;
    }

    // Récupération des données
    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    double salaire = ui->employeSalaireEdit->text().toDouble();

    // Séparation nom/prénom
    QString nom = nomPrenom;
    QString prenom = "";
    if(nomPrenom.contains(" ")) {
        QStringList parts = nomPrenom.split(" ");
        nom = parts[0];
        prenom = parts.mid(1).join(" ");
    }

    // Générer un ID unique
    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    // Créer l'objet Employe avec TOUTES les données
    Employe newEmploye;
    newEmploye.setId(id);
    newEmploye.setNom(nom);
    newEmploye.setPrenom(prenom);
    newEmploye.setEmail(email);
    newEmploye.setTelephone(telephone);
    newEmploye.setRole(poste);  // CHANGEMENT : setPoste → setRole
    newEmploye.setSalaire(salaire);
    newEmploye.setDateEmbauche(QDate::currentDate().toString("yyyy-MM-dd"));
    newEmploye.setHoraire("9h-17h");
    newEmploye.setGenre("Non spécifié");

    bool test = newEmploye.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Employé ajouté avec succès");
        refreshEmployeTable();
        clearEmployeForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé");
    }
}



void MainWindow::on_deleteEmployeBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->employeTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé à supprimer");
        return;
    }

    int row = ui->employeTable->currentRow();
    int id = ui->employeTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet employé?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Employe employe;
        bool test = employe.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Employé supprimé avec succès");
            refreshEmployeTable();
            clearEmployeForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'employé");
        }
    }
}

void MainWindow::on_editEmployeBtn_clicked()
{
    if(currentEmployeId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé à modifier");
        return;
    }

    if(!validateEmployeForm()) {
        return;
    }

    // Récupération des données
    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    double salaire = ui->employeSalaireEdit->text().toDouble();

    Employe employe;
    bool test = employe.modifier(currentEmployeId, nomPrenom.split(" ")[0],
                                 nomPrenom.split(" ").size() > 1 ? nomPrenom.split(" ")[1] : "",
                                 email, telephone, poste,
                                 QDate::currentDate().toString("yyyy-MM-dd"), salaire);

    if(test) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès");
        refreshEmployeTable();
        clearEmployeForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'employé. Vérifiez que les données sont valides.");
    }
}

void MainWindow::on_searchEmployeLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshEmployeTable();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, nom_prenom, email, telephone, poste, salaire, date_embauche, statut FROM employe "
                  "WHERE nom_prenom LIKE :search OR email LIKE :search OR telephone LIKE :search OR poste LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->employeTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->employeTable->insertRow(row);
            ui->employeTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->employeTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->employeTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->employeTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->employeTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->employeTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            ui->employeTable->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
            ui->employeTable->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
            row++;
        }
    }
}

void MainWindow::on_employeTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    currentEmployeId = ui->employeTable->item(row, 0)->text().toInt();
    ui->employeNameEdit->setText(ui->employeTable->item(row, 1)->text());
    ui->employeEmailEdit->setText(ui->employeTable->item(row, 2)->text());
    ui->employePhoneEdit->setText(ui->employeTable->item(row, 3)->text());
    ui->employePosteEdit->setText(ui->employeTable->item(row, 4)->text());
    ui->employeSalaireEdit->setText(ui->employeTable->item(row, 5)->text());
    ui->selectedEmployeIdLabel->setText(QString::number(currentEmployeId));

    // Activer le bouton modifier et désactiver le bouton ajouter
    ui->editEmployeBtn->setEnabled(true);
    ui->addEmployeBtn->setEnabled(false);
}

void MainWindow::on_clearEmployeFormBtn_clicked()
{
    clearEmployeForm();
}

void MainWindow::on_refreshEmployeTableBtn_clicked()
{
    refreshEmployeTable();  // Cette fonction existe déjà, elle appelle maintenant votre nouvelle méthode
}

// ============================================================================
// GESTION PROJETS
// ============================================================================

void MainWindow::refreshProjetTable()
{
    Projet p;
    QSqlQueryModel *model = p.afficher();

    if (model) {
        // Vider le tableau existant
        ui->projetTable->setRowCount(0);

        // Définir les en-têtes de colonnes
        QStringList headers;
        headers << "ID" << "Nom" << "Description" << "Date Début"
                << "Date Fin" << "Budget" << "Statut" << "Chef Projet ID";
        ui->projetTable->setColumnCount(headers.size());
        ui->projetTable->setHorizontalHeaderLabels(headers);

        // Remplir le tableau avec les données
        for (int row = 0; row < model->rowCount(); ++row) {
            ui->projetTable->insertRow(row);

            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->projetTable->setItem(row, col, item);
            }
        }

        // Ajuster la taille des colonnes
        ui->projetTable->resizeColumnsToContents();

        // Libérer la mémoire du modèle
        delete model;
    }
}

void MainWindow::clearProjetForm()
{
    ui->projetNomEdit->clear();
    ui->projetDescriptionEdit->clear();
    ui->projetClientIdEdit->clear();
    ui->projetEmployeIdEdit->clear();
    ui->projetBudgetEdit->clear();
    currentProjetId = -1;
    ui->addProjetBtn->setEnabled(true);
    ui->editProjetBtn->setEnabled(false);
    ui->selectedProjetIdLabel->setText("Aucun");
}

bool MainWindow::validateProjetForm()
{
    QString nom = ui->projetNomEdit->text().trimmed();
    QString description = ui->projetDescriptionEdit->text().trimmed();
    QString clientId = ui->projetClientIdEdit->text().trimmed();
    QString employeId = ui->projetEmployeIdEdit->text().trimmed();
    QString budget = ui->projetBudgetEdit->text().trimmed();

    // Vérification des champs vides
    if(nom.isEmpty() || description.isEmpty() || clientId.isEmpty() || employeId.isEmpty() || budget.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    // Validation des IDs
    bool clientOk, employeOk;
    int clientIdValue = clientId.toInt(&clientOk);
    int employeIdValue = employeId.toInt(&employeOk);

    if(!clientOk || clientIdValue <= 0) {
        showValidationError("L'ID client doit être un nombre positif");
        ui->projetClientIdEdit->setFocus();
        return false;
    }

    if(!employeOk || employeIdValue <= 0) {
        showValidationError("L'ID employé doit être un nombre positif");
        ui->projetEmployeIdEdit->setFocus();
        return false;
    }

    // Validation du budget
    bool budgetOk;
    double budgetValue = budget.toDouble(&budgetOk);
    if(!budgetOk || budgetValue <= 0) {
        showValidationError("Le budget doit être un nombre positif");
        ui->projetBudgetEdit->setFocus();
        return false;
    }

    return true;
}

void MainWindow::on_addProjetBtn_clicked()
{
    if(!validateProjetForm()) {
        return;
    }

    // Récupération des données
    QString nom = ui->projetNomEdit->text().trimmed();
    QString description = ui->projetDescriptionEdit->text().trimmed();
    int clientId = ui->projetClientIdEdit->text().toInt();
    int employeId = ui->projetEmployeIdEdit->text().toInt();
    double budget = ui->projetBudgetEdit->text().toDouble();

    // Générer un ID unique
    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    Projet newProjet;
    newProjet.setId(id);
    newProjet.setNom(nom);
    newProjet.setDescription(description);
    newProjet.setClient(QString::number(clientId));
    newProjet.setBudget(budget);

    bool test = newProjet.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Projet ajouté avec succès");
        refreshProjetTable();
        clearProjetForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du projet. Vérifiez que les données sont valides.");
    }
}

void MainWindow::on_deleteProjetBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->projetTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un projet à supprimer");
        return;
    }

    int row = ui->projetTable->currentRow();
    int id = ui->projetTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer ce projet?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Projet projet;
        bool test = projet.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Projet supprimé avec succès");
            refreshProjetTable();
            clearProjetForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression du projet");
        }
    }
}

void MainWindow::on_editProjetBtn_clicked()
{
    if(currentProjetId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un projet à modifier");
        return;
    }

    if(!validateProjetForm()) {
        return;
    }

    // Récupération des données
    QString nom = ui->projetNomEdit->text().trimmed();
    QString description = ui->projetDescriptionEdit->text().trimmed();
    int clientId = ui->projetClientIdEdit->text().toInt();
    int employeId = ui->projetEmployeIdEdit->text().toInt();
    double budget = ui->projetBudgetEdit->text().toDouble();

    Projet projet;
    projet.setId(currentProjetId);
    projet.setNom(nom);
    projet.setDescription(description);
    projet.setClient(QString::number(clientId));
    projet.setBudget(budget);

    bool test = projet.modifier(currentProjetId, nom, description, QString::number(clientId),
                                QDate::currentDate().toString("yyyy-MM-dd"),
                                QDate::currentDate().addDays(30).toString("yyyy-MM-dd"),
                                budget, "En cours");

    if(test) {
        QMessageBox::information(this, "Succès", "Projet modifié avec succès");
        refreshProjetTable();
        clearProjetForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du projet. Vérifiez que les données sont valides.");
    }
}

void MainWindow::on_searchProjetLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshProjetTable();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, nom, description, client_id, employe_id, date_debut, date_fin, budget, statut FROM projet "
                  "WHERE nom LIKE :search OR description LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->projetTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->projetTable->insertRow(row);
            ui->projetTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->projetTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->projetTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->projetTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->projetTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->projetTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            ui->projetTable->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
            ui->projetTable->setItem(row, 7, new QTableWidgetItem(query.value(7).toString()));
            ui->projetTable->setItem(row, 8, new QTableWidgetItem(query.value(8).toString()));
            row++;
        }
    }
}

void MainWindow::on_projetTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    currentProjetId = ui->projetTable->item(row, 0)->text().toInt();
    ui->projetNomEdit->setText(ui->projetTable->item(row, 1)->text());
    ui->projetDescriptionEdit->setText(ui->projetTable->item(row, 2)->text());
    ui->projetClientIdEdit->setText(ui->projetTable->item(row, 3)->text());
    ui->projetEmployeIdEdit->setText(ui->projetTable->item(row, 4)->text());
    ui->projetBudgetEdit->setText(ui->projetTable->item(row, 7)->text());
    ui->selectedProjetIdLabel->setText(QString::number(currentProjetId));

    // Activer le bouton modifier et désactiver le bouton ajouter
    ui->editProjetBtn->setEnabled(true);
    ui->addProjetBtn->setEnabled(false);
}

void MainWindow::on_clearProjetFormBtn_clicked()
{
    clearProjetForm();
}

void MainWindow::on_refreshProjetTableBtn_clicked()
{
    refreshProjetTable();
}

// ============================================================================
// GESTION FINANCES
// ============================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>
#include <QDate>
#include <QSqlQueryModel>
// Assurez-vous d'inclure les headers des Dialogues et de la classe Finance
#include "alerteretarddialog.h" 
#include "historiquedialog.h"
#include "finance.h" 

// Définition de la variable globale ou membre
// int currentFinanceId = -1; // Doit être déclaré dans mainwindow.h

// =====================================================================
// CONSTRUCTEUR (OÙ LES CONNEXIONS MANUELLES DOIVENT ÊTRE PLACÉES)
// =====================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialisation
    currentFinanceId = -1;
    // Désactiver le bouton modifier au démarrage
    ui->editFinanceBtn->setEnabled(false); 

    // =========================================================
    // CONNEXIONS MANUELLES DE LA BARRE LATÉRALE
    // (Les connexions on_..._clicked sont automatiques par convention)
    // =========================================================

    // Page 0 : Clients
    connect(ui->clientsBtn, &QPushButton::toggled, this, [=](bool checked) {
        if (checked) {
            ui->stackedWidget->setCurrentIndex(0); 
        }
    });

    // Page 1 : Employés
    connect(ui->employesBtn, &QPushButton::toggled, this, [=](bool checked) {
        if (checked) {
            ui->stackedWidget->setCurrentIndex(1); 
        }
    });

    // Page 2 : Projets
    connect(ui->projetsBtn, &QPushButton::toggled, this, [=](bool checked) {
        if (checked) {
            ui->stackedWidget->setCurrentIndex(2); 
        }
    });
    
    // Page 3 : Finances - C'est ici que l'on charge les données au changement de page
    connect(ui->financesBtn, &QPushButton::toggled, this, [=](bool checked) {
        if (checked) {
            ui->stackedWidget->setCurrentIndex(3); 
            refreshFinanceTable(); // Rafraîchir lorsque l'utilisateur arrive sur la page
        }
    });
    
    // ... Ajoutez les connexions pour les autres boutons (equipementsBtn, mailingBtn) ...
}

MainWindow::~MainWindow()
{
    delete ui;
}

// =====================================================================
// FONCTIONS DE GESTION DE LA FENÊTRE PRINCIPALE
// =====================================================================

/**
 * @brief Rafraîchit le QTableWidget des opérations financières.
 * CORRECTION : Utilise 7 colonnes (pour cohérence avec la BDD et la recherche).
 */
void MainWindow::refreshFinanceTable()
{
    qDebug() << "🔄 Rafraîchissement du tableau finances...";

    Finance f;
    // Assurez-vous que f.afficher() retourne les 7 colonnes : ID, Type, Montant, Date, Description, Projet ID, Statut
    QSqlQueryModel *model = f.afficher(); 

    if (model) {
        qDebug() << "Modèle chargé, lignes:" << model->rowCount();

        ui->financeTable->setRowCount(0);

        QStringList headers;
        headers << "ID" << "Type" << "Montant" << "Date" << "Description" << "Projet ID" << "Statut";
        
        ui->financeTable->setColumnCount(headers.size()); 
        ui->financeTable->setHorizontalHeaderLabels(headers);

        for (int row = 0; row < model->rowCount(); ++row) {
            ui->financeTable->insertRow(row);
            // Assurez-vous que le modèle retourne 7 colonnes ou ajustez model->columnCount()
            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->financeTable->setItem(row, col, item);
            }
        }

        ui->financeTable->resizeColumnsToContents();
        // Le modèle est copié par QSqlQueryModel, il est sécuritaire de le supprimer si vous l'avez créé dynamiquement
        // Cependant, si f.afficher() retourne un pointeur, il faut s'assurer qu'il soit bien détruit.
        delete model; 

        qDebug() << "✅ Tableau finances rafraîchi -" << ui->financeTable->rowCount() << "lignes affichées";
    } else {
        qDebug() << "❌ Erreur lors du chargement du modèle. Erreur SQL:" << QSqlDatabase::database().lastError().text();
    }
}

/**
 * @brief Vide le formulaire et réinitialise l'ID de l'opération sélectionnée.
 */
void MainWindow::clearFinanceForm()
{
    ui->financeTypeEdit->clear();
    ui->financeDescriptionEdit->clear();
    ui->financeMontantEdit->clear();
    ui->financeProjetIdEdit->clear();
    ui->selectedFinanceIdLabel->clear();
    currentFinanceId = -1;
    // Réactiver le bouton Ajouter et désactiver le bouton Modifier
    ui->editFinanceBtn->setEnabled(false);
    ui->addFinanceBtn->setEnabled(true);
}

/**
 * @brief Valide les champs du formulaire financier.
 */
bool MainWindow::validateFinanceForm()
{
    QString type = ui->financeTypeEdit->text().trimmed();
    QString montant = ui->financeMontantEdit->text().trimmed();
    QString description = ui->financeDescriptionEdit->text().trimmed();
    QString projetId = ui->financeProjetIdEdit->text().trimmed();

    // Vérification des champs vides
    if(type.isEmpty() || montant.isEmpty() || description.isEmpty() || projetId.isEmpty()) {
        // showValidationError doit être défini dans mainwindow.h
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    // Validation du montant
    bool montantOk;
    double montantValue = montant.toDouble(&montantOk);
    if(!montantOk || montantValue <= 0) {
        showValidationError("Le montant doit être un nombre positif (format 123.45)");
        ui->financeMontantEdit->setFocus();
        return false;
    }

    // Validation de l'ID projet
    bool projetOk;
    int projetIdValue = projetId.toInt(&projetOk);
    if(!projetOk || projetIdValue <= 0) {
        showValidationError("L'ID projet doit être un nombre entier positif");
        ui->financeProjetIdEdit->setFocus();
        return false;
    }

    return true;
}

// =====================================================================
// SLOTS D'ACTIONS (on_..._clicked)
// =====================================================================

/**
 * @brief Ajoute une nouvelle opération financière.
 * CORRECTION : Utilise la fonction validateFinanceForm() complète.
 */
void MainWindow::on_addFinanceBtn_clicked()
{
    // 1. Validation complète
    if (!validateFinanceForm()) {
        return; // La fonction validateFinanceForm() a déjà géré l'affichage de l'erreur
    }

    // 2. Récupérer les données APRES validation
    QString type = ui->financeTypeEdit->text().trimmed();
    QString description = ui->financeDescriptionEdit->text().trimmed();
    double montant = ui->financeMontantEdit->text().toDouble();
    QString projetId = ui->financeProjetIdEdit->text().trimmed();
    
    // 3. Ajouter à la base
    Finance f;
    f.setType(type);
    f.setDescription(description);
    f.setMontant(montant);
    f.setProjet_id(projetId);
    f.setDateOperation(QDate::currentDate().toString("dd/MM/yyyy"));

    if (f.ajouter()) {
        QMessageBox::information(this, "Succès", "Opération financière ajoutée avec succès !");
        refreshFinanceTable();
        clearFinanceForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout: " + QSqlDatabase::database().lastError().text());
    }
}

/**
 * @brief Supprime l'opération financière sélectionnée.
 */
void MainWindow::on_deleteFinanceBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->financeTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une opération financière à supprimer");
        return;
    }

    int row = ui->financeTable->currentRow();
    int id = ui->financeTable->item(row, 0)->text().toInt(); // L'ID est toujours la première colonne

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette opération financière?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Finance finance;
        if(finance.supprimer(id)) {
            QMessageBox::information(this, "Succès", "Opération financière supprimée avec succès");
            refreshFinanceTable();
            clearFinanceForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'opération financière");
        }
    }
}

/**
 * @brief Modifie l'opération financière sélectionnée.
 * CORRECTION : Ajout du projetId à l'appel de finance.modifier().
 */
void MainWindow::on_editFinanceBtn_clicked()
{
    if(currentFinanceId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une opération financière à modifier");
        return;
    }
    
    // Utiliser la validation complète
    if (!validateFinanceForm()) {
        return;
    }

    // Récupération des données après validation
    QString type = ui->financeTypeEdit->text().trimmed();
    QString description = ui->financeDescriptionEdit->text().trimmed();
    double montant = ui->financeMontantEdit->text().toDouble();
    QString projetId = ui->financeProjetIdEdit->text().trimmed(); 
    QString categorie = "Général"; 
    QString dateOperation = QDate::currentDate().toString("dd/MM/yyyy");

    // Utiliser la méthode modifier
    Finance finance;
    // ASSUMPTION : la signature de modifier a été mise à jour dans la classe Finance
    bool test = finance.modifier(currentFinanceId, type, description, montant,
                                 dateOperation, categorie, projetId); 

    if(test) {
        QMessageBox::information(this, "Succès", "Opération financière modifiée avec succès");
        refreshFinanceTable();
        clearFinanceForm();
        currentFinanceId = -1;

        ui->editFinanceBtn->setEnabled(false);
        ui->addFinanceBtn->setEnabled(true);

        qDebug() << "✅ Modification réussie";
    } else {
        QString error = QSqlDatabase::database().lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la modification: " + error);
        qDebug() << "❌ Erreur modification:" << error;
    }
}

/**
 * @brief Recherche les opérations financières.
 */
void MainWindow::on_searchFinanceLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshFinanceTable();
        return;
    }

    QSqlQuery query;
    // La requête doit retourner 7 colonnes pour correspondre au QTableWidget
    query.prepare("SELECT id, type, montant, date_operation, description, projet_id, statut FROM finance "
                  "WHERE type LIKE :search OR description LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->financeTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->financeTable->insertRow(row);
            // CORRECTION: Attention à l'ordre des colonnes ici : la description et la date ont été inversées
            // Si la requête est: SELECT id, type, montant, date_operation, description, projet_id, statut
            ui->financeTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // ID
            ui->financeTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Type
            ui->financeTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Montant
            ui->financeTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString())); // Date
            ui->financeTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // Description
            ui->financeTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // Projet ID
            ui->financeTable->setItem(row, 6, new QTableWidgetItem(query.value(6).toString())); // Statut
            row++;
        }
    }
}

/**
 * @brief Charge les données de l'opération sélectionnée dans le formulaire.
 */
void MainWindow::on_financeTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    currentFinanceId = ui->financeTable->item(row, 0)->text().toInt();
    
    // Le mapping des colonnes doit correspondre aux en-têtes et à l'ordre affiché dans la table
    ui->financeTypeEdit->setText(ui->financeTable->item(row, 1)->text()); 
    ui->financeMontantEdit->setText(ui->financeTable->item(row, 2)->text());
    // Note: La date est en colonne 3, la description en 4.
    ui->financeDescriptionEdit->setText(ui->financeTable->item(row, 4)->text()); 
    ui->financeProjetIdEdit->setText(ui->financeTable->item(row, 5)->text());
    
    ui->selectedFinanceIdLabel->setText(QString::number(currentFinanceId));

    // Activer le bouton modifier et désactiver le bouton ajouter
    ui->editFinanceBtn->setEnabled(true);
    ui->addFinanceBtn->setEnabled(false);
}

/**
 * @brief Vide le formulaire financier.
 */
void MainWindow::on_clearFinanceFormBtn_clicked()
{
    clearFinanceForm();
}

/**
 * @brief Rafraîchit le tableau financier.
 */
void MainWindow::on_refreshFinanceTableBtn_clicked()
{
    refreshFinanceTable();
}

/**
 * @brief Ouvre la boîte de dialogue des alertes de retard.
 */
void MainWindow::on_actionAlerteRetard_triggered()
{
    AlerteRetardDialog *alerteDialog = new AlerteRetardDialog(this);
    alerteDialog->exec();    
}

/**
 * @brief Ouvre la boîte de dialogue de l'historique.
 */
void MainWindow::on_actionHistorique_triggered()
{
    HistoriqueDialog *historiqueDialog = new HistoriqueDialog(this);
    historiqueDialog->exec();
}
// ============================================================================
// GESTION equipement
// ============================================================================

void MainWindow::on_equipementsBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(4); // 4 pour la page équipements
    refreshEquipementTable();
}

void MainWindow::refreshEquipementTable()
{
    Equipement e;
    QSqlQueryModel *model = e.afficher();

    if (model) {
        ui->equipementTable->setRowCount(0);

        QStringList headers;
        headers << "ID" << "Nom" << "Type" << "État" << "Prix (€)" << "Date d'ajout";
        ui->equipementTable->setColumnCount(headers.size());
        ui->equipementTable->setHorizontalHeaderLabels(headers);

        for (int row = 0; row < model->rowCount(); ++row) {
            ui->equipementTable->insertRow(row);
            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->equipementTable->setItem(row, col, item);
            }
        }

        ui->equipementTable->resizeColumnsToContents();
        delete model;
    }
}

void MainWindow::clearEquipementForm()
{
    ui->equipementNomEdit->clear();
    ui->equipementTypeEdit->clear();
    ui->equipementEtatEdit->clear();
    ui->equipementPrixEdit->clear();
    currentEquipementId = -1;
    ui->addEquipementBtn->setEnabled(true);
    ui->editEquipementBtn->setEnabled(false);
    ui->selectedEquipementIdLabel->setText("Aucun");
}

bool MainWindow::validateEquipementForm()
{
    QString nom = ui->equipementNomEdit->text().trimmed();
    QString type = ui->equipementTypeEdit->text().trimmed();
    QString etat = ui->equipementEtatEdit->text().trimmed();
    QString prix = ui->equipementPrixEdit->text().trimmed();

    if(nom.isEmpty() || type.isEmpty() || etat.isEmpty() || prix.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    if(!Equipement::validerNom(nom)) {
        showValidationError("Le nom doit contenir au moins 2 caractères");
        ui->equipementNomEdit->setFocus();
        return false;
    }

    bool prixOk;
    double prixValue = prix.toDouble(&prixOk);
    if(!prixOk || prixValue < 0) {
        showValidationError("Le prix doit être un nombre positif");
        ui->equipementPrixEdit->setFocus();
        return false;
    }

    return true;
}

void MainWindow::on_addEquipementBtn_clicked()
{
    if(!validateEquipementForm()) {
        return;
    }

    QString nom = ui->equipementNomEdit->text().trimmed();
    QString type = ui->equipementTypeEdit->text().trimmed();
    QString etat = ui->equipementEtatEdit->text().trimmed();
    double prix = ui->equipementPrixEdit->text().toDouble();

    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    Equipement newEquipement(id, nom, type, etat, prix);
    bool test = newEquipement.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Équipement ajouté avec succès");
        refreshEquipementTable();
        clearEquipementForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'équipement");
    }
}

void MainWindow::on_deleteEquipementBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->equipementTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un équipement à supprimer");
        return;
    }

    int row = ui->equipementTable->currentRow();
    int id = ui->equipementTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cet équipement?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Equipement equipement;
        bool test = equipement.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Équipement supprimé avec succès");
            refreshEquipementTable();
            clearEquipementForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'équipement");
        }
    }
}

void MainWindow::on_editEquipementBtn_clicked()
{
    if(currentEquipementId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un équipement à modifier");
        return;
    }

    if(!validateEquipementForm()) {
        return;
    }

    QString nom = ui->equipementNomEdit->text().trimmed();
    QString type = ui->equipementTypeEdit->text().trimmed();
    QString etat = ui->equipementEtatEdit->text().trimmed();
    double prix = ui->equipementPrixEdit->text().toDouble();

    Equipement equipement;
    bool test = equipement.modifier(currentEquipementId, nom, type, etat, prix);

    if(test) {
        QMessageBox::information(this, "Succès", "Équipement modifié avec succès");
        refreshEquipementTable();
        clearEquipementForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'équipement");
    }
}

void MainWindow::on_searchEquipementLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshEquipementTable();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, nom, type, etat, prix, date_ajout FROM equipement "
                  "WHERE nom LIKE :search OR type LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->equipementTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->equipementTable->insertRow(row);
            ui->equipementTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->equipementTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->equipementTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->equipementTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->equipementTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->equipementTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            row++;
        }
    }
}

void MainWindow::on_equipementTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    currentEquipementId = ui->equipementTable->item(row, 0)->text().toInt();
    ui->equipementNomEdit->setText(ui->equipementTable->item(row, 1)->text());
    ui->equipementTypeEdit->setText(ui->equipementTable->item(row, 2)->text());
    ui->equipementEtatEdit->setText(ui->equipementTable->item(row, 3)->text());
    ui->equipementPrixEdit->setText(ui->equipementTable->item(row, 4)->text());
    ui->selectedEquipementIdLabel->setText(QString::number(currentEquipementId));

    ui->editEquipementBtn->setEnabled(true);
    ui->addEquipementBtn->setEnabled(false);
}

void MainWindow::on_clearEquipementFormBtn_clicked()
{
    clearEquipementForm();
}

void MainWindow::on_refreshEquipementTableBtn_clicked()
{
    refreshEquipementTable();
}


// ============================================================================
// MÉTHODES UTILITAIRES
// ============================================================================

void MainWindow::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Erreur de validation", message);
}
// ============================================================================
// MAILING
// ============================================================================




// Initialisation du module mailing
void MainWindow::initialiserInterfaceMailing()
{
    // Configuration de la table mailing
    QStringList headers = {"ID", "Sujet", "Destinataires", "Date Création", "Date Envoi", "Statut", "Ouverts", "Clics"};
    ui->mailingTable->setColumnCount(headers.size());
    ui->mailingTable->setHorizontalHeaderLabels(headers);

    // Connexions pour EmailJSManager - CORRECTION ICI
    connect(emailManager, &EmailSMTPManager::emailEnvoye,
            this, &MainWindow::onEmailEnvoye);
    connect(emailManager, &EmailSMTPManager::progressionEnvoi,
            this, &MainWindow::onProgression);
    connect(emailManager, &EmailSMTPManager::envoiTermine,
            this, &MainWindow::onEnvoiTermine);
    connect(emailManager, &EmailSMTPManager::erreur,
            this, &MainWindow::onErreurEmail);

    // Remplir la table avec des données d'exemple
    refreshMailingTable();

    qDebug() << "✅ Interface mailing initialisée avec EmailJS";
}

QString MainWindow::corrigerEmail(const QString &email)
{
    return email.trimmed().toLower();
}



// Slots pour les signaux d'EmailManager
void MainWindow::onEmailEnvoye(const QString& email, bool succes, const QString& details)
{
    QString statut = succes ? "✓ Succès" : "✗ Échec";
    qDebug() << "Email à" << email << ":" << statut << "-" << details;

    // Mettre à jour le statut dans la barre de statut
    if (succes) {
        statusBar()->showMessage(QString("Email envoyé à %1").arg(email), 3000);
    } else {
        statusBar()->showMessage(QString("Échec envoi à %1: %2").arg(email).arg(details), 5000);
    }
}

void MainWindow::onProgressionEnvoi(int valeur, int maximum)
{
    qDebug() << "Progression:" << valeur << "/" << maximum;

    // Vous pourriez mettre à jour une barre de progression ici
    // progressBar->setValue(valeur);
    // progressBar->setMaximum(maximum);
}

void MainWindow::onEnvoiTermine()
{
    QMessageBox::information(this, "Succès", "Campagne d'emails terminée avec succès !");

    // Réactiver le bouton
    ui->sendMailingBtn->setEnabled(true);
    ui->sendMailingBtn->setText("📧 Envoyer Campagne");

    // Réinitialiser le formulaire
    ui->mailingSujetEdit->clear();
    ui->mailingMessageEdit->clear();
}

void MainWindow::onErreurEmail(const QString &message)
{
    qDebug() << "❌ Erreur EmailJS:" << message;

    // Message d'erreur plus informatif
    QString messageDetaille = "Erreur lors de l'envoi d'email:\n\n" + message;

    // Si c'est une erreur réseau, donner plus de détails
    if (message.contains("réseau", Qt::CaseInsensitive) || message.contains("network", Qt::CaseInsensitive)) {
        messageDetaille += "\n\nVérifiez votre connexion internet et les paramètres EmailJS.";
    }

    QMessageBox::critical(this, "Erreur d'envoi EmailJS", messageDetaille);

    // Réactiver le bouton
    ui->sendMailingBtn->setEnabled(true);
    ui->sendMailingBtn->setText("📧 Envoyer Campagne");
}


void MainWindow::on_mailingBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->mailingPage);
    refreshMailingTable();
}

void MainWindow::on_addMailingBtn_clicked()
{
    if (!validateMailingForm()) {
        return;
    }

    QString sujet = ui->mailingSujetEdit->text();
    QString message = ui->mailingMessageEdit->toPlainText();

    // Logique pour créer une campagne (à implémenter selon votre base de données)
    QMessageBox::information(this, "Succès", "Campagne créée avec succès!");
    refreshMailingTable();
    clearMailingForm();
}

void MainWindow::on_sendMailingBtn_clicked()
{
    QString sujet = ui->mailingSujetEdit->text();
    QString message = ui->mailingMessageEdit->toPlainText();

    if (sujet.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le sujet et le message.");
        return;
    }

    QVector<QString> destinataires = obtenirDestinataires();

    if (destinataires.isEmpty()) {
        QMessageBox::information(this, "Information", "Aucun destinataire trouvé.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation",
        QString("Envoyer cet email à %1 destinataires?").arg(destinataires.size()),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        emailManager->envoyerEmailMultiple(destinataires, sujet, message);
        QMessageBox::information(this, "Envoi démarré", "L'envoi a commencé. Surveillez la progression.");
    }
}

void MainWindow::on_sendTestMailBtn_clicked()
{
    QString sujet = ui->mailingSujetEdit->text() + " [TEST]";
    QString message = ui->mailingMessageEdit->toPlainText();

    if (sujet.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le sujet et le message.");
        return;
    }

    // Envoyer un test à votre propre email - REMPLACEZ par votre vrai email
    QVector<QString> testDestinataires = {"oussamazayane2005@gmail.com"}; // ← REMPLACEZ par votre email
    emailManager->envoyerEmailMultiple(testDestinataires, sujet, message);

    QMessageBox::information(this, "Test envoyé",
                             "Email de test envoyé à oussamazayane2005@gmail.com!\n\nVérifiez votre boîte de réception.");
}

void MainWindow::clearMailingForm()
{
    ui->mailingSujetEdit->clear();
    ui->mailingMessageEdit->clear();
    ui->selectedMailingIdLabel->setText("Aucun");
    currentMailingId = -1;
}

// ============================================================================
// IMPLÉMENTATIONS MANQUANTES POUR LE MAILING
// ============================================================================

void MainWindow::on_editMailingBtn_clicked()
{
    if (currentMailingId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une campagne à modifier.");
        return;
    }

    QString sujet = ui->mailingSujetEdit->text();
    QString message = ui->mailingMessageEdit->toPlainText();

    if (sujet.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir le sujet et le message.");
        return;
    }

    // Ici vous devriez mettre à jour la campagne dans la base de données
    // Pour l'instant, on simule juste la modification
    QMessageBox::information(this, "Succès", "Campagne modifiée avec succès!");
    refreshMailingTable();
}

void MainWindow::on_searchMailingLineEdit_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        refreshMailingTable();
        return;
    }

    // Filtrage simple de la table
    for (int i = 0; i < ui->mailingTable->rowCount(); ++i) {
        bool match = false;
        for (int j = 0; j < ui->mailingTable->columnCount(); ++j) {
            QTableWidgetItem *item = ui->mailingTable->item(i, j);
            if (item && item->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->mailingTable->setRowHidden(i, !match);
    }
}

void MainWindow::on_mailingTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int row = item->row();
    currentMailingId = ui->mailingTable->item(row, 0)->text().toInt();

    // Mettre à jour le label
    ui->selectedMailingIdLabel->setText(QString::number(currentMailingId));

    // Remplir le formulaire avec les données de la ligne sélectionnée
    QString sujet = ui->mailingTable->item(row, 1)->text();
    QString message = "Ceci est un exemple de message pour la campagne: " + sujet;

    ui->mailingSujetEdit->setText(sujet);
    ui->mailingMessageEdit->setText(message);

    // Activer le bouton modifier
    ui->editMailingBtn->setEnabled(true);
}

void MainWindow::on_clearMailingFormBtn_clicked()
{
    clearMailingForm();
}

void MainWindow::on_refreshMailingTableBtn_clicked()
{
    refreshMailingTable();
}

// ============================================================================
// FONCTIONS UTILITAIRES POUR LE MAILING
// ============================================================================

void MainWindow::refreshMailingTable()
{
    ui->mailingTable->setRowCount(0);

    // Données d'exemple - remplacez par vos vraies données
    QVector<QStringList> campagnes = {
        {"1", "Promotion Printemps 2024", "25 clients", "01/03/2024", "02/03/2024", "✅ Envoyé", "20", "5"},
        {"2", "Nouveaux Services", "18 clients", "15/03/2024", "16/03/2024", "✅ Envoyé", "15", "3"},
        {"3", "Offre Spéciale Été", "30 clients", "01/06/2024", "", "⏳ Planifié", "0", "0"},
        {"4", "Newsletter Avril", "22 clients", "01/04/2024", "01/04/2024", "✅ Envoyé", "18", "4"}
    };

    for (const QStringList &campagne : campagnes) {
        int row = ui->mailingTable->rowCount();
        ui->mailingTable->insertRow(row);

        for (int col = 0; col < campagne.size(); ++col) {
            ui->mailingTable->setItem(row, col, new QTableWidgetItem(campagne[col]));
        }
    }

    // Ajuster la largeur des colonnes
    ui->mailingTable->resizeColumnsToContents();
}


bool MainWindow::validateMailingForm()
{
    if (ui->mailingSujetEdit->text().isEmpty()) {
        showValidationError("Le sujet est obligatoire");
        ui->mailingSujetEdit->setFocus();
        return false;
    }

    if (ui->mailingMessageEdit->toPlainText().isEmpty()) {
        showValidationError("Le message est obligatoire");
        ui->mailingMessageEdit->setFocus();
        return false;
    }

    return true;
}

void MainWindow::actualiserStatistiquesMailing()
{
    int totalCampagnes = ui->mailingTable->rowCount();
    int campagnesEnvoyees = 0;
    int totalOuverts = 0;
    int totalClics = 0;

    for (int i = 0; i < totalCampagnes; ++i) {
        QTableWidgetItem *statutItem = ui->mailingTable->item(i, 5);
        QTableWidgetItem *ouvertsItem = ui->mailingTable->item(i, 6);
        QTableWidgetItem *clicsItem = ui->mailingTable->item(i, 7);

        if (statutItem && statutItem->text().contains("Envoyé")) {
            campagnesEnvoyees++;
        }

        if (ouvertsItem) {
            totalOuverts += ouvertsItem->text().toInt();
        }

        if (clicsItem) {
            totalClics += clicsItem->text().toInt();
        }
    }

    qDebug() << "📊 Statistiques mailing:";
    qDebug() << "  Campagnes totales:" << totalCampagnes;
    qDebug() << "  Campagnes envoyées:" << campagnesEnvoyees;
    qDebug() << "  Emails ouverts:" << totalOuverts;
    qDebug() << "  Clics:" << totalClics;
}

QVector<QString> MainWindow::obtenirDestinataires()
{
    QVector<QString> emails;

    // Exemple d'emails - remplacez par une requête à votre base de données
    emails << "client1@example.com"
           << "client2@example.com"
           << "client3@example.com"
           << "client4@example.com"
           << "client5@example.com";

    // Pour utiliser votre base de données, décommentez ceci :
    /*
    QSqlQuery query("SELECT email FROM client WHERE statut = 'Actif'");
    while (query.next()) {
        QString email = query.value(0).toString();
        if (validerEmail(email)) {
            emails.append(email);
        }
    }
    */

    qDebug() << "📧 Destinataires trouvés:" << emails.size();
    return emails;
}

bool MainWindow::validerEmail(const QString &email)
{
    QRegularExpression regex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex.match(email).hasMatch();
}

QString MainWindow::genererMessageAutomatique(const QString &nomClient, const QString &typeMessage)
{
    QString message;

    QString prenom = nomClient.split(" ").first();

    if (typeMessage == "promotion") {
        message = QString(
                      "<!DOCTYPE html>"
                      "<html>"
                      "<head>"
                      "<style>"
                      "body { font-family: Arial, sans-serif; color: #333; line-height: 1.6; }"
                      ".header { background-color: #3498DB; color: white; padding: 20px; text-align: center; }"
                      ".content { padding: 20px; }"
                      ".footer { background-color: #F8F9FA; padding: 15px; text-align: center; color: #666; font-size: 12px; }"
                      ".button { background-color: #E74C3C; color: white; padding: 12px 24px; text-decoration: none; border-radius: 5px; display: inline-block; margin: 10px 0; }"
                      "</style>"
                      "</head>"
                      "<body>"
                      "<div class='header'>"
                      "<h1>🎬 Smart Studio</h1>"
                      "<p>Votre partenaire en création de contenu digital</p>"
                      "</div>"
                      "<div class='content'>"
                      "<h2>Bonjour %1,</h2>"
                      "<p>Nous espérons que vous passez une excellente journée !</p>"
                      "<p>Nous sommes ravis de vous proposer une <strong>offre exclusive</strong> pour vos prochains projets de création de contenu :</p>"
                      "<ul>"
                      "<li>📸 <strong>Photographie professionnelle</strong> - Capturer l'essence de votre marque</li>"
                      "<li>🎥 <strong>Vidéos corporate</strong> - Raconter votre histoire</li>"
                      "<li>📱 <strong>Contenu pour réseaux sociaux</strong> - Engager votre audience</li>"
                      "<li>🎨 <strong>Design graphique</strong> - Donner vie à vos idées</li>"
                      "</ul>"
                      "<p>💡 <strong>Offre spéciale : 15%% de réduction sur votre premier projet !</strong></p>"
                      "<p>Prêt à donner vie à vos idées ? Répondez simplement à cet email pour en discuter.</p>"
                      "<p>Cordialement,<br>"
                      "<strong>L'équipe Smart Studio</strong></p>"
                      "</div>"
                      "<div class='footer'>"
                      "<p>Smart Digital Content Creation Studio<br>"
                      "Email: contact@smartstudio.com | Tel: +33 1 23 45 67 89</p>"
                      "<p>© 2024 Smart Studio. Tous droits réservés.</p>"
                      "</div>"
                      "</body>"
                      "</html>"
                      ).arg(prenom);
    } else {
        message = QString(
                      "<!DOCTYPE html>"
                      "<html>"
                      "<head>"
                      "<style>"
                      "body { font-family: Arial, sans-serif; color: #333; line-height: 1.6; }"
                      ".header { background-color: #2C3E50; color: white; padding: 20px; text-align: center; }"
                      ".content { padding: 20px; }"
                      ".footer { background-color: #F8F9FA; padding: 15px; text-align: center; color: #666; font-size: 12px; }"
                      "</style>"
                      "</head>"
                      "<body>"
                      "<div class='header'>"
                      "<h1>🎬 Smart Studio</h1>"
                      "</div>"
                      "<div class='content'>"
                      "<h2>Bonjour %1,</h2>"
                      "<p>Merci de faire confiance à <strong>Smart Studio</strong> pour vos besoins en création de contenu digital.</p>"
                      "<p>Nous sommes toujours à votre disposition pour discuter de vos projets futurs.</p>"
                      "<p>N'hésitez pas à nous contacter si vous avez des questions ou des besoins spécifiques.</p>"
                      "<p>Cordialement,<br>"
                      "<strong>L'équipe Smart Studio</strong></p>"
                      "</div>"
                      "<div class='footer'>"
                      "<p>Smart Digital Content Creation Studio<br>"
                      "Email: contact@smartstudio.com | Tel: +33 1 23 45 67 89</p>"
                      "</div>"
                      "</body>"
                      "</html>"
                      ).arg(prenom);
    }

    return message;
}


QString MainWindow::genererMessageReel(const QString &prenom)
{
    QDate aujourdhui = QDate::currentDate();
    QString dateStr = aujourdhui.toString("dd/MM/yyyy");

    return QString(
               "<!DOCTYPE html>"
               "<html>"
               "<head>"
               "<meta charset='UTF-8'>"
               "<style>"
               "body { font-family: 'Arial', sans-serif; color: #333; line-height: 1.6; max-width: 600px; margin: 0 auto; background: #f4f4f4; }"
               ".container { background: white; border-radius: 10px; overflow: hidden; box-shadow: 0 0 20px rgba(0,0,0,0.1); }"
               ".header { background: linear-gradient(135deg, #3498db, #2c3e50); color: white; padding: 30px; text-align: center; }"
               ".content { padding: 30px; }"
               ".footer { background: #34495e; color: #bdc3c7; padding: 20px; text-align: center; font-size: 12px; }"
               ".offer { background: #e74c3c; color: white; padding: 20px; border-radius: 8px; margin: 20px 0; text-align: center; }"
               ".button { display: inline-block; background: #e74c3c; color: white; padding: 15px 30px; text-decoration: none; border-radius: 5px; font-weight: bold; margin: 15px 0; }"
               ".signature { border-top: 2px solid #3498db; padding-top: 20px; margin-top: 20px; }"
               "</style>"
               "</head>"
               "<body>"
               "<div class='container'>"
               "<div class='header'>"
               "<h1 style='margin:0; font-size: 28px;'>🎬 SMART STUDIO</h1>"
               "<p style='margin:10px 0 0 0; opacity: 0.9;'>Création de Contenu Digital Professionnel</p>"
               "</div>"
               "<div class='content'>"
               "<h2 style='color: #2c3e50;'>Bonjour <strong>%1</strong>,</h2>"
               "<p>Nous espérons que ce message vous trouve en pleine forme !</p>"
               "<div class='offer'>"
               "<h3 style='margin:0; font-size: 22px;'>🚀 OFFRE EXCLUSIVE -20%%</h3>"
               "<p style='margin:10px 0 0 0; font-size: 16px;'>Valable jusqu'au 31 décembre 2024</p>"
               "</div>"
               "<p><strong>Nos services premium :</strong></p>"
               "<ul>"
               "<li>📸 <strong>Photographie Professionnelle</strong> - Shooting produit & corporate</li>"
               "<li>🎥 <strong>Production Vidéo</strong> - Films institutionnels & publicitaires</li>"
               "<li>📱 <strong>Stratégie Réseaux Sociaux</strong> - Contenu engageant & community management</li>"
               "<li>🎨 <strong>Design Graphique</strong> - Identité visuelle & supports print/digital</li>"
               "<li>🌐 <strong>Développement Web</strong> - Sites vitrine & e-commerce</li>"
               "</ul>"
               "<p><strong>Pourquoi nous choisir ?</strong></p>"
               "<ul>"
               "<li>✅ <strong>Équipe expérimentée</strong> - 5 ans d'expertise</li>"
               "<li>✅ <strong>Résultats mesurables</strong> - ROI optimisé</li>"
               "<li>✅ <strong>Accompagnement personnalisé</strong> - Sur-mesure</li>"
               "<li>✅ <strong>Délais garantis</strong> - Respectés à 100%%</li>"
               "</ul>"
               "<div style='text-align: center; margin: 30px 0;'>"
               "<a href='mailto:contact@smartstudio.com?subject=Demande%20de%20devis' class='button'>"
               "📞 DEMANDER UN DEVIS GRATUIT"
               "</a>"
               "</div>"
               "<div class='signature'>"
               "<p><strong>L'équipe Smart Studio</strong><br>"
               "<em>Votre succès est notre motivation</em></p>"
               "</div>"
               "</div>"
               "<div class='footer'>"
               "<p>📧 <a href='mailto:contact@smartstudio.com' style='color: #3498db;'>contact@smartstudio.com</a> | "
               "📱 +33 1 23 45 67 89</p>"
               "<p>📍 123 Avenue de la Création, 75000 Paris</p>"
               "<p><small>Email envoyé le %2 | © 2024 Smart Studio</small></p>"
               "</div>"
               "</div>"
               "</body>"
               "</html>"
               ).arg(prenom).arg(dateStr);
}
void MainWindow::on_envoyerEmailClientBtn_clicked()
{
    if (currentClientId == -1) {
        QMessageBox::warning(this, "Aucun client sélectionné",
                             "Veuillez sélectionner un client dans le tableau.");
        return;
    }

    // Trouver le client sélectionné dans le tableau
    for (int row = 0; row < ui->clientTable->rowCount(); ++row) {
        QTableWidgetItem *idItem = ui->clientTable->item(row, 0);
        if (idItem && idItem->text().toInt() == currentClientId) {
            QString nomPrenom = ui->clientTable->item(row, 1)->text();
            QString email = ui->clientTable->item(row, 2)->text();

            envoyerEmailClient(nomPrenom, email);
            return;
        }
    }

    QMessageBox::warning(this, "Client non trouvé",
                         "Impossible de trouver le client sélectionné dans le tableau.");
}

void MainWindow::onProgression(int pourcentage)
{
    // Simple affichage dans la console et barre de statut
    qDebug() << "📧 Progression envoi emails:" << pourcentage << "%";
    statusBar()->showMessage(QString("Envoi emails: %1%").arg(pourcentage));

    // Pour l'instant, pas de progressBar - on se concentre sur le fonctionnement de base
}

void MainWindow::on_chatbotBtn_clicked()
{
    chatbotDialog->show();
    chatbotDialog->raise();
    chatbotDialog->activateWindow();
}


void MainWindow::mettreAJourStatutVisuel()
{
    for (int row = 0; row < ui->clientTable->rowCount(); ++row) {
        QTableWidgetItem *statutItem = ui->clientTable->item(row, 5);

        if (statutItem) {
            QString statut = statutItem->text();

            if (statut == "Actif") {
                statutItem->setBackground(QColor("#D5F5E3"));
                statutItem->setForeground(QColor("#27AE60"));
                statutItem->setText("● Actif");
                statutItem->setToolTip("Client actif - En relation commerciale");
            } else {
                statutItem->setBackground(QColor("#FDEDEC"));
                statutItem->setForeground(QColor("#E74C3C"));
                statutItem->setText("● Inactif");
                statutItem->setToolTip("Client inactif - Aucune activité récente");
            }

            statutItem->setTextAlignment(Qt::AlignCenter);
            statutItem->setFont(QFont("Arial", 10, QFont::Bold));
        }
    }


    // Activer/désactiver le bouton basculer statut
    QPushButton *toggleBtn = findChild<QPushButton*>("toggleStatutBtn");
    if (toggleBtn) {
        toggleBtn->setEnabled(currentClientId != -1);
    }
}



void MainWindow::creerStatistiquesVisuelles()
{
    // ============================================================================
    // CRÉATION DES STATISTIQUES SIMPLES
    // ============================================================================

    // Widget conteneur principal
    QWidget *statsWidget = new QWidget();
    statsWidget->setObjectName("statsWidget");
    QVBoxLayout *mainStatsLayout = new QVBoxLayout(statsWidget);

    // Titre
    QLabel *titleLabel = new QLabel("📊 STATISTIQUES CLIENTS");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-weight: bold;"
        "    font-size: 16px;"
        "    color: white;"
        "    padding: 12px;"
        "    background-color: #34495E;"
        "    border-radius: 8px;"
        "    text-align: center;"
        "}"
        );
    mainStatsLayout->addWidget(titleLabel);

    // Widget pour les indicateurs circulaires visuels
    QWidget *circleWidget = new QWidget();
    QHBoxLayout *circleLayout = new QHBoxLayout(circleWidget);

    // Style pour les cercles
    QString circleStyle =
        "QLabel {"
        "    background: qradialgradient("
        "        cx: 0.5, cy: 0.5, radius: 0.9,"
        "        fx: 0.5, fy: 0.5,"
        "        stop: 0 %1,"
        "        stop: 1 %2"
        "    );"
        "    border-radius: 60px;"
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    min-width: 120px;"
        "    min-height: 120px;"
        "    max-width: 120px;"
        "    max-height: 120px;"
        "    border: 3px solid %3;"
        "    text-align: center;"
        "}";

    // Cercle pour les clients actifs
    QLabel *circleActifs = new QLabel();
    circleActifs->setObjectName("circleActifs");
    circleActifs->setAlignment(Qt::AlignCenter);
    circleActifs->setStyleSheet(circleStyle.arg("#27AE60").arg("#229954").arg("#27AE60"));
    circleActifs->setText("🟢\nACTIFS\n0\n0%");

    // Cercle pour les clients inactifs
    QLabel *circleInactifs = new QLabel();
    circleInactifs->setObjectName("circleInactifs");
    circleInactifs->setAlignment(Qt::AlignCenter);
    circleInactifs->setStyleSheet(circleStyle.arg("#E74C3C").arg("#C0392B").arg("#E74C3C"));
    circleInactifs->setText("🔴\nINACTIFS\n0\n0%");

    // Cercle pour les nouveaux clients
    QLabel *circleNouveaux = new QLabel();
    circleNouveaux->setObjectName("circleNouveaux");
    circleNouveaux->setAlignment(Qt::AlignCenter);
    circleNouveaux->setStyleSheet(circleStyle.arg("#3498DB").arg("#2980B9").arg("#3498DB"));
    circleNouveaux->setText("🆕\nNOUVEAUX\n0\n0%");

    // Cercle pour le total
    QLabel *circleTotal = new QLabel();
    circleTotal->setObjectName("circleTotal");
    circleTotal->setAlignment(Qt::AlignCenter);
    circleTotal->setStyleSheet(circleStyle.arg("#9B59B6").arg("#8E44AD").arg("#9B59B6"));
    circleTotal->setText("👥\nTOTAL\n0");

    // Ajouter les cercles au layout
    circleLayout->addWidget(circleActifs);
    circleLayout->addWidget(circleInactifs);
    circleLayout->addWidget(circleNouveaux);
    circleLayout->addWidget(circleTotal);
    circleLayout->setSpacing(15);
    circleLayout->setContentsMargins(10, 10, 10, 10);

    mainStatsLayout->addWidget(circleWidget);

    // Widget pour les détails
    QWidget *detailsWidget = new QWidget();
    QHBoxLayout *detailsLayout = new QHBoxLayout(detailsWidget);

    // Style pour les mini-cartes
    QString miniCardStyle =
        "QLabel {"
        "    background-color: %1;"
        "    border-radius: 6px;"
        "    color: white;"
        "    font-weight: bold;"
        "    padding: 8px;"
        "    font-size: 11px;"
        "    min-width: 70px;"
        "    text-align: center;"
        "    border: 1px solid %2;"
        "}";

    // Mini-cartes pour les détails
    QLabel *miniActifs = new QLabel();
    miniActifs->setObjectName("miniActifs");
    miniActifs->setStyleSheet(miniCardStyle.arg("#27AE60").arg("#229954"));
    miniActifs->setText("Actifs\n0");

    QLabel *miniInactifs = new QLabel();
    miniInactifs->setObjectName("miniInactifs");
    miniInactifs->setStyleSheet(miniCardStyle.arg("#E74C3C").arg("#C0392B"));
    miniInactifs->setText("Inactifs\n0");

    QLabel *miniNouveaux = new QLabel();
    miniNouveaux->setObjectName("miniNouveaux");
    miniNouveaux->setStyleSheet(miniCardStyle.arg("#3498DB").arg("#2980B9"));
    miniNouveaux->setText("Nouveaux\n0");

    QLabel *miniTotal = new QLabel();
    miniTotal->setObjectName("miniTotal");
    miniTotal->setStyleSheet(miniCardStyle.arg("#9B59B6").arg("#8E44AD"));
    miniTotal->setText("Total\n0");

    // Ajouter les mini-cartes
    detailsLayout->addWidget(miniActifs);
    detailsLayout->addWidget(miniInactifs);
    detailsLayout->addWidget(miniNouveaux);
    detailsLayout->addWidget(miniTotal);
    detailsLayout->setSpacing(8);

    mainStatsLayout->addWidget(detailsWidget);

    // Ajouter le widget des statistiques à l'interface
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
    if (mainLayout) {
        mainLayout->insertWidget(1, statsWidget);
    }

    qDebug() << "✅ Statistiques créées avec succès";
}

void MainWindow::mettreAJourStatistiquesVisuelles()
{
    QSqlQuery query;
    int totalClients = 0;
    int activeClients = 0;
    int inactiveClients = 0;
    int newThisMonth = 0;

    // Récupérer les données
    query.exec("SELECT COUNT(*) FROM client");
    if (query.next()) {
        totalClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) {
        activeClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE statut != 'Actif' OR statut IS NULL OR statut = ''");
    if (query.next()) {
        inactiveClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE MONTH(date_ajout) = MONTH(CURRENT_DATE) AND YEAR(date_ajout) = YEAR(CURRENT_DATE)");
    if (query.next()) {
        newThisMonth = query.value(0).toInt();
    }

    // Calculer les pourcentages
    double activePercentage = totalClients > 0 ? (activeClients * 100.0) / totalClients : 0;
    double inactivePercentage = totalClients > 0 ? (inactiveClients * 100.0) / totalClients : 0;
    double newPercentage = totalClients > 0 ? (newThisMonth * 100.0) / totalClients : 0;

    // Mettre à jour le diagramme circulaire (texte seulement)
    QLabel *chartLabel = findChild<QLabel*>("chartLabel");
    if (chartLabel) {
        QString performanceColor;
        QString performanceText;

        if (activePercentage >= 70) {
            performanceColor = "#27AE60";
            performanceText = "EXCELLENT";
        } else if (activePercentage >= 50) {
            performanceColor = "#F39C12";
            performanceText = "BON";
        } else {
            performanceColor = "#E74C3C";
            performanceText = "FAIBLE";
        }

        // Mettre à jour le style avec la couleur de performance
        chartLabel->setStyleSheet(
            QString(
                "QLabel {"
                "    background: qradialgradient("
                "        cx: 0.5, cy: 0.5, radius: 0.9,"
                "        fx: 0.5, fy: 0.5,"
                "        stop: 0 %1,"
                "        stop: 1 #2C3E50"
                "    );"
                "    border-radius: 100px;"
                "    border: 3px solid %2;"
                "    font-weight: bold;"
                "    color: white;"
                "}"
                ).arg(performanceColor).arg(performanceColor)
            );

        // Texte du diagramme
        QString chartText = QString(
                                "📊\n"
                                "%1%\n"
                                "ACTIFS\n"
                                "%2"
                                ).arg(activePercentage, 0, 'f', 1).arg(performanceText);

        chartLabel->setText(chartText);
        chartLabel->setToolTip(QString(
                                   "Performance globale:\n"
                                   "• %1% clients actifs\n"
                                   "• %2% clients inactifs\n"
                                   "• %3 nouveaux ce mois\n"
                                   "• %4 clients total"
                                   ).arg(activePercentage, 0, 'f', 1)
                                   .arg(inactivePercentage, 0, 'f', 1)
                                   .arg(newThisMonth)
                                   .arg(totalClients));
    }

    // Mettre à jour les cartes de statistiques
    QLabel *cardActifs = findChild<QLabel*>("cardActifs");
    QLabel *cardInactifs = findChild<QLabel*>("cardInactifs");
    QLabel *cardNouveaux = findChild<QLabel*>("cardNouveaux");
    QLabel *cardTotal = findChild<QLabel*>("cardTotal");

    if (cardActifs) {
        cardActifs->setText(QString("🟢 ACTIFS\n%1\n%2%")
                                .arg(activeClients)
                                .arg(activePercentage, 0, 'f', 1));
    }

    if (cardInactifs) {
        cardInactifs->setText(QString("🔴 INACTIFS\n%1\n%2%")
                                  .arg(inactiveClients)
                                  .arg(inactivePercentage, 0, 'f', 1));
    }

    if (cardNouveaux) {
        cardNouveaux->setText(QString("🆕 NOUVEAUX\n%1\n%2%")
                                  .arg(newThisMonth)
                                  .arg(newPercentage, 0, 'f', 1));
    }

    if (cardTotal) {
        cardTotal->setText(QString("👥 TOTAL\n%1").arg(totalClients));
    }

    // Mettre à jour la barre de statut
    QString performanceMessage;
    if (activePercentage >= 70) {
        performanceMessage = "🚀 Excellente performance!";
    } else if (activePercentage >= 50) {
        performanceMessage = "📈 Bonne performance";
    } else if (activePercentage >= 30) {
        performanceMessage = "⚡ Performance moyenne";
    } else {
        performanceMessage = "⚠️ Amélioration nécessaire";
    }

    statusBar()->showMessage(QString("%1 | Actifs: %2% | Inactifs: %3% | Total: %4")
                                 .arg(performanceMessage)
                                 .arg(activePercentage, 0, 'f', 1)
                                 .arg(inactivePercentage, 0, 'f', 1)
                                 .arg(totalClients));
}


void MainWindow::refreshClientTable()
{
    qDebug() << "🔄 Rafraîchissement tableau clients...";

    QString queryStr = "SELECT ID, NOM_PRENOM, EMAIL, TELEPHONE, DATE_AJOUT, STATUT FROM client";

    if (ui->activeClientsOnly->isChecked()) {
        queryStr += " WHERE STATUT = 'Actif'";
    }

    QSqlQuery query(queryStr);

    // Vider le tableau
    ui->clientTable->setRowCount(0);

    // Configurer les colonnes avec les bons noms
    ui->clientTable->setColumnCount(6);
    QStringList headers = {"ID", "NOM_PRENOM", "EMAIL", "TELEPHONE", "DATE_AJOUT", "STATUT"};
    ui->clientTable->setHorizontalHeaderLabels(headers);

    // Remplir le tableau
    int row = 0;
    while (query.next()) {
        ui->clientTable->insertRow(row);

        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());

            // Meilleure police et alignement
            item->setFont(QFont("Arial", 9));

            // Centrer ID et STATUT
            if (col == 0 || col == 5) {
                item->setTextAlignment(Qt::AlignCenter);
            }

            ui->clientTable->setItem(row, col, item);
        }
        row++;
    }

    // Meilleure taille des colonnes
    ui->clientTable->setColumnWidth(0, 50);    // ID
    ui->clientTable->setColumnWidth(1, 150);   // NOM_PRENOM
    ui->clientTable->setColumnWidth(2, 150);   // EMAIL
    ui->clientTable->setColumnWidth(3, 100);   // TELEPHONE
    ui->clientTable->setColumnWidth(4, 100);   // DATE_AJOUT
    ui->clientTable->setColumnWidth(5, 80);    // STATUT

    // Rendre certaines colonnes extensibles
    ui->clientTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->clientTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    // Meilleure apparence
    ui->clientTable->setAlternatingRowColors(true);
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->setSelectionMode(QAbstractItemView::SingleSelection);

    qDebug() << "✅ Tableau rafraîchi -" << row << "clients";

    // Mettre à jour les statistiques
    mettreAJourStatistiquesCirculaires();
}

// Appliquer un style moderne à l'interface
void MainWindow::appliquerStyleModerne()
{
    // Style amélioré pour les tables
    this->setStyleSheet(
        "QMainWindow {"
        "    background-color: #F8F9FA;"
        "}"

        "#statsWidget {"
        "    background-color: white;"
        "    border-radius: 10px;"
        "    border: 2px solid #DEE2E6;"
        "    margin: 5px;"
        "    padding: 5px;"
        "}"

        "CircularChart {"
        "    background-color: white;"
        "    border-radius: 8px;"
        "}"

        "QTableWidget {"
        "    background-color: white;"
        "    border: 1px solid #DEE2E6;"
        "    border-radius: 8px;"
        "    gridline-color: #DEE2E6;"
        "    font-size: 11px;"
        "}"

        "QTableWidget::item {"
        "    padding: 8px;"
        "    border-bottom: 1px solid #F8F9FA;"
        "}"

        "QTableWidget::item:selected {"
        "    background-color: #E3F2FD;"
        "    color: #1976D2;"
        "}"

        "QHeaderView::section {"
        "    background-color: #2C3E50;"
        "    color: white;"
        "    padding: 12px;"
        "    border: none;"
        "    font-weight: bold;"
        "    font-size: 12px;"
        "}"

        "QTableWidget QTableCornerButton::section {"
        "    background-color: #2C3E50;"
        "}"

        // Style pour les indicateurs circulaires
        "#statsWidget {"
        "    background-color: #FFFFFF;"
        "    border-radius: 10px;"
        "    border: 1px solid #DEE2E6;"
        "    margin: 5px;"
        "}"
        );
}

void MainWindow::creerStatistiquesCirculaires()
{
    // Widget conteneur principal
    QWidget *statsWidget = new QWidget();
    statsWidget->setObjectName("statsWidget");
    QVBoxLayout *mainStatsLayout = new QVBoxLayout(statsWidget);

    // Titre
    QLabel *titleLabel = new QLabel("📊 STATISTIQUES CLIENTS");
    titleLabel->setStyleSheet(
        "QLabel {"
        "    font-weight: bold;"
        "    font-size: 14px;"
        "    color: white;"
        "    padding: 8px;"
        "    background-color: #34495E;"
        "    border-radius: 6px;"
        "    text-align: center;"
        "    margin-bottom: 8px;"
        "}"
        );
    mainStatsLayout->addWidget(titleLabel);

    // Container pour les cercles (REDUCED SIZE)
    QWidget *circlesWidget = new QWidget();
    QHBoxLayout *circlesLayout = new QHBoxLayout(circlesWidget);

    // Style pour les cercles (HALF SIZE - 75px instead of 150px)
    QString circleStyle =
        "QLabel {"
        "    background: qconicalgradient("
        "        cx: 0.5, cy: 0.5, angle: 0,"
        "        stop: 0 %1,"
        "        stop: %2 %1,"
        "        stop: %2 %3,"
        "        stop: 1.0 %3"
        "    );"
        "    border-radius: 37px;"  // Half size
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 11px;"      // Smaller font
        "    min-width: 75px;"      // Half width
        "    min-height: 75px;"     // Half height
        "    max-width: 75px;"
        "    max-height: 75px;"
        "    border: 3px solid %4;"
        "    qproperty-alignment: 'AlignCenter';"
        "}";

    // Cercle principal - Actifs
    QLabel *mainCircle = new QLabel();
    mainCircle->setObjectName("mainCircle");
    mainCircle->setText("0%\nACTIFS");
    mainCircle->setStyleSheet(circleStyle.arg("#27AE60").arg("0.0").arg("#ECF0F1").arg("#27AE60"));

    // Cercle Inactifs
    QLabel *circle2 = new QLabel();
    circle2->setObjectName("circle2");
    circle2->setText("0%\nINACTIFS");
    circle2->setStyleSheet(circleStyle.arg("#E74C3C").arg("0.0").arg("#ECF0F1").arg("#E74C3C"));

    // Cercle Nouveaux
    QLabel *circle3 = new QLabel();
    circle3->setObjectName("circle3");
    circle3->setText("0%\nNOUVEAUX");
    circle3->setStyleSheet(circleStyle.arg("#3498DB").arg("0.0").arg("#ECF0F1").arg("#3498DB"));

    // Ajouter les cercles
    circlesLayout->addWidget(mainCircle);
    circlesLayout->addWidget(circle2);
    circlesLayout->addWidget(circle3);
    circlesLayout->setSpacing(10);  // Reduced spacing
    circlesLayout->setContentsMargins(5, 5, 5, 5);

    mainStatsLayout->addWidget(circlesWidget);

    // Légende (smaller)
    QWidget *legendWidget = new QWidget();
    QHBoxLayout *legendLayout = new QHBoxLayout(legendWidget);

    QString legendStyle =
        "QLabel {"
        "    background-color: %1;"
        "    border-radius: 4px;"
        "    color: white;"
        "    font-weight: bold;"
        "    padding: 4px 8px;"
        "    font-size: 10px;"
        "    margin: 1px;"
        "}";

    QLabel *legend1 = new QLabel();
    legend1->setObjectName("legend1");
    legend1->setText("🟢 0% Actifs");
    legend1->setStyleSheet(legendStyle.arg("#27AE60"));

    QLabel *legend2 = new QLabel();
    legend2->setObjectName("legend2");
    legend2->setText("🔴 0% Inactifs");
    legend2->setStyleSheet(legendStyle.arg("#E74C3C"));

    QLabel *legend3 = new QLabel();
    legend3->setObjectName("legend3");
    legend3->setText("🔵 0% Nouveaux");
    legend3->setStyleSheet(legendStyle.arg("#3498DB"));

    legendLayout->addWidget(legend1);
    legendLayout->addWidget(legend2);
    legendLayout->addWidget(legend3);
    legendLayout->setSpacing(5);

    mainStatsLayout->addWidget(legendWidget);

    // Ajouter à l'interface principale
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
    if (mainLayout) {
        mainLayout->insertWidget(1, statsWidget);
    }

    qDebug() << "✅ Statistiques circulaires (réduites) créées!";
}

void MainWindow::mettreAJourStatistiquesCirculaires()
{
    QSqlQuery query;
    int totalClients = 0;
    int activeClients = 0;
    int inactiveClients = 0;
    int newThisMonth = 0;

    // Get real data
    query.exec("SELECT COUNT(*) FROM client");
    if (query.next()) totalClients = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) activeClients = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM client WHERE statut != 'Actif' OR statut IS NULL OR statut = ''");
    if (query.next()) inactiveClients = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM client WHERE MONTH(date_ajout) = MONTH(CURRENT_DATE) AND YEAR(date_ajout) = YEAR(CURRENT_DATE)");
    if (query.next()) newThisMonth = query.value(0).toInt();

    // Calculate percentages
    double activePercentage = totalClients > 0 ? (activeClients * 100.0) / totalClients : 0;
    double inactivePercentage = totalClients > 0 ? (inactiveClients * 100.0) / totalClients : 0;
    double newPercentage = totalClients > 0 ? (newThisMonth * 100.0) / totalClients : 0;

    // Convert to fractions
    double activeFraction = activePercentage / 100.0;
    double inactiveFraction = inactivePercentage / 100.0;
    double newFraction = newPercentage / 100.0;

    // Update circles with smaller size style
    QString smallCircleStyle =
        "QLabel {"
        "    background: qconicalgradient("
        "        cx: 0.5, cy: 0.5, angle: 0,"
        "        stop: 0 %1,"
        "        stop: %2 %1,"
        "        stop: %2 %3,"
        "        stop: 1.0 %3"
        "    );"
        "    border-radius: 37px;"
        "    color: white;"
        "    font-weight: bold;"
        "    font-size: 11px;"
        "    min-width: 75px;"
        "    min-height: 75px;"
        "    max-width: 75px;"
        "    max-height: 75px;"
        "    border: 3px solid %4;"
        "    qproperty-alignment: 'AlignCenter';"
        "}";

    QLabel *mainCircle = findChild<QLabel*>("mainCircle");
    if (mainCircle) {
        mainCircle->setText(QString("%1%\nACTIFS").arg(activePercentage, 0, 'f', 0));
        mainCircle->setStyleSheet(smallCircleStyle.arg("#27AE60").arg(activeFraction).arg("#ECF0F1").arg("#27AE60"));
    }

    QLabel *circle2 = findChild<QLabel*>("circle2");
    if (circle2) {
        circle2->setText(QString("%1%\nINACTIFS").arg(inactivePercentage, 0, 'f', 0));
        circle2->setStyleSheet(smallCircleStyle.arg("#E74C3C").arg(inactiveFraction).arg("#ECF0F1").arg("#E74C3C"));
    }

    QLabel *circle3 = findChild<QLabel*>("circle3");
    if (circle3) {
        circle3->setText(QString("%1%\nNOUVEAUX").arg(newPercentage, 0, 'f', 0));
        circle3->setStyleSheet(smallCircleStyle.arg("#3498DB").arg(newFraction).arg("#ECF0F1").arg("#3498DB"));
    }

    // Update legend
    QLabel *legend1 = findChild<QLabel*>("legend1");
    QLabel *legend2 = findChild<QLabel*>("legend2");
    QLabel *legend3 = findChild<QLabel*>("legend3");

    if (legend1) legend1->setText(QString("🟢 %1% Actifs").arg(activePercentage, 0, 'f', 0));
    if (legend2) legend2->setText(QString("🔴 %1% Inactifs").arg(inactivePercentage, 0, 'f', 0));
    if (legend3) legend3->setText(QString("🔵 %1% Nouveaux").arg(newPercentage, 0, 'f', 0));

    qDebug() << "📊 Stats mises à jour - Actifs:" << activePercentage << "%";
}





// Créer des indicateurs circulaires pour les statistiques
void MainWindow::creerIndicateursCirculaires()
{
    // Widget simple pour éviter les erreurs
    QWidget *statsWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(statsWidget);

    // Indicateur Actifs
    QLabel *labelActifs = new QLabel("🟢 Actifs: 0");
    labelActifs->setObjectName("labelActifs");
    labelActifs->setStyleSheet("font-weight: bold; color: #27AE60; padding: 5px;");

    // Indicateur Inactifs
    QLabel *labelInactifs = new QLabel("🔴 Inactifs: 0");
    labelInactifs->setObjectName("labelInactifs");
    labelInactifs->setStyleSheet("font-weight: bold; color: #E74C3C; padding: 5px;");

    // Indicateur Nouveaux
    QLabel *labelNouveaux = new QLabel("🆕 Nouveaux: 0");
    labelNouveaux->setObjectName("labelNouveaux");
    labelNouveaux->setStyleSheet("font-weight: bold; color: #3498DB; padding: 5px;");

    layout->addWidget(labelActifs);
    layout->addWidget(labelInactifs);
    layout->addWidget(labelNouveaux);

    // Ajouter à l'interface
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
    if (mainLayout) {
        mainLayout->insertWidget(1, statsWidget);
    }
}

// Mettre à jour les indicateurs circulaires
void MainWindow::mettreAJourIndicateursCirculaires()
{
    QSqlQuery query;
    int actifs = 0, inactifs = 0, nouveaux = 0;

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) actifs = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Inactif' OR statut IS NULL OR statut = ''");
    if (query.next()) inactifs = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM client WHERE MONTH(date_ajout) = MONTH(CURRENT_DATE) AND YEAR(date_ajout) = YEAR(CURRENT_DATE)");
    if (query.next()) nouveaux = query.value(0).toInt();

    // Mettre à jour les labels
    QLabel *labelActifs = findChild<QLabel*>("labelActifs");
    QLabel *labelInactifs = findChild<QLabel*>("labelInactifs");
    QLabel *labelNouveaux = findChild<QLabel*>("labelNouveaux");

    if (labelActifs) labelActifs->setText(QString("🟢 Actifs: %1").arg(actifs));
    if (labelInactifs) labelInactifs->setText(QString("🔴 Inactifs: %1").arg(inactifs));
    if (labelNouveaux) labelNouveaux->setText(QString("🆕 Nouveaux: %1").arg(nouveaux));
}

// Dans le constructeur MainWindow, après la création des autres boutons
void MainWindow::ajouterBoutonStatut()
{
    QPushButton *toggleStatutBtn = new QPushButton("🔄 Basculer Statut", this);
    toggleStatutBtn->setObjectName("toggleStatutBtn");
    toggleStatutBtn->setStyleSheet(
        "QPushButton {"
        "    background-color: #9B59B6;"
        "    color: white;"
        "    border: none;"
        "    padding: 8px 16px;"
        "    border-radius: 5px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #8E44AD;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #7D3C98;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #BDC3C7;"
        "    color: #7F8C8D;"
        "}"
        );
    toggleStatutBtn->setEnabled(false);

    // Ajouter au layout existant
    QHBoxLayout *boutonsLayout = nullptr;
    QLayout *layout = ui->groupBox->layout();

    if (layout) {
        for (int i = 0; i < layout->count(); ++i) {
            QLayoutItem *item = layout->itemAt(i);
            if (item && item->layout()) {
                QHBoxLayout *hbox = qobject_cast<QHBoxLayout*>(item->layout());
                if (hbox) {
                    // Vérifier si c'est le layout des boutons clients
                    for (int j = 0; j < hbox->count(); ++j) {
                        QWidget *widget = hbox->itemAt(j)->widget();
                        if (widget && (widget->objectName().contains("Client") ||
                                       qobject_cast<QPushButton*>(widget))) {
                            boutonsLayout = hbox;
                            break;
                        }
                    }
                    if (boutonsLayout) break;
                }
            }
        }
    }

    // Ajouter le bouton
    if (boutonsLayout) {
        boutonsLayout->addWidget(toggleStatutBtn);
    } else {
        // Fallback : ajouter dans le layout principal
        QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(ui->groupBox->layout());
        if (mainLayout) {
            mainLayout->addWidget(toggleStatutBtn);
        }
    }

    // Connexion du signal
    connect(toggleStatutBtn, &QPushButton::clicked, this, &MainWindow::on_toggleStatutBtn_clicked);
}

// Méthode pour basculer le statut d'un client
void MainWindow::basculerStatutClient()
{
    if (currentClientId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT statut FROM client WHERE id = :id");
    query.bindValue(":id", currentClientId);

    if (!query.exec() || !query.next()) {
        QMessageBox::critical(this, "Erreur", "Impossible de récupérer le statut du client");
        return;
    }

    QString ancienStatut = query.value(0).toString();
    QString nouveauStatut = (ancienStatut == "Actif") ? "Inactif" : "Actif";

    // Mettre à jour le statut
    query.prepare("UPDATE client SET statut = :statut WHERE id = :id");
    query.bindValue(":statut", nouveauStatut);
    query.bindValue(":id", currentClientId);

    if (query.exec()) {
        QString message = QString("Statut changé de '%1' à '%2'")
                              .arg(ancienStatut).arg(nouveauStatut);
        statusBar()->showMessage(message, 3000);

        // Rafraîchir l'interface
        refreshClientTable();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du statut");
    }
}


void MainWindow::on_toggleStatutBtn_clicked()
{
    basculerStatutClient(); // Appel simple sans paramètre
}

void MainWindow::mettreAJourBoutonStatut()
{
    QPushButton *toggleBtn = findChild<QPushButton*>("toggleStatutBtn");
    if (!toggleBtn) return;

    toggleBtn->setEnabled(currentClientId != -1);

    if (currentClientId != -1) {
        // Récupérer le statut actuel pour personnaliser le bouton
        QSqlQuery query;
        query.prepare("SELECT statut FROM client WHERE id = :id");
        query.bindValue(":id", currentClientId);

        if (query.exec() && query.next()) {
            QString statut = query.value(0).toString();
            if (statut == "Actif") {
                toggleBtn->setText("🔴 Rendre Inactif");
                toggleBtn->setStyleSheet(
                    "QPushButton {"
                    "    background-color: #E74C3C;"
                    "    color: white;"
                    "    border: none;"
                    "    padding: 8px 16px;"
                    "    border-radius: 5px;"
                    "    font-weight: bold;"
                    "}"
                    "QPushButton:hover {"
                    "    background-color: #C0392B;"
                    "}"
                    );
            } else {
                toggleBtn->setText("🟢 Rendre Actif");
                toggleBtn->setStyleSheet(
                    "QPushButton {"
                    "    background-color: #27AE60;"
                    "    color: white;"
                    "    border: none;"
                    "    padding: 8px 16px;"
                    "    border-radius: 5px;"
                    "    font-weight: bold;"
                    "}"
                    "QPushButton:hover {"
                    "    background-color: #229954;"
                    "}"
                    );
            }
        }
    } else {
        // Aucun client sélectionné
        toggleBtn->setText("🔄 Basculer Statut");
        toggleBtn->setStyleSheet(
            "QPushButton {"
            "    background-color: #9B59B6;"
            "    color: white;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 5px;"
            "    font-weight: bold;"
            "}"
            "QPushButton:hover {"
            "    background-color: #8E44AD;"
            "}"
            "QPushButton:disabled {"
            "    background-color: #BDC3C7;"
            "    color: #7F8C8D;"
            "}"
            );
    }
}



