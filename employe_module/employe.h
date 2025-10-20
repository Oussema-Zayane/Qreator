#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>
#include <QSqlQueryModel>

class Employe {
public:
    Employe();
    Employe(int id, const QString& nom, const QString& prenom, const QString& email,
            const QString& telephone, const QString& role, const QString& horaire, const QString& genre);

    bool add();             // insert this employee into the DB
    bool update();          // update using this->id
    static bool removeById(int id); // delete by id
    static QSqlQueryModel* showAll(); // returns a model pointer (caller owns)

    // getters / setters (light)
    int getId() const { return id; }

private:
    int id;
    QString nom, prenom, email, telephone, role, horaire, genre;
};

#endif // EMPLOYE_H
