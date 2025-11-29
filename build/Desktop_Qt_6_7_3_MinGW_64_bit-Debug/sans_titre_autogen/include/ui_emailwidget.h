/********************************************************************************
** Form generated from reading UI file 'emailwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAILWIDGET_H
#define UI_EMAILWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmailWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *mailingGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_44;
    QPushButton *configSendGridBtn;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_45;
    QLabel *sendGridStatusLabel;
    QHBoxLayout *horizontalLayout_20;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_46;
    QTextEdit *mailclient;
    QPushButton *selectClientBtn;
    QLabel *label_47;
    QTextEdit *textEdit_message_email_3;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *generateWelcomeBtn;
    QPushButton *generatePromoBtn;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *clearMessageBtn;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_48;
    QPushButton *sendEmailBtn;
    QLabel *label_49;
    QLineEdit *newsletterSubject;
    QTextEdit *newsletterMessage;
    QPushButton *sendNewsletterBtn;
    QLabel *label_50;
    QTextEdit *emailStatusText;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_51;
    QLabel *validEmailsCountLabel;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *refreshMailingBtn;
    QTableWidget *clientsEmailTable;

    void setupUi(QWidget *EmailWidget)
    {
        if (EmailWidget->objectName().isEmpty())
            EmailWidget->setObjectName("EmailWidget");
        EmailWidget->resize(1200, 700);
        verticalLayout = new QVBoxLayout(EmailWidget);
        verticalLayout->setObjectName("verticalLayout");
        mailingGroupBox = new QGroupBox(EmailWidget);
        mailingGroupBox->setObjectName("mailingGroupBox");
        mailingGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    font-weight: bold;\n"
"    color: #2C3E50;\n"
"    border: 2px solid #E74C3C;\n"
"    border-radius: 8px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top center;\n"
"    padding: 0 10px;\n"
"    background-color: #E74C3C;\n"
"    color: white;\n"
"    border-radius: 4px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(mailingGroupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        label_44 = new QLabel(mailingGroupBox);
        label_44->setObjectName("label_44");
        label_44->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; font-size: 14px;"));

        horizontalLayout_19->addWidget(label_44);

        configSendGridBtn = new QPushButton(mailingGroupBox);
        configSendGridBtn->setObjectName("configSendGridBtn");
        configSendGridBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #E74C3C;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 10px 20px;\n"
"    border-radius: 5px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #C0392B;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #A93226;\n"
"}"));

        horizontalLayout_19->addWidget(configSendGridBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_7);

        label_45 = new QLabel(mailingGroupBox);
        label_45->setObjectName("label_45");
        label_45->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_19->addWidget(label_45);

        sendGridStatusLabel = new QLabel(mailingGroupBox);
        sendGridStatusLabel->setObjectName("sendGridStatusLabel");
        sendGridStatusLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #E74C3C; background-color: #FDEDEC; padding: 4px 8px; border-radius: 4px;"));

        horizontalLayout_19->addWidget(sendGridStatusLabel);


        verticalLayout_2->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        groupBox_2 = new QGroupBox(mailingGroupBox);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_14 = new QVBoxLayout(groupBox_2);
        verticalLayout_14->setObjectName("verticalLayout_14");
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        label_46 = new QLabel(groupBox_2);
        label_46->setObjectName("label_46");
        label_46->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        horizontalLayout_21->addWidget(label_46);

        mailclient = new QTextEdit(groupBox_2);
        mailclient->setObjectName("mailclient");
        mailclient->setMaximumSize(QSize(300, 40));
        mailclient->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"    font-weight: bold;\n"
"}\n"
"QTextEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        horizontalLayout_21->addWidget(mailclient);

        selectClientBtn = new QPushButton(groupBox_2);
        selectClientBtn->setObjectName("selectClientBtn");
        selectClientBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #3498DB;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #2980B9;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #21618C;\n"
"}"));

        horizontalLayout_21->addWidget(selectClientBtn);


        verticalLayout_14->addLayout(horizontalLayout_21);

        label_47 = new QLabel(groupBox_2);
        label_47->setObjectName("label_47");
        label_47->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        verticalLayout_14->addWidget(label_47);

        textEdit_message_email_3 = new QTextEdit(groupBox_2);
        textEdit_message_email_3->setObjectName("textEdit_message_email_3");
        textEdit_message_email_3->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    padding: 12px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    color: #2C3E50;\n"
"    font-size: 12px;\n"
"    min-height: 200px;\n"
"}\n"
"QTextEdit:focus {\n"
"    border-color: #3498DB;\n"
"}"));

        verticalLayout_14->addWidget(textEdit_message_email_3);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        generateWelcomeBtn = new QPushButton(groupBox_2);
        generateWelcomeBtn->setObjectName("generateWelcomeBtn");
        generateWelcomeBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #27AE60;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #229954;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #1E8449;\n"
"}"));

        horizontalLayout_22->addWidget(generateWelcomeBtn);

        generatePromoBtn = new QPushButton(groupBox_2);
        generatePromoBtn->setObjectName("generatePromoBtn");
        generatePromoBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #F39C12;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #D68910;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #B9770E;\n"
"}"));

        horizontalLayout_22->addWidget(generatePromoBtn);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_8);

        clearMessageBtn = new QPushButton(groupBox_2);
        clearMessageBtn->setObjectName("clearMessageBtn");
        clearMessageBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #95A5A6;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #7F8C8D;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #616A6B;\n"
"}"));

        horizontalLayout_22->addWidget(clearMessageBtn);


        verticalLayout_14->addLayout(horizontalLayout_22);


        horizontalLayout_20->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(mailingGroupBox);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
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
        verticalLayout_15 = new QVBoxLayout(groupBox_3);
        verticalLayout_15->setObjectName("verticalLayout_15");
        label_48 = new QLabel(groupBox_3);
        label_48->setObjectName("label_48");
        label_48->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #8E44AD;"));

        verticalLayout_15->addWidget(label_48);

        sendEmailBtn = new QPushButton(groupBox_3);
        sendEmailBtn->setObjectName("sendEmailBtn");
        sendEmailBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #8E44AD;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 15px;\n"
"    border-radius: 8px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #7D3C98;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6C3483;\n"
"}"));

        verticalLayout_15->addWidget(sendEmailBtn);

        label_49 = new QLabel(groupBox_3);
        label_49->setObjectName("label_49");
        label_49->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #8E44AD; margin-top: 20px;"));

        verticalLayout_15->addWidget(label_49);

        newsletterSubject = new QLineEdit(groupBox_3);
        newsletterSubject->setObjectName("newsletterSubject");
        newsletterSubject->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2E86AB;\n"
"}\n"
"QLineEdit:focus {\n"
"    border-color: #8E44AD;\n"
"}"));

        verticalLayout_15->addWidget(newsletterSubject);

        newsletterMessage = new QTextEdit(groupBox_3);
        newsletterMessage->setObjectName("newsletterMessage");
        newsletterMessage->setMaximumSize(QSize(16777215, 100));
        newsletterMessage->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: white;\n"
"    color: #2C3E50;\n"
"    font-size: 12px;\n"
"}\n"
"QTextEdit:focus {\n"
"    border-color: #8E44AD;\n"
"}"));

        verticalLayout_15->addWidget(newsletterMessage);

        sendNewsletterBtn = new QPushButton(groupBox_3);
        sendNewsletterBtn->setObjectName("sendNewsletterBtn");
        sendNewsletterBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #16A085;\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 12px;\n"
"    border-radius: 6px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #138D75;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #117A65;\n"
"}"));

        verticalLayout_15->addWidget(sendNewsletterBtn);

        label_50 = new QLabel(groupBox_3);
        label_50->setObjectName("label_50");
        label_50->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #8E44AD; margin-top: 15px;"));

        verticalLayout_15->addWidget(label_50);

        emailStatusText = new QTextEdit(groupBox_3);
        emailStatusText->setObjectName("emailStatusText");
        emailStatusText->setMaximumSize(QSize(16777215, 80));
        emailStatusText->setStyleSheet(QString::fromUtf8("QTextEdit {\n"
"    padding: 8px;\n"
"    border: 2px solid #BDC3C7;\n"
"    border-radius: 4px;\n"
"    background-color: #F8F9FA;\n"
"    color: #2C3E50;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"}"));

        verticalLayout_15->addWidget(emailStatusText);


        horizontalLayout_20->addWidget(groupBox_3);


        verticalLayout_2->addLayout(horizontalLayout_20);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        label_51 = new QLabel(mailingGroupBox);
        label_51->setObjectName("label_51");
        label_51->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #2C3E50;"));

        horizontalLayout_23->addWidget(label_51);

        validEmailsCountLabel = new QLabel(mailingGroupBox);
        validEmailsCountLabel->setObjectName("validEmailsCountLabel");
        validEmailsCountLabel->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #27AE60; background-color: #D5F5E3; padding: 4px 8px; border-radius: 4px;"));

        horizontalLayout_23->addWidget(validEmailsCountLabel);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_23->addItem(horizontalSpacer_9);

        refreshMailingBtn = new QPushButton(mailingGroupBox);
        refreshMailingBtn->setObjectName("refreshMailingBtn");
        refreshMailingBtn->setStyleSheet(QString::fromUtf8("QPushButton {\n"
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

        horizontalLayout_23->addWidget(refreshMailingBtn);


        verticalLayout_2->addLayout(horizontalLayout_23);

        clientsEmailTable = new QTableWidget(mailingGroupBox);
        if (clientsEmailTable->columnCount() < 5)
            clientsEmailTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientsEmailTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientsEmailTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        clientsEmailTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        clientsEmailTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        clientsEmailTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        clientsEmailTable->setObjectName("clientsEmailTable");
        clientsEmailTable->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: white;\n"
"    alternate-background-color: #F8F9FA;\n"
"    selection-background-color: #E74C3C;\n"
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
"    background-color: #E74C3C;\n"
"    color: white;\n"
"}\n"
"QHeaderView::section {\n"
"    background-color: #2C3E50;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"}"));
        clientsEmailTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        clientsEmailTable->setSelectionMode(QAbstractItemView::SingleSelection);
        clientsEmailTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        clientsEmailTable->setShowGrid(true);
        clientsEmailTable->setGridStyle(Qt::SolidLine);
        clientsEmailTable->setAlternatingRowColors(true);
        clientsEmailTable->setSortingEnabled(true);
        clientsEmailTable->horizontalHeader()->setHighlightSections(false);
        clientsEmailTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_2->addWidget(clientsEmailTable);


        verticalLayout->addWidget(mailingGroupBox);


        retranslateUi(EmailWidget);

        QMetaObject::connectSlotsByName(EmailWidget);
    } // setupUi

    void retranslateUi(QWidget *EmailWidget)
    {
        EmailWidget->setWindowTitle(QCoreApplication::translate("EmailWidget", "Email Widget", nullptr));
        mailingGroupBox->setTitle(QCoreApplication::translate("EmailWidget", "\360\237\223\247 Syst\303\250me de Mailing Clients", nullptr));
        label_44->setText(QCoreApplication::translate("EmailWidget", "\342\232\231\357\270\217 Configuration SendGrid", nullptr));
        configSendGridBtn->setText(QCoreApplication::translate("EmailWidget", "Configurer SendGrid", nullptr));
        label_45->setText(QCoreApplication::translate("EmailWidget", "Status: ", nullptr));
        sendGridStatusLabel->setText(QCoreApplication::translate("EmailWidget", "Non configur\303\251", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("EmailWidget", "\360\237\223\235 Composition du Message", nullptr));
        label_46->setText(QCoreApplication::translate("EmailWidget", "\360\237\223\247 Email du client:", nullptr));
        mailclient->setPlaceholderText(QCoreApplication::translate("EmailWidget", "email@exemple.com ou s\303\251lectionnez un client", nullptr));
        selectClientBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\221\245 S\303\251lectionner Client", nullptr));
        label_47->setText(QCoreApplication::translate("EmailWidget", "\360\237\222\254 Message:", nullptr));
        textEdit_message_email_3->setPlaceholderText(QCoreApplication::translate("EmailWidget", "Tapez votre message ici... (Un message automatique sera g\303\251n\303\251r\303\251 si vide)", nullptr));
        generateWelcomeBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\221\213 Message de Bienvenue", nullptr));
        generatePromoBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\216\211 Message Promotionnel", nullptr));
        clearMessageBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\227\221\357\270\217 Effacer", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("EmailWidget", "\360\237\223\212 Actions Rapides", nullptr));
        label_48->setText(QCoreApplication::translate("EmailWidget", "Envoi individuel:", nullptr));
        sendEmailBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\232\200 Envoyer Email", nullptr));
        label_49->setText(QCoreApplication::translate("EmailWidget", "Newsletter group\303\251e:", nullptr));
        newsletterSubject->setPlaceholderText(QCoreApplication::translate("EmailWidget", "Sujet de la newsletter...", nullptr));
        newsletterMessage->setPlaceholderText(QCoreApplication::translate("EmailWidget", "Message de la newsletter...", nullptr));
        sendNewsletterBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\223\250 Envoyer \303\240 Tous les Clients", nullptr));
        label_50->setText(QCoreApplication::translate("EmailWidget", "Statut d'envoi:", nullptr));
        label_51->setText(QCoreApplication::translate("EmailWidget", "\360\237\223\213 Clients avec emails valides:", nullptr));
        validEmailsCountLabel->setText(QCoreApplication::translate("EmailWidget", "0", nullptr));
        refreshMailingBtn->setText(QCoreApplication::translate("EmailWidget", "\360\237\224\204 Actualiser la Liste", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientsEmailTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("EmailWidget", "ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientsEmailTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("EmailWidget", "Nom/Pr\303\251nom", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientsEmailTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("EmailWidget", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientsEmailTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("EmailWidget", "T\303\251l\303\251phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = clientsEmailTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("EmailWidget", "Statut Email", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmailWidget: public Ui_EmailWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAILWIDGET_H
