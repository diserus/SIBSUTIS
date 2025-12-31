#include "qquestionwidget.h"

#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QString>
QQuestionWidget::QQuestionWidget(int questionNumber, QWidget *parent)
    : QWidget(parent)
{
    setObjectName("questionsPanel");

    QSizePolicy sp(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sp.setVerticalStretch(0);
    setSizePolicy(sp);
    setMinimumHeight(160);

    lblQuestion = new QLabel(tr("Вопрос %1").arg(questionNumber), this);

    edtQuestion = new QLineEdit(this);
    edtQuestion->setPlaceholderText(tr("Введите текст вопроса"));
    edtQuestion->setMinimumHeight(30);

    cbType = new QComboBox(this);
    cbType->addItem(tr("Один вариант ответа"),   SingleChoice);
    cbType->addItem(tr("Несколько вариантов"),   MultipleChoice);
    cbType->addItem(tr("Свободный ввод ответа"), FreeInput);

    cbDiff = new QComboBox(this);
    cbDiff->addItem(tr("Лёгкий"), Easy);
    cbDiff->addItem(tr("Нормальный"), Medium);
    cbDiff->addItem(tr("Сложный"), Hard);


    auto *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(lblQuestion);
    headerLayout->addWidget(cbType);
    headerLayout->addWidget(cbDiff);
    headerLayout->addStretch();

    btnDeleteQuestion = new QPushButton(tr("Удалить вопрос"), this);
    btnAddAnswer      = new QPushButton(tr("Добавить вариант ответа"), this);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(btnDeleteQuestion);
    buttonsLayout->addWidget(btnAddAnswer);

    answerLayout = new QVBoxLayout;
    answerLayout->setContentsMargins(0, 0, 0, 0);
    answerLayout->setSpacing(4);

    radioGroup = new QButtonGroup(this);
    radioGroup->setExclusive(true);


    answerLayout->addWidget(createAnswerRow(this));
    answerLayout->addWidget(createAnswerRow(this));
    answerLayout->addWidget(createAnswerRow(this));
    answerLayout->addWidget(createAnswerRow(this));

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(3);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(edtQuestion);
    mainLayout->addLayout(answerLayout);
    mainLayout->addLayout(buttonsLayout);

    connect(btnAddAnswer, &QPushButton::clicked,
            this, &QQuestionWidget::addAnswerRow);
    connect(btnDeleteQuestion, &QPushButton::clicked,
            this, &QQuestionWidget::deleteQuestion);
    connect(cbType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &QQuestionWidget::onTypeChanged);
    connect(cbDiff, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &QQuestionWidget::onDiffChanged);
    setQuestionNumber(questionNumber);
}

QWidget* QQuestionWidget::createAnswerRow(QWidget *parent)
{
    auto *row = new QWidget(parent);
    auto *lay = new QHBoxLayout(row);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(4);

    QAbstractButton *rb = nullptr;
    if (this->mode == SingleChoice)
    {
        rb = new QRadioButton(row);
        rb->setMinimumHeight(18);
    }
    else
    {
        rb = new QCheckBox(row);
        rb->setMinimumHeight(18);
    }

    radioGroup->addButton(rb);

    auto *edit = new QLineEdit(row);
    edit->setMinimumHeight(30);

    lay->addWidget(rb);
    lay->addWidget(edit);

    return row;
}

void QQuestionWidget::setQuestionNumber(int number)
{
    m_number = number;
    lblQuestion->setText(tr("Вопрос %1").arg(number));
}

QString QQuestionWidget::questionText() const
{
    return edtQuestion ? edtQuestion->text() : QString();
}

void QQuestionWidget::setQuestionText(const QString &text)
{
    if (edtQuestion)
        edtQuestion->setText(text);
}

void QQuestionWidget::addAnswerRow()
{
    answerLayout->addWidget(createAnswerRow(this));
}

void QQuestionWidget::deleteQuestion()
{
    emit requestRemove(this);
}

void QQuestionWidget::onTypeChanged(int index)
{
    btnAddAnswer->setEnabled(true);
    auto mode = static_cast<QuestionMode>(cbType->itemData(index).toInt());
    this->mode = mode;
    rebuildAllRows(mode);
}

void QQuestionWidget::onDiffChanged(int index)
{
    auto diff = static_cast<QuestionDifficulty>(cbDiff->itemData(index).toInt());
    this->difficulty = diff;
}

void QQuestionWidget::rebuildAllRows(QuestionMode mode)
{

    const auto buttons = radioGroup->buttons();
    for (QAbstractButton *b : buttons)
        radioGroup->removeButton(b);

    int rows = answerLayout->count();

    if (mode == FreeInput) {

        btnAddAnswer->setEnabled(false);
        for (int i = rows - 1; i >= 1; --i) {
            QLayoutItem *item = answerLayout->takeAt(i);
            if (QWidget *w = item->widget())
                w->deleteLater();
            delete item;
        }
        rows = answerLayout->count();


        if (rows == 0) {
            answerLayout->addWidget(createAnswerRow(this));
        }


        if (auto *row = qobject_cast<QWidget*>(answerLayout->itemAt(0)->widget()))
            rebuildAnswerRow(row, FreeInput);

        return;
    }


    rows = answerLayout->count();
    for (int i = 0; i < rows; ++i) {
        if (auto *row = qobject_cast<QWidget*>(answerLayout->itemAt(i)->widget()))
            rebuildAnswerRow(row, mode);
    }
}


void QQuestionWidget::rebuildAnswerRow(QWidget *row, QuestionMode mode)
{
    auto *lay = qobject_cast<QHBoxLayout*>(row->layout());
    if (!lay)
        return;

    QString text;
    if (lay->count() > 0) {
        if (auto *oldEdit = qobject_cast<QLineEdit*>(lay->itemAt(lay->count()-1)->widget()))
            text = oldEdit->text();
    }


    while (lay->count() > 0) {
        auto *item = lay->takeAt(0);
        if (auto *w = item->widget())
            w->deleteLater();
        delete item;
    }

    if (mode == FreeInput) {
        auto *edit = new QLineEdit(row);
        edit->setMinimumHeight(30);
        lay->addWidget(edit);
        edit->setText(text);
        return;
    }

    QWidget *selector = nullptr;
    if (mode == SingleChoice) {
        auto *rb = new QRadioButton(row);
        rb->setMinimumHeight(18);
        radioGroup->addButton(rb);
        selector = rb;
    } else {
        auto *chk = new QCheckBox(row);
        chk->setMinimumHeight(18);
        selector = chk;
    }

    auto *edit = new QLineEdit(row);
    edit->setMinimumHeight(30);

    lay->addWidget(selector);
    lay->addWidget(edit);
    edit->setText(text);
}
bool QQuestionWidget::hasAnyAnswers() const
{
    if (!answerLayout)
        return false;

    int nonEmpty = 0;

    for (int i = 0; i < answerLayout->count(); ++i) {
        auto *row = answerLayout->itemAt(i)->widget();
        if (!row) continue;

        auto *edit = row->findChild<QLineEdit*>();
        if (!edit) continue;

        if (!edit->text().trimmed().isEmpty())
            ++nonEmpty;
    }

    return nonEmpty > 0;
}
bool QQuestionWidget::hasCorrectAnswer() const
{
    if (!answerLayout)
        return false;


    if (getMode() == FreeInput) {
        for (int i = 0; i < answerLayout->count(); ++i) {
            auto *row = answerLayout->itemAt(i)->widget();
            if (!row) continue;
            auto *edit = row->findChild<QLineEdit*>();
            if (!edit) continue;
            if (!edit->text().trimmed().isEmpty())
                return true;
        }
        return false;
    }


    for (int i = 0; i < answerLayout->count(); ++i) {
        auto *row = answerLayout->itemAt(i)->widget();
        if (!row) continue;

        auto *btn = row->findChild<QAbstractButton*>();
        if (btn && btn->isChecked())
            return true;
    }

    return false;
}
QList<QQuestionWidget::AnswerRow> QQuestionWidget::answerRows() const
{
    QList<AnswerRow> result;

    for (int i = 0; i < answerLayout->count(); ++i) {
        auto *row = answerLayout->itemAt(i)->widget();
        if (!row) continue;

        auto *rb   = row->findChild<QAbstractButton*>();
        auto *edit = row->findChild<QLineEdit*>();
        if (!edit) continue;

        AnswerRow r;
        r.text = edit->text();
        r.correct = rb && rb->isChecked();
        result.append(r);
    }

    return result;
}

