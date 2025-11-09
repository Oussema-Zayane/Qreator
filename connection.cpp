#include "connection.h"

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
}

Connection::~Connection()
{
    if(db.isOpen()) {
        db.close();
    }
}

Connection& Connection::getInstance()
{
    static Connection instance;
    return instance;
}

bool Connection::createConnection()
{
    db.setDatabaseName("Projetbase");
    db.setUserName("C##Oussema");
    db.setPassword("esprit18");

    if(db.open()) {
        qDebug() << "Connexion établie";
        return true;
    } else {
        qDebug() << "Échec de la connexion :" << db.lastError().text();
        return false;
    }
}
