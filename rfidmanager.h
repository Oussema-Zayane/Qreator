#ifndef RFIDMANAGER_H
#define RFIDMANAGER_H

#include <QObject>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QThread>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class RFIDManager : public QObject
{
    Q_OBJECT

public:
    explicit RFIDManager(QObject *parent = nullptr);
    ~RFIDManager();

    // Connexion Arduino
    bool startRFID();
    void stopRFID();
    bool isConnected() const { return serialPort && serialPort->isOpen(); }

    // Vérification employé
    bool checkEmployeeUID(const QString &uid, QString &nom, QString &prenom, QString &role);

    // Association carte
    bool associateCardToEmployee(int employeId, const QString &rfidUID);

    // Communication Arduino
    void sendToArduino(const QString &command);

    // Utilitaires
    void cleanupUID(QString &uid);
    QString getLastUID() const { return lastUID; }
    void resetLastUID() { lastUID.clear(); }
    void displayOnLCD(const QString &message1, const QString &message2 = "");

signals:
    void cardScanned(const QString &uid);
    void arduinoConnected(bool connected);
    void errorOccurred(const QString &error);
    void arduinoMessageReceived(const QString &message);

private slots:
    void readSerialData();

private:
    QSerialPort *serialPort;
    QString lastUID;
    QString buffer;

    // Méthodes privées
    void processReceivedLine(const QString &line);
    void processRFIDLine(const QString &line);
    QTimer *scanCooldownTimer;
    bool isScanInCooldown;

    // Recherche ports
    QStringList findAvailablePorts();

};

// Fonction d'authentification RFID pour employé
bool authenticateEmployeWithRFID(QString &nom, QString &prenom, QString &role);

#endif // RFIDMANAGER_H
