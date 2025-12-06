#include "equipement.h"
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPainter>
#include <QDesktopServices>
#include <QDate>
#include <QPrinter>
#include <QPainter>
#include <QFileDialog>
#include "pdfexporter.h"
#include <QPrinter>
#include <QPainter>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include <QTime>




Equipement::Equipement() : id(0), nom(""), type(""), etat(""), prix(0) {}

Equipement::Equipement(int id, QString nom, QString type, QString etat, double prix)
    : id(id), nom(nom), type(type), etat(etat), prix(prix) {}

bool Equipement::validerNom(const QString& nom)
{
    return !nom.isEmpty() && nom.length() >= 2;
}

bool Equipement::validerPrix(double prix)
{
    return prix >= 0;
}

bool Equipement::ajouter()
{
    if (!validerNom(nom) || !validerPrix(prix)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO equipement (id, nom, type, etat, prix, date_ajout) "
                  "VALUES (:id, :nom, :type, :etat, :prix, SYSDATE)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);

    return query.exec();
}

bool Equipement::supprimer(int id)
{
    // Récupérer les infos avant suppression pour archivage
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT nom, type, etat, prix FROM equipement WHERE id = :id");
    selectQuery.bindValue(":id", id);

    if (selectQuery.exec() && selectQuery.next()) {
        QString nom = selectQuery.value(0).toString();
        QString type = selectQuery.value(1).toString();
        QString etat = selectQuery.value(2).toString();
        double prix = selectQuery.value(3).toDouble();

        // Archiver la suppression
        archiverSuppression(id, nom, type, etat, prix);
    }

    // Supprimer l'équipement
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM equipement WHERE id = :id");
    deleteQuery.bindValue(":id", id);

    return deleteQuery.exec();
}

bool Equipement::archiverSuppression(int id, QString nom, QString type, QString etat, double prix)
{
    QSqlQuery query;
    query.prepare("INSERT INTO equipement_historique (id_original, nom, type, etat, prix, date_suppression) "
                  "VALUES (:id, :nom, :type, :etat, :prix, SYSDATE)");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);

    return query.exec();
}

QSqlQueryModel* Equipement::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT ID, NOM, TYPE, ETAT, PRIX, DATE_AJOUT FROM EQUIPEMENT ORDER BY DATE_AJOUT DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'ajout"));
    return model;
}

QSqlQueryModel* Equipement::afficherHistoriqueSuppressions()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id_original, nom, type, etat, prix, date_suppression "
                    "FROM equipement_historique ORDER BY date_suppression DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Original"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date suppression"));
    return model;
}

QSqlQueryModel* Equipement::afficherEquipementsEnPanne()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom, type, etat, prix, date_ajout "
                    "FROM equipement WHERE etat LIKE '%panne%' OR etat LIKE '%Panne%' ORDER BY date_ajout DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("État"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Prix"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date d'ajout"));
    return model;
}

