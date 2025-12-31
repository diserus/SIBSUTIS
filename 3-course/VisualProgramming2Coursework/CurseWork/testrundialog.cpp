#include "testrundialog.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLineEdit>
#include <QMessageBox>
#include <QTimer>

static QString normText(QString s) { return s.trimmed().toLower(); }

static QString formatTime(int sec)
{
    if (sec < 0) sec = 0;
    const int m = sec / 60;
    const int s = sec % 60;
    return QString("%1:%2").arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0'));
}

TestRunDialog::TestRunDialog(const QString& jsonPath, const QString& testId, QWidget* parent)
    : QDialog(parent)
{
    setObjectName("testRunDialog");
    setWindowTitle("Прохождение теста");
    setModal(true);

    auto* root = new QVBoxLayout(this);

    lblTitle = new QLabel(this);
    lblTimer = new QLabel(this);
    lblQText = new QLabel(this);
    lblQText->setWordWrap(true);

    root->addWidget(lblTitle);
    root->addWidget(lblTimer);
    root->addWidget(lblQText);

    auto* answersBox = new QWidget(this);
    answerLayout = new QVBoxLayout(answersBox);
    root->addWidget(answersBox);

    auto* nav = new QHBoxLayout;
    btnPrev = new QPushButton("Назад", this);
    btnNext = new QPushButton("Далее", this);
    btnFinish = new QPushButton("Завершить", this);
    nav->addWidget(btnPrev);
    nav->addWidget(btnNext);
    nav->addStretch();
    nav->addWidget(btnFinish);
    root->addLayout(nav);

    lblTitle->setObjectName("lblTitle");
    lblTimer->setObjectName("lblTimer");
    lblQText->setObjectName("lblQText");

    btnPrev->setObjectName("btnPrev");
    btnNext->setObjectName("btnNext");
    btnFinish->setObjectName("btnFinish");

    setStyleSheet(R"(
        QDialog#testRunDialog {
            background-color: #f5f7fb;
            font-family: "Segoe UI";
            font-size: 10pt;
            color: #1f2937;
        }

        QWidget { color: #1f2937; }

        QLabel#lblTitle {
            font-size: 14pt;
            font-weight: 700;
            color: #111827;
        }

        QLabel#lblTimer {
            font-size: 11pt;
            font-weight: 600;
            color: #0b5ed7;
        }

        QLabel#lblQText {
            font-size: 12pt;
            font-weight: 500;
            color: #111827;
        }

        QLineEdit {
            background-color: #ffffff;
            border: 1px solid #d1d5db;
            border-radius: 8px;
            padding: 6px 10px;
            selection-background-color: #0b5ed7;
            color: #111827;
        }
        QLineEdit:focus { border: 1px solid #0b5ed7; }

        QRadioButton, QCheckBox {
            spacing: 10px;
            padding: 4px 2px;
            color: #111827;
        }

        QRadioButton::indicator {
            width: 16px;
            height: 16px;
            border-radius: 8px;
            background: #ffffff;
            border: 1px solid #d1d5db;
        }
        QRadioButton::indicator:hover {
            border: 1px solid #0b5ed7;
        }
        QRadioButton::indicator:checked {
            background-color: #0b5ed7;
            border: 1px solid #005A9E;

        }

        QCheckBox::indicator {
            width: 16px;
            height: 16px;
            border-radius: 4px;
            background: #ffffff;
            border: 1px solid #d1d5db;
        }
        QCheckBox::indicator:hover {
            border: 1px solid #0b5ed7;
        }
        QCheckBox::indicator:checked {
            border-radius: 4px;
            background: #0b5ed7;
            border: 1px solid #0b5ed7;
        }

        QPushButton#btnPrev,
        QPushButton#btnNext {
            background-color: #0b5ed7;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 6px 12px;
            font-weight: 600;
            min-height: 32px;
            min-width: 120px;
        }
        QPushButton#btnPrev:hover,
        QPushButton#btnNext:hover {
            background-color: #0a53be;
        }
        QPushButton#btnPrev:pressed,
        QPushButton#btnNext:pressed {
            background-color: rgba(0, 0, 0, 25);
        }
        QPushButton#btnPrev:disabled,
        QPushButton#btnNext:disabled {
            background-color: #9ca3af;
            color: #f3f4f6;
        }

        QPushButton#btnFinish {
            background-color: #22c55e;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 6px 14px;
            font-weight: 700;
            min-height: 32px;
            min-width: 140px;
        }
        QPushButton#btnFinish:hover { background-color: #16a34a; }
        QPushButton#btnFinish:pressed { background-color: #15803d; }

        QScrollBar:vertical {
            background: transparent;
            width: 10px;
            margin: 6px 4px 6px 0px;
        }
        QScrollBar::handle:vertical {
            background: rgba(11, 94, 215, 120);
            border-radius: 5px;
            min-height: 30px;
        }
        QScrollBar::handle:vertical:hover {
            background: rgba(11, 94, 215, 170);
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0px;
        }
        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
        }
        )");

    connect(btnPrev, &QPushButton::clicked, this, &TestRunDialog::onPrev);
    connect(btnNext, &QPushButton::clicked, this, &TestRunDialog::onNext);
    connect(btnFinish, &QPushButton::clicked, this, &TestRunDialog::onFinish);

    if (!loadFromFile(jsonPath, testId)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить тест.");
        reject();
        return;
    }

    lblTimer->setText(QString("Осталось: %1").arg(formatTime(m_timeLeftSec)));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TestRunDialog::onTick);
    if (m_timeLeftSec > 0) timer->start(1000);

    showQuestion(0);
}

