#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "client.h"
#include "employe.h"
#include "projet.h"
#include "finance.h"
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






{
    ui->setupUi(this);



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

void MainWindow::refreshClientTable()
{
    QString queryStr = "SELECT id, nom_prenom, email, telephone, date_ajout, statut FROM client";

    if (ui->activeClientsOnly->isChecked()) {
        queryStr += " WHERE statut = 'Actif'";
    }

    QSqlQuery query(queryStr);

    // Configurer les colonnes
    ui->clientTable->setColumnCount(6);
    ui->clientTable->setHorizontalHeaderLabels({"ID", "Nom/Prénom", "Email", "Téléphone", "Date d'ajout", "Statut"});

    // Vider le tableau
    ui->clientTable->setRowCount(0);

    // Remplir le tableau
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

    // Ajuster la largeur des colonnes
    ui->clientTable->horizontalHeader()->setStretchLastSection(true);
    ui->clientTable->resizeColumnsToContents();

    // METTRE À JOUR LES STATISTIQUES AVEC LES POURCENTAGES
    updateClientStats();
}



void MainWindow::updateClientStats()
{
    QSqlQuery query;
    int totalClients = 0;
    int activeClients = 0;
    int newThisMonth = 0;

    // ============================================================================
    // CALCULS DES DONNÉES DE BASE (SIMPLIFIÉS)
    // ============================================================================

    // Total clients
    query.exec("SELECT COUNT(*) FROM client");
    if (query.next()) {
        totalClients = query.value(0).toInt();
    }

    // Clients actifs
    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) {
        activeClients = query.value(0).toInt();
    }

    // Nouveaux ce mois
    query.exec("SELECT COUNT(*) FROM client WHERE MONTH(date_ajout) = MONTH(CURRENT_DATE) AND YEAR(date_ajout) = YEAR(CURRENT_DATE)");
    if (query.next()) {
        newThisMonth = query.value(0).toInt();
    }

    // ============================================================================
    // CALCULS DES POURCENTAGES
    // ============================================================================

    double activePercentage = 0.0;
    double monthlyGrowthPercentage = 0.0;

    if (totalClients > 0) {
        activePercentage = (activeClients * 100.0) / totalClients;
        monthlyGrowthPercentage = (newThisMonth * 100.0) / totalClients;
    }

    // ============================================================================
    // FORMATAGE DES TEXTES AVEC POURCENTAGES
    // ============================================================================

    // Total clients (simple)
    ui->totalClientsLabel->setText(QString::number(totalClients));

    // Clients actifs avec pourcentage
    QString activeText = QString("%1\n%2% Actifs")
                             .arg(activeClients)
                             .arg(activePercentage, 0, 'f', 1);
    ui->activeClientsLabel->setText(activeText);

    // Nouveaux ce mois avec pourcentage
    QString monthlyText = QString("%1\n%2% Ce mois")
                              .arg(newThisMonth)
                              .arg(monthlyGrowthPercentage, 0, 'f', 1);
    ui->newThisMonthLabel->setText(monthlyText);

    // ============================================================================
    // INDICATEUR DE PERFORMANCE DANS LA STATUSBAR
    // ============================================================================

    // Indicateur simple dans la barre de statut
    QString performanceText;

    if (activePercentage >= 80.0 && monthlyGrowthPercentage >= 10.0) {
        performanceText = "🚀 Excellente performance";
    } else if (activePercentage >= 60.0 && monthlyGrowthPercentage >= 5.0) {
        performanceText = "📈 Bonne performance";
    } else if (activePercentage >= 40.0) {
        performanceText = "📊 Performance stable";
    } else {
        performanceText = "⚠️  Amélioration nécessaire";
    }

    statusBar()->showMessage(performanceText);
}

