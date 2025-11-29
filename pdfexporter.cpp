#include "pdfexporter.h"
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QDate>

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
