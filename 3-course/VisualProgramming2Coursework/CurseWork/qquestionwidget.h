#ifndef QQUESTIONWIDGET_H
#define QQUESTIONWIDGET_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QVBoxLayout;
class QButtonGroup;
class QQuestionWidget : public QWidget
{
    Q_OBJECT
public:
    enum QuestionMode {
        SingleChoice = 0,
        MultipleChoice,
        FreeInput
    };
    enum QuestionDifficulty {
        Easy = 10,
        Medium = 15,
        Hard = 20
    };

    struct AnswerRow {
        QString text;
        bool correct;
    };
    QList<AnswerRow> answerRows() const;

    Q_ENUM(QuestionMode)
    Q_ENUM(QuestionDifficulty)
    explicit QQuestionWidget(int questionNumber, QWidget *parent = nullptr);

    void setQuestionNumber(int number);
    int  questionNumber() const { return m_number; }
    bool hasAnyAnswers() const;
    bool hasCorrectAnswer() const;
    QString questionText() const;
    void setQuestionText(const QString &text);
    QuestionMode getMode() const { return static_cast<QuestionMode>(mode); }
    QuestionDifficulty getDiff() const {return static_cast<QuestionDifficulty>(difficulty);}
signals:
    void requestRemove(QQuestionWidget *self);

private slots:
    void addAnswerRow();
    void deleteQuestion();
    void onTypeChanged(int index);
    void onDiffChanged(int index);
private:
    QWidget* createAnswerRow(QWidget *parent);
    void rebuildAnswerRow(QWidget *row, QuestionMode mode);
    void rebuildAllRows(QuestionMode mode);

private:
    int          m_number = 0;
    int          mode = 0;
    int          difficulty = 10;
    QLabel      *lblQuestion = nullptr;
    QLineEdit   *edtQuestion = nullptr;
    QComboBox   *cbType = nullptr;
    QComboBox   *cbDiff = nullptr;
    QPushButton *btnDeleteQuestion = nullptr;
    QPushButton *btnAddAnswer = nullptr;
    QVBoxLayout *answerLayout = nullptr;

    QButtonGroup *radioGroup = nullptr;
};

#endif
