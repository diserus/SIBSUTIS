// AuthService.cpp
#include "AuthService.h"
#include "PasswordHasher.h"

#include <QJsonObject>

AuthService::AuthService(UserRepository& repo) : m_repo(repo) {}

bool AuthService::login(const QString& login, const QString& password, AuthUser* outUser, QString* error) {
    if (!m_repo.ensureLoaded()) { if (error) *error = "Не удалось загрузить users.json"; return false; }

    const QJsonObject u = m_repo.findByLogin(login.trimmed());
    if (u.isEmpty()) { if (error) *error = "Неверный логин или пароль"; return false; }

    const QByteArray salt = QByteArray::fromHex(u.value("salt").toString().toUtf8());
    const QByteArray storedHash = QByteArray::fromHex(u.value("hash").toString().toUtf8());
    if (salt.isEmpty() || storedHash.isEmpty()) { if (error) *error = "Пользовательская запись повреждена"; return false; }

    const QByteArray calcHash = PasswordHasher::hashPassword(password, salt);
    if (!PasswordHasher::constantTimeEqual(calcHash, storedHash)) { if (error) *error = "Неверный логин или пароль"; return false; }

    if (outUser) {
        outUser->login = u.value("login").toString();
        outUser->role  = u.value("role").toString();
        if (outUser->role.isEmpty()) outUser->role = "student";
    }
    return true;
}

bool AuthService::registerUser(const QString& login,
                               const QString& password,
                               const QString& role,
                               QString* error)
{
    const QString l = login.trimmed();
    const QString r = role.trimmed().toLower();

    if (l.isEmpty() || password.isEmpty()) { if (error) *error = "Логин/пароль не должны быть пустыми"; return false; }
    if (password.size() < 6) { if (error) *error = "Пароль слишком короткий (минимум 6 символов)"; return false; }

    if (r != "student" && r != "teacher") { if (error) *error = "Неизвестная роль"; return false; }

    if (!m_repo.ensureLoaded()) { if (error) *error = "Не удалось загрузить users.json"; return false; }
    if (!m_repo.findByLogin(l).isEmpty()) { if (error) *error = "Логин уже занят"; return false; }

    const QByteArray salt = PasswordHasher::makeSalt(16);
    const QByteArray hash = PasswordHasher::hashPassword(password, salt);

    QJsonObject obj;
    obj["login"] = l;
    obj["role"]  = r;
    obj["salt"]  = QString::fromUtf8(salt.toHex());
    obj["hash"]  = QString::fromUtf8(hash.toHex());

    return m_repo.addUser(obj, error);
}
