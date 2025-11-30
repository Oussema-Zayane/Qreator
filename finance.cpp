#include "Finance.h" // Inclure l'en-tête de la classe renommée
#include "connection.h" // Assurez-vous que cette connexion est toujours valide
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QObject>

// NOTE : J'ai ajouté 'projet_id' ici. Assurez-vous qu'il est défini dans Finance.h !
Finance::Finance()
{
    id = 0;
    revenu = 0.0;
    benefices = 0.0;
    depense = 0.0;
    tva = 0.0;
    modePaiment = "";
    statut = "";
    projet_id = ""; // <-- AJOUT CRITIQUE
    delai = QDate::currentDate();
}

// Constructeur mis à jour pour inclure projet_id
Finance::Finance(int id, double revenu, double benefices, QDate delai, 
                 QString modePaiment, QString statut, double depense, QString projetId) // <-- AJOUT CRITIQUE
{
    this->id = id;
    this->revenu = revenu;
    this->benefices = benefices;
    this->delai = delai;
    this->modePaiment = modePaiment;
    this->statut = statut;
    this->depense = depense;
    this->projet_id = projetId; // <-- AJOUT CRITIQUE
}

// Getters
int Finance::getId() const
{
    return id;
}

double Finance::getRevenu() const
{
    return revenu;
}

double Finance::getBenefices() const
{
    return benefices;
}

QDate Finance::getDelai() const
{
    return delai;
}

QString Finance::getModePaiment() const
{
    return modePaiment;
}

QString Finance::getStatut() const
{
    return statut;
}

double Finance::getDepense() const
{
    return depense;
}

double Finance::getTva() const
{
    return tva;
}

// Getter pour projet_id
QString Finance::getProjet_id() const
{
    return projet_id;
}

// Setters
void Finance::setId(int id)
{
    this->id = id;
}

void Finance::setRevenu(double revenu)
{
    this->revenu = revenu;
}

void Finance::setBenefices(double benefices)
{
    this->benefices = benefices;
}

void Finance::setDelai(QDate delai)
{
    this->delai = delai;
}

void Finance::setModePaiment(QString modePaiment)
{
    this->modePaiment = modePaiment;
}

void Finance::setStatut(QString statut)
{
    this->statut = statut;
}

void Finance::setDepense(double depense)
{
    this->depense = depense;
}

void Finance::setTva(double tva)
{
    this->tva = tva;
}

// Setter pour projet_id
void Finance::setProjet_id(QString projetId)
{
    this->projet_id = projetId;
}


// Calculer les bénéfices (Revenu - Dépense)
bool Finance::calculerBenefices()
{
    benefices = revenu - depense;
    return true;
}

// --- CRUD Methods ---

// Create - Ajouter un enregistrement
bool Finance::ajouter()
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
        return false;
    }
    
    calculerBenefices();
    tva = benefices * 0.20;
    
    QSqlQuery query(db);
    // AJOUT DE PROJET_ID DANS L'INSERT
    query.prepare("INSERT INTO FINANCES (REVENU, BENEFICES, DELAI, MODEPAIMENT, STATUT, DEPENSE, TVA, PROJET_ID) "
                  "VALUES (:revenu, :benefices, :delai, :modePaiment, :statut, :depense, :tva, :projet_id)");
    
    query.bindValue(":revenu", revenu);
    query.bindValue(":benefices", benefices);
    query.bindValue(":delai", delai);
    query.bindValue(":modePaiment", modePaiment.isEmpty() ? QVariant(QVariant::String) : modePaiment);
    query.bindValue(":statut", statut.isEmpty() ? QVariant(QVariant::String) : statut);
    query.bindValue(":depense", depense);
    query.bindValue(":tva", tva);
    query.bindValue(":projet_id", projet_id); // <-- LIAISON DU PROJET ID
    
    if (query.exec()) {
        qDebug() << "Enregistrement ajouté avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de l'ajout:" << query.lastError().text();
        return false;
    }
}

// Read - Afficher tous les enregistrements
QSqlQuery Finance::afficher()
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
        return query;
    }
    
    query = QSqlQuery(db);
    // AJOUT DE PROJET_ID DANS LE SELECT
    // Les colonnes seront dans cet ordre: ROWID, REVENU, DEPENSE, BENEFICES, TVA, DATE_ENTREE, DELAI_JOURS, MODEPAIMENT, STATUT, PROJET_ID
    query.prepare("SELECT ROWID, REVENU, DEPENSE, BENEFICES, TVA, DELAI as DATE_ENTREE, "
                  "ABS(ROUND(SYSDATE - DELAI)) as DELAI_JOURS, MODEPAIMENT, STATUT, PROJET_ID "
                  "FROM FINANCES ORDER BY DELAI DESC");
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération des données:" << query.lastError().text();
    }
    
    return query;
}