bool TestRunDialog::loadFromFile(const QString& jsonPath, const QString& testId)
{
    QFile f(jsonPath);
    if (!f.open(QIODevice::ReadOnly)) return false;

    QJsonParseError pe{};
    const auto doc = QJsonDocument::fromJson(f.readAll(), &pe);
    if (pe.error != QJsonParseError::NoError || !doc.isObject()) return false;

    const QJsonObject root = doc.object();
    const QJsonArray tests = root.value("tests").toArray();

    QJsonObject testObj;
    for (const auto& v : tests) {
        const auto o = v.toObject();
        if (o.value("id").toString() == testId) { testObj = o; break; }
    }
    if (testObj.isEmpty()) return false;

    lblTitle->setText(QString("%1 (%2)")
                          .arg(testObj.value("title").toString(),
                               testObj.value("subject").toString()));

    m_timeLimitSec = testObj.value("timeLimitSec").toInt(0);
    m_timeLeftSec = m_timeLimitSec;

    const QJsonArray qs = testObj.value("questions").toArray();
    for (const auto& qv : qs) {
        const QJsonObject q = qv.toObject();
        Question qq;
        qq.id = q.value("id").toString();
        qq.type = q.value("type").toString();
        qq.text = q.value("text").toString();
        qq.points = q.value("points").toInt(1);

        const QJsonArray opts = q.value("options").toArray();
        for (const auto& ov : opts) {
            const auto o = ov.toObject();
            qq.options.push_back({ o.value("id").toString(), o.value("text").toString() });
        }

        for (const auto& av : q.value("answer").toArray())
            qq.correctIds.push_back(av.toString());

        for (const auto& tv : q.value("answerText").toArray())
            qq.correctText.push_back(tv.toString());

        m_questions.push_back(qq);
        m_maxScore += qq.points;
    }

    m_userChoiceIds.resize(m_questions.size());
    m_userText.resize(m_questions.size());
    return !m_questions.isEmpty();
}

void TestRunDialog::onTick()
{
    if (m_timeLeftSec <= 0) return;

    --m_timeLeftSec;
    lblTimer->setText(QString("Осталось: %1").arg(formatTime(m_timeLeftSec)));

    if (m_timeLeftSec == 0) {
        m_timeout = true;
        onFinish();
    }
}

