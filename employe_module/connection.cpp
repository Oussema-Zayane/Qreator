#include "connection.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QDebug>

static const QString CONNECTION_NAME = QStringLiteral("qt_conn");
static const QString DSN_NAME = QStringLiteral("Source_Projet2A"); // your DSN
static const QString DB_USER = QStringLiteral("ihebb");
static const QString DB_PASS = QStringLiteral("esprit25");

QString dbConnectionName() { return CONNECTION_NAME; }

bool createConnection()
{
    // remove any previous connection with same name (safe cleanup)
    if (QSqlDatabase::contains(CONNECTION_NAME)) {
        QSqlDatabase::removeDatabase(CONNECTION_NAME);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", CONNECTION_NAME);
    db.setDatabaseName(DSN_NAME);
    db.setUserName(DB_USER);
    db.setPassword(DB_PASS);

    if (!db.open()) {
        qCritical() << "DB open failed:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Erreur de connexion",
                              "Impossible de se connecter à la base Oracle:\n" + db.lastError().text());
        return false;
    }

    qDebug() << "Connected to Oracle via ODBC using DSN" << DSN_NAME;
    return true;
}