// Update - Modifier un enregistrement
bool Finance::modifier(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
        return false;
    }
    
    if (rowId.isEmpty()) {
        qDebug() << "Erreur: ROWID est vide";
        return false;
    }
    
    calculerBenefices();
    tva = benefices * 0.20;
    
    QSqlQuery query(db);
    // AJOUT DE PROJET_ID DANS L'UPDATE
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
    query.bindValue(":projet_id", projet_id); // <-- LIAISON DU PROJET ID
    
    if (query.exec()) {
        qDebug() << "Enregistrement modifié avec succès";
        return true;
    } else {
        qDebug() << "Erreur lors de la modification:" << query.lastError().text();
        return false;
    }
}

// Sauvegarder dans l'historique avant suppression
bool Finance::sauvegarderDansHistorique(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
        return false;
    }
    
    if (rowId.isEmpty()) {
        qDebug() << "Erreur: ROWID est vide";
        return false;
    }
    
    // --- Logique de création de table/séquence (LAISSÉE TELLE QUELLE) ---
    QSqlQuery checkTableQuery(db);
    checkTableQuery.prepare("SELECT COUNT(*) FROM USER_TABLES WHERE TABLE_NAME = 'FINANCES_HISTORIQUE'");
    bool tableExists = false;
    if (checkTableQuery.exec() && checkTableQuery.next()) {
        tableExists = (checkTableQuery.value(0).toInt() > 0);
    }
    
    if (!tableExists) {
        QSqlQuery createQuery(db);
        QString createTableSQL = 
            "CREATE TABLE FINANCES_HISTORIQUE ("
            "ID NUMBER PRIMARY KEY,"
            "REVENU NUMBER(10,2),"
            "DEPENSE NUMBER(10,2),"
            "BENEFICES NUMBER(10,2),"
            "TVA NUMBER(10,2),"
            "DELAI DATE,"
            "MODEPAIMENT VARCHAR2(50),"
            "STATUT VARCHAR2(50),"
            "PROJET_ID VARCHAR2(50)," // <-- AJOUT CRITIQUE DANS LA TABLE HISTORIQUE
            "DATE_SUPPRESSION TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "ROWID_ORIGINAL VARCHAR2(50))";
        createQuery.exec(createTableSQL);
    }
    
    QSqlQuery checkSeqQuery(db);
    checkSeqQuery.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
    bool sequenceExists = false;
    if (checkSeqQuery.exec() && checkSeqQuery.next()) {
        sequenceExists = (checkSeqQuery.value(0).toInt() > 0);
    }
    
    if (!sequenceExists) {
        QSqlQuery createSeqQuery(db);
        QString createSeqSQL = "CREATE SEQUENCE SEQ_FINANCES_HISTORIQUE START WITH 1 INCREMENT BY 1";
        if (!createSeqQuery.exec(createSeqSQL)) {
            // Logique de vérification/erreur
        } else {
            sequenceExists = true;
        }
    }
    // --- FIN Logique de création de table/séquence ---

    
    // Récupérer les données de la transaction à supprimer (avec PROJET_ID)
    QSqlQuery selectQuery(db);
    selectQuery.prepare("SELECT REVENU, DEPENSE, BENEFICES, TVA, DELAI, MODEPAIMENT, STATUT, PROJET_ID " // <-- AJOUT PROJET_ID
                        "FROM FINANCES WHERE ROWID=CHARTOROWID(:id)");
    selectQuery.bindValue(":id", rowId);
    
    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "Erreur lors de la récupération des données pour l'historique:" << selectQuery.lastError().text();
        return false;
    }
    
    double revenu = selectQuery.value(0).toDouble();
    double depense = selectQuery.value(1).toDouble();
    double benefices = selectQuery.value(2).toDouble();
    double tva = selectQuery.value(3).toDouble();
    QDate delai = selectQuery.value(4).toDate();
    QString modePaiment = selectQuery.value(5).toString();
    QString statut = selectQuery.value(6).toString();
    QString projetIdOriginal = selectQuery.value(7).toString(); // <-- RÉCUPÉRATION DU PROJET ID
    
    QSqlQuery finalCheckQuery(db);
    finalCheckQuery.prepare("SELECT COUNT(*) FROM USER_SEQUENCES WHERE SEQUENCE_NAME = 'SEQ_FINANCES_HISTORIQUE'");
    bool finalSequenceExists = false;
    if (finalCheckQuery.exec() && finalCheckQuery.next()) {
        finalSequenceExists = (finalCheckQuery.value(0).toInt() > 0);
    }
    
    // Insérer dans l'historique
    QSqlQuery insertQuery(db);
    
    if (finalSequenceExists) {
        // AJOUT DE PROJET_ID DANS L'INSERT DE L'HISTORIQUE
        insertQuery.prepare("INSERT INTO FINANCES_HISTORIQUE (ID, REVENU, DEPENSE, BENEFICES, TVA, DELAI, "
                            "MODEPAIMENT, STATUT, PROJET_ID, ROWID_ORIGINAL) "
                            "VALUES (SEQ_FINANCES_HISTORIQUE.NEXTVAL, :revenu, :depense, :benefices, :tva, "
                            ":delai, :modePaiment, :statut, :projet_id, :rowId)");
    } else {
        // Logique alternative pour ID
        QSqlQuery maxIdQuery(db);
        maxIdQuery.prepare("SELECT NVL(MAX(ID), 0) + 1 FROM FINANCES_HISTORIQUE");
        int nextId = 1;
        if (maxIdQuery.exec() && maxIdQuery.next()) {
            nextId = maxIdQuery.value(0).toInt();
        }
        
        // AJOUT DE PROJET_ID DANS L'INSERT DE L'HISTORIQUE
        insertQuery.prepare("INSERT INTO FINANCES_HISTORIQUE (ID, REVENU, DEPENSE, BENEFICES, TVA, DELAI, "
                            "MODEPAIMENT, STATUT, PROJET_ID, ROWID_ORIGINAL) "
                            "VALUES (:id, :revenu, :depense, :benefices, :tva, "
                            ":delai, :modePaiment, :statut, :projet_id, :rowId)");
        insertQuery.bindValue(":id", nextId);
    }
    
    insertQuery.bindValue(":revenu", revenu);
    insertQuery.bindValue(":depense", depense);
    insertQuery.bindValue(":benefices", benefices);
    insertQuery.bindValue(":tva", tva);
    insertQuery.bindValue(":delai", delai);
    insertQuery.bindValue(":modePaiment", modePaiment.isEmpty() ? QVariant(QVariant::String) : modePaiment);
    insertQuery.bindValue(":statut", statut.isEmpty() ? QVariant(QVariant::String) : statut);
    insertQuery.bindValue(":projet_id", projetIdOriginal); // <-- LIAISON DU PROJET ID DANS L'HISTORIQUE
    insertQuery.bindValue(":rowId", rowId);
    
    if (insertQuery.exec()) {
        qDebug() << "Transaction sauvegardée dans l'historique";
        return true;
    } else {
        qDebug() << "Erreur lors de la sauvegarde dans l'historique:" << insertQuery.lastError().text();
        return false;
    }
}

