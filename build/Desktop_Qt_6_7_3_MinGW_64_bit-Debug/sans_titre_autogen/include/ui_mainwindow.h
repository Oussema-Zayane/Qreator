/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *clientNameEdit;
    QLabel *label_2;
    QLineEdit *clientEmailEdit;
    QLabel *label_3;
    QLineEdit *clientPhoneEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QLabel *selectedClientIdLabel;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearFormBtn;
    QHBoxLayout *horizontalLayout;
    QPushButton *addClientBtn;
    QPushButton *editClientBtn;
    QPushButton *deleteClientBtn;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *searchLineEdit;
    QPushButton *refreshTableBtn;
    QTableWidget *clientTable;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setAlignment(Qt::AlignCenter);
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        clientNameEdit = new QLineEdit(groupBox);
        clientNameEdit->setObjectName("clientNameEdit");
        clientNameEdit->setMaxLength(50);

        formLayout->setWidget(0, QFormLayout::FieldRole, clientNameEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        clientEmailEdit = new QLineEdit(groupBox);
        clientEmailEdit->setObjectName("clientEmailEdit");
        clientEmailEdit->setMaxLength(100);

        formLayout->setWidget(1, QFormLayout::FieldRole, clientEmailEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        clientPhoneEdit = new QLineEdit(groupBox);
        clientPhoneEdit->setObjectName("clientPhoneEdit");
        clientPhoneEdit->setMaxLength(20);

        formLayout->setWidget(2, QFormLayout::FieldRole, clientPhoneEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_5);

        selectedClientIdLabel = new QLabel(groupBox);
        selectedClientIdLabel->setObjectName("selectedClientIdLabel");
        selectedClientIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2E86AB;"));
        selectedClientIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(selectedClientIdLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        clearFormBtn = new QPushButton(groupBox);
        clearFormBtn->setObjectName("clearFormBtn");
        clearFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #6C757D;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #5A6268;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #545B62;\n"
"}"));

        horizontalLayout_3->addWidget(clearFormBtn);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_3);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addClientBtn = new QPushButton(centralwidget);
        addClientBtn->setObjectName("addClientBtn");
        addClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #6C757D;\n"
"    color: #CED4DA;\n"
"}"));

        horizontalLayout->addWidget(addClientBtn);

        editClientBtn = new QPushButton(centralwidget);
        editClientBtn->setObjectName("editClientBtn");
        editClientBtn->setEnabled(false);
        editClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #6C757D;\n"
"    color: #CED4DA;\n"
"}"));

        horizontalLayout->addWidget(editClientBtn);

        deleteClientBtn = new QPushButton(centralwidget);
        deleteClientBtn->setObjectName("deleteClientBtn");
        deleteClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout->addWidget(deleteClientBtn);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_2->addWidget(label_4);

        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #DEE2E6;\n"
"    border-radius: 4px;\n"
"    font-size: 12px;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #2E86AB;\n"
"    background-color: #F8F9FA;\n"
"}"));

        horizontalLayout_2->addWidget(searchLineEdit);

        refreshTableBtn = new QPushButton(centralwidget);
        refreshTableBtn->setObjectName("refreshTableBtn");
        refreshTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"    font-size: 11px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_2->addWidget(refreshTableBtn);


        verticalLayout->addLayout(horizontalLayout_2);

        clientTable = new QTableWidget(centralwidget);
        if (clientTable->columnCount() < 6)
            clientTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        clientTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        clientTable->setObjectName("clientTable");
        clientTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #2E86AB;\n"
"    selection-color: white;\n"
"    gridline-color: #DEE2E6;\n"
"    border: 1px solid #DEE2E6;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #DEE2E6;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #343A40;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    font-size: 11px;\n"
"}"));
        clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        clientTable->setSelectionMode(QAbstractItemView::SingleSelection);
        clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        clientTable->setShowGrid(true);
        clientTable->setGridStyle(Qt::SolidLine);
        clientTable->setAlternatingRowColors(true);
        clientTable->setSortingEnabled(true);
        clientTable->horizontalHeader()->setMinimumSectionSize(40);
        clientTable->horizontalHeader()->setHighlightSections(false);
        clientTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(clientTable);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gestion des Clients - CRUD Complet", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Informations Client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom:", nullptr));
        clientNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Jean Dupont (min. 2 caract\303\250res)", nullptr));
#if QT_CONFIG(tooltip)
        clientNameEdit->setToolTip(QCoreApplication::translate("MainWindow", "Lettres, espaces, apostrophes et tirets uniquement", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        clientEmailEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: jean.dupont@email.com", nullptr));
#if QT_CONFIG(tooltip)
        clientEmailEdit->setToolTip(QCoreApplication::translate("MainWindow", "Format d'email valide requis", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        clientPhoneEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 01 23 45 67 89", nullptr));
#if QT_CONFIG(tooltip)
        clientPhoneEdit->setToolTip(QCoreApplication::translate("MainWindow", "Format fran\303\247ais: 10 chiffres commen\303\247ant par 0", nullptr));
#endif // QT_CONFIG(tooltip)
        label_5->setText(QCoreApplication::translate("MainWindow", "ID Client S\303\251lectionn\303\251:", nullptr));
        selectedClientIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouveau Client", nullptr));
#if QT_CONFIG(tooltip)
        clearFormBtn->setToolTip(QCoreApplication::translate("MainWindow", "Vider le formulaire pour ajouter un nouveau client", nullptr));
#endif // QT_CONFIG(tooltip)
        addClientBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Client", nullptr));
#if QT_CONFIG(tooltip)
        addClientBtn->setToolTip(QCoreApplication::translate("MainWindow", "Ajouter un nouveau client \303\240 la base de donn\303\251es", nullptr));
#endif // QT_CONFIG(tooltip)
        editClientBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Client", nullptr));
#if QT_CONFIG(tooltip)
        editClientBtn->setToolTip(QCoreApplication::translate("MainWindow", "Modifier le client s\303\251lectionn\303\251 (doit \303\252tre s\303\251lectionn\303\251 dans le tableau)", nullptr));
#endif // QT_CONFIG(tooltip)
        deleteClientBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Client", nullptr));
#if QT_CONFIG(tooltip)
        deleteClientBtn->setToolTip(QCoreApplication::translate("MainWindow", "Supprimer le client s\303\251lectionn\303\251 (doit \303\252tre s\303\251lectionn\303\251 dans le tableau)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom, email ou t\303\251l\303\251phone...", nullptr));
#if QT_CONFIG(tooltip)
        searchLineEdit->setToolTip(QCoreApplication::translate("MainWindow", "Recherche en temps r\303\251el dans les clients", nullptr));
#endif // QT_CONFIG(tooltip)
        refreshTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
#if QT_CONFIG(tooltip)
        refreshTableBtn->setToolTip(QCoreApplication::translate("MainWindow", "Actualiser la liste des clients", nullptr));
#endif // QT_CONFIG(tooltip)
        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = clientTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
