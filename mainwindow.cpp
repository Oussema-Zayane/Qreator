#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QSqlQuery>
#include <QHeaderView>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentClientId(-1)
{
    ui->setupUi(this);

    setWindowTitle("Gestion des Clients - CRUD");

    // Configuration du tableau
    ui->clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Configuration des validateurs de saisie
    // Validateur pour le nom/prénom (lettres, espaces, apostrophes)
    QRegularExpressionValidator *nameValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-ZÀ-ÿ]+([ '-][a-zA-ZÀ-ÿ]+)*$"), this);
    ui->clientNameEdit->setValidator(nameValidator);

    // Validateur pour l'email
    QRegularExpressionValidator *emailValidator = new QRegularExpressionValidator(QRegularExpression("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"), this);
    ui->clientEmailEdit->setValidator(emailValidator);

    // Validateur pour le téléphone (format français)
    QRegularExpressionValidator *phoneValidator = new QRegularExpressionValidator(QRegularExpression("^(0[1-9])(?:[ _.-]?([0-9]{2})){4}$"), this);
    ui->clientPhoneEdit->setValidator(phoneValidator);

    // Initialiser l'affichage
    refreshTable();

    // Connecter les signaux et slots
    connect(ui->addClientBtn, &QPushButton::clicked, this, &MainWindow::on_addClientBtn_clicked);
    connect(ui->deleteClientBtn, &QPushButton::clicked, this, &MainWindow::on_deleteClientBtn_clicked);
    connect(ui->editClientBtn, &QPushButton::clicked, this, &MainWindow::on_editClientBtn_clicked);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_textChanged);
    connect(ui->clientTable, &QTableWidget::itemClicked, this, &MainWindow::on_clientTable_itemClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshTable()
{
    QSqlQuery query("SELECT id, nom_prenom, email, telephone, date_ajout, statut FROM client");

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
}

void MainWindow::clearForm()
{
    ui->clientNameEdit->clear();
    ui->clientEmailEdit->clear();
    ui->clientPhoneEdit->clear();
    currentClientId = -1;
    ui->addClientBtn->setEnabled(true);
    ui->editClientBtn->setEnabled(false);
}

bool MainWindow::validateForm()
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

void MainWindow::showValidationError(const QString& message)
{
    QMessageBox::warning(this, "Erreur de validation", message);
}

void MainWindow::on_addClientBtn_clicked()
{
    if(!validateForm()) {
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
        refreshTable();
        clearForm();
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
        bool test = client.supprimer(id);

        if(test) {
            QMessageBox::information(this, "Succès", "Client supprimé avec succès");
            refreshTable();
            clearForm();
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

    if(!validateForm()) {
        return;
    }

    // Récupération des données
    QString nomPrenom = ui->clientNameEdit->text().trimmed();
    QString email = ui->clientEmailEdit->text().trimmed();
    QString telephone = ui->clientPhoneEdit->text().trimmed();

    bool test = client.modifier(currentClientId, nomPrenom, email, telephone);

    if(test) {
        QMessageBox::information(this, "Succès", "Client modifié avec succès");
        refreshTable();
        clearForm();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du client. Vérifiez que les données sont valides.");
    }
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    if(text.isEmpty()) {
        refreshTable();
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
    int row = item->row();

    currentClientId = ui->clientTable->item(row, 0)->text().toInt();
    ui->clientNameEdit->setText(ui->clientTable->item(row, 1)->text());
    ui->clientEmailEdit->setText(ui->clientTable->item(row, 2)->text());
    ui->clientPhoneEdit->setText(ui->clientTable->item(row, 3)->text());

    // Activer le bouton modifier et désactiver le bouton ajouter
    ui->editClientBtn->setEnabled(true);
    ui->addClientBtn->setEnabled(false);
}
