#include "testeditor.h"
#include "ui_testeditor.h"
#include "qquestionwidget.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QDialogButtonBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDateTime>
#include <QMessageBox>
#include <QComboBox>
#include <QDir>
#include <QString>
TestEditor::TestEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestEditor)
{
    ui->setupUi(this);

    setMinimumHeight(600);
    if (auto btnEnd = findChild<QPushButton*>("endTest")) {
        connect(btnEnd, &QPushButton::clicked,
                this, &TestEditor::onEndTestClicked);
    }

    scrollQuestions = new QScrollArea(this);
    scrollQuestions->setObjectName("scrollQuestions");
    scrollQuestions->setWidgetResizable(true);
    scrollQuestions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollQuestions->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    questionContainer = new QWidget(scrollQuestions);
    questionContainer->setObjectName("questionContainer");
    questionContainer->setSizePolicy(QSizePolicy::Preferred,
                                     QSizePolicy::MinimumExpanding);

    questionLayout = new QVBoxLayout(questionContainer);
    questionLayout->setObjectName("questionLayout");
    questionLayout->setContentsMargins(8, 8, 8, 8);
    questionLayout->setSpacing(8);



    scrollQuestions->setWidget(questionContainer);

    ui->verticalLayout_2->insertWidget(1, scrollQuestions);
    ui->verticalLayout_2->setStretch(0, 0);
    ui->verticalLayout_2->setStretch(1, 1);
    ui->verticalLayout_2->setStretch(2, 0);

    onAddQuestionClicked();

    if (auto btn = findChild<QPushButton*>("addQuestion")) {
        connect(btn, &QPushButton::clicked,
                this, &TestEditor::onAddQuestionClicked);
    }
}

TestEditor::~TestEditor()
{
    delete ui;
}

void TestEditor::onAddQuestionClicked()
{
    int questionNumber = 0;
    for (int i = 0; i < questionLayout->count(); ++i) {
        if (questionLayout->itemAt(i)->widget())
            ++questionNumber;
    }
    ++questionNumber;

    auto *w = new QQuestionWidget(questionNumber, questionContainer);
    questionLayout->addWidget(w);

    connect(w, &QQuestionWidget::requestRemove,
            this, &TestEditor::removeQuestionWidget);

    scrollQuestions->ensureWidgetVisible(w);
}

