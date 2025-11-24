#include "chatbotdialog.h"
#include "ui_chatbotdialog.h"
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QScrollBar>
#include <QDateTime>
#include <QTimer>

ChatbotDialog::ChatbotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatbotDialog),
    networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // Configuration de l'interface
    setWindowTitle("🤖 Assistant Client - Smart Studio");
    setFixedSize(600, 500);

    // Connexions
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &ChatbotDialog::on_apiResponseReceived);

    // Message de bienvenue
    addMessage("Assistant", "Bonjour ! Je suis l'assistant de Smart Studio. 🤖\n"
                            "Comment puis-je vous aider aujourd'hui ?\n\n"
                            "Je peux vous renseigner sur :\n"
                            "• Nos services de création de contenu\n"
                            "• Les tarifs et devis\n"
                            "• Le suivi de vos projets\n"
                            "• La gestion de vos équipements\n"
                            "• Et bien plus encore !", false);
}

ChatbotDialog::~ChatbotDialog()
{
    delete ui;
}

void ChatbotDialog::addMessage(const QString &sender, const QString &message, bool isUser)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm");
    QString cssClass = isUser ? "user-message" : "bot-message";
    QString senderIcon = isUser ? "👤" : "🤖";

    QString htmlMessage = QString(
                              "<div class='message %1'>"
                              "<div class='sender'>%2 <strong>%3</strong> <span class='time'>%4</span></div>"
                              "<div class='content'>%5</div>"
                              "</div>"
                              ).arg(cssClass, senderIcon, sender, timestamp, message.toHtmlEscaped().replace("\n", "<br>"));

    ui->chatDisplay->append(htmlMessage);

    // Scroll vers le bas
    QScrollBar *scrollBar = ui->chatDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void ChatbotDialog::on_sendButton_clicked()
{
    QString message = ui->inputText->text().trimmed();
    if (message.isEmpty()) return;

    // Ajouter le message de l'utilisateur
    addMessage("Vous", message, true);
    ui->inputText->clear();

    // Envoyer au chatbot
    sendToChatbot(message);
}

void ChatbotDialog::on_inputText_returnPressed()
{
    on_sendButton_clicked();
}

void ChatbotDialog::sendToChatbot(const QString &message)
{
    // SIMULATION - Remplace par une vraie API plus tard
    addMessage("Assistant", "Je réfléchis... 🔄", false);

    // Pour l'instant, on simule des réponses basiques
    QTimer::singleShot(1000, [this, message]() {
        QString response;

        if (message.contains("bonjour", Qt::CaseInsensitive) ||
            message.contains("salut", Qt::CaseInsensitive)) {
            response = "Bonjour ! Ravie de vous aider. 😊\n"
                       "Que souhaitez-vous savoir sur Smart Studio ?";
        }
        else if (message.contains("prix", Qt::CaseInsensitive) ||
                 message.contains("tarif", Qt::CaseInsensitive) ||
                 message.contains("combien", Qt::CaseInsensitive)) {
            response = "💰 **Nos tarifs varient selon le projet :**\n\n"
                       "• **Photographie** : à partir de 250€\n"
                       "• **Vidéo** : à partir de 500€\n"
                       "• **Design** : à partir de 150€\n"
                       "• **Site web** : à partir de 800€\n\n"
                       "Je peux vous préparer un devis personnalisé !";
        }
        else if (message.contains("service", Qt::CaseInsensitive) ||
                 message.contains("offre", Qt::CaseInsensitive)) {
            response = "🎬 **Nos services :**\n\n"
                       "• 📸 Photographie professionnelle\n"
                       "• 🎥 Production vidéo\n"
                       "• 📱 Contenu réseaux sociaux\n"
                       "• 🎨 Design graphique\n"
                       "• 🌐 Développement web\n"
                       "• 📊 Stratégie digitale\n\n"
                       "Lequel vous intéresse ?";
        }
        else if (message.contains("contact", Qt::CaseInsensitive) ||
                 message.contains("email", Qt::CaseInsensitive) ||
                 message.contains("téléphone", Qt::CaseInsensitive)) {
            response = "📞 **Nous contacter :**\n\n"
                       "• 📧 Email : contact@smartstudio.com\n"
                       "• 📞 Téléphone : +33 1 23 45 67 89\n"
                       "• 📍 Adresse : 123 Avenue de la Création, Paris\n"
                       "• 💬 Disponible du lundi au vendredi, 9h-18h";
        }
        else if (message.contains("merci", Qt::CaseInsensitive)) {
            response = "Je vous en prie ! 😊\n"
                       "N'hésitez pas si vous avez d'autres questions.";
        }
        else {
            response = "Je comprends que vous souhaitez savoir : \"" + message + "\"\n\n"
                                                                                 "En tant qu'assistant de Smart Studio, je peux vous aider avec :\n"
                                                                                 "• Les informations sur nos services\n"
                                                                                 "• Les tarifs et devis\n"
                                                                                 "• Le suivi de projet\n"
                                                                                 "• La gestion client\n"
                                                                                 "• Nos équipements disponibles\n\n"
                                                                                 "Pouvez-vous reformuler votre question ?";
        }

        // Remplacer le message "Je réfléchis..." par la vraie réponse
        QTextCursor cursor = ui->chatDisplay->textCursor();
        cursor.movePosition(QTextCursor::End);
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();

        addMessage("Assistant", response, false);
    });
}

void ChatbotDialog::on_apiResponseReceived(QNetworkReply *reply)
{
    // À implémenter pour une vraie API
    reply->deleteLater();
}
