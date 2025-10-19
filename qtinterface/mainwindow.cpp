#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QCheckBox>
#include <QSplitter>
#include <QTextEdit>
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , equipmentWidget(nullptr)
    , employeeWidget(nullptr)
    , financeWidget(nullptr)
{
    ui->setupUi(this);

    // Set window title
    setWindowTitle("Section Client Interface Unifiée");

    // Configure table columns to stretch properly
    ui->clientTable->horizontalHeader()->setStretchLastSection(true);

    // Setup sidebar
    setupSidebar();

    // Setup all UIs
    setupEquipmentUI();
    setupEmployeeUI();
    setupFinanceUI();

    // Show client section by default
    showClientSection();
}

void MainWindow::setupSidebar()
{
    // Create sidebar widget
    QWidget *sidebar = new QWidget(this);
    sidebar->setFixedWidth(200);
    sidebar->setStyleSheet(
        "QWidget {"
        "    background-color: #2c3e50;"
        "    color: white;"
        "}"
        "QPushButton {"
        "    background-color: #34495e;"
        "    color: white;"
        "    border: none;"
        "    padding: 12px 15px;"
        "    text-align: left;"
        "    font-weight: bold;"
        "    border-radius: 5px;"
        "    margin: 2px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #3498db;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #2980b9;"
        "}"
        );

    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);

    // Title
    QLabel *titleLabel = new QLabel("GESTION", sidebar);
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: #3498db; padding: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    sidebarLayout->addWidget(titleLabel);

    // Menu buttons
    QPushButton *equipmentBtn = new QPushButton("Équipement", sidebar);
    QPushButton *employeeBtn = new QPushButton("Employé", sidebar);
    QPushButton *clientBtn = new QPushButton("Client", sidebar);
    QPushButton *projectBtn = new QPushButton("Projet", sidebar);
    QPushButton *financeBtn = new QPushButton("Finance", sidebar);

    // Connect buttons to slots
    connect(equipmentBtn, &QPushButton::clicked, this, &MainWindow::onEquipmentClicked);
    connect(employeeBtn, &QPushButton::clicked, this, &MainWindow::onEmployeeClicked);
    connect(clientBtn, &QPushButton::clicked, this, &MainWindow::onClientClicked);
    connect(projectBtn, &QPushButton::clicked, this, &MainWindow::onProjectClicked);
    connect(financeBtn, &QPushButton::clicked, this, &MainWindow::onFinanceClicked);

    // Add buttons to layout
    sidebarLayout->addWidget(equipmentBtn);
    sidebarLayout->addWidget(employeeBtn);
    sidebarLayout->addWidget(clientBtn);
    sidebarLayout->addWidget(projectBtn);
    sidebarLayout->addWidget(financeBtn);

    // Add spacer at the bottom
    sidebarLayout->addStretch();

    // Add sidebar to main layout
    ui->horizontalLayout->insertWidget(0, sidebar);
}

