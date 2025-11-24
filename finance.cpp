#include "finance.h"
#include <QSqlError>

Finance::Finance() : id(0), montant(0) {}

Finance::Finance(int id, QString type, QString description, double montant,
                 QString dateOperation, QString categorie)
    : id(id), type(type), description(description), montant(montant),
    dateOperation(dateOperation), categorie(categorie) {}

bool Finance::ajouter()
{
    QSqlQuery query;

    // 1. Trouver le prochain ID disponible avec une méthode plus fiable
    int nextId = 1;

    // Méthode alternative pour trouver le max ID
    QSqlQuery maxQuery;
    if (maxQuery.exec("SELECT MAX(ID) FROM FINANCE")) {
        if (maxQuery.next()) {
            nextId = maxQuery.value(0).toInt() + 1;
            qDebug() << "Prochain ID calculé:" << nextId;
        }
    } else {
        qDebug() << "Erreur recherche ID max:" << maxQuery.lastError().text();
        // En cas d'erreur, on essaie une autre méthode
        QSqlQuery countQuery("SELECT COUNT(*) FROM FINANCE");
        if (countQuery.exec() && countQuery.next()) {
            nextId = countQuery.value(0).toInt() + 1;
            qDebug() << "Prochain ID (méthode count):" << nextId;
        }
    }

    // 2. Vérifier que l'ID n'existe pas déjà (sécurité)
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM FINANCE WHERE ID = :id");
    checkQuery.bindValue(":id", nextId);

    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        // L'ID existe déjà, on prend le suivant
        nextId++;
        qDebug() << "ID existait déjà, nouvel ID:" << nextId;
    }

    qDebug() << "ID final utilisé:" << nextId;

    // 3. Insérer avec l'ID
    query.prepare("INSERT INTO FINANCE (ID, TYPE, DESCRIPTION, MONTANT, DATE_OPERATION, CATEGORIE) "
                  "VALUES (:id, :type, :description, :montant, TO_DATE(:date_operation, 'DD/MM/YYYY'), :categorie)");

    query.bindValue(":id", nextId);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":montant", montant);
    query.bindValue(":date_operation", dateOperation);
    query.bindValue(":categorie", categorie);

    if (query.exec()) {
        qDebug() << "✅ Insertion réussie, ID:" << nextId;
        return true;
    } else {
        qDebug() << "❌ Erreur insertion:" << query.lastError().text();

        // Si c'est encore une violation de contrainte, on réessaie avec un ID différent
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
    model->setQuery("SELECT ID, TYPE, MONTANT, "
                    "TO_CHAR(DATE_OPERATION, 'DD/MM/YYYY'), "
                    "DESCRIPTION, CATEGORIE "
                    "FROM FINANCE ORDER BY DATE_OPERATION DESC");
    return model;
}

bool Finance::modifier(int id, QString type, QString description, double montant,
                       QString dateOperation, QString categorie)
{
    QSqlQuery query;
    query.prepare("UPDATE FINANCE SET TYPE=:type, DESCRIPTION=:description, MONTANT=:montant, "
                  "DATE_OPERATION=TO_DATE(:date_operation, 'DD/MM/YYYY'), CATEGORIE=:categorie "
                  "WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":montant", montant);
    query.bindValue(":date_operation", dateOperation);
    query.bindValue(":categorie", categorie);

    qDebug() << "Execution modification - ID:" << id;

    if (query.exec()) {
        qDebug() << "✅ Modification réussie pour ID:" << id;
        return true;
    } else {
        qDebug() << "❌ Erreur modification ID" << id << ":" << query.lastError().text();
        return false;
    }
}

bool Finance::modifier()
{
    if (type.isEmpty() || description.isEmpty()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE FINANCE SET TYPE=:type, DESCRIPTION=:description, MONTANT=:montant, "
                  "DATE_OPERATION=TO_DATE(:date_operation, 'DD/MM/YYYY'), CATEGORIE=:categorie "
                  "WHERE ID=:id");

    query.bindValue(":id", id);
    query.bindValue(":type", type);
    query.bindValue(":description", description);
    query.bindValue(":montant", montant);
    query.bindValue(":date_operation", dateOperation);
    query.bindValue(":categorie", categorie);

    return query.exec();
}

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
