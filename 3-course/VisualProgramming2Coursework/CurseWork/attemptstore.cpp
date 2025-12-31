#include "attemptstore.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

AttemptStore::AttemptStore(QString filePath) : m_path(std::move(filePath)) {}

void AttemptStore::add(const AttemptRecord& r) {
    m_attempts.push_back(r);
}

QVector<AttemptRecord> AttemptStore::byUser(const QString& user) const {
    QVector<AttemptRecord> out;
    for (const auto& a : m_attempts)
        if (a.user == user) out.push_back(a);
    return out;
}

QVector<AttemptRecord> AttemptStore::byTest(const QString& testId) const {
    QVector<AttemptRecord> out;
    for (const auto& a : m_attempts)
        if (a.testId == testId) out.push_back(a);
    return out;
}

bool AttemptStore::load(QString* err)
{
    m_attempts.clear();

    QFile f(m_path);
    if (!f.exists()) return true;
    if (!f.open(QIODevice::ReadOnly)) {
        if (err) *err = "Не удалось открыть attempts.json";
        return false;
    }

    QJsonParseError pe{};
    const auto doc = QJsonDocument::fromJson(f.readAll(), &pe);
    if (pe.error != QJsonParseError::NoError || !doc.isObject()) {
        if (err) *err = "attempts.json повреждён";
        return false;
    }

    const QJsonObject root = doc.object();
    const QJsonArray arr = root.value("attempts").toArray();

    for (const auto& v : arr) {
        const auto o = v.toObject();
        AttemptRecord a;
        a.user = o.value("user").toString();
        a.testId = o.value("testId").toString();
        a.title = o.value("title").toString();
        a.subject = o.value("subject").toString();
        a.difficulty = o.value("difficulty").toString();
        a.author = o.value("author").toString();

        a.score = o.value("score").toInt(0);
        a.maxScore = o.value("maxScore").toInt(0);
        a.timeSpentSec = o.value("timeSpentSec").toInt(0);
        a.timeLimitSec = o.value("timeLimitSec").toInt(0);
        a.timeout = o.value("timeout").toBool(false);
        a.finishedAtIso = o.value("finishedAtIso").toString();

        m_attempts.push_back(a);
    }

    return true;
}

bool AttemptStore::save(QString* err)
{
    QJsonArray arr;
    for (const auto& a : m_attempts) {
        QJsonObject o;
        o["user"] = a.user;
        o["testId"] = a.testId;
        o["title"] = a.title;
        o["subject"] = a.subject;
        o["difficulty"] = a.difficulty;
        o["author"] = a.author;

        o["score"] = a.score;
        o["maxScore"] = a.maxScore;
        o["timeSpentSec"] = a.timeSpentSec;
        o["timeLimitSec"] = a.timeLimitSec;
        o["timeout"] = a.timeout;
        o["finishedAtIso"] = a.finishedAtIso;

        arr.append(o);
    }

    QJsonObject root;
    root["version"] = 1;
    root["attempts"] = arr;

    QFile f(m_path);
    if (!f.open(QIODevice::WriteOnly)) {
        if (err) *err = "Не удалось записать attempts.json";
        return false;
    }

    f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}
