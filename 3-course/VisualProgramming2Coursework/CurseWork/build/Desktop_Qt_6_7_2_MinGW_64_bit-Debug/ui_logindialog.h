/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QWidget *widget;
    QLabel *label;
    QLineEdit *login;
    QLineEdit *password;
    QPushButton *btnLogin;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QPushButton *btnRegister;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(400, 500);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginDialog->sizePolicy().hasHeightForWidth());
        LoginDialog->setSizePolicy(sizePolicy);
        LoginDialog->setMinimumSize(QSize(400, 500));
        LoginDialog->setMaximumSize(QSize(400, 500));
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::ContactNew));
        LoginDialog->setWindowIcon(icon);
        LoginDialog->setStyleSheet(QString::fromUtf8("QDialog#LoginDialog{\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                stop:0 #4b6cb7, stop:1 #182848);\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"    color: #333333;\n"
"}\n"
""));
        LoginDialog->setModal(false);
        widget = new QWidget(LoginDialog);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 60, 320, 390));
        widget->setStyleSheet(QString::fromUtf8("background-color: #ffffff;\n"
"    border-radius: 16px;"));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(80, 20, 170, 30));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI")});
        font.setPointSize(20);
        font.setWeight(QFont::DemiBold);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font-size: 20pt;\n"
"    font-weight: 600;\n"
"    color: #000000;"));
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setFrameShadow(QFrame::Shadow::Plain);
        label->setLineWidth(1);
        login = new QLineEdit(widget);
        login->setObjectName("login");
        login->setGeometry(QRect(80, 90, 150, 40));
        login->setMinimumSize(QSize(0, 0));
        login->setBaseSize(QSize(0, 0));
        login->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: none;\n"
"    border-bottom: 2px solid #cccccc;\n"
"    padding: 6px 0;\n"
"    background: transparent;\n"
"    color: #333333;\n"
"	padding-left: 10px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-bottom: 1px solid #4b6cb7;\n"
"}\n"
""));
        password = new QLineEdit(widget);
        password->setObjectName("password");
        password->setGeometry(QRect(80, 160, 150, 40));
        password->setMinimumSize(QSize(0, 0));
        password->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    border: none;\n"
"    border-bottom: 2px solid #cccccc;\n"
"    padding: 6px 0;\n"
"    background: transparent;\n"
"    color: #333333;\n"
"	padding-left: 10px;\n"
"\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border-bottom: 1px solid #4b6cb7;\n"
"}\n"
""));
        password->setEchoMode(QLineEdit::EchoMode::Password);
        btnLogin = new QPushButton(widget);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(100, 270, 120, 50));
        btnLogin->setMinimumSize(QSize(0, 0));
        btnLogin->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #1e90ff;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"    border-radius: 18px;      /* \320\277\320\276\321\207\321\202\320\270 \320\272\321\200\321\203\320\263\320\273\320\260\321\217 \320\277\320\276 \320\262\321\213\321\201\320\276\321\202\320\265 */\n"
"    padding: 8px 32px;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #0f7be0;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #0b5ca7;\n"
"}"));
        widget1 = new QWidget(widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(60, 330, 217, 19));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        label_2 = new QLabel(widget1);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        btnRegister = new QPushButton(widget1);
        btnRegister->setObjectName("btnRegister");
        btnRegister->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    color: #1e90ff;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    color: #0f7be0;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    color: #0b5ca7;\n"
"}"));

        horizontalLayout->addWidget(btnRegister);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "\320\222\321\205\320\276\320\264 \320\262 \321\201\320\270\321\201\321\202\320\265\320\274\321\203", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", nullptr));
        login->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        password->setPlaceholderText(QCoreApplication::translate("LoginDialog", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginDialog", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "\320\235\320\265\321\202 \320\260\320\272\320\272\320\260\321\203\320\275\321\202\320\260?", nullptr));
        btnRegister->setText(QCoreApplication::translate("LoginDialog", "\320\227\320\260\321\200\320\265\320\263\320\270\321\201\321\202\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214\321\201\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
