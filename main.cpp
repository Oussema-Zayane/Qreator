#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Établir la connexion à la BD
    Connection& conn = Connection::getInstance();
    bool test = conn.createConnection();

    if(test) {
        QMessageBox::information(nullptr, "Succès",
                                 "Connexion à la base de données réussie !");
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        QMessageBox::critical(nullptr, "Erreur",
                              "Impossible de se connecter à la base de données.\n"
                              "Cliquez sur Annuler pour quitter.",
                              QMessageBox::Cancel);
        return -1;
    }
}
