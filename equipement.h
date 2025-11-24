#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Equipement
{
private:
    int id;
    QString nom;
    QString type;
    QString etat;
    double prix;

public:
    Equipement();
    Equipement(int id, QString nom, QString type, QString etat, double prix);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getType() const { return type; }
    QString getEtat() const { return etat; }
    double getPrix() const { return prix; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setType(QString type) { this->type = type; }
    void setEtat(QString etat) { this->etat = etat; }
    void setPrix(double prix) { this->prix = prix; }

    // CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString nom, QString type, QString etat, double prix);

    // Validation
    static bool validerNom(const QString& nom);
    static bool validerPrix(double prix);
};

#endif // EQUIPEMENT_H
