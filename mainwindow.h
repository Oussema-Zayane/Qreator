#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addClientBtn_clicked();
    void on_deleteClientBtn_clicked();
    void on_editClientBtn_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_clientTable_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Client client;
    int currentClientId; // Pour stocker l'ID du client en cours de modification

    void refreshTable();
    void clearForm();
    bool validateForm();
    void showValidationError(const QString& message);
};

#endif // MAINWINDOW_H
