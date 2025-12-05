#include "employe.h"

Employe::Employe() : id(0), nom(""), prenom(""), email(""), telephone(""),
    role(""), horaire(""), genre(""), dateEmbauche(""), salaire(0) {}

Employe::Employe(int id, QString nom, QString prenom, QString email, QString telephone,
                 QString role, QString horaire, QString genre, QString dateEmbauche, double salaire)
    : id(id), nom(nom), prenom(prenom), email(email), telephone(telephone),
    role(role), horaire(horaire), genre(genre), dateEmbauche(dateEmbauche), salaire(salaire) {}

bool Employe::validerNomPrenom(const QString& text)
{
    return text.length() >= 2;
}

bool Employe::validerEmail(const QString& email)
{
    return email.contains("@") && email.contains(".");
}

bool Employe::validerTelephone(const QString& telephone)
{
    return telephone.length() >= 10;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (id, nom, prenom, email, telephone, role, horaire, genre, date_embauche, salaire, statut) "
                  "VALUES (:id, :nom, :prenom, :email, :telephone, :role, :horaire, :genre, TO_DATE(:date_embauche, 'YYYY-MM-DD'), :salaire, 'Actif')");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":role", role);  // MAINTENANT ça correspond !
    query.bindValue(":horaire", horaire);
    query.bindValue(":genre", genre);
    query.bindValue(":date_embauche", dateEmbauche);
    query.bindValue(":salaire", salaire);

    return query.exec();
}

bool Employe::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom, prenom, email, telephone, role, horaire, genre, date_embauche, salaire, statut FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Rôle")); // Changé Poste → Rôle
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Horaire"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Genre"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Date embauche"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Statut"));
    return model;
}

bool Employe::modifier(int id, QString nom, QString prenom, QString email, QString telephone,
                       QString role, QString dateEmbauche, double salaire)
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET nom = :nom, prenom = :prenom, email = :email, "
                  "telephone = :telephone, role = :role, "
                  "date_embauche = TO_DATE(:date_embauche, 'YYYY-MM-DD'), salaire = :salaire WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":telephone", telephone);
    query.bindValue(":role", role);  // MAINTENANT ça correspond !
    query.bindValue(":date_embauche", dateEmbauche);
    query.bindValue(":salaire", salaire);

    return query.exec();
}
