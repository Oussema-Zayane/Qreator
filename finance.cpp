#include "Finance.h" 
#include "connection.h" // Nécessaire pour l'accès à la connexion
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QObject>
#include <QSqlRecord> // Ajout pour une meilleure gestion des données

// Nom de la connexion par défaut, établi par le Singleton
#define CONNECTION_NAME "qt_sql_default_connection" 

// --- Constructeurs et Setters/Getters ---

Finance::Finance()
{
    id = 0;
    revenu = 0.0;
    benefices = 0.0;
    depense = 0.0;
    tva = 0.0;
    modePaiment = "";
    statut = "";
    projet_id = ""; // Initialisation de PROJET_ID
    delai = QDate::currentDate();
}

Finance::Finance(int id, double revenu, double benefices, QDate delai, 
                 QString modePaiment, QString statut, double depense, QString projetId)
{
    this->id = id;
    this->revenu = revenu;
    this->benefices = benefices;
    this->delai = delai;
    this->modePaiment = modePaiment;
    this->statut = statut;
    this->depense = depense;
    this->projet_id = projetId; // Attribution de PROJET_ID
}

// Getters
int Finance::getId() const { return id; }
double Finance::getRevenu() const { return revenu; }
double Finance::getBenefices() const { return benefices; }
QDate Finance::getDelai() const { return delai; }
QString Finance::getModePaiment() const { return modePaiment; }
QString Finance::getStatut() const { return statut; }
double Finance::getDepense() const { return depense; }
double Finance::getTva() const { return tva; }
QString Finance::getProjet_id() const { return projet_id; }

// Setters
void Finance::setId(int id) { this->id = id; }
void Finance::setRevenu(double revenu) { this->revenu = revenu; }
void Finance::setBenefices(double benefices) { this->benefices = benefices; }
void Finance::setDelai(QDate delai) { this->delai = delai; }
void Finance::setModePaiment(QString modePaiment) { this->modePaiment = modePaiment; }
void Finance::setStatut(QString statut) { this->statut = statut; }
void Finance::setDepense(double depense) { this->depense = depense; }
void Finance::setTva(double tva) { this->tva = tva; }
void Finance::setProjet_id(QString projetId) { this->projet_id = projetId; }

// Calculer les bénéfices (Revenu - Dépense)
bool Finance::calculerBenefices()
{
    benefices = revenu - depense;
    tva = benefices * 0.20; // Calculer la TVA en même temps
    return true;
}

// --- CRUD Methods ---

/**
 * @brief Ajoute un enregistrement à la table FINANCES.
 */
bool Finance::ajouter()
{
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte.";
        return false;
    }
    
    calculerBenefices();
    
    QSqlQuery query(db);
    // Requête avec PROJET_ID
    query.prepare("INSERT INTO FINANCES (REVENU, BENEFICES, DELAI, MODEPAIMENT, STATUT, DEPENSE, TVA, PROJET_ID) "
                  "VALUES (:revenu, :benefices, :delai, :modePaiment, :statut, :depense, :tva, :projet_id)");
    
    query.bindValue(":revenu", revenu);
    query.bindValue(":benefices", benefices);
    query.bindValue(":delai", delai);
    query.bindValue(":modePaiment", modePaiment.isEmpty() ? QVariant(QVariant::String) : modePaiment);
    query.bindValue(":statut", statut.isEmpty() ? QVariant(QVariant::String) : statut);
    query.bindValue(":depense", depense);
    query.bindValue(":tva", tva);
    query.bindValue(":projet_id", projet_id);
    
    if (query.exec()) {
        qDebug() << "Enregistrement ajouté avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

/**
 * @brief Récupère tous les enregistrements de la table FINANCES.
 */
QSqlQuery Finance::afficher()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte pour l'affichage.";
        return query; // Retourne une requête invalide
    }
    
    query = QSqlQuery(db);
    // Requête avec PROJET_ID
    query.prepare("SELECT ROWID, REVENU, DEPENSE, BENEFICES, TVA, DELAI as DATE_ENTREE, "
                  "ABS(ROUND(SYSDATE - DELAI)) as DELAI_JOURS, MODEPAIMENT, STATUT, PROJET_ID "
                  "FROM FINANCES ORDER BY DELAI DESC");
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des données:" << query.lastError().text();
    }
    
    return query;
}

/**
 * @brief Modifie un enregistrement dans la table FINANCES.
 */
