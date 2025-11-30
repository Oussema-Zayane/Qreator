#ifndef HISTORIQUEDIALOG_H
#define HISTORIQUEDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QHeaderView>

class HistoriqueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistoriqueDialog(QWidget *parent = nullptr);
    ~HistoriqueDialog();
    void refreshTable();

private slots:
    void on_btnRestaurer_clicked();
    void on_btnSupprimerDef_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    QTableView *tableView;
    QPushButton *btnRestaurer;
    QPushButton *btnSupprimerDef;
    QPushButton *btnFermer;
    QSqlQueryModel *model;
    QString selectedHistoryId;
    
    void setupUI();
    bool createHistoriqueTable();
};

#endif // HISTORIQUEDIALOG_H

