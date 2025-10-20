#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection()) {
        // createConnection already shows error message
        return -1;
    }

    MainWindow w;
    w.setWindowTitle("Gestion des Employés - Interface");
    w.resize(1920, 1080);
    w.show();

    return a.exec();
}
