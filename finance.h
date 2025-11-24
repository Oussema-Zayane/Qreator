#ifndef FINANCE_H
#define FINANCE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Finance
{
private:
    int id;
    QString type; // "Revenu" ou "Dépense"
    QString description;
    double montant;
    QString dateOperation;
    QString categorie;
    QString projet_id; // Ajout du membre manquant

public:
    Finance();
    Finance(int id, QString type, QString description, double montant, QString dateOperation, QString categorie);

    // Getters
    int getId() const { return id; }
    QString getType() const { return type; }
    QString getDescription() const { return description; }
    double getMontant() const { return montant; }
    QString getDateOperation() const { return dateOperation; }
    QString getCategorie() const { return categorie; }
    QString getProjet_id() const { return projet_id; }

    // Setters
    void setId(int id) { this->id = id; }
    void setType(QString type) { this->type = type; }
    void setDescription(QString desc) { description = desc; }
    void setMontant(double montant) { this->montant = montant; }
    void setDateOperation(QString date) { dateOperation = date; }
    void setCategorie(QString categorie) { this->categorie = categorie; }
    void setProjet_id(QString projetId) { projet_id = projetId; }

    // CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString type, QString description, double montant, QString dateOperation, QString categorie);
    bool modifier(); // Ajout de la méthode sans paramètres

    // Statistiques
    static double getTotalRevenus();
    static double getTotalDepenses();
    static double getBenefices();
};

#endif // FINANCE_H
