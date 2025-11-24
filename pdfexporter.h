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

private:
    QString createClientsPdfHtml();
};

#endif // PDFEXPORTER_H
