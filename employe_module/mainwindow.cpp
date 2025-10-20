#include "mainwindow.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QSplitter>
#include <QProgressBar>

#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QPixmap>
#include <QSpacerItem>
#include <QSizePolicy>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <QTextCharFormat>
#include <QtPrintSupport/QPrinter>
#include <QMessageBox>
#include <QRegularExpression>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "connection.h" // for dbConnectionName()

/* helper to append a row to a model */
static void appendRow(QStandardItemModel* m, const QList<QVariant>& cols) {
    QList<QStandardItem*> items;
    items.reserve(cols.size());
    for (const auto& v : cols) {
        auto *it = new QStandardItem(v.toString());
        it->setEditable(false);
        items << it;
    }
    m->appendRow(items);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    empModel(new QStandardItemModel(this)),
    empProxy(new QSortFilterProxyModel(this)),
    absModel(new QStandardItemModel(this)),
    absProxy(new QSortFilterProxyModel(this)),
    logoLabel(nullptr),
    titleLabel(nullptr),
    barMonteurs(nullptr),
    barGraphistes(nullptr),
    barRedacteurs(nullptr),
    barTech(nullptr),
    barRH(nullptr)
{
    setupUI();
    applyPalette();

    // load from DB
    loadEmployeesFromDb();
    loadAbsencesFromDb();
    removeOrphanAbsences();
    updateStatsFromEmployees();

    // PDF export only
    connect(btnPdfEmp, &QPushButton::clicked, this, [=]{
        exportModelToPdf(empModel, "Liste des Employés - Smart Studio");
    });
    connect(btnPdfAbs, &QPushButton::clicked, this, [=]{
        exportModelToPdf(absModel, "Suivi des Absences - Smart Studio");
    });

    connectSignals();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    auto *rootVBox = new QVBoxLayout(central);
    rootVBox->setContentsMargins(10, 8, 10, 10);
    rootVBox->setSpacing(8);

    buildHeaderBar(central, rootVBox);

    auto *split = new QSplitter(Qt::Horizontal, central);
    buildLeftPane(central, split);
    buildRightPane(central, split);
    split->setSizes({720, 540});

    rootVBox->addWidget(split);
}

/* HEADER */
void MainWindow::buildHeaderBar(QWidget* parent, QVBoxLayout* root)
{
    auto *bar = new QWidget(parent);
    auto *barLay = new QHBoxLayout(bar);
    barLay->setContentsMargins(10, 0, 10, 0);

    logoLabel = new QLabel(bar);
    logoLabel->setFixedSize(44, 28);

    QPixmap px("logo.png"); // place logo.png next to exe
    if (!px.isNull())
        logoLabel->setPixmap(px.scaled(44, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    titleLabel = new QLabel("Gestion des Employés — Smart Studio", bar);
    titleLabel->setObjectName("HeaderTitle");

    auto *sp = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);

    barLay->addWidget(logoLabel);
    barLay->addSpacing(8);
    barLay->addWidget(titleLabel);
    barLay->addItem(sp);

    root->addWidget(bar);
}

/* LEFT PANE (Employees) */
void MainWindow::buildLeftPane(QWidget* parent, QSplitter* split)
{
    auto *left = new QWidget(split);
    auto *leftVBox = new QVBoxLayout(left);

    // Model + proxy
    empModel->setColumnCount(8);
    empModel->setHorizontalHeaderLabels({"ID","Nom","Prénom","Email","Téléphone","Rôle","Horaire","Genre"});
    empProxy->setSourceModel(empModel);
    empProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    empProxy->setFilterKeyColumn(-1); // filter all columns
    empProxy->setSortCaseSensitivity(Qt::CaseInsensitive);

    auto *formGroup = new QGroupBox("Informations Employé", left);
    auto *form = new QFormLayout(formGroup);

    employeeNameEdit    = new QLineEdit(left);
    employeeSurnameEdit = new QLineEdit(left);
    employeeEmailEdit   = new QLineEdit(left);
    employeePhoneEdit   = new QLineEdit(left);
    employeeRoleCombo   = new QComboBox(left); // dropdown now
    employeeRoleCombo->addItems({"Monteur","Graphiste","Rédacteurs","Tech Studio","RH/Support"});
    employeeHoraireEdit = new QLineEdit(left);
    employeeGenreCombo  = new QComboBox(left);
    employeeGenreCombo->addItems({"Homme","Femme"});

    form->addRow("Nom:",        employeeNameEdit);
    form->addRow("Prénom:",     employeeSurnameEdit);
    form->addRow("Email:",      employeeEmailEdit);
    form->addRow("Téléphone:",  employeePhoneEdit);
    form->addRow("Rôle:",       employeeRoleCombo);
    form->addRow("Horaire:",    employeeHoraireEdit);
    form->addRow("Genre:",      employeeGenreCombo);

    leftVBox->addWidget(formGroup);

    auto *btns = new QHBoxLayout();
    btnAddEmp  = new QPushButton("Ajouter", left);
    btnEditEmp = new QPushButton("Modifier", left);
    btnDelEmp  = new QPushButton("Supprimer", left);
    btnPdfEmp  = new QPushButton("Exporter PDF", left);
    btns->addWidget(btnAddEmp);
    btns->addWidget(btnEditEmp);
    btns->addWidget(btnDelEmp);
    btns->addWidget(btnPdfEmp);
    leftVBox->addLayout(btns);

    auto *search = new QHBoxLayout();
    employeeSearchBar = new QLineEdit(left);
    auto *btnSearch = new QPushButton("🔍", left); // just visual
    employeeSortCombo = new QComboBox(left);
    employeeSortCombo->addItems({"Par Nom","Par Rôle","Par Horaire"});
    search->addWidget(new QLabel("Recherche:", left));
    search->addWidget(employeeSearchBar);
    search->addWidget(btnSearch);
    search->addStretch();
    search->addWidget(new QLabel("Trier par:", left));
    search->addWidget(employeeSortCombo);
    leftVBox->addLayout(search);

    employeeTable = new QTableView(left);
    employeeTable->setModel(empProxy);
    employeeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    employeeTable->setSelectionMode(QAbstractItemView::SingleSelection);
    employeeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    employeeTable->horizontalHeader()->setStretchLastSection(true);
    employeeTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    leftVBox->addWidget(employeeTable);

    split->addWidget(left);
}

/* RIGHT PANE (Absences) */
void MainWindow::buildRightPane(QWidget* parent, QSplitter* split)
{
    auto *right = new QWidget(split);
    auto *rightVBox = new QVBoxLayout(right);

    // Model + proxy
    absModel->setColumnCount(6);
    absModel->setHorizontalHeaderLabels({"ID Employé","Nom","Type d'absence","Début","Fin","Raison"});
    absProxy->setSourceModel(absModel);
    absProxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
    absProxy->setFilterKeyColumn(-1);
    absProxy->setSortCaseSensitivity(Qt::CaseInsensitive);

    auto *absGroup = new QGroupBox("Suivi des Absences", right);
    auto *absForm = new QFormLayout(absGroup);

    absenceTypeCombo  = new QComboBox(right);
    absenceTypeCombo->addItems({"Congé","Maladie","Retard","Autre"});
    absenceStartEdit  = new QDateEdit(QDate::currentDate(), right);
    absenceEndEdit    = new QDateEdit(QDate::currentDate(), right);
    absenceStartEdit->setCalendarPopup(true);
    absenceEndEdit->setCalendarPopup(true);
    absenceReasonEdit = new QLineEdit(right);

    absForm->addRow("Type d'absence:", absenceTypeCombo);
    absForm->addRow("Début:",          absenceStartEdit);
    absForm->addRow("Fin:",            absenceEndEdit);
    absForm->addRow("Raison:",         absenceReasonEdit);

    rightVBox->addWidget(absGroup);

    auto *absBtns = new QHBoxLayout();
    btnAddAbs  = new QPushButton("Ajouter", right);
    btnEditAbs = new QPushButton("Modifier", right);
    btnDelAbs  = new QPushButton("Supprimer", right);
    btnPdfAbs  = new QPushButton("Exporter PDF", right);
    absBtns->addWidget(btnAddAbs);
    absBtns->addWidget(btnEditAbs);
    absBtns->addWidget(btnDelAbs);
    absBtns->addWidget(btnPdfAbs);
    rightVBox->addLayout(absBtns);

    absenceTable = new QTableView(right);
    absenceTable->setModel(absProxy);
    absenceTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    absenceTable->setSelectionMode(QAbstractItemView::SingleSelection);
    absenceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    absenceTable->horizontalHeader()->setStretchLastSection(true);
    absenceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    rightVBox->addWidget(absenceTable);

    // ---- Stats bars ----
    auto *chartGroup = new QGroupBox("Statistiques — Répartition des rôles", right);
    auto *chartLay = new QVBoxLayout(chartGroup);

    auto mkRow = [&](const QString& label, QProgressBar*& outBar){
        auto *row = new QWidget(chartGroup);
        auto *rowLay = new QHBoxLayout(row);
        rowLay->setContentsMargins(6,0,6,0);
        auto *lbl = new QLabel(label, row); lbl->setMinimumWidth(110);
        outBar = new QProgressBar(row);
        outBar->setRange(0,100); outBar->setValue(0);
        outBar->setTextVisible(true); outBar->setFormat("%p%");
        rowLay->addWidget(lbl); rowLay->addWidget(outBar);
        chartLay->addWidget(row);
    };
    mkRow("Monteurs",   barMonteurs);
    mkRow("Graphistes", barGraphistes);
    mkRow("Rédacteurs", barRedacteurs);
    mkRow("Tech Studio",barTech);
    mkRow("RH/Support", barRH);

    rightVBox->addWidget(chartGroup);
    split->addWidget(right);
}

/* Palette / Styles */
void MainWindow::applyPalette()
{
    setStyleSheet(
        "QMainWindow { background-color: #f8f9fa; color: #2c3e50; }"
        "QLabel#HeaderTitle { font-size: 16pt; font-weight: 700; color: #4D4F52; }"
        "QWidget { background-color: #f8f9fa; font-size: 10pt; color: #2c3e50; }"
        "QLabel { color: #2c3e50; font-weight: bold; }"
        "QGroupBox { background-color: #FFFFFF; border: 2px solid #A7C7E7; border-radius: 10px; margin-top: 10px; padding: 10px; }"
        "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 6px 10px; background-color: #A7C7E7; color: #FFFFFF; border-radius: 6px; }"
        "QPushButton { background-color: #A7C7E7; color: white; border: none; padding: 8px 15px; border-radius: 6px; font-weight: bold; }"
        "QPushButton:hover { background-color: #95B8E7; }"
        "QLineEdit, QComboBox, QDateEdit { border: 2px solid #A7C7E7; border-radius: 6px; padding: 6px; background-color: #FFFFFF; font-size: 10pt; color: #2c3e50; }"
        "QProgressBar { border: 1px solid #A7C7E7; border-radius: 6px; text-align: center; }"
        "QProgressBar::chunk { background-color: #CDEFE4; border-radius: 6px; }"
        "QTableView { background-color: #FFFFFF; border: 2px solid #A7C7E7; border-radius: 6px; gridline-color: #E1F5FE; color: #2c3e50; }"
        "QHeaderView::section { background-color: #A7C7E7; color: white; padding: 8px; border: none; font-weight: bold; }"
        "QSplitter::handle { background-color: #CDEFE4; margin: 2px; } "
        );
}

/* Wiring */
void MainWindow::connectSignals()
{
    connect(btnAddEmp,  &QPushButton::clicked, this, &MainWindow::onAddEmployee);
    connect(btnEditEmp, &QPushButton::clicked, this, &MainWindow::onEditEmployee);
    connect(btnDelEmp,  &QPushButton::clicked, this, &MainWindow::onDeleteEmployee);

    connect(employeeSearchBar, &QLineEdit::textChanged, this, &MainWindow::onFilterEmployees);
    connect(employeeSortCombo, &QComboBox::currentIndexChanged, this, &MainWindow::onSortEmployees);
    connect(employeeTable->selectionModel(), &QItemSelectionModel::currentRowChanged,
            this, &MainWindow::onEmployeeSelectionChanged);

    connect(btnAddAbs,  &QPushButton::clicked, this, &MainWindow::onAddAbsence);
    connect(btnEditAbs, &QPushButton::clicked, this, &MainWindow::onEditAbsence);
    connect(btnDelAbs,  &QPushButton::clicked, this, &MainWindow::onDeleteAbsence);
}

/* Employees: CRUD */
void MainWindow::onAddEmployee()
{
    const QString nom = employeeNameEdit->text().trimmed();
    const QString prenom = employeeSurnameEdit->text().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Nom et Prénom sont obligatoires.");
        return;
    }

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("INSERT INTO employe (nom, prenom, email, telephone, role, horaire, genre) "
              "VALUES (:nom, :prenom, :email, :tel, :role, :horaire, :genre)");
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":email", employeeEmailEdit->text().trimmed());
    q.bindValue(":tel", employeePhoneEdit->text().trimmed());
    q.bindValue(":role", employeeRoleCombo->currentText());
    q.bindValue(":horaire", employeeHoraireEdit->text().trimmed());
    q.bindValue(":genre", employeeGenreCombo->currentText());

    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ajouter l'employé:\n" + q.lastError().text());
        return;
    }

    loadEmployeesFromDb();
    updateStatsFromEmployees();
}

