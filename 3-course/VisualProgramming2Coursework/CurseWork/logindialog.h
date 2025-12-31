#pragma once

#include <QDialog>
#include <QString>

#include "authservice.h"
#include "userrepository.h"

namespace Ui { class LoginDialog; }

class LoginDialog : public QDialog {
    Q_OBJECT
public:
    explicit LoginDialog(QWidget* parent = nullptr);
    ~LoginDialog();

    AuthUser user() const { return m_user; }

private slots:
    void on_btnLogin_clicked();
    void on_btnRegister_clicked();

private:
    Ui::LoginDialog* ui = nullptr;

    AuthUser m_user;
    int m_failedAttempts = 0;
    qint64 m_lockUntilMs = 0;

    UserRepository m_usersRepo;
    AuthService m_auth;
};
