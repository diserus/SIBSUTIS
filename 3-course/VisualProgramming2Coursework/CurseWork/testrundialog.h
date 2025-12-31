#pragma once

#include <QDialog>
#include <QVector>
#include <QStringList>

class QLabel;
class QPushButton;
class QVBoxLayout;
class QButtonGroup;
class QLineEdit;
class QTimer;
class QAbstractButton;
class TestRunDialog : public QDialog {
    Q_OBJECT
public:
    explicit TestRunDialog(const QString& jsonPath, const QString& testId, QWidget* parent = nullptr);

    int score() const { return m_score; }
    int maxScore() const { return m_maxScore; }
    int timeSpentSec() const { return m_timeLimitSec > 0 ? (m_timeLimitSec - m_timeLeftSec) : 0; }
    int timeLimitSec() const { return m_timeLimitSec; }
    bool wasTimeout() const { return m_timeout; }

private slots:
    void onPrev();
    void onNext();
    void onFinish();
    void onTick();

private:
    struct Option { QString id; QString text; };
    struct Question {
        QString id;
        QString type;
        QString text;
        int points = 1;
        QVector<Option> options;
        QStringList correctIds;
        QStringList correctText;
    };

    bool loadFromFile(const QString& jsonPath, const QString& testId);
    void showQuestion(int index);
    void saveCurrentAnswer();
    int calculateScore() const;

private:
    QVector<Question> m_questions;
    QVector<QStringList> m_userChoiceIds;
    QVector<QString> m_userText;

    int m_index = 0;

    int m_timeLimitSec = 0;
    int m_timeLeftSec = 0;
    bool m_timeout = false;

    int m_score = 0;
    int m_maxScore = 0;

    QLabel* lblTitle = nullptr;
    QLabel* lblTimer = nullptr;
    QLabel* lblQText = nullptr;
    QVBoxLayout* answerLayout = nullptr;

    QPushButton* btnPrev = nullptr;
    QPushButton* btnNext = nullptr;
    QPushButton* btnFinish = nullptr;

    QButtonGroup* singleGroup = nullptr;
    QVector<QAbstractButton*> multiChecks;
    QLineEdit* textEdit = nullptr;

    QTimer* timer = nullptr;
};
