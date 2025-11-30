#include "alerteretarddialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QAbstractItemView>
#include <QMessageBox>

AlerteRetardDialog::AlerteRetardDialog(const QList<TransactionRetard> &transactions, QWidget *parent)
    : QDialog(parent)
    , model(nullptr)
    , transactionsRetard(transactions)
{
    setWindowTitle("⚠️ Alertes - Transactions en Retard");
    setMinimumSize(900, 500);
    setModal(true);
    
    setupUI();
    populateTable();
}

AlerteRetardDialog::~AlerteRetardDialog()
{
    if (model) {
        delete model;
    }
}

void AlerteRetardDialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Titre
    QLabel *titleLabel = new QLabel("⚠️ Transactions ayant dépassé le délai", this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #e74c3c; padding: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);
    
    // Message d'information
    QLabel *infoLabel = new QLabel(
        QString("Il y a %1 transaction(s) en retard.\n"
                "Vous pouvez augmenter le délai de 3 jours et ajouter 20% à la TVA pour chaque transaction.")
        .arg(transactionsRetard.size()), this);
    infoLabel->setStyleSheet("font-size: 12px; color: #2c3e50; padding: 10px;");
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Table view
    tableView = new QTableView(this);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet(
        "QTableView {"
        "    background-color: #ffffff;"
        "    border: 2px solid #e1e8ed;"
        "    border-radius: 12px;"
        "    gridline-color: #e8ecf1;"
        "    selection-background-color: #ffebee;"
        "    selection-color: #2c3e50;"
        "    alternate-background-color: #fff5f5;"
        "    font-size: 13px;"
        "}"
        "QTableView::item:selected {"
        "    background-color: #ffcdd2;"
        "    color: #c62828;"
        "}"
    );
    
    model = new QStandardItemModel(this);
    tableView->setModel(model);
    
    mainLayout->addWidget(tableView);
    
    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    btnAugmenterDelai = new QPushButton("✅ Augmenter Délai (+3 jours) et TVA (+20%)", this);
    btnAugmenterDelai->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2ecc71, stop:1 #27ae60);"
        "    color: white;"
        "    padding: 12px 25px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    font-size: 13px;"
        "    min-width: 300px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #27ae60, stop:1 #229954);"
        "}"
    );
    connect(btnAugmenterDelai, &QPushButton::clicked, this, &AlerteRetardDialog::on_btnAugmenterDelai_clicked);
    
    btnIgnorer = new QPushButton("Ignorer", this);
    btnIgnorer->setStyleSheet(
        "QPushButton {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #95a5a6, stop:1 #7f8c8d);"
        "    color: white;"
        "    padding: 12px 25px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    min-width: 120px;"
        "}"
        "QPushButton:hover {"
        "    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #7f8c8d, stop:1 #6c7a7b);"
        "}"
    );
    connect(btnIgnorer, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addWidget(btnAugmenterDelai);
    buttonLayout->addWidget(btnIgnorer);
    buttonLayout->addStretch();
    
    mainLayout->addLayout(buttonLayout);
}

void AlerteRetardDialog::populateTable()
{
    // Créer un modèle personnalisé pour afficher les données
    model->clear();
    
    // Créer les colonnes
    model->setColumnCount(8);
    model->setHeaderData(0, Qt::Horizontal, "Revenu");
    model->setHeaderData(1, Qt::Horizontal, "Dépenses");
    model->setHeaderData(2, Qt::Horizontal, "Bénéfices");
    model->setHeaderData(3, Qt::Horizontal, "TVA");
    model->setHeaderData(4, Qt::Horizontal, "Date Délai");
    model->setHeaderData(5, Qt::Horizontal, "Jours Retard");
    model->setHeaderData(6, Qt::Horizontal, "Mode Paiement");
    model->setHeaderData(7, Qt::Horizontal, "Statut");
    
    // Ajouter les lignes
    for (int i = 0; i < transactionsRetard.size(); ++i) {
        const TransactionRetard &trans = transactionsRetard[i];
        QList<QStandardItem*> rowItems;
        
        // Colonne 0: Revenu (avec ROWID stocké dans UserRole)
        QStandardItem *itemRevenu = new QStandardItem(QString::number(trans.revenu, 'f', 2) + " TND");
        itemRevenu->setData(trans.rowId, Qt::UserRole);
        rowItems.append(itemRevenu);
        
        // Colonne 1: Dépenses
        rowItems.append(new QStandardItem(QString::number(trans.depense, 'f', 2) + " TND"));
        
        // Colonne 2: Bénéfices
        rowItems.append(new QStandardItem(QString::number(trans.benefices, 'f', 2) + " TND"));
        
        // Colonne 3: TVA
        rowItems.append(new QStandardItem(QString::number(trans.tva, 'f', 2) + " TND"));
        
        // Colonne 4: Date Délai
        rowItems.append(new QStandardItem(trans.delai.toString("dd/MM/yyyy")));
        
        // Colonne 5: Jours Retard
        rowItems.append(new QStandardItem(QString::number(trans.joursRetard) + " jour(s)"));
        
        // Colonne 6: Mode Paiement
        rowItems.append(new QStandardItem(trans.modePaiment.isEmpty() ? "N/A" : trans.modePaiment));
        
        // Colonne 7: Statut
        rowItems.append(new QStandardItem(trans.statut.isEmpty() ? "N/A" : trans.statut));
        
        // Ajouter la ligne au modèle
        model->appendRow(rowItems);
    }
    
    tableView->setModel(model);
    
    // Ajuster la largeur des colonnes
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    
    // Sélectionner toutes les lignes par défaut
    tableView->selectAll();
}