void TestEditor::onEndTestClicked()
{
    QDialog dlg(this);
    dlg.setWindowTitle("Параметры теста");
    int anySingle = 0;
    int anyMulti = 0;
    int anyFree = 0;
    auto* layout = new QFormLayout(&dlg);

    auto* edtSubject = new QLineEdit(&dlg);
    auto* edtTopic = new QLineEdit(&dlg);
    auto* sbMinutes = new QSpinBox(&dlg);
    auto* cbDiff = new QComboBox(&dlg);
    cbDiff->addItem(tr("Лёгкий"), QQuestionWidget::Easy);
    cbDiff->addItem(tr("Средний"), QQuestionWidget::Medium);
    cbDiff->addItem(tr("Сложный"), QQuestionWidget::Hard);
    sbMinutes->setRange(1,300);
    sbMinutes->setValue(10);

    layout->addRow(QStringLiteral("Предмет:"), edtSubject);
    layout->addRow(QStringLiteral("Тема:"), edtTopic);
    layout->addRow(QStringLiteral("Сложность:"), cbDiff);
    layout->addRow(QStringLiteral("Время (мин):"), sbMinutes);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dlg);
    layout->addRow(buttons);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::rejected);

    if (dlg.exec() != QDialog::Accepted) return;

    const QString subject = edtSubject->text();
    const QString topic = edtTopic->text();
    const int durationMin = sbMinutes->value();

    QJsonArray questionArray;

    int qIndex = 1;
    for (int i = 0; i < questionLayout->count(); ++i)
    {
        auto* item = questionLayout->itemAt(i);
        if (!item) continue;
        auto* qw = qobject_cast<QQuestionWidget*>(item->widget());
        if (!qw) continue;

        if (qw->questionText().trimmed().isEmpty()) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Вопрос %1 не заполнен. Заполните текст вопроса.")
                                     .arg(qw->questionNumber()));
            return;
        }

        if (!qw->hasAnyAnswers()) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Для вопроса %1 не добавлены ответы.")
                                     .arg(qw->questionNumber()));
            return;
        }
        if (!qw->hasCorrectAnswer()) {
            QMessageBox::warning(this, tr("Ошибка"),
                                 tr("Для вопроса %1 не выбран правильный ответ.")
                                     .arg(qw->questionNumber()));
            return;
        }
        QJsonObject qObj;

        qObj["id"] = QStringLiteral("q%1").arg(qIndex++);

        QString typeStr;
        switch (qw->getMode()) {
        case QQuestionWidget::SingleChoice:
            typeStr = "single";
            anySingle = 1;
            break;
        case QQuestionWidget::MultipleChoice:
            typeStr = "multiple";
            anyMulti = 1;
            break;
        case QQuestionWidget::FreeInput:
            typeStr = "text";
            anyFree = 1;
            break;
        }
        qObj["type"] = typeStr;

        qObj["text"] = qw->questionText();

        qObj["points"] = qw->getDiff() / 10;

        QJsonArray optionArray;
        QJsonArray answerArray;

        const auto rows = qw->answerRows();
        QChar optionId = 'a';
        for (const auto &row: rows)
        {
            QJsonObject opt;
            const QString optId = QString(optionId);

            opt["id"] = optId;
            opt["text"] = row.text;
            optionArray.append(opt);

            if (row.correct) answerArray.append(optId);
            optionId = QChar(optionId.unicode() + 1);
        }
        if (typeStr == "text")
        {

            const auto rows = qw->answerRows();
            if (!rows.isEmpty() && !rows[0].text.trimmed().isEmpty())
            {
                answerArray.append(rows[0].text.trimmed().toLower());
            }
            QJsonObject textRules;
            textRules["caseSesitive"] = false;
            textRules["trim"] = true;
            qObj["textRules"] = textRules;
            qObj["answerText"] = answerArray;

        } else {
            qObj["options"] = optionArray;
            qObj["answer"] = answerArray;
        }

        if (typeStr == "multiple") {
            QJsonObject grading;
            grading["mode"] = "allOrNothing";
            qObj["granding"] = grading;
        }

        questionArray.append(qObj);
    }
    QJsonObject testObj;
    testObj["id"] = QStringLiteral("t_%1_%2").arg(subject.left(3).toLower()).arg(QDateTime::currentDateTimeUtc().toSecsSinceEpoch());
    testObj["title"] = ui->edtTitle->text().trimmed();
    testObj["topic"] = topic;
    testObj["subject"] = subject;
    int dift = static_cast<QQuestionWidget::QuestionDifficulty>(cbDiff->currentData().toInt());
    switch(dift)
    {
    case QQuestionWidget::QuestionDifficulty::Easy:
        testObj["difficulty"] = "Easy";
        break;
    case QQuestionWidget::QuestionDifficulty::Medium:
        testObj["difficulty"] = "Medium";
        break;
    case QQuestionWidget::QuestionDifficulty::Hard:
        testObj["difficulty"] = "Hard";
        break;
    }
    testObj["author"] = m_author;
    testObj["timeLimitSec"] = durationMin * 60;
    testObj["questions"] = questionArray;
    testObj["anySingle"] = anySingle;
    testObj["anyMulti"] = anyMulti;
    testObj["anyFree"] = anyFree;
    QJsonArray testsArray;
    testsArray.append(testObj);

    QJsonObject root;
    root["version"] = 1;
    root["tests"] = testsArray;

    QJsonDocument doc(root);

    const QString filename = QStringLiteral("test_%1_%2.json").arg(subject).arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    const QString fullPath = QDir(QCoreApplication::applicationDirPath()).filePath(filename);
    QFile file(fullPath);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл для записи: %1").arg(filename));
        return;
    }
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    QMessageBox::information(this, tr("Готово"), tr("Тест сохранён в файл:\n%1").arg(filename));
    emit finished(true, filename);
    close();
}
void TestEditor::closeEvent(QCloseEvent* e)
{
    emit finished(false, QString());
    QMainWindow::closeEvent(e);
}
void TestEditor::removeQuestionWidget(QQuestionWidget *w)
{
    questionLayout->removeWidget(w);
    w->deleteLater();

    int num = 1;
    for (int i = 0; i < questionLayout->count(); ++i) {
        if (auto item = questionLayout->itemAt(i)) {
            if (auto qw = qobject_cast<QQuestionWidget*>(item->widget())) {
                qw->setQuestionNumber(num++);
            }
        }
    }
}

