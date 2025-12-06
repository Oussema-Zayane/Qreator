#include "pdfexporter.h"
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPainter>
#include <QDir>
#include <QFileInfo>
#include <QSqlError>
#include <QTime>
#include <QSqlRecord>
#include <QDesktopServices>

PdfExporter::PdfExporter(QObject *parent) : QObject(parent)
{
}

bool PdfExporter::exportClientsToPdf(const QString &fileName)
{
    // Vérifier s'il y a des clients
    QSqlQuery countQuery("SELECT COUNT(*) FROM client");
    if (countQuery.next() && countQuery.value(0).toInt() == 0) {
        return false;
    }

    // Créer le document HTML
    QString html = createClientsPdfHtml();

    // Créer le document
    QTextDocument document;
    document.setHtml(html);

    // Configurer l'imprimante PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    // Exporter en PDF
    document.print(&printer);

    return true;
}

QString PdfExporter::createClientsPdfHtml()
{
    QString html;

    // En-tête HTML avec style
    html += "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<style>"
            "body { font-family: Arial, sans-serif; margin: 20px; color: #2C3E50; }"
            "h1 { color: #3498DB; text-align: center; margin-bottom: 10px; }"
            ".subtitle { text-align: center; color: #7F8C8D; margin-bottom: 20px; }"
            "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
            "th { background-color: #2C3E50; color: white; padding: 12px; text-align: left; font-weight: bold; }"
            "td { padding: 10px; border: 1px solid #BDC3C7; }"
            "tr:nth-child(even) { background-color: #F8F9FA; }"
            ".actif { color: #27AE60; font-weight: bold; }"
            ".inactif { color: #E74C3C; font-weight: bold; }"
            ".stats { margin-top: 30px; padding: 15px; background-color: #ECF0F1; border-radius: 5px; }"
            ".stats h3 { color: #2C3E50; margin-top: 0; }"
            ".footer { margin-top: 30px; text-align: center; color: #7F8C8D; font-size: 12px; }"
            "</style>"
            "</head>"
            "<body>";

    // Titre et informations
    html += "<h1>LISTE DES CLIENTS - SMART STUDIO</h1>"
            "<div class=\"subtitle\">"
            "Date d'export: " + QDate::currentDate().toString("dd/MM/yyyy") +
            "</div>";

    // Tableau des clients
    html += "<table>"
            "<tr>"
            "<th>ID</th>"
            "<th>Nom/Prénom</th>"
            "<th>Email</th>"
            "<th>Téléphone</th>"
            "<th>Date d'ajout</th>"
            "<th>Statut</th>"
            "</tr>";

    QSqlQuery query("SELECT id, nom_prenom, email, telephone, date_ajout, statut FROM client ORDER BY id");

    int totalClients = 0;
    int activeClients = 0;

    while (query.next()) {
        totalClients++;
        QString statut = query.value(5).toString();
        if (statut == "Actif") activeClients++;

        html += "<tr>";
        for (int i = 0; i < 6; i++) {
            QString value = query.value(i).toString();

            // Formater la date
            if (i == 4 && !value.isEmpty()) {
                QDate date = QDate::fromString(value, "yyyy-MM-dd");
                if (date.isValid()) {
                    value = date.toString("dd/MM/yyyy");
                }
            }

            // Colorer le statut
            if (i == 5) {
                QString cssClass = (value == "Actif") ? "actif" : "inactif";
                html += "<td class='" + cssClass + "'>" + value + "</td>";
            } else {
                html += "<td>" + value + "</td>";
            }
        }
        html += "</tr>";
    }

    html += "</table>";

    // Statistiques
    html += "<div class=\"stats\">"
            "<h3>📊 Statistiques</h3>"
            "<p><strong>Total clients:</strong> " + QString::number(totalClients) + "</p>"
                                              "<p><strong>Clients actifs:</strong> " + QString::number(activeClients) + "</p>"
                                               "<p><strong>Clients inactifs:</strong> " + QString::number(totalClients - activeClients) + "</p>"
                                                              "</div>";

    // Pied de page
    html += "<div class=\"footer\">"
            "Document généré par Smart Studio - Gestion Complète<br>"
            "© " + QString::number(QDate::currentDate().year()) + " Smart Digital Content Creation Studio"
                                                             "</div>";

    html += "</body></html>";

    return html;
}

