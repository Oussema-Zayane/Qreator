#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QRegularExpression>

class Client
{
private:
    int id;
    QString nomPrenom;
    QString email;
    QString telephone;

public:
    Client();
    Client(int id, QString nomPrenom, QString email, QString telephone);
    static QVector<Client> chargerTousLesClients(QSqlDatabase db);

    // Getters
    int getId() const { return id; }
    QString getNomPrenom() const { return nomPrenom; }
    QString getEmail() const { return email; }
    QString getTelephone() const { return telephone; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNomPrenom(QString np) { nomPrenom = np; }
    void setEmail(QString e) { email = e; }
    void setTelephone(QString t) { telephone = t; }

    // Fonctionnalités CRUD
    bool ajouter();
    bool supprimer(int id);
    QSqlQueryModel* afficher();
    bool modifier(int id, QString nomPrenom, QString email, QString telephone);

    // Méthodes de validation
    static bool validerNomPrenom(const QString& nomPrenom);
    static bool validerEmail(const QString& email);
    static bool validerTelephone(const QString& telephone);
};

#endif // CLIENT_H