void MainWindow::setupEquipmentUI()
{
    equipmentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(equipmentWidget);

    // Title
    QLabel *titleLabel = new QLabel("Gestion des Équipements");
    titleLabel->setStyleSheet("font-size: 18pt; font-weight: bold; color: #2c3e50; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // Equipment form
    QGroupBox *formGroup = new QGroupBox("Informations Équipement");
    formGroup->setStyleSheet(ui->groupBox->styleSheet());
    QFormLayout *formLayout = new QFormLayout(formGroup);

    QLineEdit *nameEdit = new QLineEdit();
    QComboBox *typeCombo = new QComboBox();
    typeCombo->addItems({"Routeur", "Switch", "Serveur", "Ordinateur", "Imprimante", "Autre"});
    QLineEdit *modelEdit = new QLineEdit();
    QDateEdit *acquisitionDateEdit = new QDateEdit();
    acquisitionDateEdit->setCalendarPopup(true);
    QComboBox *statusCombo = new QComboBox();
    statusCombo->addItems({"Disponible", "En maintenance", "Hors service", "Réservé"});

    formLayout->addRow("Nom:", nameEdit);
    formLayout->addRow("Type:", typeCombo);
    formLayout->addRow("Modèle:", modelEdit);
    formLayout->addRow("Date d'acquisition:", acquisitionDateEdit);
    formLayout->addRow("Statut:", statusCombo);

    mainLayout->addWidget(formGroup);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Ajouter");
    QPushButton *modifyBtn = new QPushButton("Modifier");
    QPushButton *deleteBtn = new QPushButton("Supprimer");
    QPushButton *notifyBtn = new QPushButton("Notifier");
    QPushButton *historyBtn = new QPushButton("Historique");

    addBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    modifyBtn->setStyleSheet(ui->editClientBtn->styleSheet());
    deleteBtn->setStyleSheet(ui->deleteClientBtn->styleSheet());
    notifyBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    historyBtn->setStyleSheet(ui->editClientBtn->styleSheet());

    buttonLayout->addWidget(addBtn);
    buttonLayout->addWidget(modifyBtn);
    buttonLayout->addWidget(deleteBtn);
    buttonLayout->addWidget(notifyBtn);
    buttonLayout->addWidget(historyBtn);

    mainLayout->addLayout(buttonLayout);

    // Equipment table
    QTableWidget *equipmentTable = new QTableWidget();
    equipmentTable->setColumnCount(6);
    equipmentTable->setHorizontalHeaderLabels({"Nom", "Type", "Modèle", "Date acquisition", "Statut", "Disponibilité"});
    equipmentTable->setStyleSheet(ui->clientTable->styleSheet());
    equipmentTable->horizontalHeader()->setStretchLastSection(true);

    mainLayout->addWidget(equipmentTable);

    // Statistics
    QHBoxLayout *statsLayout = new QHBoxLayout();
    QLabel *totalLabel = new QLabel("Total équipements: 0");
    QLabel *availableLabel = new QLabel("Disponibles: 0");
    QLabel *maintenanceLabel = new QLabel("En maintenance: 0");

    totalLabel->setStyleSheet(ui->totalClientsLabel->styleSheet());
    availableLabel->setStyleSheet(ui->activeClientsLabel->styleSheet());
    maintenanceLabel->setStyleSheet(ui->newClientsLabel->styleSheet());

    statsLayout->addWidget(totalLabel);
    statsLayout->addWidget(availableLabel);
    statsLayout->addWidget(maintenanceLabel);
    statsLayout->addStretch();

    mainLayout->addLayout(statsLayout);

    // Add to main layout but hide initially
    ui->horizontalLayout->addWidget(equipmentWidget);
    equipmentWidget->setVisible(false);
}

void MainWindow::setupEmployeeUI()
{
    employeeWidget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(employeeWidget);

    // Left side - Employee management
    QWidget *leftWidget = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    // Title
    QLabel *titleLabel = new QLabel("Gestion des Employés — Smart Studio");
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: #2c3e50; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(titleLabel);

    // Employee form
    QGroupBox *formGroup = new QGroupBox("Informations Employés");
    formGroup->setStyleSheet(ui->groupBox->styleSheet());
    QFormLayout *formLayout = new QFormLayout(formGroup);

    QLineEdit *lastNameEdit = new QLineEdit();
    QLineEdit *firstNameEdit = new QLineEdit();
    QLineEdit *emailEdit = new QLineEdit();
    QLineEdit *phoneEdit = new QLineEdit();
    QComboBox *roleCombo = new QComboBox();
    roleCombo->addItems({"Monteur", "Graphiste", "Rédacteur", "Tech Studio", "BV/Support"});
    QComboBox *scheduleCombo = new QComboBox();
    scheduleCombo->addItems({"Matin", "Soir", "Complet"});
    QComboBox *genderCombo = new QComboBox();
    genderCombo->addItems({"Homme", "Femme"});

    formLayout->addRow("Nom:", lastNameEdit);
    formLayout->addRow("Prénom:", firstNameEdit);
    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Téléphone:", phoneEdit);
    formLayout->addRow("Rôle:", roleCombo);
    formLayout->addRow("Horaires:", scheduleCombo);
    formLayout->addRow("Genre:", genderCombo);

    leftLayout->addWidget(formGroup);

    // Employee buttons
    QHBoxLayout *empButtonLayout = new QHBoxLayout();
    QPushButton *addEmpBtn = new QPushButton("Ajouter");
    QPushButton *modifyEmpBtn = new QPushButton("Modifier");
    QPushButton *deleteEmpBtn = new QPushButton("Supprimer");
    QPushButton *exportEmpBtn = new QPushButton("Exporter PDF");

    addEmpBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    modifyEmpBtn->setStyleSheet(ui->editClientBtn->styleSheet());
    deleteEmpBtn->setStyleSheet(ui->deleteClientBtn->styleSheet());
    exportEmpBtn->setStyleSheet(ui->exportPdfBtn->styleSheet());

    empButtonLayout->addWidget(addEmpBtn);
    empButtonLayout->addWidget(modifyEmpBtn);
    empButtonLayout->addWidget(deleteEmpBtn);
    empButtonLayout->addWidget(exportEmpBtn);

    leftLayout->addLayout(empButtonLayout);

    // Search
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *searchLabel = new QLabel("Rechercher:");
    searchLabel->setStyleSheet("font-weight: bold;");
    QLineEdit *searchEdit = new QLineEdit();
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    searchLayout->addStretch();

    leftLayout->addLayout(searchLayout);

    // Employee table
    QTableWidget *employeeTable = new QTableWidget();
    employeeTable->setColumnCount(7);
    employeeTable->setHorizontalHeaderLabels({"ID", "Nom", "Prénom", "Email", "Téléphone", "Rôle", "Horaires", "Genre"});
    employeeTable->setStyleSheet(ui->clientTable->styleSheet());
    employeeTable->horizontalHeader()->setStretchLastSection(true);

    leftLayout->addWidget(employeeTable);

    // Right side - Absences and Statistics
    QWidget *rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    // Absences section
    QGroupBox *absenceGroup = new QGroupBox("Gestion des Absences");
    absenceGroup->setStyleSheet(ui->groupBox->styleSheet());
    QFormLayout *absenceLayout = new QFormLayout(absenceGroup);

    QComboBox *absenceTypeCombo = new QComboBox();
    absenceTypeCombo->addItems({"Congé", "Maladie", "Formation", "Personnel"});
    QDateEdit *startDateEdit = new QDateEdit();
    startDateEdit->setCalendarPopup(true);
    QDateEdit *endDateEdit = new QDateEdit();
    endDateEdit->setCalendarPopup(true);
    QLineEdit *reasonEdit = new QLineEdit();

    absenceLayout->addRow("Type d'absence:", absenceTypeCombo);
    absenceLayout->addRow("Début:", startDateEdit);
    absenceLayout->addRow("Fin:", endDateEdit);
    absenceLayout->addRow("Raison:", reasonEdit);

    rightLayout->addWidget(absenceGroup);

    // Absence buttons
    QHBoxLayout *absenceButtonLayout = new QHBoxLayout();
    QPushButton *addAbsenceBtn = new QPushButton("Ajouter");
    QPushButton *modifyAbsenceBtn = new QPushButton("Modifier");
    QPushButton *deleteAbsenceBtn = new QPushButton("Supprimer");
    QPushButton *exportAbsenceBtn = new QPushButton("Exporter PDF");

    addAbsenceBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    modifyAbsenceBtn->setStyleSheet(ui->editClientBtn->styleSheet());
    deleteAbsenceBtn->setStyleSheet(ui->deleteClientBtn->styleSheet());
    exportAbsenceBtn->setStyleSheet(ui->exportPdfBtn->styleSheet());

    absenceButtonLayout->addWidget(addAbsenceBtn);
    absenceButtonLayout->addWidget(modifyAbsenceBtn);
    absenceButtonLayout->addWidget(deleteAbsenceBtn);
    absenceButtonLayout->addWidget(exportAbsenceBtn);

    rightLayout->addLayout(absenceButtonLayout);

    // Absence table
    QTableWidget *absenceTable = new QTableWidget();
    absenceTable->setColumnCount(6);
    absenceTable->setHorizontalHeaderLabels({"ID Employé", "Nom", "Type d'absence", "Début", "Fin", "Raison"});
    absenceTable->setStyleSheet(ui->clientTable->styleSheet());
    absenceTable->horizontalHeader()->setStretchLastSection(true);

    rightLayout->addWidget(absenceTable);

    // Statistics
    QGroupBox *statsGroup = new QGroupBox("Répartition des rôles");
    statsGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *statsLayout = new QVBoxLayout(statsGroup);

    QLabel *monteursLabel = new QLabel("Monteurs: 50%");
    QLabel *graphistesLabel = new QLabel("Graphistes: 25%");
    QLabel *redacteursLabel = new QLabel("Rédacteurs: 25%");
    QLabel *techLabel = new QLabel("Tech Studio: 0%");
    QLabel *supportLabel = new QLabel("BV/Support: 0%");

    statsLayout->addWidget(monteursLabel);
    statsLayout->addWidget(graphistesLabel);
    statsLayout->addWidget(redacteursLabel);
    statsLayout->addWidget(techLabel);
    statsLayout->addWidget(supportLabel);

    rightLayout->addWidget(statsGroup);

    // Add both sides to main layout
    mainLayout->addWidget(leftWidget, 2);
    mainLayout->addWidget(rightWidget, 1);

    // Add to main layout but hide initially
    ui->horizontalLayout->addWidget(employeeWidget);
    employeeWidget->setVisible(false);
}

void MainWindow::setupFinanceUI()
{
    financeWidget = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(financeWidget);

    // Left side - Dashboard
    QWidget *leftWidget = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);

    // Title
    QLabel *titleLabel = new QLabel("Smart digital content creation studio");
    titleLabel->setStyleSheet("font-size: 16pt; font-weight: bold; color: #2c3e50; margin: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    leftLayout->addWidget(titleLabel);

    // Dashboard section
    QGroupBox *dashboardGroup = new QGroupBox("DASHBOARD");
    dashboardGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *dashboardLayout = new QVBoxLayout(dashboardGroup);

    QHBoxLayout *dashboardButtons = new QHBoxLayout();
    QPushButton *addBtn = new QPushButton("Ajouter");
    QPushButton *deleteBtn = new QPushButton("Supprimer");
    QPushButton *modifyBtn = new QPushButton("Modifier");
    QPushButton *consultBtn = new QPushButton("Consulter");
    QPushButton *exportBtn = new QPushButton("Extraire en PDF");

    addBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    deleteBtn->setStyleSheet(ui->deleteClientBtn->styleSheet());
    modifyBtn->setStyleSheet(ui->editClientBtn->styleSheet());
    consultBtn->setStyleSheet(ui->addClientBtn->styleSheet());
    exportBtn->setStyleSheet(ui->exportPdfBtn->styleSheet());

    dashboardButtons->addWidget(addBtn);
    dashboardButtons->addWidget(deleteBtn);
    dashboardButtons->addWidget(modifyBtn);
    dashboardButtons->addWidget(consultBtn);
    dashboardButtons->addWidget(exportBtn);

    dashboardLayout->addLayout(dashboardButtons);
    leftLayout->addWidget(dashboardGroup);

    // Revenues section
    QGroupBox *revenueGroup = new QGroupBox("REVENUS");
    revenueGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *revenueLayout = new QVBoxLayout(revenueGroup);

    QTableWidget *revenueTable = new QTableWidget();
    revenueTable->setColumnCount(4);
    revenueTable->setHorizontalHeaderLabels({"Clients", "Projets", "Équipements", "Finance"});
    revenueTable->setStyleSheet(ui->clientTable->styleSheet());
    revenueTable->horizontalHeader()->setStretchLastSection(true);

    revenueLayout->addWidget(revenueTable);
    leftLayout->addWidget(revenueGroup);

    // Expenses section
    QGroupBox *expenseGroup = new QGroupBox("DÉPENSES");
    expenseGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *expenseLayout = new QVBoxLayout(expenseGroup);

    QTableWidget *expenseTable = new QTableWidget();
    expenseTable->setColumnCount(5);
    expenseTable->setHorizontalHeaderLabels({"Bénéfices", "Facture", "Client", "Date", "Montant"});
    expenseTable->setStyleSheet(ui->clientTable->styleSheet());
    expenseTable->horizontalHeader()->setStretchLastSection(true);

    expenseLayout->addWidget(expenseTable);
    leftLayout->addWidget(expenseGroup);

    // Right side - Distribution
    QWidget *rightWidget = new QWidget();
    QVBoxLayout *rightLayout = new QVBoxLayout(rightWidget);

    // Distribution section
    QGroupBox *distributionGroup = new QGroupBox("RÉPARTITION");
    distributionGroup->setStyleSheet(ui->groupBox->styleSheet());
    QFormLayout *distributionLayout = new QFormLayout(distributionGroup);

    QLabel *revenueLabel = new QLabel("Revenus: 0 €");
    QLabel *expenseLabel = new QLabel("Dépenses: 0 €");
    QLabel *profitLabel = new QLabel("Bénéfices: 0 €");
    QLabel *taxLabel = new QLabel("TVA: 0 €");

    distributionLayout->addRow(revenueLabel);
    distributionLayout->addRow(expenseLabel);
    distributionLayout->addRow(profitLabel);
    distributionLayout->addRow(taxLabel);

    rightLayout->addWidget(distributionGroup);

    // Charts placeholder
    QGroupBox *chartsGroup = new QGroupBox("GRAPHIQUES");
    chartsGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *chartsLayout = new QVBoxLayout(chartsGroup);

    QLabel *chartPlaceholder = new QLabel("Graphiques de répartition des finances");
    chartPlaceholder->setAlignment(Qt::AlignCenter);
    chartPlaceholder->setStyleSheet("color: #666; font-style: italic;");
    chartPlaceholder->setMinimumHeight(200);

    chartsLayout->addWidget(chartPlaceholder);
    rightLayout->addWidget(chartsGroup);

    // Financial summary
    QGroupBox *summaryGroup = new QGroupBox("RÉSUMÉ FINANCIER");
    summaryGroup->setStyleSheet(ui->groupBox->styleSheet());
    QVBoxLayout *summaryLayout = new QVBoxLayout(summaryGroup);

    QLabel *monthlyRevenue = new QLabel("Revenu mensuel: 0 €");
    QLabel *monthlyExpense = new QLabel("Dépense mensuelle: 0 €");
    QLabel *netProfit = new QLabel("Bénéfice net: 0 €");
    QLabel *growth = new QLabel("Croissance: 0%");

    summaryLayout->addWidget(monthlyRevenue);
    summaryLayout->addWidget(monthlyExpense);
    summaryLayout->addWidget(netProfit);
    summaryLayout->addWidget(growth);

    rightLayout->addWidget(summaryGroup);

    // Add both sides to main layout
    mainLayout->addWidget(leftWidget, 2);
    mainLayout->addWidget(rightWidget, 1);

    // Add to main layout but hide initially
    ui->horizontalLayout->addWidget(financeWidget);
    financeWidget->setVisible(false);
}

void MainWindow::onEquipmentClicked()
{
    showEquipmentSection();
}

void MainWindow::onEmployeeClicked()
{
    showEmployeeSection();
}

void MainWindow::onClientClicked()
{
    showClientSection();
}

void MainWindow::onProjectClicked()
{
    ui->splitter->setVisible(false);
    if (equipmentWidget) equipmentWidget->setVisible(false);
    if (employeeWidget) employeeWidget->setVisible(false);
    if (financeWidget) financeWidget->setVisible(false);
    setWindowTitle("Gestion des Projets");
}

void MainWindow::onFinanceClicked()
{
    showFinanceSection();
}

void MainWindow::showClientSection()
{
    ui->splitter->setVisible(true);
    if (equipmentWidget) equipmentWidget->setVisible(false);
    if (employeeWidget) employeeWidget->setVisible(false);
    if (financeWidget) financeWidget->setVisible(false);
    setWindowTitle("Section Client Interface Unifiée");
}

void MainWindow::showEquipmentSection()
{
    ui->splitter->setVisible(false);
    if (equipmentWidget) equipmentWidget->setVisible(true);
    if (employeeWidget) employeeWidget->setVisible(false);
    if (financeWidget) financeWidget->setVisible(false);
    setWindowTitle("Gestion des Équipements");
}

void MainWindow::showEmployeeSection()
{
    ui->splitter->setVisible(false);
    if (equipmentWidget) equipmentWidget->setVisible(false);
    if (employeeWidget) employeeWidget->setVisible(true);
    if (financeWidget) financeWidget->setVisible(false);
    setWindowTitle("Gestion des Employés — Smart Studio");
}

void MainWindow::showFinanceSection()
{
    ui->splitter->setVisible(false);
    if (equipmentWidget) equipmentWidget->setVisible(false);
    if (employeeWidget) employeeWidget->setVisible(false);
    if (financeWidget) financeWidget->setVisible(true);
    setWindowTitle("Smart digital content creation studio - Finance");
}

MainWindow::~MainWindow()
{
    delete ui;
}
