#include "sidebar.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>

SideBar::SideBar(QWidget *parent) : QWidget(parent)
{
    setupUI();
}

void SideBar::setupUI()
{
    mainLayout = new QVBoxLayout(this);

    // Style de la sidebar
    setStyleSheet("QWidget { background-color: #2C3E50; }"
                  "QPushButton { background-color: #34495E; color: white; border: none; "
                  "padding: 15px; text-align: left; font-weight: bold; font-size: 14px; }"
                  "QPushButton:hover { background-color: #3498DB; }"
                  "QPushButton:pressed { background-color: #2980B9; }");

    // Création des boutons
    clientsBtn = new QPushButton("👥 Gestion Clients");
    employesBtn = new QPushButton("👨‍💼 Gestion Employés");
    projetsBtn = new QPushButton("📁 Gestion Projets");
    financesBtn = new QPushButton("💰 Gestion Finances");

    // Ajout des boutons au layout
    mainLayout->addWidget(clientsBtn);
    mainLayout->addWidget(employesBtn);
    mainLayout->addWidget(projetsBtn);
    mainLayout->addWidget(financesBtn);

    // Espaceur pour pousser les boutons vers le haut
    mainLayout->addStretch();

    // Connexions
    connect(clientsBtn, &QPushButton::clicked, this, &SideBar::onClientsClicked);
    connect(employesBtn, &QPushButton::clicked, this, &SideBar::onEmployesClicked);
    connect(projetsBtn, &QPushButton::clicked, this, &SideBar::onProjetsClicked);
    connect(financesBtn, &QPushButton::clicked, this, &SideBar::onFinancesClicked);
}

void SideBar::onClientsClicked() { emit menuClicked("Clients"); }
void SideBar::onEmployesClicked() { emit menuClicked("Employes"); }
void SideBar::onProjetsClicked() { emit menuClicked("Projets"); }
void SideBar::onFinancesClicked() { emit menuClicked("Finances"); }
