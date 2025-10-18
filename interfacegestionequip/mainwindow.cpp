#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_delete_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_delete_7_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_pushButton_delete_3_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}



void MainWindow::on_pushButton_delete_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

