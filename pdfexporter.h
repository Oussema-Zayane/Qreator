#ifndef PDFEXPORTER_H
#define PDFEXPORTER_H

#include <QObject>
#include <QString>
#include <QSqlQuery>

class PdfExporter : public QObject
{
    Q_OBJECT

public:
    explicit PdfExporter(QObject *parent = nullptr);
    bool exportClientsToPdf(const QString &fileName);
    bool exportEquipementsToPdf(const QString& filename); // Nouvelle méthode
    QString createEquipementsPdfHtml(); // AJOUTE CETTE LIGNE



private:
    QString createClientsPdfHtml();
    bool creerPdfVide(const QString &fileName, const QString &message); // AJOUTE CETTE LIGNE

};

#endif // PDFEXPORTER_H
