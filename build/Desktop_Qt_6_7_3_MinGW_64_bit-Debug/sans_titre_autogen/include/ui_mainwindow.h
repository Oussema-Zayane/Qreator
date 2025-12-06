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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_17;
    QPushButton *clientsBtn;
    QPushButton *employesBtn;
    QPushButton *projetsBtn;
    QPushButton *financesBtn;
    QPushButton *equipementsBtn;
    QPushButton *mailingBtn;
    QSpacerItem *verticalSpacer;
    QLabel *label_18;
    QStackedWidget *stackedWidget;
    QWidget *clientsPage;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
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
    QHBoxLayout *horizontalLayout_4;
    QPushButton *addClientBtn;
    QPushButton *editClientBtn;
    QPushButton *deleteClientBtn;
    QPushButton *exportPdfBtn;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *searchLineEdit;
    QPushButton *refreshTableBtn;
    QTableWidget *clientTable;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QLabel *totalClientsLabel;
    QLabel *label_9;
    QLabel *activeClientsLabel;
    QLabel *label_11;
    QLabel *newThisMonthLabel;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *activeClientsOnly;
    QWidget *employesPage;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *employesGroupBox;
    QVBoxLayout *verticalLayout_7;
    QFormLayout *formLayout_2;
    QLabel *label_8;
    QLineEdit *employeNameEdit;
    QLabel *label_10;
    QLineEdit *employeEmailEdit;
    QLabel *label_12;
    QLineEdit *employePhoneEdit;
    QLabel *label_13;
    QLineEdit *employePosteEdit;
    QLabel *label_14;
    QLineEdit *employeSalaireEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_15;
    QLabel *selectedEmployeIdLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clearEmployeFormBtn;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *addEmployeBtn;
    QPushButton *editEmployeBtn;
    QPushButton *deleteEmployeBtn;
    QPushButton *refreshEmployeTableBtn;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_16;
    QLineEdit *searchEmployeLineEdit;
    QTableWidget *employeTable;
    QWidget *projetsPage;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *projetsGroupBox;
    QVBoxLayout *verticalLayout_8;
    QFormLayout *formLayout_3;
    QLabel *label_25;
    QLineEdit *projetNomEdit;
    QLabel *label_26;
    QLineEdit *projetDescriptionEdit;
    QLabel *label_27;
    QLineEdit *projetClientIdEdit;
    QLabel *label_28;
    QLineEdit *projetEmployeIdEdit;
    QLabel *label_29;
    QLineEdit *projetBudgetEdit;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_30;
    QLabel *selectedProjetIdLabel;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *clearProjetFormBtn;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *addProjetBtn;
    QPushButton *editProjetBtn;
    QPushButton *deleteProjetBtn;
    QPushButton *refreshProjetTableBtn;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_31;
    QLineEdit *searchProjetLineEdit;
    QTableWidget *projetTable;
    QWidget *financesPage;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *financesGroupBox;
    QVBoxLayout *verticalLayout_9;
    QFormLayout *formLayout_4;
    QLabel *label_32;
    QLineEdit *financeTypeEdit;
    QLabel *label_33;
    QLineEdit *financeMontantEdit;
    QLabel *label_34;
    QLineEdit *financeDescriptionEdit;
    QLabel *label_35;
    QLineEdit *financeProjetIdEdit;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_36;
    QLabel *selectedFinanceIdLabel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *clearFinanceFormBtn;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *addFinanceBtn;
    QPushButton *editFinanceBtn;
    QPushButton *deleteFinanceBtn;
    QPushButton *refreshFinanceTableBtn;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_37;
    QLineEdit *searchFinanceLineEdit;
    QTableWidget *financeTable;
    QWidget *equipementsPage;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *equipementsGroupBox;
    QVBoxLayout *verticalLayout_11;
    QFormLayout *formLayout_5;
    QLabel *label_38;
    QLineEdit *equipementNomEdit;
    QLabel *label_39;
    QLineEdit *equipementTypeEdit;
    QLabel *label_40;
    QLineEdit *equipementEtatEdit;
    QLabel *label_41;
    QLineEdit *equipementPrixEdit;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_42;
    QLabel *selectedEquipementIdLabel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *clearEquipementFormBtn;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *addEquipementBtn;
    QPushButton *editEquipementBtn;
    QPushButton *deleteEquipementBtn;
    QPushButton *refreshEquipementTableBtn;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_43;
    QLineEdit *searchEquipementLineEdit;
    QTableWidget *equipementTable;
    QWidget *mailingPage;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *mailingGroupBox;
    QVBoxLayout *verticalLayout_13;
    QFormLayout *formLayout_6;
    QLabel *label_44;
    QLineEdit *mailingSujetEdit;
    QLabel *label_45;
    QComboBox *mailingDestinatairesCombo;
    QLabel *label_46;
    QTextEdit *mailingMessageEdit;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_47;
    QLabel *selectedMailingIdLabel;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *clearMailingFormBtn;
    QHBoxLayout *horizontalLayout_20;
    QPushButton *sendTestMailBtn;
    QPushButton *addMailingBtn;
    QPushButton *editMailingBtn;
    QPushButton *sendMailingBtn;
    QPushButton *refreshMailingTableBtn;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_48;
    QLineEdit *searchMailingLineEdit;
    QTableWidget *mailingTable;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 850);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #F8F9FA;\n"
"    font-family: Arial, sans-serif;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-color: #2C3E50;\n"
"    border-radius: 10px;\n"
"    margin: 5px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(sidebarWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_17 = new QLabel(sidebarWidget);
        label_17->setObjectName("label_17");
        label_17->setStyleSheet(QString::fromUtf8("color: #3498DB; \n"
"font-weight: bold; \n"
"font-size: 16px; \n"
"padding: 20px; \n"
"background-color: #34495E; \n"
"border-radius: 5px;\n"
"text-align: center;"));
        label_17->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_17);

        clientsBtn = new QPushButton(sidebarWidget);
        clientsBtn->setObjectName("clientsBtn");
        clientsBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        clientsBtn->setCheckable(true);
        clientsBtn->setChecked(true);

        verticalLayout_2->addWidget(clientsBtn);

        employesBtn = new QPushButton(sidebarWidget);
        employesBtn->setObjectName("employesBtn");
        employesBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        employesBtn->setCheckable(true);

        verticalLayout_2->addWidget(employesBtn);

        projetsBtn = new QPushButton(sidebarWidget);
        projetsBtn->setObjectName("projetsBtn");
        projetsBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        projetsBtn->setCheckable(true);

        verticalLayout_2->addWidget(projetsBtn);

        financesBtn = new QPushButton(sidebarWidget);
        financesBtn->setObjectName("financesBtn");
        financesBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        financesBtn->setCheckable(true);

        verticalLayout_2->addWidget(financesBtn);

        equipementsBtn = new QPushButton(sidebarWidget);
        equipementsBtn->setObjectName("equipementsBtn");
        equipementsBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        equipementsBtn->setCheckable(true);

        verticalLayout_2->addWidget(equipementsBtn);

        mailingBtn = new QPushButton(sidebarWidget);
        mailingBtn->setObjectName("mailingBtn");
        mailingBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #34495E;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    text-align: left;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    border-radius: 5px;\n"
