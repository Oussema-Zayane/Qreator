#include "emailsmtpmanager.h"
#include <QDebug>
#include <QTimer>


EmailSMTPManager::EmailSMTPManager(QObject *parent)
    : QObject(parent), etape(0), indexDestinataire(0)
{
    socket = new QSslSocket(this);
    connect(socket, &QSslSocket::connected, this, &EmailSMTPManager::onConnected);
    connect(socket, &QSslSocket::encrypted, this, &EmailSMTPManager::onEncrypted);
    connect(socket, &QSslSocket::readyRead, this, &EmailSMTPManager::onReadyRead);
}

void EmailSMTPManager::configurerSMTP(const QString &email, const QString &motDePasseApp)
{
    emailUtilisateur = email;
    motDePasse = motDePasseApp;
}

void EmailSMTPManager::envoyerEmail(const QString &destinataire,
                                    const QString &sujet,
                                    const QString &messageHtml)
{
    listeDestinataires = QStringList{ destinataire };
    sujetCourant = sujet;
    messageCourant = messageHtml;
    indexDestinataire = 0;

    envoyerAuDestinataire();
}

void EmailSMTPManager::envoyerEmailMultiple(const QStringList &destinataires,
                                            const QString &sujet,
                                            const QString &messageHtml)
{
    listeDestinataires = destinataires;
    sujetCourant = sujet;
    messageCourant = messageHtml;
    indexDestinataire = 0;

    envoyerAuDestinataire();
}

void EmailSMTPManager::envoyerAuDestinataire()
{
    if (indexDestinataire >= listeDestinataires.size()) {
        emit envoiTermine();
        return;
    }

    destinataireCourant = listeDestinataires[indexDestinataire];
    etape = 0;

    qDebug() << "Envoi →" << destinataireCourant;

    socket->abort();
    socket->connectToHostEncrypted("smtp.gmail.com", 465);
}

void EmailSMTPManager::envoyerCommande(const QString &cmd)
{
    socket->write(cmd.toUtf8() + "\r\n");
}

void EmailSMTPManager::onConnected()
{
    qDebug() << "Connecté SMTP";
}

void EmailSMTPManager::onEncrypted()
{
    envoyerCommande("EHLO smtp.gmail.com");
    etape = 1;
}

void EmailSMTPManager::onReadyRead()
{
    QString r = socket->readAll();
    qDebug() << "SMTP →" << r;

    if (r.contains("5.7.0") || r.startsWith("535")) {
        emit erreur("Authentification Gmail incorrecte (vérifie le mot de passe d'application)");
        return;
    }

    if (etape == 1 && r.contains("250")) {
        envoyerCommande("AUTH LOGIN");
        etape = 2;
    }
    else if (etape == 2 && r.contains("334")) {
        envoyerCommande(emailUtilisateur.toUtf8().toBase64());
        etape = 3;
    }
    else if (etape == 3 && r.contains("334")) {
        envoyerCommande(motDePasse.toUtf8().toBase64());
        etape = 4;
    }
    else if (etape == 4 && r.contains("235")) {
        envoyerCommande("MAIL FROM:<" + emailUtilisateur + ">");
        etape = 5;
    }
    else if (etape == 5 && r.contains("250")) {
        envoyerCommande("RCPT TO:<" + destinataireCourant + ">");
        etape = 6;
    }
    else if (etape == 6 && r.contains("250")) {
        envoyerCommande("DATA");
        etape = 7;
    }
    else if (etape == 7 && r.contains("354")) {

        QString data =
            "Subject: " + sujetCourant + "\r\n"
                                         "From: " + emailUtilisateur + "\r\n"
                                 "To: " + destinataireCourant + "\r\n"
                                    "MIME-Version: 1.0\r\n"
                                    "Content-Type: text/html; charset=UTF-8\r\n\r\n" +
            messageCourant +
            "\r\n.\r\n";

        socket->write(data.toUtf8());
        etape = 8;
    }
    else if (etape == 8 && r.contains("250")) {

        emit emailEnvoye(destinataireCourant, true, "✔ Email envoyé");

        indexDestinataire++;
        emit progressionEnvoi((indexDestinataire * 100) / listeDestinataires.size());

        envoyerCommande("QUIT");

        QTimer::singleShot(300, this, &EmailSMTPManager::envoyerAuDestinataire);
    }
}
