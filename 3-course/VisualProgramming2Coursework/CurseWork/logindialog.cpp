#include "logindialog.h"
#include "ui_logindialog.h"

#include "registerdialog.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent),
    ui(new Ui::LoginDialog),
    m_usersRepo(QCoreApplication::applicationDirPath() + "/users.json"),
    m_auth(m_usersRepo)
{
    ui->setupUi(this);

    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::on_btnLogin_clicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginDialog::on_btnRegister_clicked);
}

LoginDialog::~LoginDialog() {
    delete ui;
}

void LoginDialog::on_btnLogin_clicked() {
    const qint64 now = QDateTime::currentMSecsSinceEpoch();
    if (now < m_lockUntilMs) {
        QMessageBox::warning(this, "Блокировка", "Слишком много попыток. Подожди 30 секунд.");
        return;
    }

    const QString login = ui->login->text().trimmed();
    const QString pass  = ui->password->text();
    if (login.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите логин и пароль.");
        return;
    }

    AuthUser u;
    QString err;
    if (!m_auth.login(login, pass, &u, &err)) {
        ui->password->clear();
        m_failedAttempts++;
        if (m_failedAttempts >= 5) {
            m_lockUntilMs = now + 30 * 1000;
            m_failedAttempts = 0;
        }
        QMessageBox::warning(this, "Ошибка входа", err.isEmpty() ? "Неверный логин или пароль." : err);
        return;
    }

    m_failedAttempts = 0;
    m_lockUntilMs = 0;
    m_user = u;
    accept();
}

void LoginDialog::on_btnRegister_clicked() {
    RegisterDialog d(nullptr);
    d.setWindowModality(Qt::ApplicationModal);

    d.setStyleSheet("");

    if (d.exec() != QDialog::Accepted)
        return;

    if (d.login().isEmpty() || d.password().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Логин/пароль не должны быть пустыми.");
        return;
    }
    if (d.password() != d.password2()) {
        QMessageBox::warning(this, "Ошибка", "Пароли не совпадают.");
        return;
    }

    QString err;
    if (!m_auth.registerUser(d.login(), d.password(), d.role(), &err)) {
        QMessageBox::warning(this, "Ошибка регистрации", err.isEmpty() ? "Не удалось создать пользователя." : err);
        return;
    }

    QMessageBox::information(this, "Готово", "Аккаунт создан. Теперь можно войти.");
}