// SUPPRIMEZ cette fonction pour l'instant ou gardez-la simple :


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

    // Vérification des champs vides
    if(nomPrenom.isEmpty() || email.isEmpty() || telephone.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    // Validation du nom/prénom
    if(!Client::validerNomPrenom(nomPrenom)) {
        showValidationError("Le nom/prénom doit contenir uniquement des lettres, espaces, apostrophes ou tirets, et avoir au moins 2 caractères");
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

    return true;
}

void MainWindow::on_addClientBtn_clicked()
{
    if(!validateClientForm()) {
        return;
    }

    // Récupération des données
    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    // Générer un ID unique
    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    Client newClient(id, nomPrenom, email, telephone);
    bool test = newClient.ajouter();

    if(test) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès");
        refreshClientTable();  // Cela va mettre à jour les stats automatiquement
        clearClientForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout du client. Vérifiez que les données sont valides.");
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

void MainWindow::refreshFinanceTable()
{
    qDebug() << "🔄 Rafraîchissement du tableau finances...";

    Finance f;
    QSqlQueryModel *model = f.afficher();

    if (model) {
        qDebug() << "Modèle chargé, lignes:" << model->rowCount();

        ui->financeTable->setRowCount(0);

        QStringList headers;
        headers << "ID" << "Type" << "Montant" << "Date" << "Description" << "Catégorie";
        ui->financeTable->setColumnCount(headers.size());
        ui->financeTable->setHorizontalHeaderLabels(headers);

        for (int row = 0; row < model->rowCount(); ++row) {
            ui->financeTable->insertRow(row);
            for (int col = 0; col < model->columnCount(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(
                    model->data(model->index(row, col)).toString());
                ui->financeTable->setItem(row, col, item);
            }
        }

        ui->financeTable->resizeColumnsToContents();
        delete model;

        qDebug() << "✅ Tableau finances rafraîchi -" << ui->financeTable->rowCount() << "lignes affichées";
    } else {
        qDebug() << "❌ Erreur lors du chargement du modèle";
    }
}

void MainWindow::clearFinanceForm()
{
    ui->financeTypeEdit->clear();
    ui->financeDescriptionEdit->clear();
    ui->financeMontantEdit->clear();
    ui->financeProjetIdEdit->clear();
    ui->selectedFinanceIdLabel->clear();
    currentFinanceId = -1;
}

bool MainWindow::validateFinanceForm()
{
    QString type = ui->financeTypeEdit->text().trimmed();
    QString montant = ui->financeMontantEdit->text().trimmed();
    QString description = ui->financeDescriptionEdit->text().trimmed();
    QString projetId = ui->financeProjetIdEdit->text().trimmed();

    // Vérification des champs vides
    if(type.isEmpty() || montant.isEmpty() || description.isEmpty() || projetId.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    // Validation du montant
    bool montantOk;
    double montantValue = montant.toDouble(&montantOk);
    if(!montantOk || montantValue <= 0) {
        showValidationError("Le montant doit être un nombre positif");
        ui->financeMontantEdit->setFocus();
        return false;
    }

    // Validation de l'ID projet
    bool projetOk;
    int projetIdValue = projetId.toInt(&projetOk);
    if(!projetOk || projetIdValue <= 0) {
        showValidationError("L'ID projet doit être un nombre positif");
        ui->financeProjetIdEdit->setFocus();
        return false;
    }

    return true;
}

void MainWindow::on_addFinanceBtn_clicked()
{
    // RÉCUPÉRER LES VRAIES VALEURS DU FORMULAIRE
    QString type = ui->financeTypeEdit->text();
    QString description = ui->financeDescriptionEdit->text();
    double montant = ui->financeMontantEdit->text().toDouble();
    QString projetId = ui->financeProjetIdEdit->text();

    // Validation
    if (type.isEmpty() || description.isEmpty() || montant <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement");
        return;
    }

    // Ajouter à la base
    Finance f;
    f.setType(type);
    f.setDescription(description);
    f.setMontant(montant);
    f.setProjet_id(projetId);  // ← CORRECTION ICI : setProjet_id() au lieu de setProjetId()
    f.setDateOperation(QDate::currentDate().toString("dd/MM/yyyy"));

    if (f.ajouter()) {
        QMessageBox::information(this, "Succès", "Opération financière ajoutée avec succès !");
        refreshFinanceTable();
        // Vider le formulaire
        ui->financeTypeEdit->clear();
        ui->financeDescriptionEdit->clear();
        ui->financeMontantEdit->clear();
        ui->financeProjetIdEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout: " + QSqlDatabase::database().lastError().text());
    }
}


void MainWindow::on_deleteFinanceBtn_clicked()
{
    QList<QTableWidgetItem*> selected = ui->financeTable->selectedItems();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une opération financière à supprimer");
        return;
    }

    int row = ui->financeTable->currentRow();
    int id = ui->financeTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                  "Êtes-vous sûr de vouloir supprimer cette opération financière?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Finance finance;
        bool test = finance.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Opération financière supprimée avec succès");
            refreshFinanceTable();
            clearFinanceForm();
        } else {
            QMessageBox::critical(this, "Erreur", "Échec de la suppression de l'opération financière");
        }
    }
}

void MainWindow::on_editFinanceBtn_clicked()
{
    if(currentFinanceId == -1) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une opération financière à modifier");
        return;
    }

    // Debug
    qDebug() << "=== TENTATIVE MODIFICATION ===";
    qDebug() << "ID sélectionné:" << currentFinanceId;
    qDebug() << "Type:" << ui->financeTypeEdit->text();
    qDebug() << "Montant:" << ui->financeMontantEdit->text();
    qDebug() << "Description:" << ui->financeDescriptionEdit->text();
    qDebug() << "Projet ID:" << ui->financeProjetIdEdit->text();

    // Récupération des données CORRECTE
    QString type = ui->financeTypeEdit->text().trimmed();
    QString description = ui->financeDescriptionEdit->text().trimmed();
    double montant = ui->financeMontantEdit->text().toDouble();
    QString projetId = ui->financeProjetIdEdit->text().trimmed(); // Garder en QString
    QString categorie = "Général"; // Si vous avez un champ catégorie, adaptez
    QString dateOperation = QDate::currentDate().toString("dd/MM/yyyy");

    // Validation
    if(type.isEmpty() || description.isEmpty() || montant <= 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs correctement");
        return;
    }

    // Utiliser la méthode modifier
    Finance finance;
    bool test = finance.modifier(currentFinanceId, type, description, montant,
                                 dateOperation, categorie);

    if(test) {
        QMessageBox::information(this, "Succès", "Opération financière modifiée avec succès");
        refreshFinanceTable();
        clearFinanceForm();
        currentFinanceId = -1;

        // Réactiver/désactiver les boutons
        ui->editFinanceBtn->setEnabled(false);
        ui->addFinanceBtn->setEnabled(true);

        qDebug() << "✅ Modification réussie";
    } else {
        QString error = QSqlDatabase::database().lastError().text();
        QMessageBox::critical(this, "Erreur", "Échec de la modification: " + error);
        qDebug() << "❌ Erreur modification:" << error;
    }
}

