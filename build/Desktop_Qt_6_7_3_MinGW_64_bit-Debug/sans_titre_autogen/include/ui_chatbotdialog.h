/********************************************************************************
** Form generated from reading UI file 'chatbotdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATBOTDIALOG_H
#define UI_CHATBOTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ChatbotDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *chatDisplay;
    QHBoxLayout *horizontalLayout;
    QLineEdit *inputText;
    QPushButton *sendButton;

    void setupUi(QDialog *ChatbotDialog)
    {
        if (ChatbotDialog->objectName().isEmpty())
            ChatbotDialog->setObjectName("ChatbotDialog");
        ChatbotDialog->resize(600, 500);
        ChatbotDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2);\n"
"}\n"
"\n"
"QTextEdit {\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 10px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    font-family: 'Segoe UI', Arial, sans-serif;\n"
"}\n"
"\n"
"QTextEdit:focus {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    color: #2c3e50;\n"
"    border: 2px solid #dee2e6;\n"
"    border-radius: 20px;\n"
"    padding: 10px 15px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-color: #3498db;\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    border: none;\n"
"    border-radius: 20px;\n"
"    padding: 10px 20px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #2980b9;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    backgroun"
                        "d-color: #21618c;\n"
"}\n"
"\n"
".message {\n"
"    margin: 10px 0;\n"
"    padding: 12px;\n"
"    border-radius: 15px;\n"
"    max-width: 80%;\n"
"}\n"
"\n"
".user-message {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"    margin-left: auto;\n"
"    border-bottom-right-radius: 5px;\n"
"}\n"
"\n"
".bot-message {\n"
"    background-color: #ecf0f1;\n"
"    color: #2c3e50;\n"
"    margin-right: auto;\n"
"    border-bottom-left-radius: 5px;\n"
"}\n"
"\n"
".sender {\n"
"    font-size: 12px;\n"
"    opacity: 0.8;\n"
"    margin-bottom: 5px;\n"
"}\n"
"\n"
".time {\n"
"    font-size: 10px;\n"
"    opacity: 0.6;\n"
"}\n"
"\n"
".content {\n"
"    font-size: 14px;\n"
"    line-height: 1.4;\n"
"}"));
        verticalLayout = new QVBoxLayout(ChatbotDialog);
        verticalLayout->setObjectName("verticalLayout");
        chatDisplay = new QTextEdit(ChatbotDialog);
        chatDisplay->setObjectName("chatDisplay");
        chatDisplay->setReadOnly(true);

        verticalLayout->addWidget(chatDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        inputText = new QLineEdit(ChatbotDialog);
        inputText->setObjectName("inputText");

        horizontalLayout->addWidget(inputText);

        sendButton = new QPushButton(ChatbotDialog);
        sendButton->setObjectName("sendButton");

        horizontalLayout->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(ChatbotDialog);

        QMetaObject::connectSlotsByName(ChatbotDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatbotDialog)
    {
        ChatbotDialog->setWindowTitle(QCoreApplication::translate("ChatbotDialog", "\360\237\244\226 Assistant Client", nullptr));
        chatDisplay->setHtml(QCoreApplication::translate("ChatbotDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:14px; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        inputText->setPlaceholderText(QCoreApplication::translate("ChatbotDialog", "Tapez votre message ici...", nullptr));
        sendButton->setText(QCoreApplication::translate("ChatbotDialog", "Envoyer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatbotDialog: public Ui_ChatbotDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATBOTDIALOG_H
