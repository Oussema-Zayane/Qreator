#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void onEquipmentClicked();
    void onEmployeeClicked();
    void onClientClicked();
    void onProjectClicked();
    void onFinanceClicked();

private:
    Ui::MainWindow *ui;
    void setupSidebar();
    void showClientSection();
    void showEquipmentSection();
    void showEmployeeSection();
    void showFinanceSection();
    void setupEquipmentUI();
    void setupEmployeeUI();
    void setupFinanceUI();

    QWidget *equipmentWidget;
    QWidget *employeeWidget;
    QWidget *financeWidget;
};

#endif // MAINWINDOW_H
