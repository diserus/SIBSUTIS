#pragma once
#include <QByteArray>
#include <QCryptographicHash>
#include <QRandomGenerator>
#include <QString>

class PasswordHasher {
public:
    static QByteArray makeSalt(int n = 16) {
        QByteArray salt;
        salt.resize(n);
        for (int i = 0; i < n; ++i)
            salt[i] = char(QRandomGenerator::system()->generate() & 0xFF);
        return salt;
    }

    static QByteArray hashPassword(const QString& password, const QByteArray& salt) {
        QByteArray h = salt + password.toUtf8();
        h = QCryptographicHash::hash(h, QCryptographicHash::Sha256);
        for (int i = 0; i < 100000; ++i)
            h = QCryptographicHash::hash(h, QCryptographicHash::Sha256);
        return h;
    }

    static bool constantTimeEqual(const QByteArray& a, const QByteArray& b) {
        if (a.size() != b.size()) return false;
        uchar diff = 0;
        for (int i = 0; i < a.size(); ++i)
            diff |= uchar(a[i] ^ b[i]);
        return diff == 0;
    }
};
