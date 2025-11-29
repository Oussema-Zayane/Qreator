#include "chatbotdialog.h"
#include "ui_chatbotdialog.h"
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonArray>
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

    // Mode 100% gratuit - pas besoin de clé API
    apiKey = "";

    // Connexions
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &ChatbotDialog::on_apiResponseReceived);

    // Message de bienvenue
    addMessage("Assistant", "Bonjour ! Je suis l'assistant Smart Studio. 🤖\n"
                            "Comment puis-je vous aider aujourd'hui ?", false);
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
    addMessage("Assistant", "Je réfléchis... 🔄", false);

    // MODE 100% GRATUIT - Intelligence locale
    QTimer::singleShot(800, [this, message]() {
        QString response = getAdvancedResponse(message);
        replaceLastMessage(response);
    });
}

void ChatbotDialog::replaceLastMessage(const QString &newMessage)
{
    QTextCursor cursor = ui->chatDisplay->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.select(QTextCursor::BlockUnderCursor);
    cursor.removeSelectedText();

    addMessage("Assistant", newMessage, false);
}

QString ChatbotDialog::getAdvancedResponse(const QString &message)
{
    QString lowerMsg = message.toLower().trimmed();

    // 🔥 INTELLIGENCE AVANCÉE SANS API
    if (lowerMsg.contains("bonjour") || lowerMsg.contains("salut") || lowerMsg.contains("coucou") || lowerMsg.contains("hello")) {
        return "Bonjour ! 😊 Je suis l'assistant Smart Studio.\n\n"
               "🎯 **Comment puis-je vous aider ?**\n"
               "• Découvrir nos services créatifs\n• Obtenir un devis personnalisé\n• Planifier un projet\n• Nous contacter";
    }

    else if (lowerMsg.contains("service") || lowerMsg.contains("quoi") || lowerMsg.contains("offre") || lowerMsg.contains("faites")) {
        return "🎬 **NOS SERVICES CRÉATIFS**\n\n"
               "📸 **PHOTOGRAPHIE PROFESSIONNELLE**\n• Shooting portrait & corporate\n• Photo produit e-commerce\n• Reportage événementiel\n• Retouches professionnelles\n\n"
               "🎥 **PRODUCTION VIDÉO**\n• Films institutionnels\n• Publicités & spots TV\n• Vidéos réseaux sociaux\n• Drone & prises de vues aériennes\n\n"
               "🎨 **DESIGN GRAPHIQUE**\n• Identité visuelle (logo, charte)\n• Supports print (flyers, affiches)\n• Packaging & étiquettes\n• Illustrations sur mesure\n\n"
               "🌐 **DÉVELOPPEMENT DIGITAL**\n• Sites vitrine responsive\n• Boutiques e-commerce\n• Applications web\n• Référencement SEO\n\n"
               "📱 **STRATÉGIE DIGITALE**\n• Community management\n• Campagnes publicitaires\n• Création de contenu\n• Analyse de performance";
    }

    else if (lowerMsg.contains("prix") || lowerMsg.contains("tarif") || lowerMsg.contains("combien") || lowerMsg.contains("coût") || lowerMsg.contains("€")) {
        return "💰 **DEVIS PERSONNALISÉ GRATUIT**\n\n"
               "📸 **Photographie**\n• Shooting basique : 250€ 🡒 450€\n• Pack entreprise : 450€ 🡒 800€\n• Événement (demi-journée) : 600€ 🡒 900€\n\n"
               "🎥 **Vidéo**\n• Clip 1-2min : 500€ 🡒 900€\n• Film corporate 3-5min : 800€ 🡒 1500€\n• Publicité 30sec : 1200€ 🡒 2000€\n\n"
               "🎨 **Design**\n• Logo : 150€ 🡒 300€\n• Charte graphique complète : 400€ 🡒 700€\n• Maquette site web : 200€ 🡒 400€\n\n"
               "🌐 **Site Internet**\n• Vitrine 5 pages : 800€ 🡒 1500€\n• E-commerce : 1500€ 🡒 3000€\n• Application sur mesure : devis personnalisé\n\n"
               "💡 *Tous nos devis incluent : conseil, réalisation, révisions, livraison*";
    }

    else if (lowerMsg.contains("contact") || lowerMsg.contains("email") || lowerMsg.contains("téléphone") || lowerMsg.contains("tel") || lowerMsg.contains("appeler")) {
        return "📞 **PRENONS CONTACT !**\n\n"
               "📍 **Smart Studio**\n123 Avenue de la Création\n75000 Paris, France\n\n"
               "📞 **Téléphone**\n+33 1 23 45 67 89\n*(Du lundi au vendredi, 9h-18h)*\n\n"
               "📧 **Email**\ncontact@smartstudio.com\n*(Réponse sous 24h)*\n\n"
               "💬 **Rendez-vous**\n• En studio : Lundi - Vendredi 9h-18h\n• En visio : Sur rendez-vous\n• Urgence : +33 6 12 34 56 78\n\n"
               "🌐 **Réseaux sociaux**\n@SmartStudioParis";
    }

    else if (lowerMsg.contains("projet") || lowerMsg.contains("commencer") || lowerMsg.contains("démarrer") || lowerMsg.contains("commande")) {
        return "🚀 **LANÇONS VOTRE PROJET !**\n\n"
               "1. **📞 Consultation gratuite**\n   - Analyse de vos besoins\n   - Conseils stratégiques\n   - Estimation budgétaire\n\n"
               "2. **📝 Devis personnalisé**\n   - Détail des prestations\n   - Planning de réalisation\n   - Proposition tarifaire\n\n"
               "3. **✍️ Validation & contrat**\n   - Signature du devis\n   - Planning confirmé\n   - Début de la création\n\n"
               "4. **🎨 Réalisation**\n   - Suivi régulier\n   - Validations intermédiaires\n   - Adjustements si besoin\n\n"
               "5. **🎯 Livraison**\n   - Produit final\n   - Support après livraison\n   - Satisfaction garantie\n\n"
               "**💡 Prêt à commencer ? Contactez-nous !**";
    }

    else if (lowerMsg.contains("délai") || lowerMsg.contains("temps") || lowerMsg.contains("quand") || lowerMsg.contains("durée")) {
        return "⏱️ **DÉLAIS DE RÉALISATION**\n\n"
               "• Logo & identité visuelle : 3-7 jours\n• Shooting photo : 5-10 jours\n• Vidéo 2-3min : 2-3 semaines\n• Site vitrine : 3-4 semaines\n• Application web : 6-8 semaines\n• Campagne réseaux sociaux : 1-2 semaines\n\n"
               "⚡ **Service express** : +30% de frais\n🔄 **Révisions incluses** : 2 rounds de modifications";
    }

    else if (lowerMsg.contains("portfolio") || lowerMsg.contains("exemple") || lowerMsg.contains("réalisation") || lowerMsg.contains("travail")) {
        return "🎨 **NOTRE PORTFOLIO**\n\n"
               "📸 **Projets photo récents**\n• Marque de luxe - Shooting produit\n• Startup tech - Portraits corporate\n• Restaurant - Photos culinaires\n\n"
               "🎥 **Réalisations vidéo**\n• Film corporate pour groupe international\n• Publicité télévisée marque automobile\n• Série de vidéos réseaux sociaux\n\n"
               "🌐 **Sites web livrés**\n• E-commerce mode & accessoires\n• Site vitrine cabinet d'architecture\n• Plateforme SaaS startup tech\n\n"
               "**📧 Demandez notre book complet !**";
    }

    else if (lowerMsg.contains("urgence") || lowerMsg.contains("rapide") || lowerMsg.contains("vite")) {
        return "⚡ **SERVICE URGENCE**\n\n"
               "Nous comprenons l'urgence de votre projet !\n\n"
               "📞 **Contact urgence** : +33 6 12 34 56 78\n⏱️ **Délais express** : Jusqu'à 50% plus rapide\n🎯 **Priorité absolue** sur votre projet\n\n"
               "**Appelez-nous immédiatement !**";
    }

    else if (lowerMsg.contains("merci") || lowerMsg.contains("remercie")) {
        return "Je vous en prie ! 😊\n\n"
               "Ce fut un plaisir de vous aider.\n"
               "N'hésitez pas si vous avez d'autres questions.\n\n"
               "Belle journée et à bientôt ! ✨";
    }

    else if (lowerMsg.contains("au revoir") || lowerMsg.contains("bye") || lowerMsg.contains("à bientôt") || lowerMsg.contains("salut")) {
        return "Au revoir ! 👋\n\n"
               "Merci d'avoir choisi Smart Studio.\n"
               "Nous espérons collaborer avec vous bientôt !\n\n"
               "🌟 **L'équipe Smart Studio**";
    }

    else {
        return "🤔 **Je comprends votre demande**\n\n"
               "Vous souhaitez : \"" + message + "\"\n\n"
                           "En tant qu'assistant Smart Studio, je peux vous aider avec :\n"
                           "• La découverte de nos services créatifs\n• L'obtention d'un devis personnalisé\n• La planification de votre projet\n• La prise de contact avec notre équipe\n• Les informations tarifaires et délais\n\n"
                           "**Pouvez-vous préciser votre demande ?**\n"
                           "Ou contactez-nous directement au +33 1 23 45 67 89";
    }
}

void ChatbotDialog::on_apiResponseReceived(QNetworkReply *reply)
{
    // Gardé pour compatibilité future
    reply->deleteLater();
}

QString ChatbotDialog::extractResponseFromJSON(const QByteArray &jsonData)
{
    // Gardé pour compatibilité future
    return "Fonction API désactivée - Mode local activé";
}
