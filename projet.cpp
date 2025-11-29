#include "projet.h"
#include <QRegularExpression>

Projet::Projet() : id(0), nom(""), description(""), client(""), dateDebut(""), dateFin(""), budget(0), statut("En cours") {}

Projet::Projet(int id, QString nom, QString description, QString client,
               QString dateDebut, QString dateFin, double budget, QString statut)
    : id(id), nom(nom), description(description), client(client),
    dateDebut(dateDebut), dateFin(dateFin), budget(budget), statut(statut) {}

bool Projet::ajouter()
{
    if (nom.isEmpty() || client.isEmpty()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO projet (id, nom, description, client, date_debut, date_fin, budget, statut) "
                  "VALUES (:id, :nom, :description, :client, TO_DATE(:date_debut, 'YYYY-MM-DD'), TO_DATE(:date_fin, 'YYYY-MM-DD'), :budget, :statut)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":client", client);
    query.bindValue(":date_debut", dateDebut);
    query.bindValue(":date_fin", dateFin);
    query.bindValue(":budget", budget);
    query.bindValue(":statut", statut);

    return query.exec();
}

bool Projet::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM projet WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Projet::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom, description, client, date_debut, date_fin, budget, statut FROM projet");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Client"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date début"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date fin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Budget"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool Projet::modifier(int id, QString nom, QString description, QString client,
                      QString dateDebut, QString dateFin, double budget, QString statut)
{
    if (nom.isEmpty() || client.isEmpty()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE projet SET nom = :nom, description = :description, client = :client, "
                  "date_debut = TO_DATE(:date_debut, 'YYYY-MM-DD'), date_fin = TO_DATE(:date_fin, 'YYYY-MM-DD'), "
                  "budget = :budget, statut = :statut WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":client", client);
    query.bindValue(":date_debut", dateDebut);
    query.bindValue(":date_fin", dateFin);
    query.bindValue(":budget", budget);
    query.bindValue(":statut", statut);

    return query.exec();
}

bool Projet::modifier()
{
    if (nom.isEmpty() || client.isEmpty()) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE projet SET nom = :nom, description = :description, client = :client, "
                  "date_debut = TO_DATE(:date_debut, 'YYYY-MM-DD'), date_fin = TO_DATE(:date_fin, 'YYYY-MM-DD'), "
                  "budget = :budget, statut = :statut WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":description", description);
    query.bindValue(":client", client);
    query.bindValue(":date_debut", dateDebut);
    query.bindValue(":date_fin", dateFin);
    query.bindValue(":budget", budget);
    query.bindValue(":statut", statut);

    return query.exec();
}