bool AlerteRetardDialog::augmenterDelaiEtTVA()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Base de données non connectée");
        return false;
    }
    
    // Récupérer les lignes sélectionnées
    QModelIndexList selectedIndexes = tableView->selectionModel()->selectedRows();
    
    if (selectedIndexes.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner au moins une transaction");
        return false;
    }
    
    int successCount = 0;
    int failCount = 0;
    
    // Traiter chaque transaction sélectionnée
    for (const QModelIndex &index : selectedIndexes) {
        int row = index.row();
        if (row < 0 || row >= model->rowCount()) continue;
        
        // Récupérer le ROWID depuis les données utilisateur de la première colonne
        QStandardItem *item = model->item(row, 0);
        if (!item) continue;
        
        QString rowId = item->data(Qt::UserRole).toString();
        if (rowId.isEmpty()) continue;
        
        // Trouver la transaction correspondante
        TransactionRetard trans;
        bool found = false;
        for (const TransactionRetard &t : transactionsRetard) {
            if (t.rowId == rowId) {
                trans = t;
                found = true;
                break;
            }
        }
        
        if (!found) continue;
        
        // Calculer la nouvelle date (délai + 3 jours)
        QDate nouvelleDate = trans.delai.addDays(3);
        
        // Calculer la nouvelle TVA (TVA actuelle + 20%)
        double nouvelleTVA = trans.tva * 1.20;
        
        // Mettre à jour dans la base de données
        QSqlQuery query(db);
        query.prepare("UPDATE FINANCES SET DELAI = :nouvelleDate, TVA = :nouvelleTVA "
                     "WHERE ROWID = CHARTOROWID(:rowId)");
        query.bindValue(":nouvelleDate", nouvelleDate);
        query.bindValue(":nouvelleTVA", nouvelleTVA);
        query.bindValue(":rowId", rowId);
        
        if (query.exec()) {
            successCount++;
            qDebug() << "Transaction" << rowId << "mise à jour: Délai +3 jours, TVA +20%";
        } else {
            failCount++;
            qDebug() << "Erreur lors de la mise à jour de la transaction" << rowId << ":" << query.lastError().text();
        }
    }
    
    if (successCount > 0) {
        QString message = QString("%1 transaction(s) mise(s) à jour avec succès.\n"
                                 "Délai augmenté de 3 jours et TVA augmentée de 20%.")
                         .arg(successCount);
        if (failCount > 0) {
            message += QString("\n%1 transaction(s) n'a(ont) pas pu être mise(s) à jour.").arg(failCount);
        }
        QMessageBox::information(this, "Succès", message);
        return true;
    } else {
        QMessageBox::critical(this, "Erreur", "Aucune transaction n'a pu être mise à jour.");
        return false;
    }
}

void AlerteRetardDialog::on_btnAugmenterDelai_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", 
                                  "Voulez-vous vraiment augmenter le délai de 3 jours et la TVA de 20% "
                                  "pour les transactions sélectionnées ?",
                                  QMessageBox::Yes | QMessageBox::No);
    
    if (reply == QMessageBox::Yes) {
        if (augmenterDelaiEtTVA()) {
            accept(); // Fermer le dialogue avec succès
        }
    }
}

void AlerteRetardDialog::on_btnIgnorer_clicked()
{
    reject();
}