"    margin: 2px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498DB;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:checked {\n"
"    background-color: #3498DB;\n"
"}"));
        mailingBtn->setCheckable(true);

        verticalLayout_2->addWidget(mailingBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_18 = new QLabel(sidebarWidget);
        label_18->setObjectName("label_18");
        label_18->setStyleSheet(QString::fromUtf8("color: #7F8C8D; \n"
"font-size: 10px; \n"
"padding: 10px; \n"
"text-align: center;\n"
"font-style: italic;"));
        label_18->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_18);


        horizontalLayout->addWidget(sidebarWidget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("QStackedWidget {\n"
"    background-color: transparent;\n"
"}"));
        clientsPage = new QWidget();
        clientsPage->setObjectName("clientsPage");
        verticalLayout_3 = new QVBoxLayout(clientsPage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        groupBox = new QGroupBox(clientsPage);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #3498DB;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #3498DB;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(groupBox);
        label_6->setObjectName("label_6");
        label_6->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2C3E50; font-size: 14px;"));

        verticalLayout->addWidget(label_6);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        clientNameEdit = new QLineEdit(groupBox);
        clientNameEdit->setObjectName("clientNameEdit");
        clientNameEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout->setWidget(0, QFormLayout::FieldRole, clientNameEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        clientEmailEdit = new QLineEdit(groupBox);
        clientEmailEdit->setObjectName("clientEmailEdit");
        clientEmailEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout->setWidget(1, QFormLayout::FieldRole, clientEmailEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        clientPhoneEdit = new QLineEdit(groupBox);
        clientPhoneEdit->setObjectName("clientPhoneEdit");
        clientPhoneEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout->setWidget(2, QFormLayout::FieldRole, clientPhoneEdit);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_5 = new QLabel(groupBox);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_3->addWidget(label_5);

        selectedClientIdLabel = new QLabel(groupBox);
        selectedClientIdLabel->setObjectName("selectedClientIdLabel");
        selectedClientIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedClientIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(selectedClientIdLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        clearFormBtn = new QPushButton(groupBox);
        clearFormBtn->setObjectName("clearFormBtn");
        clearFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_3->addWidget(clearFormBtn);


        formLayout->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_3);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        addClientBtn = new QPushButton(groupBox);
        addClientBtn->setObjectName("addClientBtn");
        addClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_4->addWidget(addClientBtn);

        editClientBtn = new QPushButton(groupBox);
        editClientBtn->setObjectName("editClientBtn");
        editClientBtn->setEnabled(false);
        editClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_4->addWidget(editClientBtn);

        deleteClientBtn = new QPushButton(groupBox);
        deleteClientBtn->setObjectName("deleteClientBtn");
        deleteClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout_4->addWidget(deleteClientBtn);

        exportPdfBtn = new QPushButton(groupBox);
        exportPdfBtn->setObjectName("exportPdfBtn");
        exportPdfBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #17A2B8;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #138496;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #117A8B;\n"
"}"));

        horizontalLayout_4->addWidget(exportPdfBtn);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_5->addWidget(label_4);

        searchLineEdit = new QLineEdit(groupBox);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_5->addWidget(searchLineEdit);

        refreshTableBtn = new QPushButton(groupBox);
        refreshTableBtn->setObjectName("refreshTableBtn");
        refreshTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_5->addWidget(refreshTableBtn);


        verticalLayout->addLayout(horizontalLayout_5);

        clientTable = new QTableWidget(groupBox);
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
"    selection-background-color: #3498DB;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #3498DB;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        clientTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        clientTable->setSelectionMode(QAbstractItemView::SingleSelection);
        clientTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        clientTable->setShowGrid(true);
        clientTable->setGridStyle(Qt::SolidLine);
        clientTable->setAlternatingRowColors(true);
        clientTable->setSortingEnabled(true);
        clientTable->horizontalHeader()->setHighlightSections(false);
        clientTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(clientTable);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2C3E50;"));

        horizontalLayout_6->addWidget(label_7);

        totalClientsLabel = new QLabel(groupBox);
        totalClientsLabel->setObjectName("totalClientsLabel");
        totalClientsLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));

        horizontalLayout_6->addWidget(totalClientsLabel);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2C3E50;"));

        horizontalLayout_6->addWidget(label_9);

        activeClientsLabel = new QLabel(groupBox);
        activeClientsLabel->setObjectName("activeClientsLabel");
        activeClientsLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #27AE60; background-color: #D5F5E3; padding: 4px 8px; border-radius: 4px;"));

        horizontalLayout_6->addWidget(activeClientsLabel);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2C3E50;"));

        horizontalLayout_6->addWidget(label_11);

        newThisMonthLabel = new QLabel(groupBox);
        newThisMonthLabel->setObjectName("newThisMonthLabel");
        newThisMonthLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2980B9; background-color: #D6EAF8; padding: 4px 8px; border-radius: 4px;"));

        horizontalLayout_6->addWidget(newThisMonthLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        activeClientsOnly = new QCheckBox(groupBox);
        activeClientsOnly->setObjectName("activeClientsOnly");
        activeClientsOnly->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"}\n"
"QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"QCheckBox::indicator:checked {\n"
"    background-color: #27AE60;\n"
"    border: 2px solid #27AE60;\n"
"}"));

        horizontalLayout_6->addWidget(activeClientsOnly);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_3->addWidget(groupBox);

        stackedWidget->addWidget(clientsPage);
        employesPage = new QWidget();
        employesPage->setObjectName("employesPage");
        verticalLayout_4 = new QVBoxLayout(employesPage);
        verticalLayout_4->setObjectName("verticalLayout_4");
        employesGroupBox = new QGroupBox(employesPage);
        employesGroupBox->setObjectName("employesGroupBox");
        employesGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #E67E22;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #E67E22;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(employesGroupBox);
        verticalLayout_7->setObjectName("verticalLayout_7");
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label_8 = new QLabel(employesGroupBox);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_8);

        employeNameEdit = new QLineEdit(employesGroupBox);
        employeNameEdit->setObjectName("employeNameEdit");
        employeNameEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, employeNameEdit);

        label_10 = new QLabel(employesGroupBox);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_10);

        employeEmailEdit = new QLineEdit(employesGroupBox);
        employeEmailEdit->setObjectName("employeEmailEdit");
        employeEmailEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, employeEmailEdit);

        label_12 = new QLabel(employesGroupBox);
        label_12->setObjectName("label_12");
        label_12->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_12);

        employePhoneEdit = new QLineEdit(employesGroupBox);
        employePhoneEdit->setObjectName("employePhoneEdit");
        employePhoneEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, employePhoneEdit);

        label_13 = new QLabel(employesGroupBox);
        label_13->setObjectName("label_13");
        label_13->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_13);

        employePosteEdit = new QLineEdit(employesGroupBox);
        employePosteEdit->setObjectName("employePosteEdit");
        employePosteEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, employePosteEdit);

        label_14 = new QLabel(employesGroupBox);
        label_14->setObjectName("label_14");
        label_14->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_14);

        employeSalaireEdit = new QLineEdit(employesGroupBox);
        employeSalaireEdit->setObjectName("employeSalaireEdit");
        employeSalaireEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, employeSalaireEdit);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_15 = new QLabel(employesGroupBox);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_7->addWidget(label_15);

        selectedEmployeIdLabel = new QLabel(employesGroupBox);
        selectedEmployeIdLabel->setObjectName("selectedEmployeIdLabel");
        selectedEmployeIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedEmployeIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(selectedEmployeIdLabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        clearEmployeFormBtn = new QPushButton(employesGroupBox);
        clearEmployeFormBtn->setObjectName("clearEmployeFormBtn");
        clearEmployeFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_7->addWidget(clearEmployeFormBtn);


        formLayout_2->setLayout(5, QFormLayout::SpanningRole, horizontalLayout_7);


        verticalLayout_7->addLayout(formLayout_2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        addEmployeBtn = new QPushButton(employesGroupBox);
        addEmployeBtn->setObjectName("addEmployeBtn");
        addEmployeBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_8->addWidget(addEmployeBtn);

        editEmployeBtn = new QPushButton(employesGroupBox);
        editEmployeBtn->setObjectName("editEmployeBtn");
        editEmployeBtn->setEnabled(false);
        editEmployeBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_8->addWidget(editEmployeBtn);

        deleteEmployeBtn = new QPushButton(employesGroupBox);
        deleteEmployeBtn->setObjectName("deleteEmployeBtn");
        deleteEmployeBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout_8->addWidget(deleteEmployeBtn);

        refreshEmployeTableBtn = new QPushButton(employesGroupBox);
        refreshEmployeTableBtn->setObjectName("refreshEmployeTableBtn");
        refreshEmployeTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_8->addWidget(refreshEmployeTableBtn);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_16 = new QLabel(employesGroupBox);
        label_16->setObjectName("label_16");
        label_16->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_9->addWidget(label_16);

        searchEmployeLineEdit = new QLineEdit(employesGroupBox);
        searchEmployeLineEdit->setObjectName("searchEmployeLineEdit");
        searchEmployeLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_9->addWidget(searchEmployeLineEdit);


        verticalLayout_7->addLayout(horizontalLayout_9);

        employeTable = new QTableWidget(employesGroupBox);
        if (employeTable->columnCount() < 8)
            employeTable->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(6, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        employeTable->setHorizontalHeaderItem(7, __qtablewidgetitem13);
        employeTable->setObjectName("employeTable");
        employeTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #E67E22;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #E67E22;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        employeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        employeTable->setSelectionMode(QAbstractItemView::SingleSelection);
        employeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        employeTable->setShowGrid(true);
        employeTable->setGridStyle(Qt::SolidLine);
        employeTable->setAlternatingRowColors(true);
        employeTable->setSortingEnabled(true);
        employeTable->horizontalHeader()->setHighlightSections(false);
        employeTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_7->addWidget(employeTable);


        verticalLayout_4->addWidget(employesGroupBox);

        stackedWidget->addWidget(employesPage);
        projetsPage = new QWidget();
        projetsPage->setObjectName("projetsPage");
        verticalLayout_5 = new QVBoxLayout(projetsPage);
        verticalLayout_5->setObjectName("verticalLayout_5");
        projetsGroupBox = new QGroupBox(projetsPage);
        projetsGroupBox->setObjectName("projetsGroupBox");
        projetsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #27AE60;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #27AE60;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_8 = new QVBoxLayout(projetsGroupBox);
        verticalLayout_8->setObjectName("verticalLayout_8");
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        label_25 = new QLabel(projetsGroupBox);
        label_25->setObjectName("label_25");
        label_25->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_25);

        projetNomEdit = new QLineEdit(projetsGroupBox);
        projetNomEdit->setObjectName("projetNomEdit");
        projetNomEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, projetNomEdit);

        label_26 = new QLabel(projetsGroupBox);
        label_26->setObjectName("label_26");
        label_26->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, label_26);

        projetDescriptionEdit = new QLineEdit(projetsGroupBox);
        projetDescriptionEdit->setObjectName("projetDescriptionEdit");
        projetDescriptionEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, projetDescriptionEdit);

        label_27 = new QLabel(projetsGroupBox);
        label_27->setObjectName("label_27");
        label_27->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_3->setWidget(2, QFormLayout::LabelRole, label_27);

        projetClientIdEdit = new QLineEdit(projetsGroupBox);
        projetClientIdEdit->setObjectName("projetClientIdEdit");
        projetClientIdEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, projetClientIdEdit);

        label_28 = new QLabel(projetsGroupBox);
        label_28->setObjectName("label_28");
        label_28->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_28);

        projetEmployeIdEdit = new QLineEdit(projetsGroupBox);
        projetEmployeIdEdit->setObjectName("projetEmployeIdEdit");
        projetEmployeIdEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_3->setWidget(3, QFormLayout::FieldRole, projetEmployeIdEdit);

        label_29 = new QLabel(projetsGroupBox);
        label_29->setObjectName("label_29");
        label_29->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_3->setWidget(4, QFormLayout::LabelRole, label_29);

        projetBudgetEdit = new QLineEdit(projetsGroupBox);
        projetBudgetEdit->setObjectName("projetBudgetEdit");
        projetBudgetEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, projetBudgetEdit);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_30 = new QLabel(projetsGroupBox);
        label_30->setObjectName("label_30");
        label_30->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_10->addWidget(label_30);

        selectedProjetIdLabel = new QLabel(projetsGroupBox);
        selectedProjetIdLabel->setObjectName("selectedProjetIdLabel");
        selectedProjetIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedProjetIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(selectedProjetIdLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);

        clearProjetFormBtn = new QPushButton(projetsGroupBox);
        clearProjetFormBtn->setObjectName("clearProjetFormBtn");
        clearProjetFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_10->addWidget(clearProjetFormBtn);


        formLayout_3->setLayout(5, QFormLayout::SpanningRole, horizontalLayout_10);


        verticalLayout_8->addLayout(formLayout_3);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        addProjetBtn = new QPushButton(projetsGroupBox);
        addProjetBtn->setObjectName("addProjetBtn");
        addProjetBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_11->addWidget(addProjetBtn);

        editProjetBtn = new QPushButton(projetsGroupBox);
        editProjetBtn->setObjectName("editProjetBtn");
        editProjetBtn->setEnabled(false);
        editProjetBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_11->addWidget(editProjetBtn);

        deleteProjetBtn = new QPushButton(projetsGroupBox);
        deleteProjetBtn->setObjectName("deleteProjetBtn");
        deleteProjetBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout_11->addWidget(deleteProjetBtn);

        refreshProjetTableBtn = new QPushButton(projetsGroupBox);
        refreshProjetTableBtn->setObjectName("refreshProjetTableBtn");
        refreshProjetTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_11->addWidget(refreshProjetTableBtn);


        verticalLayout_8->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_31 = new QLabel(projetsGroupBox);
        label_31->setObjectName("label_31");
        label_31->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_12->addWidget(label_31);

        searchProjetLineEdit = new QLineEdit(projetsGroupBox);
        searchProjetLineEdit->setObjectName("searchProjetLineEdit");
        searchProjetLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_12->addWidget(searchProjetLineEdit);


        verticalLayout_8->addLayout(horizontalLayout_12);

        projetTable = new QTableWidget(projetsGroupBox);
        if (projetTable->columnCount() < 9)
            projetTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(0, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(1, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(4, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(5, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(6, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(7, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        projetTable->setHorizontalHeaderItem(8, __qtablewidgetitem22);
        projetTable->setObjectName("projetTable");
        projetTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #27AE60;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #27AE60;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        projetTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        projetTable->setSelectionMode(QAbstractItemView::SingleSelection);
        projetTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        projetTable->setShowGrid(true);
        projetTable->setGridStyle(Qt::SolidLine);
        projetTable->setAlternatingRowColors(true);
        projetTable->setSortingEnabled(true);
        projetTable->horizontalHeader()->setHighlightSections(false);
        projetTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_8->addWidget(projetTable);


        verticalLayout_5->addWidget(projetsGroupBox);

        stackedWidget->addWidget(projetsPage);
        financesPage = new QWidget();
        financesPage->setObjectName("financesPage");
        verticalLayout_6 = new QVBoxLayout(financesPage);
        verticalLayout_6->setObjectName("verticalLayout_6");
        financesGroupBox = new QGroupBox(financesPage);
        financesGroupBox->setObjectName("financesGroupBox");
        financesGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #8E44AD;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #8E44AD;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_9 = new QVBoxLayout(financesGroupBox);
        verticalLayout_9->setObjectName("verticalLayout_9");
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName("formLayout_4");
        label_32 = new QLabel(financesGroupBox);
        label_32->setObjectName("label_32");
        label_32->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_32);

        financeTypeEdit = new QLineEdit(financesGroupBox);
        financeTypeEdit->setObjectName("financeTypeEdit");
        financeTypeEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_4->setWidget(0, QFormLayout::FieldRole, financeTypeEdit);

        label_33 = new QLabel(financesGroupBox);
        label_33->setObjectName("label_33");
        label_33->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_33);

        financeMontantEdit = new QLineEdit(financesGroupBox);
        financeMontantEdit->setObjectName("financeMontantEdit");
        financeMontantEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_4->setWidget(1, QFormLayout::FieldRole, financeMontantEdit);

        label_34 = new QLabel(financesGroupBox);
        label_34->setObjectName("label_34");
        label_34->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_4->setWidget(2, QFormLayout::LabelRole, label_34);

        financeDescriptionEdit = new QLineEdit(financesGroupBox);
        financeDescriptionEdit->setObjectName("financeDescriptionEdit");
        financeDescriptionEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_4->setWidget(2, QFormLayout::FieldRole, financeDescriptionEdit);

        label_35 = new QLabel(financesGroupBox);
        label_35->setObjectName("label_35");
        label_35->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_35);

        financeProjetIdEdit = new QLineEdit(financesGroupBox);
        financeProjetIdEdit->setObjectName("financeProjetIdEdit");
        financeProjetIdEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_4->setWidget(3, QFormLayout::FieldRole, financeProjetIdEdit);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_36 = new QLabel(financesGroupBox);
        label_36->setObjectName("label_36");
        label_36->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_13->addWidget(label_36);

        selectedFinanceIdLabel = new QLabel(financesGroupBox);
        selectedFinanceIdLabel->setObjectName("selectedFinanceIdLabel");
        selectedFinanceIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedFinanceIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(selectedFinanceIdLabel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_5);

        clearFinanceFormBtn = new QPushButton(financesGroupBox);
        clearFinanceFormBtn->setObjectName("clearFinanceFormBtn");
        clearFinanceFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_13->addWidget(clearFinanceFormBtn);


        formLayout_4->setLayout(4, QFormLayout::SpanningRole, horizontalLayout_13);


        verticalLayout_9->addLayout(formLayout_4);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        addFinanceBtn = new QPushButton(financesGroupBox);
        addFinanceBtn->setObjectName("addFinanceBtn");
        addFinanceBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_14->addWidget(addFinanceBtn);

        editFinanceBtn = new QPushButton(financesGroupBox);
        editFinanceBtn->setObjectName("editFinanceBtn");
        editFinanceBtn->setEnabled(false);
        editFinanceBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_14->addWidget(editFinanceBtn);

        deleteFinanceBtn = new QPushButton(financesGroupBox);
        deleteFinanceBtn->setObjectName("deleteFinanceBtn");
        deleteFinanceBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout_14->addWidget(deleteFinanceBtn);

        refreshFinanceTableBtn = new QPushButton(financesGroupBox);
        refreshFinanceTableBtn->setObjectName("refreshFinanceTableBtn");
        refreshFinanceTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_14->addWidget(refreshFinanceTableBtn);


        verticalLayout_9->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        label_37 = new QLabel(financesGroupBox);
        label_37->setObjectName("label_37");
        label_37->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_15->addWidget(label_37);

        searchFinanceLineEdit = new QLineEdit(financesGroupBox);
        searchFinanceLineEdit->setObjectName("searchFinanceLineEdit");
        searchFinanceLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_15->addWidget(searchFinanceLineEdit);


        verticalLayout_9->addLayout(horizontalLayout_15);

        financeTable = new QTableWidget(financesGroupBox);
        if (financeTable->columnCount() < 7)
            financeTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(0, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(1, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(2, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(3, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(4, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(5, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        financeTable->setHorizontalHeaderItem(6, __qtablewidgetitem29);
        financeTable->setObjectName("financeTable");
        financeTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #8E44AD;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #8E44AD;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        financeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        financeTable->setSelectionMode(QAbstractItemView::SingleSelection);
        financeTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        financeTable->setShowGrid(true);
        financeTable->setGridStyle(Qt::SolidLine);
        financeTable->setAlternatingRowColors(true);
        financeTable->setSortingEnabled(true);
        financeTable->horizontalHeader()->setHighlightSections(false);
        financeTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_9->addWidget(financeTable);


        verticalLayout_6->addWidget(financesGroupBox);

        stackedWidget->addWidget(financesPage);
        equipementsPage = new QWidget();
        equipementsPage->setObjectName("equipementsPage");
        verticalLayout_10 = new QVBoxLayout(equipementsPage);
        verticalLayout_10->setObjectName("verticalLayout_10");
        equipementsGroupBox = new QGroupBox(equipementsPage);
        equipementsGroupBox->setObjectName("equipementsGroupBox");
        equipementsGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #16A085;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #16A085;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_11 = new QVBoxLayout(equipementsGroupBox);
        verticalLayout_11->setObjectName("verticalLayout_11");
        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName("formLayout_5");
        label_38 = new QLabel(equipementsGroupBox);
        label_38->setObjectName("label_38");
        label_38->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_38);

        equipementNomEdit = new QLineEdit(equipementsGroupBox);
        equipementNomEdit->setObjectName("equipementNomEdit");
        equipementNomEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_5->setWidget(0, QFormLayout::FieldRole, equipementNomEdit);

        label_39 = new QLabel(equipementsGroupBox);
        label_39->setObjectName("label_39");
        label_39->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_39);

        equipementTypeEdit = new QLineEdit(equipementsGroupBox);
        equipementTypeEdit->setObjectName("equipementTypeEdit");
        equipementTypeEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, equipementTypeEdit);

        label_40 = new QLabel(equipementsGroupBox);
        label_40->setObjectName("label_40");
        label_40->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_40);

        equipementEtatEdit = new QLineEdit(equipementsGroupBox);
        equipementEtatEdit->setObjectName("equipementEtatEdit");
        equipementEtatEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_5->setWidget(2, QFormLayout::FieldRole, equipementEtatEdit);

        label_41 = new QLabel(equipementsGroupBox);
        label_41->setObjectName("label_41");
        label_41->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_5->setWidget(3, QFormLayout::LabelRole, label_41);

        equipementPrixEdit = new QLineEdit(equipementsGroupBox);
        equipementPrixEdit->setObjectName("equipementPrixEdit");
        equipementPrixEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_5->setWidget(3, QFormLayout::FieldRole, equipementPrixEdit);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_42 = new QLabel(equipementsGroupBox);
        label_42->setObjectName("label_42");
        label_42->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_16->addWidget(label_42);

        selectedEquipementIdLabel = new QLabel(equipementsGroupBox);
        selectedEquipementIdLabel->setObjectName("selectedEquipementIdLabel");
        selectedEquipementIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedEquipementIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(selectedEquipementIdLabel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_6);

        clearEquipementFormBtn = new QPushButton(equipementsGroupBox);
        clearEquipementFormBtn->setObjectName("clearEquipementFormBtn");
        clearEquipementFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_16->addWidget(clearEquipementFormBtn);


        formLayout_5->setLayout(4, QFormLayout::SpanningRole, horizontalLayout_16);


        verticalLayout_11->addLayout(formLayout_5);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        addEquipementBtn = new QPushButton(equipementsGroupBox);
        addEquipementBtn->setObjectName("addEquipementBtn");
        addEquipementBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_17->addWidget(addEquipementBtn);

        editEquipementBtn = new QPushButton(equipementsGroupBox);
        editEquipementBtn->setObjectName("editEquipementBtn");
        editEquipementBtn->setEnabled(false);
        editEquipementBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_17->addWidget(editEquipementBtn);

        deleteEquipementBtn = new QPushButton(equipementsGroupBox);
        deleteEquipementBtn->setObjectName("deleteEquipementBtn");
        deleteEquipementBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #DC3545;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C82333;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #BD2130;\n"
"}"));

        horizontalLayout_17->addWidget(deleteEquipementBtn);

        refreshEquipementTableBtn = new QPushButton(equipementsGroupBox);
        refreshEquipementTableBtn->setObjectName("refreshEquipementTableBtn");
        refreshEquipementTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_17->addWidget(refreshEquipementTableBtn);


        verticalLayout_11->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        label_43 = new QLabel(equipementsGroupBox);
        label_43->setObjectName("label_43");
        label_43->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_18->addWidget(label_43);

        searchEquipementLineEdit = new QLineEdit(equipementsGroupBox);
        searchEquipementLineEdit->setObjectName("searchEquipementLineEdit");
        searchEquipementLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_18->addWidget(searchEquipementLineEdit);


        verticalLayout_11->addLayout(horizontalLayout_18);

        equipementTable = new QTableWidget(equipementsGroupBox);
        if (equipementTable->columnCount() < 6)
            equipementTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(3, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(4, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        equipementTable->setHorizontalHeaderItem(5, __qtablewidgetitem35);
        equipementTable->setObjectName("equipementTable");
        equipementTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #16A085;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #16A085;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        equipementTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        equipementTable->setSelectionMode(QAbstractItemView::SingleSelection);
        equipementTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        equipementTable->setShowGrid(true);
        equipementTable->setGridStyle(Qt::SolidLine);
        equipementTable->setAlternatingRowColors(true);
        equipementTable->setSortingEnabled(true);
        equipementTable->horizontalHeader()->setHighlightSections(false);
        equipementTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_11->addWidget(equipementTable);


        verticalLayout_10->addWidget(equipementsGroupBox);

        stackedWidget->addWidget(equipementsPage);
        mailingPage = new QWidget();
        mailingPage->setObjectName("mailingPage");
        verticalLayout_12 = new QVBoxLayout(mailingPage);
        verticalLayout_12->setObjectName("verticalLayout_12");
        mailingGroupBox = new QGroupBox(mailingPage);
        mailingGroupBox->setObjectName("mailingGroupBox");
        mailingGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #D35400;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #D35400;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_13 = new QVBoxLayout(mailingGroupBox);
        verticalLayout_13->setObjectName("verticalLayout_13");
        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName("formLayout_6");
        label_44 = new QLabel(mailingGroupBox);
        label_44->setObjectName("label_44");
        label_44->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_44);

        mailingSujetEdit = new QLineEdit(mailingGroupBox);
        mailingSujetEdit->setObjectName("mailingSujetEdit");
        mailingSujetEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, mailingSujetEdit);

        label_45 = new QLabel(mailingGroupBox);
        label_45->setObjectName("label_45");
        label_45->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_6->setWidget(1, QFormLayout::LabelRole, label_45);

        mailingDestinatairesCombo = new QComboBox(mailingGroupBox);
        mailingDestinatairesCombo->addItem(QString());
        mailingDestinatairesCombo->addItem(QString());
        mailingDestinatairesCombo->addItem(QString());
        mailingDestinatairesCombo->setObjectName("mailingDestinatairesCombo");
        mailingDestinatairesCombo->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QComboBox:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_6->setWidget(1, QFormLayout::FieldRole, mailingDestinatairesCombo);

        label_46 = new QLabel(mailingGroupBox);
        label_46->setObjectName("label_46");
        label_46->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayout_6->setWidget(2, QFormLayout::LabelRole, label_46);

        mailingMessageEdit = new QTextEdit(mailingGroupBox);
        mailingMessageEdit->setObjectName("mailingMessageEdit");
        mailingMessageEdit->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"    min-height: 150px;\n"
"}\n"
"QTextEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        formLayout_6->setWidget(2, QFormLayout::FieldRole, mailingMessageEdit);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        label_47 = new QLabel(mailingGroupBox);
        label_47->setObjectName("label_47");
        label_47->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_19->addWidget(label_47);

        selectedMailingIdLabel = new QLabel(mailingGroupBox);
        selectedMailingIdLabel->setObjectName("selectedMailingIdLabel");
        selectedMailingIdLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEBD0; padding: 4px 8px; border-radius: 4px;"));
        selectedMailingIdLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(selectedMailingIdLabel);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_7);

        clearMailingFormBtn = new QPushButton(mailingGroupBox);
        clearMailingFormBtn->setObjectName("clearMailingFormBtn");
        clearMailingFormBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #7D3C98;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #6C3483;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #5B2C6F;\n"
"}"));

        horizontalLayout_19->addWidget(clearMailingFormBtn);


        formLayout_6->setLayout(3, QFormLayout::SpanningRole, horizontalLayout_19);


        verticalLayout_13->addLayout(formLayout_6);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        sendTestMailBtn = new QPushButton(mailingGroupBox);
        sendTestMailBtn->setObjectName("sendTestMailBtn");
        sendTestMailBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #17A2B8;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #138496;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #117A8B;\n"
