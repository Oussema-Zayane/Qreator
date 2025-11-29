#include "equipement.h"
#include <QSqlError>
#include <QDebug>

Equipement::Equipement() : id(0), nom(""), type(""), etat(""), prix(0) {}

Equipement::Equipement(int id, QString nom, QString type, QString etat, double prix)
    : id(id), nom(nom), type(type), etat(etat), prix(prix) {}

bool Equipement::validerNom(const QString& nom)
{
    return !nom.isEmpty() && nom.length() >= 2;
}

bool Equipement::validerPrix(double prix)
{
    return prix >= 0;
}

bool Equipement::ajouter()
{
    if (!validerNom(nom) || !validerPrix(prix)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO equipement (id, nom, type, etat, prix, date_ajout) "
                  "VALUES (:id, :nom, :type, :etat, :prix, SYSDATE)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);

    return query.exec();
}

bool Equipement::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM equipement WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom, type, etat, prix, date_ajout FROM equipement");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'ajout"));
    return model;
}

bool Equipement::modifier(int id, QString nom, QString type, QString etat, double prix)
{
    if (!validerNom(nom) || !validerPrix(prix)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE equipement SET nom = :nom, type = :type, etat = :etat, prix = :prix WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);

    return query.exec();
}
