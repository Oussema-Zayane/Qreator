#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include "employe.h"
#include "projet.h"
#include "finance.h"
#include "equipement.h"
#include "pdfexporter.h"
#include <QStringListModel>
#include <QInputDialog>
#include <QSettings>
#include <QValidator>
#include "emailsmtpmanager.h"
#include <QProgressBar>
#include "chatbotdialog.h"
#include <QProgressBar>  // Pour les barres de progression
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
#include <QConicalGradient>






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
        void on_toggleStatutBtn_clicked();
    // ============================================================================
    // NAVIGATION
    // ============================================================================
    void on_clientsBtn_clicked();
    void on_employesBtn_clicked();
    void on_projetsBtn_clicked();
    void on_financesBtn_clicked();
    void on_equipementsBtn_clicked();
    void on_mailingBtn_clicked();

    // ============================================================================
    // GESTION CLIENTS
    // ============================================================================
    void on_addClientBtn_clicked();
    void on_deleteClientBtn_clicked();
    void on_editClientBtn_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_clientTable_itemClicked(QTableWidgetItem *item);
    void on_clearFormBtn_clicked();
    void on_refreshTableBtn_clicked();
    void on_activeClientsOnly_toggled(bool checked);
    void on_exportPdfBtn_clicked();

    // ============================================================================
    // GESTION EMPLOYÉS
    // ============================================================================
    void on_addEmployeBtn_clicked();
    void on_deleteEmployeBtn_clicked();
    void on_editEmployeBtn_clicked();
    void on_searchEmployeLineEdit_textChanged(const QString &text);
    void on_employeTable_itemClicked(QTableWidgetItem *item);
    void on_clearEmployeFormBtn_clicked();
    void on_refreshEmployeTableBtn_clicked();

    // ============================================================================
    // GESTION PROJETS
    // ============================================================================
    void on_addProjetBtn_clicked();
    void on_deleteProjetBtn_clicked();
    void on_editProjetBtn_clicked();
    void on_searchProjetLineEdit_textChanged(const QString &text);
    void on_projetTable_itemClicked(QTableWidgetItem *item);
    void on_clearProjetFormBtn_clicked();
    void on_refreshProjetTableBtn_clicked();

    // ============================================================================
    // GESTION FINANCES
    // ============================================================================
    void on_addFinanceBtn_clicked();
    void on_deleteFinanceBtn_clicked();
    void on_editFinanceBtn_clicked();
    void on_searchFinanceLineEdit_textChanged(const QString &text);
    void on_financeTable_itemClicked(QTableWidgetItem *item);
    void on_clearFinanceFormBtn_clicked();
    void on_refreshFinanceTableBtn_clicked();

    // ============================================================================
    // GESTION ÉQUIPEMENTS
    // ============================================================================
    void on_addEquipementBtn_clicked();
    void on_deleteEquipementBtn_clicked();
    void on_editEquipementBtn_clicked();
    void on_searchEquipementLineEdit_textChanged(const QString &text);
    void on_equipementTable_itemClicked(QTableWidgetItem *item);
    void on_clearEquipementFormBtn_clicked();
    void on_refreshEquipementTableBtn_clicked();

    // ============================================================================
    // GESTION MAILING
    // ============================================================================
    void on_addMailingBtn_clicked();
    void on_editMailingBtn_clicked();
    void on_sendMailingBtn_clicked();
    void on_sendTestMailBtn_clicked();
    void on_searchMailingLineEdit_textChanged(const QString &text);
    void on_mailingTable_itemClicked(QTableWidgetItem *item);
    void on_clearMailingFormBtn_clicked();
    void on_refreshMailingTableBtn_clicked();

    // ============================================================================
    // SLOTS POUR EMAILJS
    // ============================================================================
    void onEmailEnvoye(const QString& email, bool succes, const QString& details);
    void onProgressionEnvoi(int valeur, int maximum);
    void onEnvoiTermine();
    void onErreurEmail(const QString &message);
    void on_envoyerEmailClientBtn_clicked();
    void onProgression(int pourcentage);  // UN SEUL paramètre !




    void on_chatbotBtn_clicked();  // AJOUTEZ CETTE LIGNE




private:
    Ui::MainWindow *ui;

    // Variables pour stocker les IDs sélectionnés
    int currentClientId;
    int currentEmployeId;
    int currentProjetId;
    int currentFinanceId;
    int currentEquipementId;
    int currentMailingId;

    // ============================================================================
    // MÉTHODES PRIVÉES - CLIENTS
    // ============================================================================
    void refreshClientTable();
    void updateClientStats();
    void clearClientForm();
    bool validateClientForm();

    // ============================================================================
    // MÉTHODES PRIVÉES - EMPLOYÉS
    // ============================================================================
    void refreshEmployeTable();
    void clearEmployeForm();
    bool validateEmployeForm();
    void loadEmployees();

    // ============================================================================
    // MÉTHODES PRIVÉES - PROJETS
    // ============================================================================
    void refreshProjetTable();
    void clearProjetForm();
    bool validateProjetForm();

    // ============================================================================
    // MÉTHODES PRIVÉES - FINANCES
    // ============================================================================
    void refreshFinanceTable();
    void clearFinanceForm();
    bool validateFinanceForm();

    // ============================================================================
    // MÉTHODES PRIVÉES - ÉQUIPEMENTS
    // ============================================================================
    void refreshEquipementTable();
    void clearEquipementForm();
    bool validateEquipementForm();

    // ============================================================================
    // MÉTHODES PRIVÉES - MAILING
    // ============================================================================
    void refreshMailingTable();
    void clearMailingForm();
    bool validateMailingForm();
    void initialiserInterfaceMailing();
    void actualiserStatistiquesMailing();

    // ============================================================================
    // MÉTHODES UTILITAIRES
    // ============================================================================
    void showValidationError(const QString& message);
    QString genererMessageAutomatique(const QString &nomClient, const QString &typeMessage = "standard");
    QString corrigerEmail(const QString &email);
    bool validerEmail(const QString &email);
    QVector<QString> obtenirDestinataires();

    // ============================================================================
    // EMAILJS MANAGER
    // ============================================================================
    EmailSMTPManager *emailManager;
    QStringListModel *completionModel;
    QStringList motsCourants;
    void envoyerEmailClient(const QString &nomPrenom, const QString &email);

    QString genererMessageReel(const QString &prenom);



    ChatbotDialog *chatbotDialog;  // AJOUTEZ CETTE LIGNE

    void creerStatistiquesVisuelles();
    void mettreAJourStatistiquesVisuelles();
    void mettreAJourStatutVisuel();
    QProgressBar *progressBarActifs = nullptr;
    QProgressBar *progressBarNouveaux = nullptr;
    QLabel *labelStatsDetails = nullptr;
    void appliquerStyleModerne();
    void creerIndicateursCirculaires();
    void mettreAJourIndicateursCirculaires();
    void basculerStatutClient();
    // ============================================================================
    // MÉTHODES PRIVÉES - AMÉLIORATIONS GRAPHIQUES
    // ============================================================================
    void ajouterBoutonStatut();  // AJOUTER CETTE DÉCLARATION
    void mettreAJourBoutonStatut();
    // ============================================================================
    // ADD THESE TWO LINES - DÉCLARATIONS DES MÉTHODES CIRCULAIRES
    // ============================================================================
    void creerStatistiquesCirculaires();
    void mettreAJourStatistiquesCirculaires();





};

#endif // MAINWINDOW_H
