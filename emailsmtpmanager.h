#ifndef EMAILSMTPMANAGER_H
#define EMAILSMTPMANAGER_H

#include <QObject>
#include <QSslSocket>
#include <QString>
#include <QStringList>

class EmailSMTPManager : public QObject {
    Q_OBJECT

public:
    explicit EmailSMTPManager(QObject *parent = nullptr);

    void configurerSMTP(const QString &email, const QString &motDePasseApp);

    // Pour un email simple
    void envoyerEmail(const QString &destinataire,
                      const QString &sujet,
                      const QString &messageHtml);

    // Pour plusieurs destinataires
    void envoyerEmailMultiple(const QStringList &destinataires,
                              const QString &sujet,
                              const QString &messageHtml);

signals:
    void emailEnvoye(const QString &destinataire, bool succes, const QString &details);
    void progressionEnvoi(int pourcentage);
    void envoiTermine();
    void erreur(const QString &details);

private slots:
    void onConnected();
    void onEncrypted();
    void onReadyRead();

private:
    QSslSocket *socket;

    QString emailUtilisateur, motDePasse;
    QString sujetCourant, messageCourant;

    QStringList listeDestinataires;
    int indexDestinataire; // Pour l’envoi multiple

    QString destinataireCourant;

    int etape;

    void envoyerCommande(const QString &cmd);
    void envoyerAuDestinataire(); // pour l’envoi multiple
};

#endif
