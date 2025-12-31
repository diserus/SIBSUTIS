#pragma once
#include <QDialog>

class QLineEdit;
class QPushButton;
class QComboBox;

class RegisterDialog : public QDialog {
    Q_OBJECT
public:
    explicit RegisterDialog(QWidget* parent = nullptr);

    QString login() const;
    QString password() const;
    QString password2() const;

    QString role() const;

private:
    QLineEdit* m_login = nullptr;
    QLineEdit* m_pass1 = nullptr;
    QLineEdit* m_pass2 = nullptr;
    QComboBox* m_role  = nullptr;
    QPushButton* m_btnOk = nullptr;
    QPushButton* m_btnCancel = nullptr;
};
