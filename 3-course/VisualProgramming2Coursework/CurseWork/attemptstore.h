#pragma once

#include <QString>
#include <QVector>

struct AttemptRecord {
    QString user;
    QString testId;
    QString title;
    QString subject;
    QString difficulty;
    QString author;

    int score = 0;
    int maxScore = 0;

    int timeSpentSec = 0;
    int timeLimitSec = 0;

    bool timeout = false;
    QString finishedAtIso;
};

class AttemptStore {
public:
    explicit AttemptStore(QString filePath);

    bool load(QString* err = nullptr);
    bool save(QString* err = nullptr);

    void add(const AttemptRecord& r);
    const QVector<AttemptRecord>& all() const { return m_attempts; }

    QVector<AttemptRecord> byUser(const QString& user) const;
    QVector<AttemptRecord> byTest(const QString& testId) const;

private:
    QString m_path;
    QVector<AttemptRecord> m_attempts;
};