// Delete - Supprimer un enregistrement
bool Finance::supprimer(const QString &rowId)
{
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
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

// Rechercher - Rechercher des enregistrements selon un critère
QSqlQuery Finance::rechercher(QString critere)
{
    QSqlQuery query;
    QSqlDatabase db = QSqlDatabase::database("qt_sql_default_connection");
    if (!db.isOpen()) {
        qDebug() << "Erreur: La base de données n'est pas ouverte";
        return query;
    }
    
    query = QSqlQuery(db);
    // AJOUT DE PROJET_ID DANS LE SELECT et dans la clause WHERE pour la recherche
    query.prepare("SELECT ROWID, REVENU, DEPENSE, BENEFICES, TVA, DELAI as DATE_ENTREE, "
                  "ABS(ROUND(SYSDATE - DELAI)) as DELAI_JOURS, MODEPAIMENT, STATUT, PROJET_ID "
                  "FROM FINANCES WHERE "
                  "REVENU LIKE :critere OR "
                  "BENEFICES LIKE :critere OR "
                  "MODEPAIMENT LIKE :critere OR "
                  "STATUT LIKE :critere OR "
                  "DEPENSE LIKE :critere OR "
                  "PROJET_ID LIKE :critere " // <-- RECHERCHE PAR PROJET ID
                  "ORDER BY DELAI DESC");
    
    QString searchPattern = "%" + critere + "%";
    query.bindValue(":critere", searchPattern);
    
    if (!query.exec()) {
        qDebug() << "Erreur lors de la recherche:" << query.lastError().text();
    }
    
    return query;
}