int Equipement::compterEquipementsEnPanne()
{
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM equipement WHERE etat LIKE '%panne%' OR etat LIKE '%Panne%'");

    if (query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}


bool Equipement::modifier(int id, QString nom, QString type, QString etat, double prix)
{
    if (!validerNom(nom) || !validerPrix(prix)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE equipement SET nom = :nom, type = :type, etat = :etat, prix = :prix WHERE id = :id");

    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":type", type);
    query.bindValue(":etat", etat);
    query.bindValue(":prix", prix);

    return query.exec();
}

bool Equipement::exporterPDF(const QString& cheminFichier)
{
    qDebug() << "🔄 Début de l'export PDF des équipements vers:" << cheminFichier;

    // Créer le printer PDF
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(cheminFichier);
    printer.setPageSize(QPageSize(QPageSize::A4));

    QPainter painter;
    if (!painter.begin(&printer)) {
        qDebug() << "❌ Erreur: Impossible d'initialiser le painter";
        return false;
    }

    // ==================== CONFIGURATION ====================
    QFont titleFont("Arial", 20, QFont::Bold);  // Augmenté de 18 à 20
    QFont subtitleFont("Arial", 14, QFont::Normal);  // Augmenté de 12 à 14
    QFont headerFont("Arial", 11, QFont::Bold);  // Augmenté de 10 à 11
    QFont dataFont("Arial", 10, QFont::Normal);  // Augmenté de 9 à 10
    QFont footerFont("Arial", 9);  // Augmenté de 8 à 9

    // Dimensions de la page
    int pageWidth = printer.width();
    int pageHeight = printer.height();
    int leftMargin = 40;  // Marge gauche
    int rightMargin = pageWidth - 40;  // Marge droite
    int usableWidth = pageWidth - 80;  // Largeur utilisable

    int y = 40;  // Position Y initiale
    int lineHeight = 28;  // Hauteur de ligne augmentée

    // ==================== EN-TÊTE ====================
    // Titre principal
    painter.setFont(titleFont);
    painter.setPen(QColor(44, 62, 80)); // #2C3E50
    painter.drawText(0, y, pageWidth, 50, Qt::AlignCenter,
                     "📦 INVENTAIRE DES ÉQUIPEMENTS");
    y += 60;

    // Sous-titre
    painter.setFont(subtitleFont);
    painter.setPen(QColor(52, 73, 94)); // #34495E
    painter.drawText(0, y, pageWidth, 30, Qt::AlignCenter,
                     "Smart Studio - Gestion du Matériel");
    y += 40;

    // Informations de date
    painter.setFont(dataFont);
    painter.setPen(Qt::black);

    QString dateStr = "Date de génération: " + QDate::currentDate().toString("dd/MM/yyyy");
    QString timeStr = "Heure: " + QTime::currentTime().toString("HH:mm");

    painter.drawText(leftMargin, y, 400, 25, Qt::AlignLeft, dateStr);
    painter.drawText(rightMargin - 200, y, 200, 25, Qt::AlignRight, timeStr);
    y += 35;

    // Ligne de séparation
    painter.setPen(QColor(189, 195, 199)); // #BDC3C7
    painter.drawLine(leftMargin, y, rightMargin, y);
    y += 25;

    // ==================== EN-TÊTES DE COLONNES ====================
    painter.setFont(headerFont);
    painter.setPen(Qt::white);
    painter.setBrush(QColor(52, 73, 94)); // #34495E

    // Dessiner le rectangle d'en-tête avec plus de hauteur
    int headerHeight = lineHeight + 10;
    painter.drawRect(leftMargin, y, usableWidth, headerHeight);

    // Définir les colonnes avec des largeurs proportionnelles
    struct Column {
        QString title;
        int width;
        Qt::Alignment alignment;
    };

    QVector<Column> columns = {
        {"ID", usableWidth * 5 / 100, Qt::AlignCenter},      // 5% de la largeur
        {"NOM", usableWidth * 25 / 100, Qt::AlignLeft},      // 25% de la largeur
        {"TYPE", usableWidth * 15 / 100, Qt::AlignLeft},     // 15% de la largeur
        {"ÉTAT", usableWidth * 15 / 100, Qt::AlignLeft},     // 15% de la largeur
        {"PRIX (€)", usableWidth * 15 / 100, Qt::AlignRight}, // 15% de la largeur
        {"DATE AJOUT", usableWidth * 25 / 100, Qt::AlignCenter} // 25% de la largeur
    };

    // Dessiner les en-têtes
    int xPos = leftMargin + 10;
    for (const Column &col : columns) {
        painter.drawText(QRect(xPos, y + 8, col.width, headerHeight),
                         col.alignment | Qt::AlignVCenter,
                         col.title);
        xPos += col.width;
    }

    y += headerHeight + 5;

    // ==================== DONNÉES ====================
    painter.setFont(dataFont);
    painter.setPen(Qt::black);

    // Récupérer les données
    QSqlQuery query;
    bool querySuccess = query.exec(
        "SELECT id, nom, type, etat, prix, "
        "TO_CHAR(date_ajout, 'DD/MM/YYYY') "
        "FROM equipement "
        "ORDER BY nom"
        );

    if (!querySuccess) {
        qDebug() << "❌ Erreur SQL:" << query.lastError().text();
        painter.end();
        return false;
    }

    int rowNum = 0;
    int totalEquipements = 0;
    double valeurTotale = 0.0;
    int panneCount = 0;
    int fonctionnelCount = 0;

    while (query.next()) {
        // Vérifier si on doit changer de page
        if (y > pageHeight - 100) {
            printer.newPage();
            y = 40;

            // Redessiner les en-têtes sur la nouvelle page
            painter.setFont(headerFont);
            painter.setPen(Qt::white);
            painter.setBrush(QColor(52, 73, 94));

            painter.drawRect(leftMargin, y, usableWidth, headerHeight);

            xPos = leftMargin + 10;
            for (const Column &col : columns) {
                painter.drawText(QRect(xPos, y + 8, col.width, headerHeight),
                                 col.alignment | Qt::AlignVCenter,
                                 col.title);
                xPos += col.width;
            }

            y += headerHeight + 5;
            painter.setFont(dataFont);
            painter.setPen(Qt::black);
        }

        // Récupérer les données
        int id = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString type = query.value(2).toString();
        QString etat = query.value(3).toString();
        double prix = query.value(4).toDouble();
        QString date = query.value(5).toString();

        // Alterner les couleurs de fond pour la lisibilité
        if (rowNum % 2 == 0) {
            painter.setBrush(QColor(248, 249, 250)); // #F8F9FA - gris très clair
        } else {
            painter.setBrush(Qt::white);
        }

        // Dessiner le fond de la ligne
        painter.setPen(Qt::NoPen);
        painter.drawRect(leftMargin, y, usableWidth, lineHeight);
        painter.setPen(Qt::black);

        // Dessiner les données de la ligne
        xPos = leftMargin + 10;

        // Colonne 1: ID
        painter.drawText(QRect(xPos, y, columns[0].width, lineHeight),
                         columns[0].alignment | Qt::AlignVCenter,
                         QString::number(id));
        xPos += columns[0].width;

        // Colonne 2: Nom (avec éventuellement un retour à la ligne si trop long)
        QString nomDisplay = nom;
        if (nom.length() > 30) {
            nomDisplay = nom.left(27) + "...";
        }
        painter.drawText(QRect(xPos, y, columns[1].width, lineHeight),
                         columns[1].alignment | Qt::AlignVCenter,
                         nomDisplay);
        xPos += columns[1].width;

        // Colonne 3: Type
        painter.drawText(QRect(xPos, y, columns[2].width, lineHeight),
                         columns[2].alignment | Qt::AlignVCenter,
                         type);
        xPos += columns[2].width;

        // Colonne 4: État (avec couleur selon l'état)
        QString etatLower = etat.toLower();
        QColor etatColor = Qt::black;

        if (etatLower.contains("panne")) {
            etatColor = QColor(231, 76, 60); // Rouge #E74C3C
            panneCount++;
        } else if (etatLower.contains("fonctionnel") || etatLower.contains("bon état")) {
            etatColor = QColor(39, 174, 96); // Vert #27AE60
            fonctionnelCount++;
        } else if (etatLower.contains("maintenance") || etatLower.contains("réparation")) {
            etatColor = QColor(241, 196, 15); // Jaune #F1C40F
        }

        painter.setPen(etatColor);
        painter.drawText(QRect(xPos, y, columns[3].width, lineHeight),
                         columns[3].alignment | Qt::AlignVCenter,
                         etat);
        painter.setPen(Qt::black);
        xPos += columns[3].width;

        // Colonne 5: Prix (formaté avec 2 décimales)
        QString prixFormatted = QString::number(prix, 'f', 2) + " €";
        painter.drawText(QRect(xPos, y, columns[4].width, lineHeight),
                         columns[4].alignment | Qt::AlignVCenter,
                         prixFormatted);
        xPos += columns[4].width;

        // Colonne 6: Date
        painter.drawText(QRect(xPos, y, columns[5].width, lineHeight),
                         columns[5].alignment | Qt::AlignVCenter,
                         date);

        y += lineHeight;
        rowNum++;
        totalEquipements++;
        valeurTotale += prix;
    }

    // ==================== RÉSUMÉ ====================
    y += 30;

    // Ligne de séparation épaisse
    painter.setPen(QPen(QColor(52, 73, 94), 2)); // #34495E, épaisseur 2
    painter.drawLine(leftMargin, y, rightMargin, y);
    y += 30;

    // Titre du résumé
    painter.setFont(headerFont);
    painter.setPen(QColor(44, 62, 80)); // #2C3E50
    painter.drawText(leftMargin, y, usableWidth, 30, Qt::AlignLeft,
                     "📊 RÉSUMÉ DE L'INVENTAIRE");
    y += 35;

    // Statistiques en deux colonnes
    painter.setFont(dataFont);
    painter.setPen(Qt::black);

    int col1X = leftMargin;
    int col2X = leftMargin + usableWidth / 2;

    // Colonne 1
    painter.drawText(col1X, y, 300, 25, Qt::AlignLeft,
                     QString("• Nombre total d'équipements: %1").arg(totalEquipements));
    y += 28;

    painter.drawText(col1X, y, 300, 25, Qt::AlignLeft,
                     QString("• Équipements fonctionnels: %1").arg(fonctionnelCount));
    y += 28;

    painter.drawText(col1X, y, 300, 25, Qt::AlignLeft,
                     QString("• Équipements en panne: %1").arg(panneCount));
    y += 28;

    // Retour au début pour la colonne 2
    y -= 84; // 28 * 3

    // Colonne 2
    painter.drawText(col2X, y, 300, 25, Qt::AlignLeft,
                     QString("• Valeur totale: %1 €").arg(QString::number(valeurTotale, 'f', 2)));
    y += 28;

    if (totalEquipements > 0) {
        double valeurMoyenne = valeurTotale / totalEquipements;
        painter.drawText(col2X, y, 300, 25, Qt::AlignLeft,
                         QString("• Valeur moyenne: %1 €").arg(QString::number(valeurMoyenne, 'f', 2)));
        y += 28;

        double pourcentFonctionnel = (fonctionnelCount * 100.0) / totalEquipements;
        double pourcentPanne = (panneCount * 100.0) / totalEquipements;

        painter.drawText(col2X, y, 300, 25, Qt::AlignLeft,
                         QString("• Taux de panne: %1%").arg(QString::number(pourcentPanne, 'f', 1)));
        y += 35;
    }

    // ==================== PIED DE PAGE ====================
    y += 20;

    // Ligne fine
    painter.setPen(QColor(220, 220, 220));
    painter.drawLine(leftMargin, y, rightMargin, y);
    y += 20;

    // Informations de pied de page
    painter.setFont(footerFont);
    painter.setPen(QColor(127, 140, 141)); // #7F8C8D

    QString footerText = QString("© %1 Smart Studio | Document généré le %2 à %3")
                             .arg(QDate::currentDate().toString("yyyy"))
                             .arg(QDate::currentDate().toString("dd/MM/yyyy"))
                             .arg(QTime::currentTime().toString("HH:mm"));

    painter.drawText(0, pageHeight - 40, pageWidth, 30,
                     Qt::AlignCenter, footerText);

    // ==================== FINALISATION ====================
    painter.end();

    // Journalisation
    qDebug() << "✅ PDF exporté avec succès vers:" << cheminFichier;
    qDebug() << "   Équipements exportés:" << totalEquipements;
    qDebug() << "   Valeur totale:" << QString::number(valeurTotale, 'f', 2) << "€";
    qDebug() << "   Taille du texte améliorée";

    return true;
}
QMap<QString, int> Equipement::getStatistiquesParEtat()
{
    QMap<QString, int> stats;
    stats["En panne"] = 0;
    stats["Neuf"] = 0;
    stats["Occasion"] = 0;

    QSqlQuery query;
    query.exec("SELECT LOWER(etat) FROM equipement");

    while (query.next()) {
        QString etat = query.value(0).toString();

        if (etat.contains("panne")) {
            stats["En panne"]++;
        }
        else if (etat.contains("neuf") || etat.contains("nouveau")) {
            stats["Neuf"]++;
        }
        else {
            stats["Occasion"]++;
        }
    }

    return stats;
}
