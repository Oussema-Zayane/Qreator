#include "historiquedialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QAbstractItemView>
//bibliothéque view inside view
#include <QMessageBox>

HistoriqueDialog::HistoriqueDialog(QWidget *parent)
    : QDialog(parent)
    , model(nullptr)
{
    setWindowTitle("📜 Historique des Transactions Supprimées");
    setMinimumSize(1000, 600);
    setModal(true);
    
    // Créer la table d'historique si elle n'existe pas
    createHistoriqueTable();
    
    setupUI();
    refreshTable();
}

HistoriqueDialog::~HistoriqueDialog()
{
    if (model) {
        delete model;
    }
}

bool HistoriqueDialog::createHistoriqueTable()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Base de données non connectée";
        return false;
    }
    
    QSqlQuery query(db);
    
    // Vérifier si la table existe déjà
    query.prepare("SELECT COUNT(*) FROM USER_TABLES WHERE TABLE_NAME = 'FINANCES_HISTORIQUE'");
    bool tableExists = false;
    if (query.exec() && query.next()) {
        tableExists = (query.value(0).toInt() > 0);
    }
    
    // Créer la table si elle n'existe pas
    if (!tableExists) {
        QString createTableSQL = 
            "CREATE TABLE FINANCES_HISTORIQUE ("
            "ID NUMBER PRIMARY KEY,"
            "REVENU NUMBER(10,2),"
            "DEPENSE NUMBER(10,2),"
            "BENEFICES NUMBER(10,2),"
            "TVA NUMBER(10,2),"
            "DELAI DATE,"
            "MODEPAIMENT VARCHAR2(50),"
            "STATUT VARCHAR2(50),"
            "DATE_SUPPRESSION TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "ROWID_ORIGINAL VARCHAR2(50))";
        
        if (!query.exec(createTableSQL)) {
            qDebug() << "Erreur lors de la création de la table d'historique:" << query.lastError().text();
            // La table existe peut-être déjà, continuer quand même
        } else {
            qDebug() << "Table FINANCES_HISTORIQUE créée avec succès";
        }
    }
    
    // Vérifier si la séquence existe
    query.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
    bool sequenceExists = false;
    if (query.exec() && query.next()) {
        sequenceExists = (query.value(0).toInt() > 0);
    }
    
    // Créer la séquence si elle n'existe pas
    if (!sequenceExists) {
        QString createSeqSQL = "CREATE SEQUENCE SEQ_FINANCES_HISTORIQUE START WITH 1 INCREMENT BY 1";
        if (!query.exec(createSeqSQL)) {
            qDebug() << "Erreur lors de la création de la séquence:" << query.lastError().text();
            // Vérifier à nouveau si la séquence existe maintenant
            QSqlQuery recheckQuery(db);
            recheckQuery.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
            if (recheckQuery.exec() && recheckQuery.next()) {
                sequenceExists = (recheckQuery.value(0).toInt() > 0);
            }
            if (!sequenceExists) {
                qDebug() << "Attention: La séquence n'a pas pu être créée. L'application utilisera une approche alternative.";
            }
        } else {
            qDebug() << "Séquence SEQ_FINANCES_HISTORIQUE créée avec succès";
        }
    }
    
    return true;
}

void HistoriqueDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Titre
    QLabel *titleLabel = new QLabel("📜 Historique des Transactions Supprimées", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50; padding: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Table view
    tableView = new QTableView(this);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet(
        "QTableView {"
        "    background-color: #ffffff;"
        "    border: 2px solid #e1e8ed;"
        "    border-radius: 12px;"
        "    gridline-color: #e8ecf1;"
        "    selection-background-color: #d6eaf8;"
        "    selection-color: #2c3e50;"
        "    alternate-background-color: #f8f9fa;"
        "    font-size: 13px;"
        "}"
        "QTableView::item:selected {"
        "    background-color: #9b59b6;"
        "    color: #ffffff;"
        "}"
    );
    
    model = new QSqlQueryModel(this);
    tableView->setModel(model);
    connect(tableView, &QTableView::clicked, this, &HistoriqueDialog::on_tableView_clicked);
    
    mainLayout->addWidget(tableView);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    btnRestaurer = new QPushButton("🔄 Restaurer", this);
    btnRestaurer->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2ecc71, stop:1 #27ae60);"
        "    color: white;"
        "    padding: 10px 20px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    min-width: 120px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #27ae60, stop:1 #229954);"
        "}"
        "QPushButton:disabled {"
        "    background: #95a5a6;"
        "}"
    );
    btnRestaurer->setEnabled(false);
    connect(btnRestaurer, &QPushButton::clicked, this, &HistoriqueDialog::on_btnRestaurer_clicked);
    
    btnSupprimerDef = new QPushButton("🗑️ Supprimer Définitivement", this);
    btnSupprimerDef->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e74c3c, stop:1 #c0392b);"
        "    color: white;"
        "    padding: 10px 20px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    min-width: 180px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #c0392b, stop:1 #a93226);"
        "}"
        "QPushButton:disabled {"
        "    background: #95a5a6;"
        "}"
    );
    btnSupprimerDef->setEnabled(false);
    connect(btnSupprimerDef, &QPushButton::clicked, this, &HistoriqueDialog::on_btnSupprimerDef_clicked);
    
    btnFermer = new QPushButton("Fermer", this);
    btnFermer->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #95a5a6, stop:1 #7f8c8d);"
        "    color: white;"
        "    padding: 10px 20px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    min-width: 100px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #7f8c8d, stop:1 #6c7a7b);"
        "}"
    );
    connect(btnFermer, &QPushButton::clicked, this, &QDialog::accept);
    
    buttonLayout->addWidget(btnRestaurer);
    buttonLayout->addWidget(btnSupprimerDef);
    buttonLayout->addWidget(btnFermer);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
}