bool PdfExporter::exportEquipementsToPdf(const QString &fileName)
{
    qDebug() << "=== DÉBUT EXPORT PDF ÉQUIPEMENTS ===";
    qDebug() << "Fichier de sortie:" << fileName;

    // 1. Vérifier la connexion
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "❌ Base de données non connectée";
        QMessageBox::critical(nullptr, "Erreur", "Base de données non connectée");
        return false;
    }

    // 2. Vérifier si la table EQUIPEMENT existe et contient des données
    QSqlQuery countQuery;
    if (!countQuery.exec("SELECT COUNT(*) FROM EQUIPEMENT")) {
        QString error = countQuery.lastError().text();
        qDebug() << "❌ Erreur COUNT:" << error;

        if (error.contains("table", Qt::CaseInsensitive) || error.contains("inexistante", Qt::CaseInsensitive)) {
            QMessageBox::warning(nullptr, "Table inexistante",
                                 "La table EQUIPEMENT n'existe pas dans la base de données.\n\n"
                                 "Assurez-vous que:\n"
                                 "1. Vous êtes connecté à la bonne base Oracle\n"
                                 "2. La table existe (nom: EQUIPEMENT en majuscules)\n"
                                 "3. Vous avez les permissions nécessaires");
        } else {
            QMessageBox::critical(nullptr, "Erreur SQL", "Erreur lors de l'accès à la table:\n" + error);
        }
        return false;
    }

    int count = 0;
    if (countQuery.next()) {
        count = countQuery.value(0).toInt();
        qDebug() << "Nombre d'équipements trouvés:" << count;
    }

    if (count == 0) {
        qDebug() << "⚠️ Table EQUIPEMENT est vide";
        QMessageBox::warning(nullptr, "Inventaire vide",
                             "La table EQUIPEMENT existe mais est vide.\n\n"
                             "Veuillez ajouter des équipements via l'interface de gestion.");

        // Créer un PDF vide avec un message
        return creerPdfVide(fileName, "Aucun équipement dans l'inventaire");
    }

    // 3. Créer le HTML
    QString html = createEquipementsPdfHtml();
    if (html.isEmpty()) {
        qDebug() << "❌ HTML vide";
        return false;
    }

    qDebug() << "HTML généré (" << html.length() << " caractères)";

    // 4. Créer le document PDF
    QTextDocument document;
    document.setHtml(html);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    // 5. Exporter
    document.print(&printer);

    qDebug() << "✅ PDF créé avec succès:" << fileName;
    qDebug() << "=== FIN EXPORT ===";

    // Ouvrir le PDF automatiquement
    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));

    return true;
}
QString PdfExporter::createEquipementsPdfHtml()
{
    qDebug() << "=== DÉBUT GÉNÉRATION HTML ÉQUIPEMENTS ===";

    // TEST IMMÉDIAT
    qDebug() << "Test direct SELECT...";
    QSqlQuery testQuery;
    bool testSuccess = testQuery.exec("SELECT ID, NOM, TYPE, ETAT, PRIX FROM EQUIPEMENT");
    qDebug() << "Test query success:" << testSuccess;
    qDebug() << "Test error:" << testQuery.lastError().text();

    if (!testSuccess) {
        // Essayer avec le nom en minuscules
        testQuery.exec("SELECT ID, NOM, TYPE, ETAT, PRIX FROM equipement");
        qDebug() << "Test lowercase success:" << testQuery.isActive();
        qDebug() << "Test lowercase error:" << testQuery.lastError().text();
    }

    QString html;

    // En-tête HTML SIMPLIFIÉ
    html += "<!DOCTYPE html>"
            "<html>"
            "<head>"
            "<meta charset=\"UTF-8\">"
            "<style>"
            "body { font-family: Arial, sans-serif; margin: 20px; color: #333; }"
            "h1 { color: #3498DB; text-align: center; }"
            "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
            "th { background-color: #2C3E50; color: white; padding: 10px; }"
            "td { padding: 8px; border: 1px solid #ddd; }"
            ".panne { color: red; font-weight: bold; }"
            ".fonctionnel { color: green; font-weight: bold; }"
            "</style>"
            "</head>"
            "<body>";

    // Titre
    html += "<h1>INVENTAIRE DES ÉQUIPEMENTS</h1>";
    html += "<p style='text-align:center;'>Date: " + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";

    // Tableau
    html += "<table border='1'>"
            "<tr>"
            "<th>ID</th><th>Nom</th><th>Type</th><th>État</th><th>Prix (€)</th><th>Date</th>"
            "</tr>";

    // REQUÊTE LA PLUS SIMPLE POSSIBLE
    QSqlQuery query;
    QString sql = "SELECT ID, NOM, TYPE, ETAT, PRIX, DATE_AJOUT FROM EQUIPEMENT ORDER BY ID";

    qDebug() << "Exécution SQL:" << sql;

    if (!query.exec(sql)) {
        qDebug() << "❌ Échec requête:" << query.lastError().text();
        html += "<tr><td colspan='6' style='color:red;text-align:center;padding:20px;'>"
                "ERREUR SQL: " + query.lastError().text() + "</td></tr>";
    } else {
        qDebug() << "✅ Requête exécutée avec succès";

        int rowCount = 0;
        while (query.next()) {
            rowCount++;

            int id = query.value(0).toInt();
            QString nom = query.value(1).toString();
            QString type = query.value(2).toString();
            QString etat = query.value(3).toString();
            double prix = query.value(4).toDouble();
            QString date = query.value(5).toString();

            qDebug() << "Ligne" << rowCount << ":" << id << nom << type << etat << prix << date;

            // Formater la date si nécessaire
            QDate qdate = QDate::fromString(date, "yyyy-MM-dd");
            if (qdate.isValid()) {
                date = qdate.toString("dd/MM/yyyy");
            }

            // Déterminer la classe CSS pour l'état
            QString etatClass = "";
            QString etatLower = etat.toLower();
            if (etatLower.contains("panne")) {
                etatClass = "panne";
            } else if (etatLower.contains("fonctionnel") || etatLower.contains("bon")) {
                etatClass = "fonctionnel";
            }

            // Ajouter la ligne au HTML
            html += "<tr>";
            html += "<td>" + QString::number(id) + "</td>";
            html += "<td>" + nom + "</td>";
            html += "<td>" + type + "</td>";
            html += "<td class='" + etatClass + "'>" + etat + "</td>";
            html += "<td style='text-align:right;'>" + QString::number(prix, 'f', 2) + " €</td>";
            html += "<td>" + date + "</td>";
            html += "</tr>";
        }

        qDebug() << "Total lignes traitées:" << rowCount;

        if (rowCount == 0) {
            html += "<tr><td colspan='6' style='text-align:center;padding:20px;color:#666;font-style:italic;'>"
                    "⚠️ Aucun équipement trouvé dans la base de données</td></tr>";
        }
    }

    html += "</table>";

    // Statistiques
    QSqlQuery statsQuery("SELECT COUNT(*), SUM(PRIX) FROM EQUIPEMENT");
    if (statsQuery.next()) {
        int total = statsQuery.value(0).toInt();
        double valeur = statsQuery.value(1).toDouble();

        html += "<div style='margin-top:30px;padding:15px;background:#f5f5f5;border-radius:5px;'>";
        html += "<h3>📊 Statistiques</h3>";
        html += "<p>Total équipements: <strong>" + QString::number(total) + "</strong></p>";
        html += "<p>Valeur totale: <strong>" + QString::number(valeur, 'f', 2) + " €</strong></p>";
        html += "</div>";
    }

    // Pied de page
    html += "<div style='margin-top:30px;text-align:center;color:#777;font-size:12px;border-top:1px solid #ddd;padding-top:10px;'>";
    html += "Document généré par Smart Studio - " + QDate::currentDate().toString("dd/MM/yyyy");
    html += "</div>";

    html += "</body></html>";

    qDebug() << "=== FIN GÉNÉRATION HTML ===";
    qDebug() << "Taille HTML:" << html.length() << "caractères";

    return html;
}