void MainWindow::onEditEmployee()
{
    const QModelIndex proxyIdx = employeeTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = empProxy->mapToSource(proxyIdx);
    const int row = srcIdx.row();
    int id = empModel->item(row, 0)->text().toInt();

    QString nom = employeeNameEdit->text().trimmed();
    QString prenom = employeeSurnameEdit->text().trimmed();
    QString email = employeeEmailEdit->text().trimmed();
    QString tel = employeePhoneEdit->text().trimmed();
    QString role = employeeRoleCombo->currentText();
    QString horaire = employeeHoraireEdit->text().trimmed();
    QString genre = employeeGenreCombo->currentText();

    if (nom.isEmpty()) nom = empModel->item(row,1)->text();
    if (prenom.isEmpty()) prenom = empModel->item(row,2)->text();
    if (email.isEmpty()) email = empModel->item(row,3)->text();
    if (tel.isEmpty()) tel = empModel->item(row,4)->text();
    if (role.isEmpty()) role = empModel->item(row,5)->text();
    if (horaire.isEmpty()) horaire = empModel->item(row,6)->text();

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("UPDATE employe SET nom=:nom, prenom=:prenom, email=:email, telephone=:tel, role=:role, horaire=:horaire, genre=:genre WHERE id=:id");
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":email", email);
    q.bindValue(":tel", tel);
    q.bindValue(":role", role);
    q.bindValue(":horaire", horaire);
    q.bindValue(":genre", genre);
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'employé:\n" + q.lastError().text());
        return;
    }

    loadEmployeesFromDb();
    updateStatsFromEmployees();
}

