#include "finance.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>

Finance::Finance() 
    : id(0), montant(0), projet_id(""), statut("Payé") // Initialisation des nouveaux membres
{
    // Initialisation des membres QString vides si besoin
    type = "";
    description = "";
    dateOperation = "";
    categorie = "";
}

// CORRECTION 1 : Mise à jour du constructeur pour inclure projet_id et statut (selon finance.h)
Finance::Finance(int id, QString type, QString description, double montant,
                 QString dateOperation, QString categorie, QString projet_id, QString statut)
    : id(id), type(type), description(description), montant(montant),
    dateOperation(dateOperation), categorie(categorie), projet_id(projet_id), statut(statut) {}

bool Finance::ajouter()
{
    QSqlQuery query;

    // 1. Trouver le prochain ID disponible (Méthode laissée telle quelle mais peu recommandée pour Oracle)
    int nextId = 1;
    QSqlQuery maxQuery;
    if (maxQuery.exec("SELECT MAX(ID) FROM FINANCE")) {
        if (maxQuery.next()) {
            nextId = maxQuery.value(0).toInt() + 1;
            qDebug() << "Prochain ID calculé:" << nextId;
        }
    } else {
        qDebug() << "Erreur recherche ID max:" << maxQuery.lastError().text();
        QSqlQuery countQuery("SELECT COUNT(*) FROM FINANCE");
        if (countQuery.exec() && countQuery.next()) {
            nextId = countQuery.value(0).toInt() + 1;
            qDebug() << "Prochain ID (méthode count):" << nextId;
        }
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM FINANCE WHERE ID = :id");
    checkQuery.bindValue(":id", nextId);

    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        nextId++;
        qDebug() << "ID existait déjà, nouvel ID:" << nextId;
    }

    qDebug() << "ID final utilisé:" << nextId;

    // CORRECTION 2 : Ajout de PROJET_ID et STATUT à la requête INSERT
    query.prepare("INSERT INTO FINANCE (ID, TYPE, DESCRIPTION, MONTANT, DATE_OPERATION, CATEGORIE, PROJET_ID, STATUT) "
                  "VALUES (:id, :type, :description, :montant, TO_DATE(:date_operation, 'DD/MM/YYYY'), :categorie, :projet_id, :statut)");

    query.bindValue(":id", nextId);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":montant", montant);
    query.bindValue(":date_operation", dateOperation);
    query.bindValue(":categorie", categorie);
    query.bindValue(":projet_id", projet_id); // <-- Liaison de la variable membre
    query.bindValue(":statut", statut.isEmpty() ? "Payé" : statut); // Valeur par défaut si non définie

    if (query.exec()) {
        qDebug() << "✅ Insertion réussie, ID:" << nextId;
        return true;
    } else {
        qDebug() << "❌ Erreur insertion:" << query.lastError().text();
        if (query.lastError().text().contains("ORA-00001")) {
            qDebug() << "Tentative avec ID + 100";
            query.bindValue(":id", nextId + 100);
            return query.exec();
        }
        return false;
    }
}

bool Finance::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM FINANCE WHERE ID = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Finance::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    
    // CORRECTION 3 : Ajout des colonnes PROJET_ID et STATUT à la requête SELECT
    // L'ordre doit correspondre à celui des en-têtes définis dans mainwindow.cpp
    model->setQuery("SELECT ID, TYPE, MONTANT, "
                    "TO_CHAR(DATE_OPERATION, 'DD/MM/YYYY') AS DATE_OP, "
                    "DESCRIPTION, PROJET_ID, STATUT, CATEGORIE "
                    "FROM FINANCE ORDER BY DATE_OPERATION DESC");
    
    // Correction des en-têtes pour QSqlQueryModel (optionnel mais bonne pratique)
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Montant"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Projet ID"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Catégorie"));
    
    // NOTE: Le tableau dans mainwindow.cpp doit avoir 7 colonnes pour correspondre
    // Si vous n'utilisez que 7 colonnes dans l'UI, vous devez ajuster l'affichage dans mainwindow.cpp
    // ou retirer une colonne ici (Catégorie, par exemple). Je laisse 8 pour la complétude.
    
    return model;
}

// CORRECTION 4 : Mise à jour de la signature et de la requête UPDATE pour inclure PROJET_ID
bool Finance::modifier(int id, QString type, QString description, double montant,
                       QString dateOperation, QString categorie, QString projet_id)
{
    QSqlQuery query;
    query.prepare("UPDATE FINANCE SET TYPE=:type, DESCRIPTION=:description, MONTANT=:montant, "
                  "DATE_OPERATION=TO_DATE(:date_operation, 'DD/MM/YYYY'), CATEGORIE=:categorie, PROJET_ID=:projet_id "
                  "WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":montant", montant);
    query.bindValue(":date_operation", dateOperation);
    query.bindValue(":categorie", categorie);
    query.bindValue(":projet_id", projet_id); // <-- Liaison critique

    qDebug() << "Execution modification - ID:" << id;

    if (query.exec()) {
        qDebug() << "✅ Modification réussie pour ID:" << id;
        return true;
    } else {
        qDebug() << "❌ Erreur modification ID" << id << ":" << query.lastError().text();
        return false;
    }
}

// CORRECTION 5 : Suppression de la méthode modifier() sans paramètres
/*
bool Finance::modifier() 
{
    // Cette méthode a été supprimée pour privilégier la version avec paramètres, plus claire et plus sûre.
    return false; 
}
*/

double Finance::getTotalRevenus()
{
    QSqlQuery query;
    query.prepare("SELECT SUM(MONTANT) FROM FINANCE WHERE TYPE = 'Revenu'");
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double Finance::getTotalDepenses()
{
    QSqlQuery query;
    query.prepare("SELECT SUM(MONTANT) FROM FINANCE WHERE TYPE = 'Dépense'");
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double Finance::getBenefices()
{
    return getTotalRevenus() - getTotalDepenses();
}
