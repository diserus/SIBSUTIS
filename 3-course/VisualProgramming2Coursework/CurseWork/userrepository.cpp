#include "userrepository.h"

#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QSaveFile>

UserRepository::UserRepository(QString filePath)
    : m_filePath(std::move(filePath)) {}

bool UserRepository::ensureLoaded() {
    if (m_loaded) return true;
    return load();
}

bool UserRepository::load(QString* error) {
    m_users = QJsonArray{};
    m_loaded = true;

    QFile f(m_filePath);
    if (!f.exists()) {
        return true;
    }
    if (!f.open(QIODevice::ReadOnly)) {
        if (error) *error = "Не удалось открыть users.json для чтения";
        return false;
    }

    QJsonParseError pe;
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &pe);
    if (pe.error != QJsonParseError::NoError || !doc.isArray()) {
        if (error) *error = "users.json поврежден или имеет неверный формат";
        return false;
    }

    m_users = doc.array();
    return true;
}

bool UserRepository::save(QString* error) {
    QSaveFile f(m_filePath);
    if (!f.open(QIODevice::WriteOnly)) {
        if (error) *error = "Не удалось открыть users.json для записи";
        return false;
    }

    const QJsonDocument doc(m_users);
    f.write(doc.toJson(QJsonDocument::Indented));
    if (!f.commit()) {
        if (error) *error = "Не удалось сохранить users.json";
        return false;
    }
    return true;
}

QJsonObject UserRepository::findByLogin(const QString& login) const {
    for (const auto& v : m_users) {
        const QJsonObject o = v.toObject();
        if (o.value("login").toString() == login)
            return o;
    }
    return {};
}

bool UserRepository::addUser(const QJsonObject& userObject, QString* error) {
    if (!m_loaded) {
        if (!load(error)) return false;
    }

    const QString login = userObject.value("login").toString().trimmed();
    if (login.isEmpty()) {
        if (error) *error = "Пустой логин";
        return false;
    }
    if (!findByLogin(login).isEmpty()) {
        if (error) *error = "Пользователь с таким логином уже существует";
        return false;
    }

    if (userObject.value("salt").toString().isEmpty() || userObject.value("hash").toString().isEmpty()) {
        if (error) *error = "Некорректные salt/hash";
        return false;
    }

    m_users.append(userObject);
    return save(error);
}
