#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QCalendarWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *central;
    QTabWidget *tabs;

    // Onglet Equipement
    QTableWidget *equipTable;
    QLineEdit *searchBar;
    QComboBox *sortCombo;

    // Onglet Calendrier
    QCalendarWidget *calendarWidget;

    // Onglet Historique
    QTableWidget *histTable;

    void setupUI();
};

#endif // MAINWINDOW_H