void MainWindow::onDeleteEmployee()
{
    const QModelIndex proxyIdx = employeeTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = empProxy->mapToSource(proxyIdx);
    int id = empModel->item(srcIdx.row(), 0)->text().toInt();

    if (QMessageBox::question(this, "Supprimer", "Confirmer la suppression ?") != QMessageBox::Yes)
        return;

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("DELETE FROM employe WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de supprimer l'employé:\n" + q.lastError().text());
        return;
    }

    loadEmployeesFromDb();
    loadAbsencesFromDb();
    updateStatsFromEmployees();
}

/* Filter / Sort / Select */
void MainWindow::onFilterEmployees(const QString& text)
{
    QRegularExpression rx(text, QRegularExpression::CaseInsensitiveOption);
    empProxy->setFilterRegularExpression(rx);
}

void MainWindow::onSortEmployees(int idx)
{
    int col = (idx == 1) ? 5 : (idx == 2) ? 6 : 1;
    employeeTable->sortByColumn(col, Qt::AscendingOrder);
}

void MainWindow::onEmployeeSelectionChanged(const QModelIndex &current, const QModelIndex &)
{
    if (!current.isValid()) return;
    int srcRow = empProxy->mapToSource(current).row();
    employeeNameEdit->setText(empModel->item(srcRow,1)->text());
    employeeSurnameEdit->setText(empModel->item(srcRow,2)->text());
    employeeEmailEdit->setText(empModel->item(srcRow,3)->text());
    employeePhoneEdit->setText(empModel->item(srcRow,4)->text());
    employeeRoleCombo->setCurrentText(empModel->item(srcRow,5)->text());
    employeeHoraireEdit->setText(empModel->item(srcRow,6)->text());
    employeeGenreCombo->setCurrentText(empModel->item(srcRow,7)->text());
}

