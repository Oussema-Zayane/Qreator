#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug> // Ajout de QDebug pour la clarté

class Connection
{
private:
    // --- Configuration Singleton ---
    
    // 1. Constructeur privé pour empêcher l'instanciation externe
    Connection();
    
    // 2. Destructeur
    ~Connection();
    
    // 3. Empêcher la copie et l'affectation
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;

    // --- Fonctions Privées d'Aide ---
    
    // Fonction pour lire le registre Windows afin de trouver les drivers Oracle
    QStringList getOracleDriversFromRegistry(); 
    
    // Note: La variable QSqlDatabase 'db' n'est plus nécessaire ici
    // car le QSqlDatabase::addDatabase utilise le nom "qt_sql_default_connection"

public:
    // --- Fonctions Publiques ---

    // 1. Méthode statique pour obtenir l'unique instance (Point d'accès du Singleton)
    static Connection& getInstance();

    // 2. Méthode principale de connexion (fusion de createConnection et createconnect)
    // C'est la seule méthode publique utilisée pour établir la connexion
    bool createconnect();
    
    // 3. Méthode d'initialisation du schéma (laisser statique si elle n'accède pas aux membres de la classe)
    // Nous la rendons non-statique (membre) pour la cohérence, mais elle peut être statique si souhaité.
    // L'implémentation dans le .cpp est membre, donc nous laissons la déclaration membre ici.
    bool initializeHistoriqueTable(); 
};

#endif // CONNECTION_H
