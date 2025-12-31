#include "mainwindow.h"
#include "logindialog.h"
#include "authservice.h"
#include "userrepository.h"
#include "testeditor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginDialog login;
    if (login.exec() != QDialog::Accepted) {
        return 0;
    }

    MainWindow w;
    w.applyUser(login.user());
    w.show();

    return a.exec();
}
