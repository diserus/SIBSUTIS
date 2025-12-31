#include "RegisterDialog.h"

#include <QComboBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

RegisterDialog::RegisterDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Регистрация");

    m_login = new QLineEdit(this);
    m_pass1 = new QLineEdit(this);
    m_pass2 = new QLineEdit(this);
    m_pass1->setEchoMode(QLineEdit::Password);
    m_pass2->setEchoMode(QLineEdit::Password);

    m_role = new QComboBox(this);
    m_role->addItem("Студент", "student");
    m_role->addItem("Учитель", "teacher");

    auto* form = new QFormLayout();
    form->addRow("Логин:", m_login);
    form->addRow("Пароль:", m_pass1);
    form->addRow("Повтор пароля:", m_pass2);
    form->addRow("Роль:", m_role);

    m_btnOk = new QPushButton("Создать аккаунт", this);
    m_btnCancel = new QPushButton("Отмена", this);

    auto* buttons = new QHBoxLayout();
    buttons->addStretch();
    buttons->addWidget(m_btnOk);
    buttons->addWidget(m_btnCancel);

    auto* root = new QVBoxLayout(this);
    root->addLayout(form);
    root->addLayout(buttons);

    connect(m_btnOk, &QPushButton::clicked, this, &QDialog::accept);
    connect(m_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
}

QString RegisterDialog::login() const { return m_login->text().trimmed(); }
QString RegisterDialog::password() const { return m_pass1->text(); }
QString RegisterDialog::password2() const { return m_pass2->text(); }

QString RegisterDialog::role() const {
    return m_role->currentData().toString();
}
