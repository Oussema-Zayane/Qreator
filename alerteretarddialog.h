#ifndef ALERTERETARDDIALOG_H
#define ALERTERETARDDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>
#include <QList>
#include <QDate>

struct TransactionRetard {
    QString rowId;
    double revenu;
    double depense;
    double benefices;
    double tva;
    QDate delai;
    QString modePaiment;
    QString statut;
    int joursRetard;
};

class AlerteRetardDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AlerteRetardDialog(const QList<TransactionRetard> &transactions, QWidget *parent = nullptr);
    ~AlerteRetardDialog();

private slots:
    void on_btnAugmenterDelai_clicked();
    void on_btnIgnorer_clicked();

private:
    QTableView *tableView;
    QPushButton *btnAugmenterDelai;
    QPushButton *btnIgnorer;
    QStandardItemModel *model;
    QList<TransactionRetard> transactionsRetard;
    
    void setupUI();
    void populateTable();
    bool augmenterDelaiEtTVA();
};

#endif // ALERTERETARDDIALOG_H

