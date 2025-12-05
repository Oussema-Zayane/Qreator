#ifndef CHATBOTDIALOG_H
#define CHATBOTDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QJsonObject>    // AJOUTE CETTE LIGNE
#include <QJsonArray>     // AJOUTE CETTE LIGNE
#include <QJsonDocument>  // AJOUTE CETTE LIGNE


namespace Ui {
class ChatbotDialog;
}

class ChatbotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatbotDialog(QWidget *parent = nullptr);
    ~ChatbotDialog();

private slots:
    void on_sendButton_clicked();
    void on_apiResponseReceived(QNetworkReply *reply);
    void on_inputText_returnPressed();

private:
    Ui::ChatbotDialog *ui;
    QNetworkAccessManager *networkManager;
    void sendToChatbot(const QString &message);
    void addMessage(const QString &sender, const QString &message, bool isUser = true);
    QString extractResponseFromJSON(const QByteArray &jsonData);
    QString apiKey;  // AJOUTE CETTE LIGNE
    QString getAdvancedResponse(const QString &message);
    void replaceLastMessage(const QString &newMessage);

};

#endif // CHATBOTDIALOG_H