"}"));

        horizontalLayout_20->addWidget(sendTestMailBtn);

        addMailingBtn = new QPushButton(mailingGroupBox);
        addMailingBtn->setObjectName("addMailingBtn");
        addMailingBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #28A745;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #218838;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E7E34;\n"
"}"));

        horizontalLayout_20->addWidget(addMailingBtn);

        editMailingBtn = new QPushButton(mailingGroupBox);
        editMailingBtn->setObjectName("editMailingBtn");
        editMailingBtn->setEnabled(false);
        editMailingBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #FFC107;\n"
"    color: #212529;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #E0A800;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #D39E00;\n"
"}\n"
"QPushButton:disabled {\n"
"    background-color: #BDC3C7;\n"
"    color: #7F8C8D;\n"
"}"));

        horizontalLayout_20->addWidget(editMailingBtn);

        sendMailingBtn = new QPushButton(mailingGroupBox);
        sendMailingBtn->setObjectName("sendMailingBtn");
        sendMailingBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #D35400;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #BA4A00;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #A04000;\n"
"}"));

        horizontalLayout_20->addWidget(sendMailingBtn);

        refreshMailingTableBtn = new QPushButton(mailingGroupBox);
        refreshMailingTableBtn->setObjectName("refreshMailingTableBtn");
        refreshMailingTableBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #2E86AB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #266D8F;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1F5A7A;\n"
