#ifndef FINANCE_H // Renommer la macro de garde
#define FINANCE_H // Renommer la macro de garde

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Finance // Renommer la classe
{
private:
    int id;
    double revenu;
    double benefices;
    QDate delai;
    QString modePaiment;
    QString statut;
    double depense;
    double tva;
    QString projet_id; // <-- AJOUT CRITIQUE pour lier à la table PROJETS

public:
    Finance();
    // Mise à jour du constructeur pour inclure le projetId
    Finance(int id, double revenu, double benefices, QDate delai, 
            QString modePaiment, QString statut, double depense, QString projetId); // <-- NOUVEAU PARAMÈTRE
    
    // Getters
    int getId() const;
    double getRevenu() const;
    double getBenefices() const;
    QDate getDelai() const;
    QString getModePaiment() const;
    QString getStatut() const;
    double getDepense() const;
    double getTva() const;
    QString getProjet_id() const; // <-- NOUVEAU GETTER
    
    // Setters
    void setId(int id);
    void setRevenu(double revenu);
    void setBenefices(double benefices);
    void setDelai(QDate delai);
    void setModePaiment(QString modePaiment);
    void setStatut(QString statut);
    void setDepense(double depense);
    void setTva(double tva);
    void setProjet_id(QString projetId); // <-- NOUVEAU SETTER
    
    // CRUD Methods (Les signatures restent les mêmes, la logique est dans Finance.cpp)
    bool ajouter();
    bool modifier(const QString &rowId);
    bool supprimer(const QString &rowId);
    bool sauvegarderDansHistorique(const QString &rowId);
    QSqlQuery afficher();
    QSqlQuery rechercher(QString critere);
    bool calculerBenefices();
};

#endif // FINANCE_H
