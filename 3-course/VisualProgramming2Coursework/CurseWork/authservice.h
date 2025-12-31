// AuthService.h
#pragma once
#include <QString>
#include "userrepository.h"

struct AuthUser {
    QString login;
    QString role;
};

class AuthService {
public:
    explicit AuthService(UserRepository& repo);

    bool login(const QString& login, const QString& password, AuthUser* outUser, QString* error = nullptr);

    bool registerUser(const QString& login,
                      const QString& password,
                      const QString& role,
                      QString* error = nullptr);

private:
    UserRepository& m_repo;
};