"}"));

        horizontalLayout_20->addWidget(refreshMailingTableBtn);


        verticalLayout_13->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        label_48 = new QLabel(mailingGroupBox);
        label_48->setObjectName("label_48");
        label_48->setStyleSheet(QString::fromUtf8("font-weight: bold; font-size: 12px;"));

        horizontalLayout_21->addWidget(label_48);

        searchMailingLineEdit = new QLineEdit(mailingGroupBox);
        searchMailingLineEdit->setObjectName("searchMailingLineEdit");
        searchMailingLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_21->addWidget(searchMailingLineEdit);


        verticalLayout_13->addLayout(horizontalLayout_21);

        mailingTable = new QTableWidget(mailingGroupBox);
        if (mailingTable->columnCount() < 9)
            mailingTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(0, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(1, __qtablewidgetitem37);
        QTableWidgetItem *__qtablewidgetitem38 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(2, __qtablewidgetitem38);
        QTableWidgetItem *__qtablewidgetitem39 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(3, __qtablewidgetitem39);
        QTableWidgetItem *__qtablewidgetitem40 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(4, __qtablewidgetitem40);
        QTableWidgetItem *__qtablewidgetitem41 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(5, __qtablewidgetitem41);
        QTableWidgetItem *__qtablewidgetitem42 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(6, __qtablewidgetitem42);
        QTableWidgetItem *__qtablewidgetitem43 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(7, __qtablewidgetitem43);
        QTableWidgetItem *__qtablewidgetitem44 = new QTableWidgetItem();
        mailingTable->setHorizontalHeaderItem(8, __qtablewidgetitem44);
        mailingTable->setObjectName("mailingTable");
        mailingTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #D35400;\n"
"    selection-color: white;\n"
"    gridline-color: #BDC3C7;\n"
"    border: 1px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"}\n"
"QTableWidget::item {\n"
"    padding: 8px;\n"
"    border-bottom: 1px solid #ECF0F1;\n"
"    color: #2E86AB;\n"
"}\n"
"QTableWidget::item:selected {\n"
"    background-color: #D35400;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        mailingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        mailingTable->setSelectionMode(QAbstractItemView::SingleSelection);
        mailingTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        mailingTable->setShowGrid(true);
        mailingTable->setGridStyle(Qt::SolidLine);
        mailingTable->setAlternatingRowColors(true);
        mailingTable->setSortingEnabled(true);
        mailingTable->horizontalHeader()->setHighlightSections(false);
        mailingTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_13->addWidget(mailingTable);


        verticalLayout_12->addWidget(mailingGroupBox);

        stackedWidget->addWidget(mailingPage);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Smart Studio - Gestion Compl\303\250te", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "SMART STUDIO", nullptr));
        clientsBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\221\245 Gestion Clients", nullptr));
        employesBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\221\250\342\200\215\360\237\222\274 Gestion Employ\303\251s", nullptr));
        projetsBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\201 Gestion Projets", nullptr));
        financesBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\222\260 Gestion Finances", nullptr));
        equipementsBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\267 Gestion \303\211quipements", nullptr));
        mailingBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247 Campagnes Mailing", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Smart Digital Content Creation Studio", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Section Client Interface Unit\303\251e", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Section Client list", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom:", nullptr));
        clientNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Jean Dupont", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        clientEmailEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: jean.dupont@email.com", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        clientPhoneEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 01 23 45 67 89", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "ID Client S\303\251lectionn\303\251:", nullptr));
        selectedClientIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouveau Client", nullptr));
        addClientBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Client", nullptr));
        editClientBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Client", nullptr));
        deleteClientBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Client", nullptr));
        exportPdfBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\204 Exporter PDF", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom, email ou t\303\251l\303\251phone...", nullptr));
        refreshTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
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
        label_7->setText(QCoreApplication::translate("MainWindow", "Total clients:", nullptr));
        totalClientsLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Clients actifs:", nullptr));
        activeClientsLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Nouveaux ce mois:", nullptr));
        newThisMonthLabel->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        activeClientsOnly->setText(QCoreApplication::translate("MainWindow", "Clients actifs seulement", nullptr));
        employesGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion des Employ\303\251s", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom:", nullptr));
        employeNameEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Marie Martin", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        employeEmailEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: marie.martin@email.com", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        employePhoneEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 01 23 45 67 89", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Poste:", nullptr));
        employePosteEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: D\303\251veloppeur", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Salaire:", nullptr));
        employeSalaireEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 3000.00", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "ID Employ\303\251 S\303\251lectionn\303\251:", nullptr));
        selectedEmployeIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearEmployeFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouvel Employ\303\251", nullptr));
        addEmployeBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Employ\303\251", nullptr));
        editEmployeBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Employ\303\251", nullptr));
        deleteEmployeBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Employ\303\251", nullptr));
        refreshEmployeTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchEmployeLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom, email ou poste...", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = employeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = employeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = employeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = employeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = employeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Poste", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = employeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Salaire", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = employeTable->horizontalHeaderItem(6);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "Date Embauche", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = employeTable->horizontalHeaderItem(7);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        projetsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion des Projets", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        projetNomEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Site Web E-commerce", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "Description:", nullptr));
        projetDescriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: D\303\251veloppement d'un site e-commerce", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "ID Client:", nullptr));
        projetClientIdEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 123", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "ID Employ\303\251:", nullptr));
        projetEmployeIdEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 456", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "Budget:", nullptr));
        projetBudgetEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 5000.00", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "ID Projet S\303\251lectionn\303\251:", nullptr));
        selectedProjetIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearProjetFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouveau Projet", nullptr));
        addProjetBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Projet", nullptr));
        editProjetBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Projet", nullptr));
        deleteProjetBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Projet", nullptr));
        refreshProjetTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchProjetLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom ou description...", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = projetTable->horizontalHeaderItem(0);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = projetTable->horizontalHeaderItem(1);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = projetTable->horizontalHeaderItem(2);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = projetTable->horizontalHeaderItem(3);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Client ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = projetTable->horizontalHeaderItem(4);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "Employ\303\251 ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = projetTable->horizontalHeaderItem(5);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "Date D\303\251but", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = projetTable->horizontalHeaderItem(6);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Date Fin", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = projetTable->horizontalHeaderItem(7);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Budget", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = projetTable->horizontalHeaderItem(8);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        financesGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion Financi\303\250re", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        financeTypeEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Vente, Achat, Salaire", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "Montant:", nullptr));
        financeMontantEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 1500.00", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Description:", nullptr));
        financeDescriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Paiement client XYZ", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "ID Projet:", nullptr));
        financeProjetIdEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 789", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "ID Finance S\303\251lectionn\303\251:", nullptr));
        selectedFinanceIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearFinanceFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouvelle Op\303\251ration", nullptr));
        addFinanceBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter Op\303\251ration", nullptr));
        editFinanceBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Op\303\251ration", nullptr));
        deleteFinanceBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer Op\303\251ration", nullptr));
        refreshFinanceTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchFinanceLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par type ou description...", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = financeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = financeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem25 = financeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem25->setText(QCoreApplication::translate("MainWindow", "Montant", nullptr));
        QTableWidgetItem *___qtablewidgetitem26 = financeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem26->setText(QCoreApplication::translate("MainWindow", "Description", nullptr));
        QTableWidgetItem *___qtablewidgetitem27 = financeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem27->setText(QCoreApplication::translate("MainWindow", "Date Op\303\251ration", nullptr));
        QTableWidgetItem *___qtablewidgetitem28 = financeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem28->setText(QCoreApplication::translate("MainWindow", "Projet ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem29 = financeTable->horizontalHeaderItem(6);
        ___qtablewidgetitem29->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        equipementsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Gestion des \303\211quipements", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "Nom:", nullptr));
        equipementNomEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Cam\303\251ra Sony A7III", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Type:", nullptr));
        equipementTypeEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Cam\303\251ra, Micro, \303\211clairage", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\303\211tat:", nullptr));
        equipementEtatEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Disponible, En usage, En r\303\251paration", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "Prix (\342\202\254):", nullptr));
        equipementPrixEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: 1500.00", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "ID \303\211quipement S\303\251lectionn\303\251:", nullptr));
        selectedEquipementIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearEquipementFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouvel \303\211quipement", nullptr));
        addEquipementBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Ajouter \303\211quipement", nullptr));
        editEquipementBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier \303\211quipement", nullptr));
        deleteEquipementBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Supprimer \303\211quipement", nullptr));
        refreshEquipementTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchEquipementLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par nom ou type...", nullptr));
        QTableWidgetItem *___qtablewidgetitem30 = equipementTable->horizontalHeaderItem(0);
        ___qtablewidgetitem30->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem31 = equipementTable->horizontalHeaderItem(1);
        ___qtablewidgetitem31->setText(QCoreApplication::translate("MainWindow", "Nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem32 = equipementTable->horizontalHeaderItem(2);
        ___qtablewidgetitem32->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem33 = equipementTable->horizontalHeaderItem(3);
        ___qtablewidgetitem33->setText(QCoreApplication::translate("MainWindow", "\303\211tat", nullptr));
        QTableWidgetItem *___qtablewidgetitem34 = equipementTable->horizontalHeaderItem(4);
        ___qtablewidgetitem34->setText(QCoreApplication::translate("MainWindow", "Prix (\342\202\254)", nullptr));
        QTableWidgetItem *___qtablewidgetitem35 = equipementTable->horizontalHeaderItem(5);
        ___qtablewidgetitem35->setText(QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        mailingGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Campagnes Mailing", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "Sujet:", nullptr));
        mailingSujetEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex: Nouvelle Offre Sp\303\251ciale", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "Destinataires:", nullptr));
        mailingDestinatairesCombo->setItemText(0, QCoreApplication::translate("MainWindow", "Tous les clients", nullptr));
        mailingDestinatairesCombo->setItemText(1, QCoreApplication::translate("MainWindow", "Clients actifs seulement", nullptr));
        mailingDestinatairesCombo->setItemText(2, QCoreApplication::translate("MainWindow", "Clients sp\303\251cifiques", nullptr));

        label_46->setText(QCoreApplication::translate("MainWindow", "Message:", nullptr));
        mailingMessageEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre message ici...", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "ID Campagne S\303\251lectionn\303\251e:", nullptr));
        selectedMailingIdLabel->setText(QCoreApplication::translate("MainWindow", "Aucun", nullptr));
        clearMailingFormBtn->setText(QCoreApplication::translate("MainWindow", "Nouvelle Campagne", nullptr));
        sendTestMailBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\247\252 Envoyer Test", nullptr));
        addMailingBtn->setText(QCoreApplication::translate("MainWindow", "\342\236\225 Cr\303\251er Campagne", nullptr));
        editMailingBtn->setText(QCoreApplication::translate("MainWindow", "\342\234\217\357\270\217 Modifier Campagne", nullptr));
        sendMailingBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\223\247 Envoyer Campagne", nullptr));
        refreshMailingTableBtn->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualiser", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 Recherche:", nullptr));
        searchMailingLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher par sujet ou statut...", nullptr));
        QTableWidgetItem *___qtablewidgetitem36 = mailingTable->horizontalHeaderItem(0);
        ___qtablewidgetitem36->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem37 = mailingTable->horizontalHeaderItem(1);
        ___qtablewidgetitem37->setText(QCoreApplication::translate("MainWindow", "Sujet", nullptr));
        QTableWidgetItem *___qtablewidgetitem38 = mailingTable->horizontalHeaderItem(2);
        ___qtablewidgetitem38->setText(QCoreApplication::translate("MainWindow", "Destinataires", nullptr));
        QTableWidgetItem *___qtablewidgetitem39 = mailingTable->horizontalHeaderItem(3);
        ___qtablewidgetitem39->setText(QCoreApplication::translate("MainWindow", "Date Cr\303\251ation", nullptr));
        QTableWidgetItem *___qtablewidgetitem40 = mailingTable->horizontalHeaderItem(4);
        ___qtablewidgetitem40->setText(QCoreApplication::translate("MainWindow", "Date Envoi", nullptr));
        QTableWidgetItem *___qtablewidgetitem41 = mailingTable->horizontalHeaderItem(5);
        ___qtablewidgetitem41->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        QTableWidgetItem *___qtablewidgetitem42 = mailingTable->horizontalHeaderItem(6);
        ___qtablewidgetitem42->setText(QCoreApplication::translate("MainWindow", "Destinataires", nullptr));
        QTableWidgetItem *___qtablewidgetitem43 = mailingTable->horizontalHeaderItem(7);
        ___qtablewidgetitem43->setText(QCoreApplication::translate("MainWindow", "Ouverts", nullptr));
        QTableWidgetItem *___qtablewidgetitem44 = mailingTable->horizontalHeaderItem(8);
        ___qtablewidgetitem44->setText(QCoreApplication::translate("MainWindow", "Clics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