/* Absences CRUD */
void MainWindow::onAddAbsence()
{
    const QModelIndex idx = employeeTable->currentIndex();
    if (!idx.isValid()) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un employé avant d'ajouter une absence.");
        return;
    }
    const QModelIndex sidx = empProxy->mapToSource(idx);
    int id_emp  = empModel->item(sidx.row(), 0)->text().toInt();
    QString nom = empModel->item(sidx.row(), 1)->text();

    if (id_emp <= 0) {
        QMessageBox::warning(this, "Erreur", "ID employé invalide.");
        return;
    }

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("INSERT INTO absence (id_employe, nom, type_abs, debut, fin, raison) "
              "VALUES (:id_emp, :nom, :type, TO_DATE(:debut,'YYYY-MM-DD'), TO_DATE(:fin,'YYYY-MM-DD'), :raison)");
    q.bindValue(":id_emp", id_emp);
    q.bindValue(":nom", nom);
    q.bindValue(":type", absenceTypeCombo->currentText());
    q.bindValue(":debut", absenceStartEdit->date().toString("yyyy-MM-dd"));
    q.bindValue(":fin",   absenceEndEdit->date().toString("yyyy-MM-dd"));
    q.bindValue(":raison", absenceReasonEdit->text().trimmed());

    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'ajouter l'absence:\n" + q.lastError().text());
        return;
    }

    loadAbsencesFromDb();
}

