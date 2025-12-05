#include "client.h"

Client::Client() : id(0), nomPrenom(""), email(""), telephone("") {}

Client::Client(int id, QString nomPrenom, QString email, QString telephone)
    : id(id), nomPrenom(nomPrenom), email(email), telephone(telephone) {}

bool Client::validerNomPrenom(const QString& nomPrenom)
{
    // Validation : au moins 2 caractères, seulement lettres, espaces et apostrophes
    QRegularExpression regex("^[a-zA-ZÀ-ÿ]+([ '-][a-zA-ZÀ-ÿ]+)*$");
    return regex.match(nomPrenom).hasMatch() && nomPrenom.length() >= 2;
}

bool Client::validerEmail(const QString& email)
{
    // Validation d'email basique
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool Client::validerTelephone(const QString& telephone)
{
    // Validation : format français, 10 chiffres
    QRegularExpression regex("^(0[1-9])(?:[ _.-]?([0-9]{2})){4}$");
    return regex.match(telephone).hasMatch();
}

bool Client::ajouter()
{
    // Validation des données avant insertion
    if (!validerNomPrenom(nomPrenom) || !validerEmail(email) || !validerTelephone(telephone)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO client (id, nom_prenom, email, telephone) "
                  "VALUES (:id, :nom_prenom, :email, :telephone)");

    query.bindValue(":id", id);
    query.bindValue(":nom_prenom", nomPrenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);

    return query.exec();
}

bool Client::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM client WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom_prenom, email, telephone, date_ajout, statut FROM client");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom/Prénom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date d'ajout"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool Client::modifier(int id, QString nomPrenom, QString email, QString telephone)
{
    // Validation des données avant modification
    if (!validerNomPrenom(nomPrenom) || !validerEmail(email) || !validerTelephone(telephone)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE client SET nom_prenom = :nom_prenom, email = :email, "
                  "telephone = :telephone WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom_prenom", nomPrenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);

    return query.exec();
}
