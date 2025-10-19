#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // === Menu vertical à gauche ===
    QVBoxLayout *menuLayout = new QVBoxLayout();
    QStringList menuButtons = {"Employés", "Client", "Équipement", "Projet", "Finance"};
    for (const QString &name : menuButtons) {
        QPushButton *btn = new QPushButton(name);
        menuLayout->addWidget(btn);
    }
    menuLayout->addStretch();

    // === Tabs à droite ===
    tabs = new QTabWidget();

    // --- Onglet Équipement ---
    QWidget *equipementTab = new QWidget();
    QVBoxLayout *equipLayout = new QVBoxLayout(equipementTab);

    // Ligne boutons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(new QPushButton("ajouter"));
    btnLayout->addWidget(new QPushButton("modifier"));
    btnLayout->addWidget(new QPushButton("effacer"));
    btnLayout->addWidget(new QPushButton("Exporter PDF"));
    equipLayout->addLayout(btnLayout);

    // Ligne recherche
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *lblSearch = new QLabel("Search");
    searchBar = new QLineEdit();
    QPushButton *searchBtn = new QPushButton("🔍");
    sortCombo = new QComboBox();
    sortCombo->addItem("Par Nom");
    sortCombo->addItem("Par Type");
    sortCombo->addItem("Par Date");

    searchLayout->addWidget(lblSearch);
    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(searchBtn);
    searchLayout->addStretch();
    searchLayout->addWidget(sortCombo);
    equipLayout->addLayout(searchLayout);

    // Tableau Equipement
    equipTable = new QTableWidget(0, 5);
    QStringList headers = {"nom", "type", "état", "date debut", "date fin"};
    equipTable->setHorizontalHeaderLabels(headers);
    equipLayout->addWidget(equipTable);

    tabs->addTab(equipementTab, "Projet");

    // --- Onglet Calendrier ---
    QWidget *calendrierTab = new QWidget();
    QVBoxLayout *calendarLayout = new QVBoxLayout(calendrierTab);

    // Ajout du calendrier
    calendarWidget = new QCalendarWidget();
    calendarLayout->addWidget(calendarWidget);

    // Optionnel: Ajouter des contrôles supplémentaires pour le calendrier
    QHBoxLayout *calendarControls = new QHBoxLayout();
    QPushButton *todayBtn = new QPushButton("Aujourd'hui");
    QPushButton *addEventBtn = new QPushButton("Ajouter Événement");

    calendarControls->addWidget(todayBtn);
    calendarControls->addWidget(addEventBtn);
    calendarControls->addStretch();

    calendarLayout->addLayout(calendarControls);

    tabs->addTab(calendrierTab, "Calendrier");

    // --- Onglet Historique ---
    QWidget *historiqueTab = new QWidget();
    QVBoxLayout *histLayout = new QVBoxLayout(historiqueTab);

    histTable = new QTableWidget(0, 5);
    histTable->setHorizontalHeaderLabels(headers);
    histLayout->addWidget(histTable);

    tabs->addTab(historiqueTab, "Etat");

    // Ajouter menu gauche + tabs à la fenêtre
    mainLayout->addLayout(menuLayout, 1);
    mainLayout->addWidget(tabs, 4);
}