void MainWindow::onEditAbsence()
{
    const QModelIndex proxyIdx = absenceTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = absProxy->mapToSource(proxyIdx);
    const int row = srcIdx.row();

    QString idEmp = absModel->item(row,0)->text();
    QString nom = absModel->item(row,1)->text();
    QString oldDeb = absModel->item(row,3)->text();

    QSqlQuery find(QSqlDatabase::database(dbConnectionName()));
    find.prepare("SELECT id FROM absence WHERE id_employe=:id_emp AND nom=:nom AND TO_CHAR(debut,'YYYY-MM-DD')=:debut");
    find.bindValue(":id_emp", idEmp);
    find.bindValue(":nom", nom);
    find.bindValue(":debut", oldDeb);
    if (!find.exec() || !find.next()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'identifier l'absence à modifier.");
        return;
    }
    int id = find.value(0).toInt();

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("UPDATE absence SET type_abs=:type, debut=TO_DATE(:debut,'YYYY-MM-DD'), fin=TO_DATE(:fin,'YYYY-MM-DD'), raison=:raison WHERE id=:id");
    q.bindValue(":type", absenceTypeCombo->currentText());
    q.bindValue(":debut", absenceStartEdit->date().toString("yyyy-MM-dd"));
    q.bindValue(":fin", absenceEndEdit->date().toString("yyyy-MM-dd"));
    q.bindValue(":raison", absenceReasonEdit->text().trimmed());
    q.bindValue(":id", id);

    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de modifier l'absence:\n" + q.lastError().text());
        return;
    }

    loadAbsencesFromDb();
}

void MainWindow::onDeleteAbsence()
{
    const QModelIndex proxyIdx = absenceTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = absProxy->mapToSource(proxyIdx);
    const int row = srcIdx.row();

    QString idEmp = absModel->item(row,0)->text();
    QString nom = absModel->item(row,1)->text();
    QString debut = absModel->item(row,3)->text();

    QSqlQuery find(QSqlDatabase::database(dbConnectionName()));
    find.prepare("SELECT id FROM absence WHERE id_employe=:id_emp AND nom=:nom AND TO_CHAR(debut,'YYYY-MM-DD')=:debut");
    find.bindValue(":id_emp", idEmp);
    find.bindValue(":nom", nom);
    find.bindValue(":debut", debut);
    if (!find.exec() || !find.next()) {
        QMessageBox::warning(this, "Erreur", "Impossible d'identifier l'absence à supprimer.");
        return;
    }
    int id = find.value(0).toInt();

    if (QMessageBox::question(this, "Supprimer", "Confirmer la suppression ?") != QMessageBox::Yes)
        return;

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    q.prepare("DELETE FROM absence WHERE id=:id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        QMessageBox::warning(this, "Erreur", "Impossible de supprimer l'absence:\n" + q.lastError().text());
        return;
    }

    loadAbsencesFromDb();
}

