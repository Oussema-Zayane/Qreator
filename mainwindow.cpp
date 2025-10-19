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

    // ---- seed 4 demo employees ----
    struct Emp {
        int id; const char* nom; const char* prenom; const char* email;
        const char* tel; const char* role; const char* horaire; const char* genre;
    } emps[] = {
                { 1,"Ben Ali","Yassine","yassine.montage@studio.tn","+216 20 111 001","Monteur","Matin","Homme"},
                { 2,"Ayari","Sarra","sarra.montage@studio.tn","+216 20 111 002","Monteur","Soir","Femme"},
                { 3,"Zitoun","Amina","amina.graph@studio.tn","+216 20 222 001","Graphiste","Matin","Femme"},
                { 4,"Haddad","Amine","amine.redac@studio.tn","+216 20 333 002","Rédacteurs","Soir","Homme"},
                };
    for (const auto& e : emps)
        appendRow(empModel, { e.id, e.nom, e.prenom, e.email, e.tel, e.role, e.horaire, e.genre });

    connectSignals();
    updateStatsFromEmployees();

    // PDF export only
    connect(btnPdfEmp, &QPushButton::clicked, this, [=]{
        exportModelToPdf(empModel, "Liste des Employés - Smart Studio");
    });
    connect(btnPdfAbs, &QPushButton::clicked, this, [=]{
        exportModelToPdf(absModel, "Suivi des Absences - Smart Studio");
    });
}

MainWindow::~MainWindow() {}

/* ---------- UI ROOT ---------- */
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

/* ---------- HEADER (logo + title) ---------- */
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

/* ---------- LEFT PANE (Employés) ---------- */
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
    employeeRoleEdit    = new QLineEdit(left);
    employeeHoraireEdit = new QLineEdit(left);
    employeeGenreCombo  = new QComboBox(left);
    employeeGenreCombo->addItems({"Homme","Femme"});

    form->addRow("Nom:",        employeeNameEdit);
    form->addRow("Prénom:",     employeeSurnameEdit);
    form->addRow("Email:",      employeeEmailEdit);
    form->addRow("Téléphone:",  employeePhoneEdit);
    form->addRow("Rôle:",       employeeRoleEdit);
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

/* ---------- RIGHT PANE (Absences + stats bars) ---------- */
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

/* ---------- Palette / Styles ---------- */
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

/* ---------- Wiring ---------- */
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

/* ---------- Employees: CRUD ---------- */
void MainWindow::onAddEmployee()
{
    const QString nom = employeeNameEdit->text().trimmed();
    const QString prenom = employeeSurnameEdit->text().trimmed();
    if (nom.isEmpty() || prenom.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Nom et Prénom sont obligatoires.");
        return;
    }
    appendRow(empModel, {
                            nextEmpId++,
                            nom,
                            prenom,
                            employeeEmailEdit->text().trimmed(),
                            employeePhoneEdit->text().trimmed(),
                            employeeRoleEdit->text().trimmed(),
                            employeeHoraireEdit->text().trimmed(),
                            employeeGenreCombo->currentText()
                        });
    updateStatsFromEmployees();
}

void MainWindow::onEditEmployee()
{
    const QModelIndex proxyIdx = employeeTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = empProxy->mapToSource(proxyIdx);
    const int row = srcIdx.row();

    auto set = [&](int col, const QString& v){ empModel->setItem(row, col, new QStandardItem(v)); };

    if (!employeeNameEdit->text().trimmed().isEmpty())   set(1, employeeNameEdit->text().trimmed());
    if (!employeeSurnameEdit->text().trimmed().isEmpty())set(2, employeeSurnameEdit->text().trimmed());
    set(3, employeeEmailEdit->text().trimmed());
    set(4, employeePhoneEdit->text().trimmed());
    set(5, employeeRoleEdit->text().trimmed());
    set(6, employeeHoraireEdit->text().trimmed());
    set(7, employeeGenreCombo->currentText());

    updateStatsFromEmployees();
}

void MainWindow::onDeleteEmployee()
{
    const QModelIndex proxyIdx = employeeTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = empProxy->mapToSource(proxyIdx);
    empModel->removeRow(srcIdx.row());
    updateStatsFromEmployees();
}

/* ---------- Employees: Filter/Sort/Select ---------- */
void MainWindow::onFilterEmployees(const QString& text)
{
    QRegularExpression rx(text, QRegularExpression::CaseInsensitiveOption);
    empProxy->setFilterRegularExpression(rx);
}

void MainWindow::onSortEmployees(int idx)
{
    // 1: Nom, 5: Rôle, 6: Horaire
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
    employeeRoleEdit->setText(empModel->item(srcRow,5)->text());
    employeeHoraireEdit->setText(empModel->item(srcRow,6)->text());
    employeeGenreCombo->setCurrentText(empModel->item(srcRow,7)->text());
}

/* ---------- Absences: simple CRUD ---------- */
void MainWindow::onAddAbsence()
{
    // If an employee is selected, link ID + name
    int id = 0; QString nom;
    const QModelIndex idx = employeeTable->currentIndex();
    if (idx.isValid()) {
        const QModelIndex sidx = empProxy->mapToSource(idx);
        id  = empModel->item(sidx.row(), 0)->text().toInt();
        nom = empModel->item(sidx.row(), 1)->text();
    }
    appendRow(absModel, {
                            id,
                            nom,
                            absenceTypeCombo->currentText(),
                            absenceStartEdit->date().toString("yyyy-MM-dd"),
                            absenceEndEdit->date().toString("yyyy-MM-dd"),
                            absenceReasonEdit->text().trimmed()
                        });
}

void MainWindow::onEditAbsence()
{
    const QModelIndex proxyIdx = absenceTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = absProxy->mapToSource(proxyIdx);
    const int row = srcIdx.row();

    absModel->setItem(row, 2, new QStandardItem(absenceTypeCombo->currentText()));
    absModel->setItem(row, 3, new QStandardItem(absenceStartEdit->date().toString("yyyy-MM-dd")));
    absModel->setItem(row, 4, new QStandardItem(absenceEndEdit->date().toString("yyyy-MM-dd")));
    absModel->setItem(row, 5, new QStandardItem(absenceReasonEdit->text().trimmed()));
}

void MainWindow::onDeleteAbsence()
{
    const QModelIndex proxyIdx = absenceTable->currentIndex();
    if (!proxyIdx.isValid()) return;
    const QModelIndex srcIdx = absProxy->mapToSource(proxyIdx);
    absModel->removeRow(srcIdx.row());
}

/* ---------- Stats ---------- */
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
    barMonteurs -> setValue(pct("Monteur"));
    barGraphistes-> setValue(pct("Graphiste"));
    barRedacteurs-> setValue(pct("Rédacteurs"));
    barTech      -> setValue(pct("Tech Studio"));
    barRH        -> setValue(pct("RH/Support"));
}

/* ---------- PDF export helper ---------- */
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