void MainWindow::on_searchFinanceLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshFinanceTable();
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id, type, montant, description, date_operation, projet_id, statut FROM finance "
                  "WHERE type LIKE :search OR description LIKE :search");
    query.bindValue(":search", "%" + text + "%");

    if(query.exec()) {
        ui->financeTable->setRowCount(0);
        int row = 0;
        while (query.next()) {
            ui->financeTable->insertRow(row);
            ui->financeTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            ui->financeTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            ui->financeTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
            ui->financeTable->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
            ui->financeTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString()));
            ui->financeTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString()));
            ui->financeTable->setItem(row, 6, new QTableWidgetItem(query.value(6).toString()));
            row++;
        }
    }
}

void MainWindow::on_financeTable_itemClicked(QTableWidgetItem *item)
{
    int row = item->row();

    currentFinanceId = ui->financeTable->item(row, 0)->text().toInt();
    ui->financeTypeEdit->setText(ui->financeTable->item(row, 1)->text());
    ui->financeMontantEdit->setText(ui->financeTable->item(row, 2)->text());
    ui->financeDescriptionEdit->setText(ui->financeTable->item(row, 3)->text());
    ui->financeProjetIdEdit->setText(ui->financeTable->item(row, 5)->text());
    ui->selectedFinanceIdLabel->setText(QString::number(currentFinanceId));

    // Activer le bouton modifier et désactiver le bouton ajouter
    ui->editFinanceBtn->setEnabled(true);
    ui->addFinanceBtn->setEnabled(false);
}

void MainWindow::on_clearFinanceFormBtn_clicked()
{
    clearFinanceForm();
}

void MainWindow::on_refreshFinanceTableBtn_clicked()
{
    refreshFinanceTable();
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