/* Stats */
void MainWindow::updateStatsFromEmployees()
{
    int total = empModel->rowCount();
    auto pct = [&](const QString& role){
        if (total == 0) return 0;
        int c = 0;
        for (int r=0;r<total;++r)
            if (empModel->item(r,5)->text().compare(role, Qt::CaseInsensitive)==0) ++c;
        return int(double(c)*100.0/double(total)+0.5);
    };
    if (barMonteurs)    barMonteurs -> setValue(pct("Monteur"));
    if (barGraphistes)  barGraphistes-> setValue(pct("Graphiste"));
    if (barRedacteurs)  barRedacteurs-> setValue(pct("Rédacteurs"));
    if (barTech)        barTech      -> setValue(pct("Tech Studio"));
    if (barRH)          barRH        -> setValue(pct("RH/Support"));
}

/* DB loaders */
void MainWindow::loadEmployeesFromDb()
{
    empModel->removeRows(0, empModel->rowCount());

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    if (!q.exec("SELECT id, nom, prenom, email, telephone, role, horaire, genre FROM employe ORDER BY id")) {
        qWarning() << "loadEmployeesFromDb failed:" << q.lastError().text();
        return;
    }
    while (q.next()) {
        QList<QVariant> cols;
        cols << q.value(0).toString()
             << q.value(1).toString()
             << q.value(2).toString()
             << q.value(3).toString()
             << q.value(4).toString()
             << q.value(5).toString()
             << q.value(6).toString()
             << q.value(7).toString();
        appendRow(empModel, cols);
    }
}

void MainWindow::loadAbsencesFromDb()
{
    absModel->removeRows(0, absModel->rowCount());

    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    if (!q.exec("SELECT id_employe, nom, type_abs, TO_CHAR(debut,'YYYY-MM-DD'), TO_CHAR(fin,'YYYY-MM-DD'), raison FROM absence ORDER BY id")) {
        qWarning() << "loadAbsencesFromDb failed:" << q.lastError().text();
        return;
    }
    while (q.next()) {
        QList<QVariant> cols;
        cols << q.value(0).toString()
             << q.value(1).toString()
             << q.value(2).toString()
             << q.value(3).toString()
             << q.value(4).toString()
             << q.value(5).toString();
        appendRow(absModel, cols);
    }
}

/* Remove orphan absences */
void MainWindow::removeOrphanAbsences()
{
    QSqlQuery q(QSqlDatabase::database(dbConnectionName()));
    if (!q.exec("DELETE FROM absence WHERE id_employe IS NULL OR id_employe = 0 OR id_employe NOT IN (SELECT id FROM employe)")) {
        qWarning() << "removeOrphanAbsences failed:" << q.lastError().text();
    } else {
        // reload absences if something changed
        loadAbsencesFromDb();
    }
}

/* PDF export */
bool MainWindow::exportModelToPdf(QStandardItemModel *model, const QString& title)
{
    if (!model) return false;

    const QString path = QFileDialog::getSaveFileName(
        this, "Exporter en PDF", title + ".pdf", "Fichiers PDF (*.pdf)");
    if (path.isEmpty()) return false;

    QTextDocument doc;
    QTextCursor cur(&doc);

    QTextCharFormat h1; h1.setFontPointSize(14); h1.setFontWeight(QFont::Bold);
    cur.insertText(title + "\n\n", h1);

    QTextTableFormat tf;
    tf.setBorder(0.5);
    tf.setCellPadding(6);
    tf.setHeaderRowCount(1);
    tf.setAlignment(Qt::AlignLeft);
    QTextTable *table = cur.insertTable(model->rowCount()+1, model->columnCount(), tf);

    QTextCharFormat th; th.setFontWeight(QFont::Bold);
    for (int c=0; c<model->columnCount(); ++c)
        table->cellAt(0, c).firstCursorPosition()
            .insertText(model->headerData(c, Qt::Horizontal).toString(), th);

    for (int r=0; r<model->rowCount(); ++r)
        for (int c=0; c<model->columnCount(); ++c)
            table->cellAt(r+1, c).firstCursorPosition()
                .insertText(model->item(r, c) ? model->item(r, c)->text() : "");

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    printer.setPageMargins(QMarginsF(15,15,15,15));
    doc.print(&printer);

    QMessageBox::information(this, "Export PDF", "Export PDF terminé !");
    return true;
}