bool Finance::modifier(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte pour la modification.";
        return false;
    }
    
    if (rowId.isEmpty()) {
        qDebug() << "Erreur: ROWID est vide";
        return false;
    }
    
    calculerBenefices();
    
    QSqlQuery query(db);
    // Requête de modification avec PROJET_ID
    query.prepare("UPDATE FINANCES SET REVENU=:revenu, BENEFICES=:benefices, DELAI=:delai, "
                  "MODEPAIMENT=:modePaiment, STATUT=:statut, DEPENSE=:depense, TVA=:tva, PROJET_ID=:projet_id WHERE ROWID=CHARTOROWID(:id)");
    
    query.bindValue(":id", rowId);
    query.bindValue(":revenu", revenu);
    query.bindValue(":benefices", benefices);
    query.bindValue(":delai", delai);
    query.bindValue(":modePaiment", modePaiment.isEmpty() ? QVariant(QVariant::String) : modePaiment);
    query.bindValue(":statut", statut.isEmpty() ? QVariant(QVariant::String) : statut);
    query.bindValue(":depense", depense);
    query.bindValue(":tva", tva);
    query.bindValue(":projet_id", projet_id);
    
    if (query.exec()) {
        qDebug() << "Enregistrement modifié avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}

/**
 * @brief Sauvegarde les données d'une transaction dans l'historique avant suppression.
 * @note La vérification et la création de la table FINANCES_HISTORIQUE sont faites par Connection::createconnect().
 */
bool Finance::sauvegarderDansHistorique(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte pour l'historique.";
        return false;
    }
    
    if (rowId.isEmpty()) {
        qDebug() << "Erreur: ROWID est vide";
        return false;
    }
    
    // 1. Récupérer les données de la transaction à supprimer (avec PROJET_ID)
    QSqlQuery selectQuery(db);
    selectQuery.prepare("SELECT REVENU, DEPENSE, BENEFICES, TVA, DELAI, MODEPAIMENT, STATUT, PROJET_ID "
                        "FROM FINANCES WHERE ROWID=CHARTOROWID(:id)");
    selectQuery.bindValue(":id", rowId);
    
    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "Erreur lors de la récupération des données pour l'historique:" << selectQuery.lastError().text();
        return false;
    }
    
    QSqlRecord record = selectQuery.record();
    
    // 2. Vérifier si la séquence existe (si le Singleton a réussi à la créer)
    QSqlQuery checkSeqQuery(db);
    checkSeqQuery.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
    bool sequenceExists = false;
    if (checkSeqQuery.exec() && checkSeqQuery.next()) {
        sequenceExists = (checkSeqQuery.value(0).toInt() > 0);
    }
    
    // 3. Insérer dans l'historique
    QSqlQuery insertQuery(db);
    
    if (sequenceExists) {
        insertQuery.prepare("INSERT INTO FINANCES_HISTORIQUE (ID, REVENU, DEPENSE, BENEFICES, TVA, DELAI, "
                            "MODEPAIMENT, STATUT, PROJET_ID, ROWID_ORIGINAL) "
                            "VALUES (SEQ_FINANCES_HISTORIQUE.NEXTVAL, :revenu, :depense, :benefices, :tva, "
                            ":delai, :modePaiment, :statut, :projet_id, :rowId)");
    } else {
        // Logique alternative pour ID si la séquence n'a pas pu être créée
        QSqlQuery maxIdQuery(db);
        maxIdQuery.prepare("SELECT NVL(MAX(ID), 0) + 1 FROM FINANCES_HISTORIQUE");
        int nextId = 1;
        if (maxIdQuery.exec() && maxIdQuery.next()) {
            nextId = maxIdQuery.value(0).toInt();
        }
        
        insertQuery.prepare("INSERT INTO FINANCES_HISTORIQUE (ID, REVENU, DEPENSE, BENEFICES, TVA, DELAI, "
                            "MODEPAIMENT, STATUT, PROJET_ID, ROWID_ORIGINAL) "
                            "VALUES (:id, :revenu, :depense, :benefices, :tva, "
                            ":delai, :modePaiment, :statut, :projet_id, :rowId)");
        insertQuery.bindValue(":id", nextId);
    }
    
    // Lier les valeurs
    insertQuery.bindValue(":revenu", record.value("REVENU"));
    insertQuery.bindValue(":depense", record.value("DEPENSE"));
    insertQuery.bindValue(":benefices", record.value("BENEFICES"));
    insertQuery.bindValue(":tva", record.value("TVA"));
    insertQuery.bindValue(":delai", record.value("DELAI"));
    insertQuery.bindValue(":modePaiment", record.value("MODEPAIMENT"));
    insertQuery.bindValue(":statut", record.value("STATUT"));
    insertQuery.bindValue(":projet_id", record.value("PROJET_ID"));
    insertQuery.bindValue(":rowId", rowId);
    
    if (insertQuery.exec()) {
        qDebug() << "Transaction sauvegardée dans l'historique";
        return true;
    } else {
        qDebug() << "Erreur lors de la sauvegarde dans l'historique:" << insertQuery.lastError().text();
        return false;
    }
}


/**
 * @brief Supprime un enregistrement après l'avoir sauvegardé dans l'historique.
 */
bool Finance::supprimer(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte pour la suppression.";
        return false;
    }
    
    if (rowId.isEmpty()) {
        qDebug() << "Erreur: ROWID est vide";
        return false;
    }
    
    // Sauvegarder dans l'historique avant de supprimer
    if (!sauvegarderDansHistorique(rowId)) {
        qDebug() << "Attention: Impossible de sauvegarder dans l'historique, suppression annulée";
        return false;
    }
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM FINANCES WHERE ROWID=CHARTOROWID(:id)");
    query.bindValue(":id", rowId);
    
    if (query.exec()) {
        qDebug() << "Enregistrement supprimé avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de la suppression:" << query.lastError().text();
        return false;
    }
}

/**
 * @brief Recherche des enregistrements par critère.
 */
QSqlQuery Finance::rechercher(QString critere)
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database(CONNECTION_NAME);
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte pour la recherche.";
        return query;
    }
    
    query = QSqlQuery(db);
    // Requête de recherche avec PROJET_ID
    query.prepare("SELECT ROWID, REVENU, DEPENSE, BENEFICES, TVA, DELAI as DATE_ENTREE, "
                  "ABS(ROUND(SYSDATE - DELAI)) as DELAI_JOURS, MODEPAIMENT, STATUT, PROJET_ID "
                  "FROM FINANCES WHERE "
                  "REVENU LIKE :critere OR "
                  "BENEFICES LIKE :critere OR "
                  "MODEPAIMENT LIKE :critere OR "
                  "STATUT LIKE :critere OR "
                  "DEPENSE LIKE :critere OR "
                  "PROJET_ID LIKE :critere "
                  "ORDER BY DELAI DESC");
    
    QString searchPattern = "%" + critere + "%";
    query.bindValue(":critere", searchPattern);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche:" << query.lastError().text();
    }
    
    return query;
}
