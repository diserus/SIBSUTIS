#pragma once
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class UserRepository {
public:
    explicit UserRepository(QString filePath);

    bool ensureLoaded();
    QJsonObject findByLogin(const QString& login) const;
    bool addUser(const QJsonObject& userObject, QString* error = nullptr);

private:
    bool load(QString* error = nullptr);
    bool save(QString* error = nullptr);

    QString m_filePath;
    QJsonArray m_users;
    bool m_loaded = false;
};
