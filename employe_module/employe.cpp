#include "employe.h"
#include "connection.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

Employe::Employe() : id(0) {}

Employe::Employe(int id, const QString& nom, const QString& prenom, const QString& email,
                 const QString& telephone, const QString& role, const QString& horaire, const QString& genre)
    : id(id), nom(nom), prenom(prenom), email(email), telephone(telephone), role(role), horaire(horaire), genre(genre) {}

bool Employe::add()
{
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("INSERT INTO employe (nom, prenom, email, telephone, role, horaire, genre) "
              "VALUES (:nom, :prenom, :email, :telephone, :role, :horaire, :genre)");
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":email", email);
    q.bindValue(":telephone", telephone);
    q.bindValue(":role", role);
    q.bindValue(":horaire", horaire);
    q.bindValue(":genre", genre);

    if (!q.exec()) {
        qDebug() << "Employe::add failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Employe::update()
{
    if (id <= 0) return false;
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, email=:email, telephone=:telephone, "
              "role=:role, horaire=:horaire, genre=:genre WHERE id=:id");
    q.bindValue(":id", id);
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":email", email);
    q.bindValue(":telephone", telephone);
    q.bindValue(":role", role);
    q.bindValue(":horaire", horaire);
    q.bindValue(":genre", genre);

    if (!q.exec()) {
        qDebug() << "Employe::update failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Employe::removeById(int id)
{
    if (id <= 0) return false;
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("DELETE FROM employe WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << "Employe::removeById failed:" << q.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Employe::showAll()
{
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQueryModel* m = new QSqlQueryModel();
    m->setQuery("SELECT id, nom, prenom, email, telephone, role, horaire, genre FROM employe ORDER BY id", db);
    return m;
}
