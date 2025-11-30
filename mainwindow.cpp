#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h" // Assurez-vous que cette classe existe
#include "client.h"     // Assurez-vous que les classes Client, Employe, etc., sont bien définies
#include "employe.h"
#include "projet.h"
#include "finance.h"
#include "equipement.h" // Ajout de l'include manquant pour Equipement
#include "alerteretarddialog.h"
#include "historiquedialog.h"
#include "pdfexporter.h"
#include "emailsmtpmanager.h"
#include "chatbotdialog.h"

#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QSqlQuery>
#include <QHeaderView>
#include <QRegularExpressionValidator>
#include <QButtonGroup>
#include <QTableWidget>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlError>
#include <QModelIndex> // Ajout pour les tables basées sur des modèles

// ============================================================================
// CONSTRUCTEUR
// ============================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentClientId(-1)
    , currentEmployeId(-1)
    , currentProjetId(-1)
    , currentFinanceId(-1)
    , currentEquipementId(-1)
    , currentMailingId(-1)
    , emailManager(new EmailSMTPManager(this))
    , completionModel(new QStringListModel(this))
    , chatbotDialog(new ChatbotDialog(this))
    , progressBarActifs(nullptr)
    , progressBarNouveaux(nullptr)
    , labelStatsDetails(nullptr)
{
    ui->setupUi(this);
    appliquerStyleModerne();
    creerIndicateursCirculaires();
    ajouterBoutonStatut();
    creerStatistiquesCirculaires();
    mettreAJourStatistiquesCirculaires();

    // Initialisation des IDs
    currentClientId = -1;
    currentEmployeId = -1;
    currentProjetId = -1;
    currentFinanceId = -1;
    currentEquipementId = -1;
    currentMailingId = -1;

    // --- Configuration EmailSMTPManager ---
    EmailSMTPManager *smtp = new EmailSMTPManager(this);

    emailManager->configurerSMTP(
        "oussamazayane2005@gmail.com",
        "efhm hspd yewe dzew"
        );

    smtp->envoyerEmail(
        "oussamazayane2005@gmail.com",
        "Bienvenue !",
        "<h2>Bonjour !</h2><p>Ceci est un email envoyé depuis Qt 😊</p>"
        );

    connect(smtp, &EmailSMTPManager::emailEnvoye, [](QString dest, bool ok, QString details){
        qDebug() << "Résultat =>" << dest << ok << details;
    });

    // --- Création du bouton Envoyer Email (Client) ---
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

    // Recherche et ajout dans le layout
    QHBoxLayout *boutonsLayout = nullptr;
    QLayout *layout = ui->groupBox->layout();
    if (layout) {
        // Logique de recherche du layout... (laissée telle quelle pour l'ajout du bouton)
        QLayoutItem *item = layout->itemAt(1); // Tentative de cibler la zone des boutons
        if(item && item->layout()){
            boutonsLayout = qobject_cast<QHBoxLayout*>(item->layout());
        }

        if (!boutonsLayout) {
             // Si le ciblage par index n'a pas fonctionné, parcourir pour trouver un QHBoxLayout
            for (int i = 0; i < layout->count(); ++i) {
                QLayoutItem *item = layout->itemAt(i);
                if (item && item->layout()) {
                    QHBoxLayout *hbox = qobject_cast<QHBoxLayout*>(item->layout());
                    if (hbox && hbox->count() > 0) { // S'assurer que c'est un layout non vide (boutons CRUD)
                        boutonsLayout = hbox;
                        break;
                    }
                }
            }
        }
    }


    // Ajouter le bouton email
    if (boutonsLayout) {
        boutonsLayout->insertWidget(1, envoyerEmailBtn);
    } else {
        qDebug() << "❌ Erreur: Impossible de trouver le layout des boutons pour insérer envoyerEmailBtn.";
    }


    // --- Création du bouton Chatbot ---
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

    // Ajouter le bouton chatbot
    if (boutonsLayout) {
        boutonsLayout->insertWidget(2, chatbotBtn);
    } else {
         qDebug() << "❌ Erreur: Impossible de trouver le layout des boutons pour insérer chatbotBtn.";
    }

    // Connexion Chatbot
    connect(chatbotBtn, &QPushButton::clicked, this, &MainWindow::on_chatbotBtn_clicked);
    connect(envoyerEmailBtn, &QPushButton::clicked, this, &MainWindow::on_envoyerEmailClientBtn_clicked);
    connect(emailManager, &EmailSMTPManager::progressionEnvoi,this, &MainWindow::onProgression);

    qDebug() << "✅ Bouton 'Envoyer Email' et 'Assistant' ajoutés dynamiquement";

    // Configuration de la navigation
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->clientsBtn);
    buttonGroup->addButton(ui->employesBtn);
    buttonGroup->addButton(ui->projetsBtn);
    buttonGroup->addButton(ui->financesBtn);
    buttonGroup->addButton(ui->equipementsBtn);
    buttonGroup->setExclusive(true);

    // Connexions pour la navigation (maintenues pour la compatibilité avec les slots)
    connect(ui->clientsBtn, &QPushButton::clicked, this, &MainWindow::on_clientsBtn_clicked);
    connect(ui->employesBtn, &QPushButton::clicked, this, &MainWindow::on_employesBtn_clicked);
    connect(ui->projetsBtn, &QPushButton::clicked, this, &MainWindow::on_projetsBtn_clicked);
    connect(ui->financesBtn, &QPushButton::clicked, this, &MainWindow::on_financesBtn_clicked);
    connect(ui->equipementsBtn, &QPushButton::clicked, this, &MainWindow::on_equipementsBtn_clicked); // NÉCESSAIRE

    // Connexions pour les actions de menu
    connect(ui->actionAlerteRetard, &QAction::triggered, this, &MainWindow::on_actionAlerteRetard_triggered);
    connect(ui->actionHistorique, &QAction::triggered, this, &MainWindow::on_actionHistorique_triggered);

    // Configuration des tables
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->employeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->employeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->projetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->projetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->financeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->financeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->equipementTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->equipementTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->mailingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->mailingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Configuration des validateurs de saisie
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-ZÀ-ÿ]+([ '-][a-zA-ZÀ-ÿ]+)*$"), this);
    ui->clientNameEdit->setValidator(nameValidator);
    ui->employeNameEdit->setValidator(nameValidator);

    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"), this);
    ui->clientEmailEdit->setValidator(emailValidator);
    ui->employeEmailEdit->setValidator(emailValidator);

    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(QRegularExpression("^(0[1-9])(?:[ _.-]?([0-9]{2})){4}$"), this);
    ui->clientPhoneEdit->setValidator(phoneValidator);
    ui->employePhoneEdit->setValidator(phoneValidator);


    // Initialiser l'affichage
    refreshClientTable();
    refreshEmployeTable();
    refreshProjetTable();
    refreshFinanceTable();
    refreshEquipementTable();
    refreshMailingTable();

    // Connecter les signaux et slots pour la gestion clients (EXISTANT)
    connect(ui->addClientBtn, &QPushButton::clicked, this, &MainWindow::on_addClientBtn_clicked);
    connect(ui->deleteClientBtn, &QPushButton::clicked, this, &MainWindow::on_deleteClientBtn_clicked);
    connect(ui->editClientBtn, &QPushButton::clicked, this, &MainWindow::on_editClientBtn_clicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_textChanged);
    connect(ui->clientTable, &QTableWidget::itemClicked, this, &MainWindow::on_clientTable_itemClicked);
    connect(ui->clearFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearFormBtn_clicked);
    connect(ui->refreshTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshTableBtn_clicked);
    connect(ui->exportPdfBtn, &QPushButton::clicked, this, &MainWindow::on_exportPdfBtn_clicked);
    connect(ui->activeClientsOnly, &QCheckBox::toggled, this, &MainWindow::on_activeClientsOnly_toggled);
    connect(ui->toggleStatutBtn, &QPushButton::clicked, this, &MainWindow::on_toggleStatutBtn_clicked); // NOUVEAU: Toggle Statut

    // Connecter les signaux et slots pour la gestion employés (EXISTANT)
    connect(ui->addEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_addEmployeBtn_clicked);
    connect(ui->deleteEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_deleteEmployeBtn_clicked);
    connect(ui->editEmployeBtn, &QPushButton::clicked, this, &MainWindow::on_editEmployeBtn_clicked);
    connect(ui->searchEmployeLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchEmployeLineEdit_textChanged);
    connect(ui->employeTable, &QTableWidget::itemClicked, this, &MainWindow::on_employeTable_itemClicked);
    connect(ui->clearEmployeFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearEmployeFormBtn_clicked);
    connect(ui->refreshEmployeTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshEmployeTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion projets (EXISTANT)
    connect(ui->addProjetBtn, &QPushButton::clicked, this, &MainWindow::on_addProjetBtn_clicked);
    connect(ui->deleteProjetBtn, &QPushButton::clicked, this, &MainWindow::on_deleteProjetBtn_clicked);
    connect(ui->editProjetBtn, &QPushButton::clicked, this, &MainWindow::on_editProjetBtn_clicked);
    connect(ui->searchProjetLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchProjetLineEdit_textChanged);
    connect(ui->projetTable, &QTableWidget::itemClicked, this, &MainWindow::on_projetTable_itemClicked);
    connect(ui->clearProjetFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearProjetFormBtn_clicked);
    connect(ui->refreshProjetTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshProjetTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion finances (EXISTANT)
    connect(ui->addFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_addFinanceBtn_clicked);
    connect(ui->deleteFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_deleteFinanceBtn_clicked);
    connect(ui->editFinanceBtn, &QPushButton::clicked, this, &MainWindow::on_editFinanceBtn_clicked);
    connect(ui->searchFinanceLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchFinanceLineEdit_textChanged);
    connect(ui->financeTable, &QTableWidget::itemClicked, this, &MainWindow::on_financeTable_itemClicked);
    connect(ui->clearFinanceFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearFinanceFormBtn_clicked);
    connect(ui->refreshFinanceTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshFinanceTableBtn_clicked);

    // Connecter les signaux et slots pour la gestion equipement (EXISTANT)
    connect(ui->addEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_addEquipementBtn_clicked);
    connect(ui->deleteEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_deleteEquipementBtn_clicked);
    connect(ui->editEquipementBtn, &QPushButton::clicked, this, &MainWindow::on_editEquipementBtn_clicked);
    connect(ui->searchEquipementLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchEquipementLineEdit_textChanged);
    connect(ui->equipementTable, &QTableWidget::itemClicked, this, &MainWindow::on_equipementTable_itemClicked);
    connect(ui->clearEquipementFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearEquipementFormBtn_clicked);
    connect(ui->refreshEquipementTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshEquipementTableBtn_clicked);

    // Connecter les signaux et slots pour le Mailing (NOUVEAU)
    connect(ui->addMailingBtn, &QPushButton::clicked, this, &MainWindow::on_addMailingBtn_clicked);
    connect(ui->editMailingBtn, &QPushButton::clicked, this, &MainWindow::on_editMailingBtn_clicked);
    connect(ui->sendMailingBtn, &QPushButton::clicked, this, &MainWindow::on_sendMailingBtn_clicked);
    connect(ui->sendTestMailBtn, &QPushButton::clicked, this, &MainWindow::on_sendTestMailBtn_clicked);
    connect(ui->searchMailingLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchMailingLineEdit_textChanged);
    connect(ui->mailingTable, &QTableWidget::itemClicked, this, &MainWindow::on_mailingTable_itemClicked);
    connect(ui->clearMailingFormBtn, &QPushButton::clicked, this, &MainWindow::on_clearMailingFormBtn_clicked);
    connect(ui->refreshMailingTableBtn, &QPushButton::clicked, this, &MainWindow::on_refreshMailingTableBtn_clicked);

    // Afficher la page clients par défaut
    ui->stackedWidget->setCurrentIndex(0);
}

// ============================================================================
// DESTRUCTEUR
// ============================================================================

MainWindow::~MainWindow()
{
    delete ui;
}

// ============================================================================
// MÉTHODES DE NAVIGATION (CORRIGÉES)
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

void MainWindow::on_equipementsBtn_clicked() {
    ui->stackedWidget->setCurrentIndex(4);
    refreshEquipementTable();
}

// ============================================================================
// MÉTHODES UTILITAIRES (CORRIGÉES)
// ============================================================================

/**
 * @brief Affiche un message d'erreur de validation.
 */
void MainWindow::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Validation du Formulaire", message);
}

/**
 * @brief Valide le format de l'email.
 */
bool MainWindow::validerEmail(const QString &email)
{
    QRegularExpression rx("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return rx.match(email).hasMatch();
}

/**
 * @brief Génère le contenu HTML d'un email réel.
 */
QString MainWindow::genererMessageReel(const QString &prenom)
{
    return QString(
        "<html><body>"
        "<h2>Cher/Chère %1,</h2>"
        "<p>Nous sommes ravis de vous contacter de la part de Smart Studio.</p>"
        "<p>Découvrez notre offre spéciale pour les clients privilégiés !</p>"
        "<p>Cordialement,</p>"
        "<p>L'équipe Smart Studio</p>"
        "</body></html>"
    ).arg(prenom);
}

QString MainWindow::genererMessageAutomatique(const QString &nomClient, const QString &typeMessage)
{
    Q_UNUSED(typeMessage); // Marquer comme non utilisé si vous n'implémentez pas de logique de type

    QString prenom = nomClient.split(" ").value(0);
    return QString("Cher/Chère %1,\n\nCeci est un message automatique de Smart Studio...").arg(prenom);
}

QString MainWindow::corrigerEmail(const QString &email)
{
    // Logique de correction de base (à implémenter)
    return email.toLower().trimmed();
}

QVector<QString> MainWindow::obtenirDestinataires()
{
    // Logique pour obtenir la liste des emails de la base de données
    QVector<QString> emails;
    QSqlQuery query("SELECT EMAIL FROM client WHERE STATUT = 'Actif'");
    while(query.next()) {
        emails.append(query.value(0).toString());
    }
    return emails;
}

// ============================================================================
// GESTION CLIENTS (EXISTANT ET CORRIGÉ)
// ============================================================================

void MainWindow::refreshClientTable()
{
    QSqlQuery query;
    QString statutFilter = ui->activeClientsOnly->isChecked() ? "WHERE STATUT = 'Actif'" : "";

    query.prepare("SELECT ID, NOM_PRENOM, EMAIL, TELEPHONE, DATE_AJOUT, STATUT FROM CLIENT " + statutFilter + " ORDER BY ID DESC");

    if (query.exec()) {
        ui->clientTable->setRowCount(0);
        int row = 0;
        QStringList headers = {"ID", "Nom & Prénom", "Email", "Téléphone", "Date Ajout", "Statut"};
        ui->clientTable->setColumnCount(headers.size());
        ui->clientTable->setHorizontalHeaderLabels(headers);

        while (query.next()) {
            ui->clientTable->insertRow(row);
            for(int col=0; col<6; ++col) {
                ui->clientTable->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
            }
            row++;
        }
        ui->clientTable->resizeColumnsToContents();
        updateClientStats(); // Mise à jour des stats après refresh
        mettreAJourStatutVisuel();
    } else {
        qDebug() << "❌ Erreur SQL lors du refresh client:" << query.lastError().text();
    }
}

void MainWindow::updateClientStats()
{
    QSqlQuery query;
    int totalClients = 0;
    int activeClients = 0;
    int newThisMonth = 0;

    // Calculs des données de base (EXISTANT)
    query.exec("SELECT COUNT(*) FROM client");
    if (query.next()) {
        totalClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE statut = 'Actif'");
    if (query.next()) {
        activeClients = query.value(0).toInt();
    }

    query.exec("SELECT COUNT(*) FROM client WHERE date_ajout >= ADD_MONTHS(TRUNC(SYSDATE, 'MM'), 0)"); // Utilisation de fonctions Oracle
    if (query.next()) {
        newThisMonth = query.value(0).toInt();
    }

    // Calculs des pourcentages (EXISTANT)
    double activePercentage = (totalClients > 0) ? (activeClients * 100.0) / totalClients : 0.0;
    double monthlyGrowthPercentage = (totalClients > 0) ? (newThisMonth * 100.0) / totalClients : 0.0;

    // Formatage des textes (EXISTANT)
    ui->totalClientsLabel->setText(QString::number(totalClients));
    ui->activeClientsLabel->setText(QString("%1\n%2% Actifs").arg(activeClients).arg(activePercentage, 0, 'f', 1));
    ui->newThisMonthLabel->setText(QString("%1\n%2% Ce mois").arg(newThisMonth).arg(monthlyGrowthPercentage, 0, 'f', 1));

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
    ui->deleteClientBtn->setEnabled(false); // Ajout: désactiver delete
    ui->selectedClientIdLabel->setText("Aucun");

    QPushButton *envoyerEmailBtn = findChild<QPushButton*>("envoyerEmailClientBtn");
    if (envoyerEmailBtn) envoyerEmailBtn->setEnabled(false);

    mettreAJourBoutonStatut();
}

bool MainWindow::validateClientForm()
{
    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    if(nomPrenom.isEmpty()) { showValidationError("Le nom et prénom sont obligatoires"); return false; }
    if(email.isEmpty()) { showValidationError("L'adresse email est obligatoire"); return false; }
    if(telephone.isEmpty()) { showValidationError("Le numéro de téléphone est obligatoire"); return false; }

    // Utilisation des méthodes de validation de la classe Client (si elles existent)
    if(!Client::validerNomPrenom(nomPrenom)) { showValidationError("Le nom est invalide"); return false; }
    if(!Client::validerEmail(email)) { showValidationError("L'adresse email n'est pas valide"); return false; }
    if(!Client::validerTelephone(telephone)) { showValidationError("Le numéro de téléphone n'est pas valide"); return false; }

    return true;
}

void MainWindow::on_addClientBtn_clicked()
{
    if(!validateClientForm()) { return; }

    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    // Utilisation de la classe Client (préférable)
    Client newClient;
    newClient.setId(QDateTime::currentDateTime().toSecsSinceEpoch() % 100000); // Génération d'ID
    newClient.setNomPrenom(nomPrenom);
    newClient.setEmail(email);
    newClient.setTelephone(telephone);
    newClient.setStatut("Actif");
    // La date est ajoutée dans la méthode Client::ajouter()

    if(newClient.ajouter()) {
        QMessageBox::information(this, "Succès", "Client ajouté avec succès");
        refreshClientTable();
        clearClientForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout. Erreur SQL: " + newClient.lastError.text());
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
    // CORRECTION : Récupérer l'ID de la première colonne (index 0)
    int id = ui->clientTable->item(row, 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation",
                                     "Êtes-vous sûr de vouloir supprimer ce client?",
                                     QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        Client client;
        // CORRECTION : Supprimer par ID
        bool test = client.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Client supprimé avec succès");
            refreshClientTable();
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
    // CORRECTION : Utilisation de la bonne signature de modifier
    bool test = client.modifier(currentClientId, nomPrenom, email, telephone);

    if(test) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès");
        refreshClientTable();
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
    // Simplification : utiliser la fonction de recherche de Client si elle existe
    Client c;
    c.rechercher(ui->clientTable, text); // Assumer que Client::rechercher met à jour la QTableWidget
}

void MainWindow::on_clientTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int row = item->row();
    currentClientId = ui->clientTable->item(row, 0)->text().toInt();
    QString nomPrenom = ui->clientTable->item(row, 1)->text();
    QString email = ui->clientTable->item(row, 2)->text();
    QString telephone = ui->clientTable->item(row, 3)->text();

    ui->clientNameEdit->setText(nomPrenom);
    ui->clientEmailEdit->setText(email);
    ui->clientPhoneEdit->setText(telephone);

    ui->selectedClientIdLabel->setText(QString::number(currentClientId));
    ui->addClientBtn->setEnabled(false);
    ui->editClientBtn->setEnabled(true);
    ui->deleteClientBtn->setEnabled(true); // Activer le bouton delete

    // ACTIVER LE BOUTON ENVOYER EMAIL
    QPushButton *envoyerEmailBtn = findChild<QPushButton*>("envoyerEmailClientBtn");
    if (envoyerEmailBtn) {
        envoyerEmailBtn->setEnabled(true);
    }
    mettreAJourBoutonStatut();
}

void MainWindow::envoyerEmailClient(const QString &nomPrenom, const QString &email)
{
    // Logique d'envoi d'email déjà implémentée dans votre code fourni
    if (!validerEmail(email)) {
        QMessageBox::warning(this, "Email invalide", QString("L'email de %1 n'est pas valide:\n%2").arg(nomPrenom).arg(email));
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirmation d'envoi",
        QString("Voulez-vous envoyer un email RÉEL à :\n\n👤 %1\n📧 %2\n\nCet email sera envoyé via EmailJS.").arg(nomPrenom).arg(email),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        QString prenom = nomPrenom.split(" ").first();
        QString sujet = QString("Smart Studio - Offre spéciale pour %1").arg(prenom);
        QString message = genererMessageReel(prenom);

        QVector<QString> destinataires = {email};
        emailManager->envoyerEmailMultiple(destinataires, sujet, message);

        QMessageBox::information(this, "Envoi démarré",
                                 QString("L'email a été envoyé à :\n\n👤 %1\n📧 %2\n\nVous recevrez une confirmation quand l'envoi sera terminé.").arg(nomPrenom).arg(email));
    }
}

void MainWindow::on_envoyerEmailClientBtn_clicked()
{
    if (currentClientId != -1) {
        int row = ui->clientTable->currentRow();
        QString nomPrenom = ui->clientTable->item(row, 1)->text();
        QString email = ui->clientTable->item(row, 2)->text();
        envoyerEmailClient(nomPrenom, email);
    }
}

void MainWindow::on_clearFormBtn_clicked() { clearClientForm(); }

void MainWindow::on_refreshTableBtn_clicked() { refreshClientTable(); }

void MainWindow::on_exportPdfBtn_clicked()
{
    // Logique d'export PDF déjà implémentée dans votre code fourni
    QSqlQuery countQuery("SELECT COUNT(*) FROM client");
    if (countQuery.next() && countQuery.value(0).toInt() == 0) {
        QMessageBox::warning(this, "Export PDF", "Aucun client à exporter.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(
        this, "Exporter les clients en PDF",
        QDir::homePath() + "/clients_smart_studio.pdf",
        "Fichiers PDF (*.pdf)"
        );

    if (fileName.isEmpty()) { return; }
    if (!fileName.endsWith(".pdf", Qt::CaseInsensitive)) { fileName += ".pdf"; }

    PdfExporter exporter;
    bool success = exporter.exportClientsToPdf(fileName);

    if (success) {
        QMessageBox::information(this, "Export PDF", "✅ Export réussi!\nFichier sauvegardé: " + fileName);
    } else {
        QMessageBox::critical(this, "Export PDF", "❌ Erreur lors de l'export PDF.");
    }
}

void MainWindow::on_activeClientsOnly_toggled(bool checked) { refreshClientTable(); }

// ============================================================================
// GESTION STATUT CLIENT (NOUVELLES DÉFINITIONS)
// ============================================================================

void MainWindow::ajouterBoutonStatut()
{
    QPushButton *toggleBtn = new QPushButton("Toggle Statut", this);
    toggleBtn->setObjectName("toggleStatutBtn");
    toggleBtn->setEnabled(false);
    toggleBtn->setStyleSheet("QPushButton {padding: 10px; border-radius: 5px; font-weight: bold;}");

    // Ajout dans le layout (à adapter à votre UI)
    QHBoxLayout *boutonsLayout = nullptr;
    QLayout *layout = ui->groupBox->layout();
    if (layout) {
         QLayoutItem *item = layout->itemAt(1);
         if(item && item->layout()){
             boutonsLayout = qobject_cast<QHBoxLayout*>(item->layout());
         }
    }
    if (boutonsLayout) {
        boutonsLayout->insertWidget(0, toggleBtn); // Avant le bouton email/chatbot
    }
}

void MainWindow::mettreAJourBoutonStatut()
{
    QPushButton *toggleBtn = findChild<QPushButton*>("toggleStatutBtn");
    if (!toggleBtn) return;

    if (currentClientId == -1) {
        toggleBtn->setEnabled(false);
        toggleBtn->setText("Toggle Statut");
        toggleBtn->setStyleSheet("background-color: #BDC3C7; color: #7F8C8D;");
        return;
    }

    // Récupérer le statut actuel du client sélectionné
    int row = ui->clientTable->currentRow();
    if (row < 0 || row >= ui->clientTable->rowCount()) return;

    QString statut = ui->clientTable->item(row, 5)->text(); // Assumer que la colonne 5 est le statut

    if (statut == "Actif") {
        toggleBtn->setText("Désactiver Client");
        toggleBtn->setStyleSheet("background-color: #E74C3C; color: white; border-radius: 5px; padding: 10px; font-weight: bold;");
    } else {
        toggleBtn->setText("Activer Client");
        toggleBtn->setStyleSheet("background-color: #2ECC71; color: white; border-radius: 5px; padding: 10px; font-weight: bold;");
    }
    toggleBtn->setEnabled(true);
}

void MainWindow::on_toggleStatutBtn_clicked()
{
    if (currentClientId == -1) return;
    basculerStatutClient();
}

void MainWindow::basculerStatutClient()
{
    if (currentClientId == -1) return;

    int row = ui->clientTable->currentRow();
    QString currentStatut = ui->clientTable->item(row, 5)->text();
    QString nouveauStatut = (currentStatut == "Actif") ? "Inactif" : "Actif";

    QSqlQuery query;
    query.prepare("UPDATE client SET statut = :statut WHERE id = :id");
    query.bindValue(":statut", nouveauStatut);
    query.bindValue(":id", currentClientId);

    if (query.exec()) {
        QMessageBox::information(this, "Statut mis à jour", "Statut changé de " + currentStatut + " à " + nouveauStatut);
        refreshClientTable();
    } else {
        QMessageBox::critical(this, "Erreur Statut", "Échec de la mise à jour du statut: " + query.lastError().text());
    }
}

void MainWindow::mettreAJourStatutVisuel()
{
    // Fonction vide, à implémenter si vous avez des indicateurs visuels autres que le bouton
}


// ============================================================================
// GESTION EMPLOYÉS (EXISTANT ET COMPLÉTÉ)
// ============================================================================

void MainWindow::refreshEmployeTable()
{
    Employe e;
    // CORRECTION : Employe::afficher doit retourner QSqlQuery pour être compatible
    QSqlQuery query = e.afficher(); // On assume que Employe::afficher() retourne QSqlQuery

    if (query.exec()) {
        ui->employeTable->setRowCount(0);

        QStringList headers;
        headers << "ID" << "Nom" << "Prénom" << "Email" << "Téléphone"
                << "Poste" << "Salaire" << "Date Embauche" << "Statut";
        ui->employeTable->setColumnCount(headers.size());
        ui->employeTable->setHorizontalHeaderLabels(headers);

        int row = 0;
        while (query.next()) {
            ui->employeTable->insertRow(row);
            for (int col = 0; col < headers.size(); ++col) {
                QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
                ui->employeTable->setItem(row, col, item);
            }
            row++;
        }
        ui->employeTable->resizeColumnsToContents();
    } else {
        qDebug() << "❌ Erreur SQL refresh employe:" << query.lastError().text();
    }
}

void MainWindow::loadEmployees() { refreshEmployeTable(); }

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
    ui->deleteEmployeBtn->setEnabled(false);
    ui->selectedEmployeIdLabel->setText("Aucun");
}

bool MainWindow::validateEmployeForm()
{
    // Logique de validation existante
    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    QString salaire = ui->employeSalaireEdit->text().trimmed();

    if(nomPrenom.isEmpty() || email.isEmpty() || telephone.isEmpty() || poste.isEmpty() || salaire.isEmpty()) {
        showValidationError("Tous les champs doivent être remplis");
        return false;
    }

    if(nomPrenom.length() < 2) { showValidationError("Le nom est trop court"); return false; }
    if(!Employe::validerEmail(email)) { showValidationError("L'adresse email n'est pas valide"); return false; }

    // Validation du salaire (EXISTANT)
    bool ok;
    double salaireValue = salaire.toDouble(&ok);
    if(!ok || salaireValue <= 0) { showValidationError("Le salaire doit être un nombre positif"); return false; }

    return true;
}

void MainWindow::on_addEmployeBtn_clicked()
{
    if(!validateEmployeForm()) { return; }

    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    double salaire = ui->employeSalaireEdit->text().toDouble();

    QString nom = nomPrenom;
    QString prenom = "";
    if(nomPrenom.contains(" ")) {
        QStringList parts = nomPrenom.split(" ");
        nom = parts[0];
        prenom = parts.mid(1).join(" ");
    }

    int id = QDateTime::currentDateTime().toSecsSinceEpoch() % 100000;

    Employe newEmploye;
    newEmploye.setId(id);
    newEmploye.setNom(nom);
    newEmploye.setPrenom(prenom);
    newEmploye.setEmail(email);
    newEmploye.setTelephone(telephone);
    newEmploye.setRole(poste);
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
        QMessageBox::critical(this, "Erreur", "Échec de l'ajout de l'employé. Erreur: " + newEmploye.lastError.text());
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

    if(!validateEmployeForm()) { return; }

    QString nomPrenom = ui->employeNameEdit->text().trimmed();
    QString email = ui->employeEmailEdit->text().trimmed();
    QString telephone = ui->employePhoneEdit->text().trimmed();
    QString poste = ui->employePosteEdit->text().trimmed();
    double salaire = ui->employeSalaireEdit->text().toDouble();

    QString nom = nomPrenom;
    QString prenom = "";
    if(nomPrenom.contains(" ")) {
        QStringList parts = nomPrenom.split(" ");
        nom = parts[0];
        prenom = parts.mid(1).join(" ");
    }

    Employe employe;
    employe.setId(currentEmployeId);
    employe.setNom(nom);
    employe.setPrenom(prenom);
    employe.setEmail(email);
    employe.setTelephone(telephone);
    employe.setRole(poste);
    employe.setSalaire(salaire);

    // CORRECTION : Assurer que Employe::modifier prend les arguments nécessaires ou est appelé correctement
    bool test = employe.modifier();

    if(test) {
        QMessageBox::information(this, "Succès", "Employé modifié avec succès");
        refreshEmployeTable();
        clearEmployeForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de l'employé.");
    }
}

void MainWindow::on_searchEmployeLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshEmployeTable();
        return;
    }
    Employe e;
    e.rechercher(ui->employeTable, text); // Assumer que Employe::rechercher met à jour la QTableWidget
}

void MainWindow::on_employeTable_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;

    int row = item->row();
    currentEmployeId = ui->employeTable->item(row, 0)->text().toInt();

    // Remplir le formulaire
    QString nom = ui->employeTable->item(row, 1)->text();
    QString prenom = ui->employeTable->item(row, 2)->text();
    ui->employeNameEdit->setText(nom + " " + prenom);
    ui->employeEmailEdit->setText(ui->employeTable->item(row, 3)->text());
    ui->employePhoneEdit->setText(ui->employeTable->item(row, 4)->text());
    ui->employePosteEdit->setText(ui->employeTable->item(row, 5)->text());
    ui->employeSalaireEdit->setText(ui->employeTable->item(row, 6)->text());

    ui->selectedEmployeIdLabel->setText(QString::number(currentEmployeId));
    ui->addEmployeBtn->setEnabled(false);
    ui->editEmployeBtn->setEnabled(true);
    ui->deleteEmployeBtn->setEnabled(true);
}

void MainWindow::on_clearEmployeFormBtn_clicked() { clearEmployeForm(); }

void MainWindow::on_refreshEmployeTableBtn_clicked() { refreshEmployeTable(); }


// ============================================================================
// GESTION PROJETS (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::refreshProjetTable()
{
    Projet p;
    QSqlQuery query = p.afficher(); // Assumer que Projet::afficher retourne QSqlQuery
    if (query.exec()) {
        ui->projetTable->setRowCount(0);
        // ... (Logique de remplissage de la table)
    }
}

void MainWindow::clearProjetForm() { ui->clearProjetFormBtn->setText("Formulaire Projet effacé"); currentProjetId = -1; }
bool MainWindow::validateProjetForm() { return true; }
void MainWindow::on_addProjetBtn_clicked() { QMessageBox::information(this, "Projets", "Ajout Projet non implémenté."); }
void MainWindow::on_deleteProjetBtn_clicked() { QMessageBox::information(this, "Projets", "Suppression Projet non implémentée."); }
void MainWindow::on_editProjetBtn_clicked() { QMessageBox::information(this, "Projets", "Modification Projet non implémentée."); }
void MainWindow::on_searchProjetLineEdit_textChanged(const QString &text) { Projet p; p.rechercher(ui->projetTable, text); }
void MainWindow::on_projetTable_itemClicked(QTableWidgetItem *item) { if(item) currentProjetId = ui->projetTable->item(item->row(), 0)->text().toInt(); }
void MainWindow::on_clearProjetFormBtn_clicked() { clearProjetForm(); }
void MainWindow::on_refreshProjetTableBtn_clicked() { refreshProjetTable(); }


// ============================================================================
// GESTION FINANCES (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::refreshFinanceTable()
{
    Finance f;
    QSqlQuery query = f.afficher(); // Assumer que Finance::afficher retourne QSqlQuery
    if (query.exec()) {
        ui->financeTable->setRowCount(0);
        // ... (Logique de remplissage de la table)
    }
}

void MainWindow::clearFinanceForm() { ui->clearFinanceFormBtn->setText("Formulaire Finance effacé"); currentFinanceId = -1; }
bool MainWindow::validateFinanceForm() { return true; }
void MainWindow::on_addFinanceBtn_clicked() { QMessageBox::information(this, "Finances", "Ajout Finance non implémenté."); }
void MainWindow::on_deleteFinanceBtn_clicked() { QMessageBox::information(this, "Finances", "Suppression Finance non implémentée."); }
void MainWindow::on_editFinanceBtn_clicked() { QMessageBox::information(this, "Finances", "Modification Finance non implémentée."); }
void MainWindow::on_searchFinanceLineEdit_textChanged(const QString &text) { Finance f; f.rechercher(ui->financeTable, text); }
void MainWindow::on_financeTable_itemClicked(QTableWidgetItem *item) { if(item) currentFinanceId = ui->financeTable->item(item->row(), 0)->text().toInt(); }
void MainWindow::on_clearFinanceFormBtn_clicked() { clearFinanceForm(); }
void MainWindow::on_refreshFinanceTableBtn_clicked() { refreshFinanceTable(); }

void MainWindow::creerStatistiquesVisuelles() { /* À implémenter */ }
void MainWindow::mettreAJourStatistiquesVisuelles() { /* À implémenter */ }
void MainWindow::creerIndicateursCirculaires() { /* À implémenter */ }
void MainWindow::mettreAJourIndicateursCirculaires() { /* À implémenter */ }
void MainWindow::creerStatistiquesCirculaires() { /* À implémenter */ }
void MainWindow::mettreAJourStatistiquesCirculaires() { /* À implémenter */ }
void MainWindow::appliquerStyleModerne() { /* À implémenter */ }


// ============================================================================
// GESTION ÉQUIPEMENTS (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::refreshEquipementTable()
{
    Equipement e;
    QSqlQuery query = e.afficher(); // Assumer que Equipement::afficher retourne QSqlQuery
    if (query.exec()) {
        ui->equipementTable->setRowCount(0);
        // ... (Logique de remplissage de la table)
    }
}

void MainWindow::clearEquipementForm() { ui->clearEquipementFormBtn->setText("Formulaire Équipement effacé"); currentEquipementId = -1; }
bool MainWindow::validateEquipementForm() { return true; }
void MainWindow::on_addEquipementBtn_clicked() { QMessageBox::information(this, "Équipements", "Ajout Équipement non implémenté."); }
void MainWindow::on_deleteEquipementBtn_clicked() { QMessageBox::information(this, "Équipements", "Suppression Équipement non implémentée."); }
void MainWindow::on_editEquipementBtn_clicked() { QMessageBox::information(this, "Équipements", "Modification Équipement non implémentée."); }
void MainWindow::on_searchEquipementLineEdit_textChanged(const QString &text) { Equipement e; e.rechercher(ui->equipementTable, text); }
void MainWindow::on_equipementTable_itemClicked(QTableWidgetItem *item) { if(item) currentEquipementId = ui->equipementTable->item(item->row(), 0)->text().toInt(); }
void MainWindow::on_clearEquipementFormBtn_clicked() { clearEquipementForm(); }
void MainWindow::on_refreshEquipementTableBtn_clicked() { refreshEquipementTable(); }


// ============================================================================
// GESTION MAILING (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::refreshMailingTable() { /* Logique de rafraîchissement */ }
void MainWindow::clearMailingForm() { /* Logique d'effacement */ }
bool MainWindow::validateMailingForm() { return true; }
void MainWindow::initialiserInterfaceMailing() { /* Logique d'initialisation */ }
void MainWindow::actualiserStatistiquesMailing() { /* Logique de stats */ }
void MainWindow::on_addMailingBtn_clicked() { QMessageBox::information(this, "Mailing", "Ajout Mailing non implémenté."); }
void MainWindow::on_editMailingBtn_clicked() { QMessageBox::information(this, "Mailing", "Modification Mailing non implémentée."); }
void MainWindow::on_sendMailingBtn_clicked() { QMessageBox::information(this, "Mailing", "Envoi de masse non implémenté."); }
void MainWindow::on_sendTestMailBtn_clicked() { QMessageBox::information(this, "Mailing", "Envoi de test non implémenté."); }
void MainWindow::on_searchMailingLineEdit_textChanged(const QString &text) { /* Logique de recherche */ }
void MainWindow::on_mailingTable_itemClicked(QTableWidgetItem *item) { if(item) currentMailingId = ui->mailingTable->item(item->row(), 0)->text().toInt(); }
void MainWindow::on_clearMailingFormBtn_clicked() { clearMailingForm(); }
void MainWindow::on_refreshMailingTableBtn_clicked() { refreshMailingTable(); }

// ============================================================================
// SLOTS EMAILS ET PROGRESSION (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::onEmailEnvoye(const QString& email, bool succes, const QString& details)
{
    qDebug() << "Résultat envoi email à" << email << ":" << (succes ? "SUCCÈS" : "ÉCHEC") << details;
}

void MainWindow::onProgressionEnvoi(int valeur, int maximum)
{
    // Utiliser la fonction générique
    onProgression((maximum > 0) ? (valeur * 100 / maximum) : 0);
}

void MainWindow::onEnvoiTermine()
{
    statusBar()->showMessage("Envoi d'emails terminé.", 5000);
}

void MainWindow::onErreurEmail(const QString &message)
{
    QMessageBox::critical(this, "Erreur d'Envoi Email", message);
}

void MainWindow::onProgression(int pourcentage)
{
    statusBar()->showMessage(QString("Envoi en cours : %1%").arg(pourcentage));
}

// ============================================================================
// SLOTS CHATBOT ET ACTIONS (DÉFINITIONS MINIMALES)
// ============================================================================

void MainWindow::on_chatbotBtn_clicked()
{
    if (chatbotDialog) {
        chatbotDialog->exec();
    }
}

void MainWindow::on_actionAlerteRetard_triggered()
{
    QMessageBox::information(this, "Action", "Alerte de Retard Déclenchée (Fenêtre à implémenter).");
    // AlerteRetardDialog alerte(this);
    // alerte.exec();
}

void MainWindow::on_actionHistorique_triggered()
{
    QMessageBox::information(this, "Action", "Historique Déclenché (Fenêtre à implémenter).");
    // HistoriqueDialog historique(this);
    // historique.exec();
}
