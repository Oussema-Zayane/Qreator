#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Employe
{
private:
    int id;
    QString nom;
    QString prenom;
    QString email;
    QString telephone;
    QString role;
    QString horaire;
    QString genre;
    QString dateEmbauche;
    double salaire;

public:
    Employe();
    Employe(int id, QString nom, QString prenom, QString email, QString telephone,
            QString role, QString horaire, QString genre, QString dateEmbauche, double salaire);

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }
    QString getPoste() const { return role; }  // Correction: getPoste au lieu de getRole
    QString getHoraire() const { return horaire; }
    QString getGenre() const { return genre; }
    QString getDateEmbauche() const { return dateEmbauche; }
    double getSalaire() const { return salaire; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }
    void setEmail(QString email) { this->email = email; }
    void setTelephone(QString telephone) { this->telephone = telephone; }
    void setRole(QString role) { this->role = role; }  // Correction: setRole
    void setHoraire(QString horaire) { this->horaire = horaire; }
    void setGenre(QString genre) { this->genre = genre; }
    void setDateEmbauche(QString date) { dateEmbauche = date; }
    void setSalaire(double salaire) { this->salaire = salaire; }

    // CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString nom, QString prenom, QString email,
                  QString telephone, QString role, QString dateEmbauche, double salaire);

    // Validation
    static bool validerNomPrenom(const QString& text);
    static bool validerEmail(const QString& email);
    static bool validerTelephone(const QString& telephone);
};

#endif // EMPLOYE_H
