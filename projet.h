#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Projet
{
private:
    int id;
    QString nom;
    QString description;
    QString client;
    QString dateDebut;
    QString dateFin;
    double budget;
    QString statut;

public:
    Projet();
    Projet(int id, QString nom, QString description, QString client,
           QString dateDebut, QString dateFin, double budget, QString statut);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getDescription() const { return description; }
    QString getClient() const { return client; }
    QString getDateDebut() const { return dateDebut; }
    QString getDateFin() const { return dateFin; }
    double getBudget() const { return budget; }
    QString getStatut() const { return statut; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setDescription(QString desc) { description = desc; }
    void setClient(QString client) { this->client = client; }
    void setDateDebut(QString date) { dateDebut = date; }
    void setDateFin(QString date) { dateFin = date; }
    void setBudget(double budget) { this->budget = budget; }
    void setStatut(QString statut) { this->statut = statut; }

    // CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString nom, QString description, QString client,
                  QString dateDebut, QString dateFin, double budget, QString statut);

    // Méthodes pour la modification simple
    bool modifier();
};

#endif // PROJET_H