void HistoriqueDialog::refreshTable()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Base de données non connectée";
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT ID, REVENU, DEPENSE, BENEFICES, TVA, DELAI, "
                  "MODEPAIMENT, STATUT, DATE_SUPPRESSION "
                  "FROM FINANCES_HISTORIQUE "
                  "ORDER BY DATE_SUPPRESSION DESC");
    
    if (query.exec()) {
        model->setQuery(query);
        
        // Définir les en-têtes des colonnes
        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "Revenu");
        model->setHeaderData(2, Qt::Horizontal, "Dépenses");
        model->setHeaderData(3, Qt::Horizontal, "Bénéfices");
        model->setHeaderData(4, Qt::Horizontal, "TVA");
        model->setHeaderData(5, Qt::Horizontal, "Date");
        model->setHeaderData(6, Qt::Horizontal, "Mode de Paiement");
        model->setHeaderData(7, Qt::Horizontal, "Statut");
        model->setHeaderData(8, Qt::Horizontal, "Date Suppression");
        
        tableView->setModel(model);
        
        // Cacher la colonne ID si nécessaire
        // tableView->hideColumn(0);
        
        // Ajuster la largeur des colonnes
        tableView->horizontalHeader()->setStretchLastSection(true);
        tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        
        // Réinitialiser la sélection
        selectedHistoryId.clear();
        btnRestaurer->setEnabled(false);
        btnSupprimerDef->setEnabled(false);
    } else {
        qDebug() << "Erreur lors du chargement de l'historique:" << query.lastError().text();
    }
}

void HistoriqueDialog::on_tableView_clicked(const QModelIndex &index)
{
    if (!index.isValid()) return;
    
    int row = index.row();
    if (row < 0 || row >= model->rowCount()) return;
    
    // Récupérer l'ID de la ligne sélectionnée (colonne 0)
    QModelIndex idIndex = model->index(row, 0);
    selectedHistoryId = model->data(idIndex).toString();
    
    // Activer les boutons
    btnRestaurer->setEnabled(true);
    btnSupprimerDef->setEnabled(true);
}

void HistoriqueDialog::on_btnRestaurer_clicked()
{
    if (selectedHistoryId.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un enregistrement à restaurer");
        return;
    }
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", 
                                  "Voulez-vous restaurer cette transaction ?",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Erreur", "Base de données non connectée");
            return;
        }
        
        // Récupérer les données de l'historique
        QSqlQuery selectQuery(db);
        selectQuery.prepare("SELECT REVENU, DEPENSE, BENEFICES, TVA, DELAI, MODEPAIMENT, STATUT "
                           "FROM FINANCES_HISTORIQUE WHERE ID = :id");
        selectQuery.bindValue(":id", selectedHistoryId);
        
        if (!selectQuery.exec() || !selectQuery.next()) {
            QMessageBox::critical(this, "Erreur", "Impossible de récupérer les données de l'historique");
            return;
        }
        
        double revenu = selectQuery.value(0).toDouble();
        double depense = selectQuery.value(1).toDouble();
        double benefices = selectQuery.value(2).toDouble();
        double tva = selectQuery.value(3).toDouble();
        QDate delai = selectQuery.value(4).toDate();
        QString modePaiment = selectQuery.value(5).toString();
        QString statut = selectQuery.value(6).toString();
        
        // Insérer dans la table FINANCES
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO FINANCES (REVENU, DEPENSE, BENEFICES, TVA, DELAI, MODEPAIMENT, STATUT) "
                           "VALUES (:revenu, :depense, :benefices, :tva, :delai, :modePaiment, :statut)");
        insertQuery.bindValue(":revenu", revenu);
        insertQuery.bindValue(":depense", depense);
        insertQuery.bindValue(":benefices", benefices);
        insertQuery.bindValue(":tva", tva);
        insertQuery.bindValue(":delai", delai);
        insertQuery.bindValue(":modePaiment", modePaiment.isEmpty() ? QVariant(QVariant::String) : modePaiment);
        insertQuery.bindValue(":statut", statut.isEmpty() ? QVariant(QVariant::String) : statut);
        
        if (insertQuery.exec()) {
            // Supprimer de l'historique
            QSqlQuery deleteQuery(db);
            deleteQuery.prepare("DELETE FROM FINANCES_HISTORIQUE WHERE ID = :id");
            deleteQuery.bindValue(":id", selectedHistoryId);
            
            if (deleteQuery.exec()) {
                QMessageBox::information(this, "Succès", "Transaction restaurée avec succès");
                refreshTable();
                // Émettre un signal pour rafraîchir la table principale (si nécessaire)
            } else {
                QMessageBox::warning(this, "Attention", "Transaction restaurée mais erreur lors de la suppression de l'historique");
            }
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la restauration: " + insertQuery.lastError().text());
        }
    }
}

void HistoriqueDialog::on_btnSupprimerDef_clicked()
{
    if (selectedHistoryId.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un enregistrement à supprimer");
        return;
    }
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", 
                                  "Êtes-vous sûr de vouloir supprimer définitivement cette transaction ?\n"
                                  "Cette action est irréversible !",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Erreur", "Base de données non connectée");
            return;
        }
        
        QSqlQuery query(db);
        query.prepare("DELETE FROM FINANCES_HISTORIQUE WHERE ID = :id");
        query.bindValue(":id", selectedHistoryId);
        
        if (query.exec()) {
            QMessageBox::information(this, "Succès", "Transaction supprimée définitivement");
            refreshTable();
        } else {
            QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression: " + query.lastError().text());
        }
    }
}

