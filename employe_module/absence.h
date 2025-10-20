#ifndef ABSENCE_H
#define ABSENCE_H

#include <QString>
#include <QSqlQueryModel>

class Absence {
public:
    Absence();
    Absence(int id, int id_employe, const QString& nom, const QString& type_abs,
            const QString& debut, const QString& fin, const QString& raison);

    bool add();
    bool update(); // uses id
    static bool removeById(int id);
    static QSqlQueryModel* showAll();

private:
    int id;
    int id_employe;
    QString nom;
    QString type_abs;
    QString debut; // yyyy-mm-dd strings
    QString fin;
    QString raison;
};

#endif // ABSENCE_H
