#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// forward decls to keep headers light
class QTableView;
class QStandardItemModel;
class QSortFilterProxyModel;
class QLineEdit;
class QComboBox;
class QDateEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QSplitter;
class QProgressBar;
class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // UI build & style
    void setupUI();
    void buildHeaderBar(QWidget* parent, QVBoxLayout* root);
    void buildLeftPane(QWidget* parent, QSplitter* split);
    void buildRightPane(QWidget* parent, QSplitter* split);
    void applyPalette();

    // Helpers
    void connectSignals();
    void updateStatsFromEmployees();
    bool exportModelToPdf(class QStandardItemModel *model, const QString& title);

    // DB helpers
    void loadEmployeesFromDb();
    void loadAbsencesFromDb();
    void removeOrphanAbsences();

private slots:
    // Employés
    void onAddEmployee();
    void onEditEmployee();
    void onDeleteEmployee();
    void onFilterEmployees(const QString& text);
    void onSortEmployees(int idx);
    void onEmployeeSelectionChanged(const QModelIndex &current, const QModelIndex &previous);

    // Absences
    void onAddAbsence();
    void onEditAbsence();
    void onDeleteAbsence();

private:
    // MODELS
    QStandardItemModel   *empModel;     // id, nom, prénom, email, tel, rôle, horaire, genre
    QSortFilterProxyModel*empProxy;

    QStandardItemModel   *absModel;     // id_employe, nom, type, début, fin, raison
    QSortFilterProxyModel*absProxy;

    // LEFT: Employés
    QLineEdit *employeeNameEdit;
    QLineEdit *employeeSurnameEdit;
    QLineEdit *employeeEmailEdit;
    QLineEdit *employeePhoneEdit;
    QComboBox *employeeRoleCombo;      // combo with 5 roles
    QLineEdit *employeeHoraireEdit;
    QComboBox *employeeGenreCombo;

    QLineEdit *employeeSearchBar;
    QComboBox *employeeSortCombo;
    QTableView *employeeTable;

    QPushButton *btnAddEmp;
    QPushButton *btnEditEmp;
    QPushButton *btnDelEmp;
    QPushButton *btnPdfEmp;

    // RIGHT: Absences
    QComboBox *absenceTypeCombo;
    QDateEdit *absenceStartEdit;
    QDateEdit *absenceEndEdit;
    QLineEdit *absenceReasonEdit;
    QTableView *absenceTable;

    QPushButton *btnAddAbs;
    QPushButton *btnEditAbs;
    QPushButton *btnDelAbs;
    QPushButton *btnPdfAbs;

    // Header (logo + title)
    QLabel *logoLabel;
    QLabel *titleLabel;

    // Stats bars
    QProgressBar *barMonteurs;
    QProgressBar *barGraphistes;
    QProgressBar *barRedacteurs;
    QProgressBar *barTech;
    QProgressBar *barRH;
};

#endif // MAINWINDOW_H