void TestRunDialog::saveCurrentAnswer()
{
    if (m_index < 0 || m_index >= m_questions.size()) return;
    const auto& q = m_questions[m_index];

    if (q.type == "text") {
        m_userText[m_index] = textEdit ? textEdit->text() : QString();
        return;
    }

    QStringList ids;
    if (q.type == "single" && singleGroup) {
        if (auto* b = singleGroup->checkedButton())
            ids << b->property("optId").toString();
    } else if (q.type == "multiple") {
        for (auto* c : multiChecks)
            if (c && c->isChecked())
                ids << c->property("optId").toString();
    }
    m_userChoiceIds[m_index] = ids;
}

void TestRunDialog::showQuestion(int index)
{
    m_index = index;

    while (answerLayout->count() > 0) {
        auto* it = answerLayout->takeAt(0);
        if (it->widget()) it->widget()->deleteLater();
        delete it;
    }

    delete singleGroup; singleGroup = nullptr;
    multiChecks.clear();
    textEdit = nullptr;

    const auto& q = m_questions[m_index];
    lblQText->setText(QString("Вопрос %1: %2").arg(m_index + 1).arg(q.text));

    if (q.type == "text") {
        textEdit = new QLineEdit(this);
        textEdit->setText(m_userText[m_index]);
        answerLayout->addWidget(textEdit);
    } else if (q.type == "single") {
        singleGroup = new QButtonGroup(this);
        singleGroup->setExclusive(true);

        for (const auto& opt : q.options) {
            auto* rb = new QRadioButton(opt.text, this);
            rb->setProperty("optId", opt.id);
            if (m_userChoiceIds[m_index].contains(opt.id)) rb->setChecked(true);
            singleGroup->addButton(rb);
            answerLayout->addWidget(rb);
        }
    } else if (q.type == "multiple") {
        for (const auto& opt : q.options) {
            auto* cb = new QCheckBox(opt.text, this);
            cb->setProperty("optId", opt.id);
            cb->setChecked(m_userChoiceIds[m_index].contains(opt.id));
            multiChecks.push_back(cb);
            answerLayout->addWidget(cb);
        }
    }

    btnPrev->setEnabled(m_index > 0);
    btnNext->setEnabled(m_index + 1 < m_questions.size());
}

void TestRunDialog::onPrev()
{
    saveCurrentAnswer();
    if (m_index > 0) showQuestion(m_index - 1);
}

void TestRunDialog::onNext()
{
    saveCurrentAnswer();
    if (m_index + 1 < m_questions.size()) showQuestion(m_index + 1);
}

int TestRunDialog::calculateScore() const
{
    int s = 0;
    for (int i = 0; i < m_questions.size(); ++i) {
        const auto& q = m_questions[i];
        bool ok = false;

        if (q.type == "text") {
            const QString u = normText(m_userText[i]);
            if (q.correctText.isEmpty()){ok = false;}
            else {
                ok = false;
                for (const auto& a: q.correctText)
                {
                    if (u==normText(a)){
                        ok = true;
                        break;
                    }
                }
            }
        } else {
            auto user = m_userChoiceIds[i]; user.sort();
            auto corr = q.correctIds; corr.sort();
            ok = (user == corr);
        }

        if (ok) s += q.points;
    }
    return s;
}

void TestRunDialog::onFinish()
{
    saveCurrentAnswer();
    if (timer) timer->stop();

    m_score = calculateScore();

    QMessageBox msg(this);
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle("Тест завершён");
    msg.setText(QString("Результат: %1 из %2").arg(m_score).arg(m_maxScore));
    msg.setStandardButtons(QMessageBox::Ok);

    msg.setStyleSheet(R"(
        QMessageBox {
            background-color: #f5f7fb;
            font-family: "Segoe UI";
            font-size: 10pt;
            color: #1f2937;
        }
        QLabel { color: #111827; }
        QPushButton {
            background-color: #0b5ed7;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 6px 14px;
            font-weight: 600;
            min-height: 30px;
        }
        QPushButton:hover { background-color: #0a53be; }
        QPushButton:pressed { background-color: rgba(0,0,0,25); }
    )");

    msg.exec();
    accept();
}

