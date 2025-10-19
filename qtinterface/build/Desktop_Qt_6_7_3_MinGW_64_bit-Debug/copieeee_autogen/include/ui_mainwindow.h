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
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *clientNameEdit;
    QLabel *label_2;
    QLineEdit *clientEmailEdit;
    QLabel *label_3;
    QLineEdit *clientPhoneEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addClientBtn;
    QPushButton *editClientBtn;
    QPushButton *deleteClientBtn;
    QPushButton *exportPdfBtn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *searchLineEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QComboBox *sortComboBox;
    QTableWidget *clientTable;
    QHBoxLayout *horizontalLayout_4;
    QLabel *totalClientsLabel;
    QLabel *activeClientsLabel;
    QLabel *newClientsLabel;
    QSpacerItem *horizontalSpacer_2;
    QSplitter *splitter_2;
    QWidget *chatWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QTextBrowser *chatHistory;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *chatInput;
    QPushButton *sendMessageBtn;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *quickReply1;
    QPushButton *quickReply2;
    QPushButton *quickReply3;
    QPushButton *quickReply4;
    QWidget *emailWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QSpinBox *clientCountSpinBox;
    QCheckBox *activeClientsOnlyCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QLineEdit *emailSubjectLineEdit;
    QLabel *label_11;
    QTextEdit *emailContentTextEdit;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *sendEmailBtn;
    QPushButton *saveTemplateBtn;
    QPushButton *loadTemplateBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(978, 805);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow {\n"
"    background-color: #f8f9fa;\n"
"    color: #2c3e50;\n"
"}\n"
"QWidget {\n"
"    background-color: #f8f9fa;\n"
"    font-size: 10pt;\n"
"    color: #2c3e50;\n"
"}\n"
"QLabel {\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"QGroupBox {\n"
"    background-color: white;\n"
"    border: 2px solid #A7C7E7;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding: 10px;\n"
"    color: #2c3e50;\n"
"    font-weight: bold;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 5px 10px;\n"
"    background-color: #A7C7E7;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton {\n"
"    background-color: #A7C7E7;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 15px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #95B8E7;\n"
"}\n"
"QLineEdit, QTextEdit, QComboBox, QSpinBox {\n"
"    border: 2px solid #A7C7E7;\n"
"    border-radius: 5p"
                        "x;\n"
"    padding: 6px;\n"
"    background-color: white;\n"
"    font-size: 10pt;\n"
"    color: #2c3e50;\n"
"}\n"
"QLineEdit:focus, QTextEdit:focus {\n"
"    border-color: #A7C7E7;\n"
"    background-color: #F0F8FF;\n"
"}\n"
"QTableWidget {\n"
"    background-color: white;\n"
"    border: 2px solid #A7C7E7;\n"
"    border-radius: 6px;\n"
"    gridline-color: #E1F5FE;\n"
"    color: #2c3e50;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #A7C7E7;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}\n"
"QSplitter::handle {\n"
"    background-color: #A7C7E7;\n"
"    margin: 2px;\n"
"}\n"
"QCheckBox {\n"
"    color: #2c3e50;\n"
"}\n"
"QTextBrowser {\n"
"    color: #2c3e50;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        leftWidget = new QWidget(splitter);
        leftWidget->setObjectName("leftWidget");
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(leftWidget);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        clientNameEdit = new QLineEdit(groupBox);
        clientNameEdit->setObjectName("clientNameEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, clientNameEdit);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        clientEmailEdit = new QLineEdit(groupBox);
        clientEmailEdit->setObjectName("clientEmailEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, clientEmailEdit);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        clientPhoneEdit = new QLineEdit(groupBox);
        clientPhoneEdit->setObjectName("clientPhoneEdit");

        formLayout->setWidget(2, QFormLayout::FieldRole, clientPhoneEdit);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        addClientBtn = new QPushButton(leftWidget);
        addClientBtn->setObjectName("addClientBtn");

        horizontalLayout_2->addWidget(addClientBtn);

        editClientBtn = new QPushButton(leftWidget);
        editClientBtn->setObjectName("editClientBtn");

        horizontalLayout_2->addWidget(editClientBtn);

        deleteClientBtn = new QPushButton(leftWidget);
        deleteClientBtn->setObjectName("deleteClientBtn");

        horizontalLayout_2->addWidget(deleteClientBtn);

        exportPdfBtn = new QPushButton(leftWidget);
        exportPdfBtn->setObjectName("exportPdfBtn");

        horizontalLayout_2->addWidget(exportPdfBtn);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(leftWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        searchLineEdit = new QLineEdit(leftWidget);
        searchLineEdit->setObjectName("searchLineEdit");

        horizontalLayout_3->addWidget(searchLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        label_5 = new QLabel(leftWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        sortComboBox = new QComboBox(leftWidget);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");

        horizontalLayout_3->addWidget(sortComboBox);


        verticalLayout_2->addLayout(horizontalLayout_3);

        clientTable = new QTableWidget(leftWidget);
        if (clientTable->columnCount() < 5)
            clientTable->setColumnCount(5);
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
        clientTable->setObjectName("clientTable");
        clientTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    border: 2px solid #A7C7E7;\n"
"    border-radius: 6px;\n"
"    gridline-color: #E1F5FE;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #A7C7E7;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));

        verticalLayout_2->addWidget(clientTable);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        totalClientsLabel = new QLabel(leftWidget);
        totalClientsLabel->setObjectName("totalClientsLabel");

        horizontalLayout_4->addWidget(totalClientsLabel);

        activeClientsLabel = new QLabel(leftWidget);
        activeClientsLabel->setObjectName("activeClientsLabel");

        horizontalLayout_4->addWidget(activeClientsLabel);

        newClientsLabel = new QLabel(leftWidget);
        newClientsLabel->setObjectName("newClientsLabel");

        horizontalLayout_4->addWidget(newClientsLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        splitter->addWidget(leftWidget);
        splitter_2 = new QSplitter(splitter);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Vertical);
        chatWidget = new QWidget(splitter_2);
        chatWidget->setObjectName("chatWidget");
        verticalLayout_3 = new QVBoxLayout(chatWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_6 = new QLabel(chatWidget);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignCenter);
        label_6->setStyleSheet(QString::fromUtf8("font-size: 14pt; font-weight: bold; color: #2c3e50;"));

        verticalLayout_3->addWidget(label_6);

        chatHistory = new QTextBrowser(chatWidget);
        chatHistory->setObjectName("chatHistory");
        chatHistory->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"    background-color: #E8F5E9;\n"
"    border: 2px solid #A5D6A7;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 10pt;\n"
"    color: #2c3e50;\n"
"}"));

        verticalLayout_3->addWidget(chatHistory);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        chatInput = new QLineEdit(chatWidget);
        chatInput->setObjectName("chatInput");

        horizontalLayout_5->addWidget(chatInput);

        sendMessageBtn = new QPushButton(chatWidget);
        sendMessageBtn->setObjectName("sendMessageBtn");

        horizontalLayout_5->addWidget(sendMessageBtn);


        verticalLayout_3->addLayout(horizontalLayout_5);

        label_7 = new QLabel(chatWidget);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        quickReply1 = new QPushButton(chatWidget);
        quickReply1->setObjectName("quickReply1");

        horizontalLayout_6->addWidget(quickReply1);

        quickReply2 = new QPushButton(chatWidget);
        quickReply2->setObjectName("quickReply2");

        horizontalLayout_6->addWidget(quickReply2);

        quickReply3 = new QPushButton(chatWidget);
        quickReply3->setObjectName("quickReply3");

        horizontalLayout_6->addWidget(quickReply3);

        quickReply4 = new QPushButton(chatWidget);
        quickReply4->setObjectName("quickReply4");

        horizontalLayout_6->addWidget(quickReply4);


        verticalLayout_3->addLayout(horizontalLayout_6);

        splitter_2->addWidget(chatWidget);
        emailWidget = new QWidget(splitter_2);
        emailWidget->setObjectName("emailWidget");
        verticalLayout_4 = new QVBoxLayout(emailWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_8 = new QLabel(emailWidget);
        label_8->setObjectName("label_8");
        label_8->setAlignment(Qt::AlignCenter);
        label_8->setStyleSheet(QString::fromUtf8("font-size: 14pt; font-weight: bold; color: #2c3e50;"));

        verticalLayout_4->addWidget(label_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_9 = new QLabel(emailWidget);
        label_9->setObjectName("label_9");

        horizontalLayout_7->addWidget(label_9);

        clientCountSpinBox = new QSpinBox(emailWidget);
        clientCountSpinBox->setObjectName("clientCountSpinBox");
        clientCountSpinBox->setValue(150);

        horizontalLayout_7->addWidget(clientCountSpinBox);

        activeClientsOnlyCheckBox = new QCheckBox(emailWidget);
        activeClientsOnlyCheckBox->setObjectName("activeClientsOnlyCheckBox");
        activeClientsOnlyCheckBox->setChecked(true);

        horizontalLayout_7->addWidget(activeClientsOnlyCheckBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_10 = new QLabel(emailWidget);
        label_10->setObjectName("label_10");

        horizontalLayout_8->addWidget(label_10);

        emailSubjectLineEdit = new QLineEdit(emailWidget);
        emailSubjectLineEdit->setObjectName("emailSubjectLineEdit");

        horizontalLayout_8->addWidget(emailSubjectLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_8);

        label_11 = new QLabel(emailWidget);
        label_11->setObjectName("label_11");

        verticalLayout_4->addWidget(label_11);

        emailContentTextEdit = new QTextEdit(emailWidget);
        emailContentTextEdit->setObjectName("emailContentTextEdit");
        emailContentTextEdit->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    background-color: #F0F8FF;\n"
"    border: 2px solid #A7C7E7;\n"
"    border-radius: 8px;\n"
"    padding: 8px;\n"
"    color: #2c3e50;\n"
"}"));

        verticalLayout_4->addWidget(emailContentTextEdit);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        sendEmailBtn = new QPushButton(emailWidget);
        sendEmailBtn->setObjectName("sendEmailBtn");

        horizontalLayout_9->addWidget(sendEmailBtn);

        saveTemplateBtn = new QPushButton(emailWidget);
        saveTemplateBtn->setObjectName("saveTemplateBtn");

        horizontalLayout_9->addWidget(saveTemplateBtn);

        loadTemplateBtn = new QPushButton(emailWidget);
        loadTemplateBtn->setObjectName("loadTemplateBtn");

        horizontalLayout_9->addWidget(loadTemplateBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_9);

        splitter_2->addWidget(emailWidget);
        splitter->addWidget(splitter_2);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Section Client Interface Unifi\303\251e", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Informations Client", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Email:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone:", nullptr));
        addClientBtn->setText(QCoreApplication::translate("MainWindow", "Ajouter Client", nullptr));
        editClientBtn->setText(QCoreApplication::translate("MainWindow", "Modifier Client", nullptr));
        deleteClientBtn->setText(QCoreApplication::translate("MainWindow", "Supprimer Client", nullptr));
        exportPdfBtn->setText(QCoreApplication::translate("MainWindow", "Exporter PDF", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Recherche:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Trier par:", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Email", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        sortComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Statut", nullptr));

        QTableWidgetItem *___qtablewidgetitem = clientTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Nom/Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Date d'ajout", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Statut", nullptr));
        totalClientsLabel->setText(QCoreApplication::translate("MainWindow", "Total clients: 0", nullptr));
        activeClientsLabel->setText(QCoreApplication::translate("MainWindow", "Clients actifs: 0", nullptr));
        newClientsLabel->setText(QCoreApplication::translate("MainWindow", "Nouveaux ce mois: 0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Support Client - Chatbot", nullptr));
        chatHistory->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Support:</span> Bonjour! Comment puis-je vous aider aujourd'hui?</p></body></html>", nullptr));
        chatInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "Tapez votre message ici...", nullptr));
        sendMessageBtn->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "R\303\251ponses rapides:", nullptr));
        quickReply1->setText(QCoreApplication::translate("MainWindow", "Probl\303\250me de connexion", nullptr));
        quickReply2->setText(QCoreApplication::translate("MainWindow", "Question facturation", nullptr));
        quickReply3->setText(QCoreApplication::translate("MainWindow", "Support technique", nullptr));
        quickReply4->setText(QCoreApplication::translate("MainWindow", "Demande information", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Campagne Email", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Nombre de clients:", nullptr));
        activeClientsOnlyCheckBox->setText(QCoreApplication::translate("MainWindow", "Clients actifs seulement", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Sujet:", nullptr));
        emailSubjectLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Sujet de l'email...", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Contenu:", nullptr));
        emailContentTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "R\303\251diger votre message ici...", nullptr));
        sendEmailBtn->setText(QCoreApplication::translate("MainWindow", "Envoyer l'email", nullptr));
        saveTemplateBtn->setText(QCoreApplication::translate("MainWindow", "Sauvegarder mod\303\250le", nullptr));
        loadTemplateBtn->setText(QCoreApplication::translate("MainWindow", "Charger mod\303\250le", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
