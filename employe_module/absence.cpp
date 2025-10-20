#include "absence.h"
#include "connection.h"

#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

Absence::Absence() : id(0), id_employe(0) {}

Absence::Absence(int id, int id_employe, const QString& nom, const QString& type_abs,
                 const QString& debut, const QString& fin, const QString& raison)
    : id(id), id_employe(id_employe), nom(nom), type_abs(type_abs), debut(debut), fin(fin), raison(raison) {}

bool Absence::add()
{
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("INSERT INTO absence (id_employe, nom, type_abs, debut, fin, raison) "
              "VALUES (:id_emp, :nom, :type, TO_DATE(:debut,'YYYY-MM-DD'), TO_DATE(:fin,'YYYY-MM-DD'), :raison)");
    q.bindValue(":id_emp", id_employe);
    q.bindValue(":nom", nom);
    q.bindValue(":type", type_abs);
    q.bindValue(":debut", debut);
    q.bindValue(":fin", fin);
    q.bindValue(":raison", raison);

    if (!q.exec()) {
        qDebug() << "Absence::add failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Absence::update()
{
    if (id <= 0) return false;
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("UPDATE absence SET type_abs=:type, debut=TO_DATE(:debut,'YYYY-MM-DD'), fin=TO_DATE(:fin,'YYYY-MM-DD'), raison=:raison WHERE id=:id");
    q.bindValue(":type", type_abs);
    q.bindValue(":debut", debut);
    q.bindValue(":fin", fin);
    q.bindValue(":raison", raison);
    q.bindValue(":id", id);

    if (!q.exec()) {
        qDebug() << "Absence::update failed:" << q.lastError().text();
        return false;
    }
    return true;
}

bool Absence::removeById(int id)
{
    if (id <= 0) return false;
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQuery q(db);
    q.prepare("DELETE FROM absence WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << "Absence::removeById failed:" << q.lastError().text();
        return false;
    }
    return true;
}

QSqlQueryModel* Absence::showAll()
{
    QSqlDatabase db = QSqlDatabase::database(dbConnectionName());
    QSqlQueryModel* m = new QSqlQueryModel();
    m->setQuery("SELECT id_employe, nom, type_abs, TO_CHAR(debut,'YYYY-MM-DD') AS debut, TO_CHAR(fin,'YYYY-MM-DD') AS fin, raison FROM absence ORDER BY id", db);
    return m;
}