bool PdfExporter::creerPdfVide(const QString &fileName, const QString &message)
{
    qDebug() << "Création d'un PDF vide avec message:" << message;

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter;
    if (!painter.begin(&printer)) {
        qDebug() << "❌ Impossible de commencer à peindre";
        return false;
    }

    // Dimensions
    int pageWidth = printer.width();
    int pageHeight = printer.height();

    // Style
    QFont titleFont("Arial", 20, QFont::Bold);
    QFont messageFont("Arial", 12);
    QFont infoFont("Arial", 10);

    // Titre
    painter.setFont(titleFont);
    painter.setPen(QColor(52, 73, 94)); // #34495E
    painter.drawText(0, 100, pageWidth, 50, Qt::AlignCenter,
                     "📦 INVENTAIRE DES ÉQUIPEMENTS");

    // Sous-titre
    painter.setFont(QFont("Arial", 14, QFont::Normal));
    painter.setPen(QColor(127, 140, 141)); // #7F8C8D
    painter.drawText(0, 160, pageWidth, 30, Qt::AlignCenter,
                     "Smart Studio - Gestion du Matériel");

    // Ligne de séparation
    painter.setPen(QColor(189, 195, 199)); // #BDC3C7
    painter.drawLine(50, 210, pageWidth - 50, 210);

    // Message principal
    painter.setFont(messageFont);
    painter.setPen(QColor(231, 76, 60)); // #E74C3C
    painter.drawText(50, 260, pageWidth - 100, 100, Qt::AlignCenter, message);

    // Instructions
    painter.setFont(infoFont);
    painter.setPen(Qt::black);
    painter.drawText(50, 380, pageWidth - 100, 100, Qt::AlignCenter,
                     "Veuillez ajouter des équipements via l'interface de gestion.");

    // Date
    QString dateStr = "Document généré le " + QDate::currentDate().toString("dd/MM/yyyy");
    painter.setFont(QFont("Arial", 9));
    painter.setPen(QColor(127, 140, 141)); // #7F8C8D
    painter.drawText(0, pageHeight - 50, pageWidth, 30,
                     Qt::AlignCenter, dateStr);

    painter.end();

    qDebug() << "✅ PDF vide créé:" << fileName;
    return true;
}
