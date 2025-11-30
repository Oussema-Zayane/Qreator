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
    QString projet_id; // Identifiant du projet lié
    QString statut; // Ajout possible si vous utilisez un statut pour les finances (ex: "payé", "en attente")

public:
    // ====================================================================
    // CONSTRUCTEURS
    // ====================================================================
    Finance();
    // Constructeur avec tous les champs
    Finance(int id, QString type, QString description, double montant, 
            QString dateOperation, QString categorie, QString projet_id, QString statut = "Payé"); 

    // ====================================================================
    // GETTERS
    // ====================================================================
    int getId() const { return id; }
    QString getType() const { return type; }
    QString getDescription() const { return description; }
    double getMontant() const { return montant; }
    QString getDateOperation() const { return dateOperation; }
    QString getCategorie() const { return categorie; }
    QString getProjet_id() const { return projet_id; }
    QString getStatut() const { return statut; }

    // ====================================================================
    // SETTERS
    // ====================================================================
    void setId(int id) { this->id = id; }
    void setType(QString type) { this->type = type; }
    void setDescription(QString desc) { description = desc; }
    void setMontant(double montant) { this->montant = montant; }
    void setDateOperation(QString date) { dateOperation = date; }
    void setCategorie(QString categorie) { this->categorie = categorie; }
    void setProjet_id(QString projetId) { projet_id = projetId; }
    void setStatut(QString statut) { this->statut = statut; }

    // ====================================================================
    // MÉTHODES CRUD
    // ====================================================================
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    
    /**
     * @brief Modifie une opération financière existante.
     * @param id : ID de l'opération à modifier.
     * @param projet_id : ID du projet lié (AJOUT CRITIQUE).
     */
    bool modifier(int id, QString type, QString description, double montant, 
                  QString dateOperation, QString categorie, QString projet_id); 

    // ====================================================================
    // STATISTIQUES
    // ====================================================================
    static double getTotalRevenus();
    static double getTotalDepenses();
    static double getBenefices();
};

#endif // FINANCE_H
