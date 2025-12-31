#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "testrundialog.h"
#include "qquestionwidget.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDateTime>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QLabel>
#include <QFileDialog>
static QTableWidgetItem* itemRO(const QString& t)
{
    auto* it = new QTableWidgetItem(t);
    it->setFlags(it->flags() & ~Qt::ItemIsEditable);
    return it;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_attempts(QDir(QCoreApplication::applicationDirPath()).filePath("attempts.json"))
{
    ui->setupUi(this);
    ui->comboBox_5->addItem("Любые");
    ui->comboBox_5->addItem("Один вариант ответа");
    ui->comboBox_5->addItem("Несколько вариантов ответа");
    ui->comboBox_5->addItem("Свободный ввод ответа");
    ui->tableTests->setColumnCount(7);
    ui->tableTests->setHorizontalHeaderLabels(
        {"Название", "Тема", "Предмет", "Сложность", "Создал", "Пройден", "Пройти"}
        );

    auto lockTable = [](QTableWidget* t)
    {
        t->setSelectionMode(QAbstractItemView::SingleSelection);
        t->setFocusPolicy(Qt::NoFocus);
        t->setEditTriggers(QAbstractItemView::NoEditTriggers);

        t->horizontalHeader()->setSectionsMovable(false);
        t->verticalHeader()->setSectionsMovable(false);
        t->horizontalHeader()->setSectionsClickable(false);
        t->verticalHeader()->setSectionsClickable(false);
        t->horizontalHeader()->setHighlightSections(false);

        auto* hh = t->horizontalHeader();
        hh->setSectionResizeMode(QHeaderView::Stretch);

        t->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        t->verticalHeader()->setDefaultSectionSize(48);
        t->verticalHeader()->setFixedWidth(30);
    };

    lockTable(ui->tableTests);
    lockTable(ui->histTestsTable);
    lockTable(ui->testAttemptsTable);

    ui->tableTests->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
    ui->tableTests->setColumnWidth(6, 90);
    ui->tableTests->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableTests->verticalHeader()->setStyleSheet(
        "QHeaderView { background-color: #ffffff; }"
        "QHeaderView::section { background-color: #ffffff; color: #111827; border: 1px solid #e5e7eb; }"
        );
    ui->tableTests->setStyleSheet(ui->tableTests->styleSheet() +
                                  "QTableCornerButton::section { background-color: #f3f6fb; border: none;border-bottom: 1px solid #e5e7eb; }"
                                  );

    setupUiLogic();
    setupStudentStatLabels();

    QString err;
    m_attempts.load(&err);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupUiLogic()
{
    connect(ui->btnTests, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->testsPage);
    });
    connect(ui->btnStats, &QPushButton::clicked, this, [this](){
        ui->stackedWidget->setCurrentWidget(ui->statisticsPage);
        refreshAllStats();
    });
    connect(ui->btnLogout, &QPushButton::clicked, this, [this](){
        close();
    });

    connect(ui->btnImportTest, &QPushButton::clicked, this, [this](){importTest();});

    connect(ui->btnAddTest, &QPushButton::clicked, this, [this]() {
        if (!m_editor) {
            m_editor = new TestEditor();
            m_editor->setAuthor(ui->lblUserName->text());
            m_editor->setAttribute(Qt::WA_DeleteOnClose);

            connect(m_editor, &TestEditor::finished, this,
                    [this](bool, const QString&) {
                        this->show();
                        m_editor = nullptr;
                        loadTestsFromJsonFiles();
                        refreshAllStats();
                    });

            this->hide();
            m_editor->show();
        }
    });

    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, [this](){ applyTestFilters(); });
    connect(ui->comboBox_3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ applyTestFilters(); });
    connect(ui->comboBox_4, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ applyTestFilters(); });
    connect(ui->comboBox_5, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ applyTestFilters(); });

    connect(ui->cboxChooseTest, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ refreshTeacherStats(); });
    connect(ui->cboxSubject, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ refreshTeacherStats(); });
    connect(ui->cboxDiff, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int){ refreshTeacherStats(); });
    connect(ui->btnExportTest, &QPushButton::clicked, this, &MainWindow::exportSelectedTest);

    ui->histTestsTable->setColumnCount(5);
    ui->histTestsTable->setHorizontalHeaderLabels({"Дата","Тест","Балл","Время","Статус"});
    ui->histTestsTable->horizontalHeader()->setStretchLastSection(true);

    ui->testAttemptsTable->setColumnCount(5);
    ui->testAttemptsTable->setHorizontalHeaderLabels({"Студент","Балл","Время","Дата","Статус"});
    ui->testAttemptsTable->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setupStudentStatLabels()
{
    auto mkVal = [this]() {
        auto* l = new QLabel("-", this);
        l->setStyleSheet("font-size: 18pt; font-weight: 700; color: #111827;");
        return l;
    };

    m_lblCompletedVal = mkVal();
    m_lblAllAttemptsVal = mkVal();
    m_lblBestVal = mkVal();
    m_lblLastVal = mkVal();


    ui->verticalLayout_7->addWidget(m_lblCompletedVal);
    ui->verticalLayout_4->addWidget(m_lblAllAttemptsVal);
    ui->verticalLayout_6->addWidget(m_lblBestVal);
    ui->verticalLayout_8->addWidget(m_lblLastVal);
}

QString MainWindow::diffRu(const QString& diffEn) const
{
    if (diffEn == "Easy") return "Лёгкая";
    if (diffEn == "Medium") return "Нормальная";
    if (diffEn == "Hard") return "Сложная";
    return diffEn;
}
void MainWindow::exportSelectedTest()
{
    if (ui->tableTests->selectedItems().isEmpty())
    {
        QMessageBox::warning(this, "Экспорт", "Выделите строку с текстом для экспорта");
        return;
    }
    const int row = ui->tableTests->currentRow();
    if (row < 0 || row >= ui->tableTests->rowCount())
    {
        QMessageBox::warning(this, "Экспорт", "Нет выделенной строки");
        return;
    }
    const auto* titleItem = ui->tableTests->item(row, 0);
    if (!titleItem) return;

    QString jsonPath = titleItem->data(Qt::UserRole).toString();
    if (jsonPath.isEmpty())
    {
        QMessageBox::warning(this, "Экспорт", "Не найден файл теста");
        return;
    }
    QFileInfo fileInfo(jsonPath);
    QString fName = QString("test_%1.json").arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    QString destFile = QFileDialog::getSaveFileName(this, "Экспорт теста", fName, "*.json");

    if (destFile.isEmpty()) return;
    if (QFile::copy(jsonPath, destFile)) {
        QMessageBox::information(this, "Экспорт",
                                 QString("Тест экспортирован:\n%1").arg(QFileInfo(destFile).fileName()));
    } else {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось скопировать файл теста.");
    }

}
void MainWindow::applyUser(const AuthUser& u)
{
    m_currentUser = u;

    ui->lblUserName->setText(u.login);
    ui->lblRole->setText(u.role);

    const bool isTeacher = (u.role == "teacher");

    ui->stackedWidget_2->setCurrentWidget(isTeacher ? ui->teacherStats : ui->studentStats);

    ui->handleTestsPanel->setVisible(isTeacher);
    ui->btnAddTest->setEnabled(isTeacher);

    ui->btnImportTest->setEnabled(isTeacher);
    ui->btnExportTest->setEnabled(isTeacher);

    ui->stackedWidget->setCurrentWidget(ui->testsPage);

    loadTestsFromJsonFiles();
    refreshAllStats();
}

void MainWindow::loadTestsFromJsonFiles()
{
    m_allTests.clear();

    const QDir dir(QCoreApplication::applicationDirPath());
    const QStringList files = dir.entryList({ "test_*.json" }, QDir::Files, QDir::Time);

    for (const QString& fn : files) {
        const QString path = dir.filePath(fn);

        QFile f(path);
        if (!f.open(QIODevice::ReadOnly))
            continue;

        QJsonParseError pe{};
        const QJsonDocument doc = QJsonDocument::fromJson(f.readAll(), &pe);
        if (pe.error != QJsonParseError::NoError || !doc.isObject())
            continue;

        const QJsonObject root = doc.object();
        const QJsonArray tests = root.value("tests").toArray();

        for (const auto& v : tests) {
            const QJsonObject t = v.toObject();

            TestInfo ti;
            ti.jsonPath = path;
            ti.testId = t.value("id").toString();
            ti.title = t.value("title").toString();
            ti.anySingle = t.value("anySingle").toInt();
            ti.anyMulti = t.value("anyMulti").toInt();
            ti.anyFree = t.value("anyFree").toInt();
            ti.topic = t.value("topic").toString();
            if (ti.topic.isEmpty())
                ti.topic = ti.title;

            ti.subject = t.value("subject").toString();
            ti.difficulty = t.value("difficulty").toString();
            ti.author = t.value("author").toString();
            ti.timeLimitSec = t.value("timeLimitSec").toInt(0);

            if (!ti.testId.isEmpty())
                m_allTests.push_back(ti);
        }
    }

    rebuildFilterCombos();
    applyTestFilters();
}

void MainWindow::importTest()
{
    QString str = QFileDialog::getOpenFileName(0, "Импортировать тест", "", "*.json");
    if (!str.isEmpty())
    {
        QFileInfo fileInfo(str);
        QString destPath = QCoreApplication::applicationDirPath() + "/" + fileInfo.fileName();
        if (QFile::copy(str, destPath)) {qDebug() << "OK!";}
    }
    loadTestsFromJsonFiles();
}

void MainWindow::rebuildFilterCombos()
{
    const QString prevSubject = ui->comboBox_3->currentText();
    const QString prevDiff = ui->comboBox_4->currentText();

    ui->comboBox_3->blockSignals(true);
    ui->comboBox_4->blockSignals(true);

    ui->comboBox_3->clear();
    ui->comboBox_4->clear();

    ui->comboBox_3->addItem("Любой");
    ui->comboBox_4->addItem("Любая", "");
    QStringList subjects;
    QStringList diffs;
    for (const auto& t : m_allTests) {
        if (!t.subject.isEmpty() && !subjects.contains(t.subject)) subjects << t.subject;
        if (!t.difficulty.isEmpty() && !diffs.contains(t.difficulty)) diffs << t.difficulty;
    }
    subjects.sort();
    diffs.sort();

    for (const auto& s : subjects) ui->comboBox_3->addItem(s);
    for (const auto& d : diffs) ui->comboBox_4->addItem(diffRu(d), d);


    ui->cboxChooseTest->blockSignals(true);
    ui->cboxSubject->blockSignals(true);
    ui->cboxDiff->blockSignals(true);

    ui->cboxChooseTest->clear();
    ui->cboxSubject->clear();
    ui->cboxDiff->clear();

    ui->cboxChooseTest->addItem("Все тесты", "");
    ui->cboxSubject->addItem("Любой", "");
    ui->cboxDiff->addItem("Любая", "");

    for (const auto& s : subjects) ui->cboxSubject->addItem(s, s);
    for (const auto& d : diffs) ui->cboxDiff->addItem(diffRu(d), d);

    for (const auto& t : m_allTests) {
        ui->cboxChooseTest->addItem(QString("%1 (%2)").arg(t.title, t.subject), t.testId);
    }

    ui->cboxChooseTest->blockSignals(false);
    ui->cboxSubject->blockSignals(false);
    ui->cboxDiff->blockSignals(false);

    ui->comboBox_3->setCurrentText(prevSubject.isEmpty() ? "Любой" : prevSubject);
    ui->comboBox_4->setCurrentText(prevDiff.isEmpty() ? "Любая" : prevDiff);

    ui->comboBox_3->blockSignals(false);
    ui->comboBox_4->blockSignals(false);
}

void MainWindow::applyTestFilters()
{
    const QString q = ui->lineEdit_2->text().trimmed().toLower();
    const QString subj = ui->comboBox_3->currentText();
    const QString diffData = ui->comboBox_4->currentData().toString();
    const int typeS = ui->comboBox_5->currentIndex();
    m_filteredTests.clear();

    for (const auto& t : m_allTests) {
        if (!q.isEmpty() && !t.title.toLower().contains(q))
            continue;

        if (subj != "Любой" && !subj.isEmpty() && t.subject != subj)
            continue;

        if (!diffData.isEmpty() && t.difficulty != diffData)
            continue;

        if (typeS < 0 || typeS > 3)
            continue;
        if ((typeS == 1 && t.anySingle == 0) || (typeS == 2 && t.anyMulti == 0) || (typeS == 3 && t.anyFree == 0))
            continue;
        m_filteredTests.push_back(t);
    }

    fillTestsTable(m_filteredTests);
}

void MainWindow::fillTestsTable(const QVector<TestInfo>& list)
{

    for (int r = 0; r < ui->tableTests->rowCount(); ++r) {
        if (auto* w = ui->tableTests->cellWidget(r, 6))
            w->deleteLater();
    }
    ui->tableTests->clearContents();
    ui->tableTests->setRowCount(0);

    const auto myAttempts = m_attempts.byUser(m_currentUser.login);

    auto wasDone = [&](const QString& testId) {
        for (const auto& a : myAttempts)
            if (a.testId == testId) return true;
        return false;
    };

    for (int i = 0; i < list.size(); ++i) {
        const auto& t = list[i];

        const int row = ui->tableTests->rowCount();
        ui->tableTests->insertRow(row);

        auto* itTitle = itemRO(t.title);
        itTitle->setData(Qt::UserRole, t.jsonPath);
        itTitle->setData(Qt::UserRole + 1, t.testId);

        ui->tableTests->setItem(row, 0, itTitle);
        ui->tableTests->setItem(row, 1, itemRO(t.topic));
        ui->tableTests->setItem(row, 2, itemRO(t.subject));
        ui->tableTests->setItem(row, 3, itemRO(diffRu(t.difficulty)));
        ui->tableTests->setItem(row, 4, itemRO(t.author));
        ui->tableTests->setItem(row, 5, itemRO(wasDone(t.testId) ? "Да" : "Нет"));

        auto* btn = new QPushButton("Пройти");

        btn->setProperty("jsonPath", t.jsonPath);
        if (m_currentUser.role == "student")
        {
            btn->setProperty("testId", t.testId);
            btn->setEnabled(m_currentUser.role == "student");
            btn->setStyleSheet(
                "QPushButton {"
                "  background-color: #22c55e;"
                "  color: white;"
                "  border: none;"
                "  border-radius: 8px;"
                "  padding: 6px 12px;"
                "  font-weight: 600;"
                "}"
                "QPushButton:hover { background-color: #16a34a; }"
                "QPushButton:pressed { background-color: #15803d; }"
                "QPushButton:disabled { background-color: #9ca3af; color: #f3f4f6; }"
                );
            connect(btn, &QPushButton::clicked, this, [this, t, row]() {
                startAttempt(t, row);
            });
        }

        else
        {
            btn->setText("Удалить");
            btn->setEnabled(m_currentUser.login == t.author);
            btn->setStyleSheet(
                "QPushButton {"
                "  background-color: #ef4546;"
                "  color: white;"
                "  border: none;"
                "  border-radius: 8px;"
                "  padding: 6px 12px;"
                "  font-weight: 600;"
                "}"
                "QPushButton:hover { background-color: #d43839; }"
                "QPushButton:pressed { background-color: #b92b2c; }"
                "QPushButton:disabled { background-color: #9ca3af; color: #f3f4f6; }"
                );
            connect(btn, &QPushButton::clicked, this, [this, t]() {
                deleteTest(t);
            });
        }

        ui->tableTests->setCellWidget(row, 6, btn);
    }
}

void MainWindow::startAttempt(const TestInfo& t, int tableRow)
{
    if (m_currentUser.role != "student")
        return;

    TestRunDialog dlg(t.jsonPath, t.testId, this);
    if (dlg.exec() != QDialog::Accepted)
        return;

    AttemptRecord r;
    r.user = m_currentUser.login;
    r.testId = t.testId;
    r.title = t.title;
    r.subject = t.subject;
    r.difficulty = t.difficulty;
    r.author = t.author;

    r.score = dlg.score();
    r.maxScore = dlg.maxScore();
    r.timeSpentSec = dlg.timeSpentSec();
    r.timeLimitSec = dlg.timeLimitSec();
    r.timeout = dlg.wasTimeout();
    r.finishedAtIso = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

    m_attempts.add(r);
    m_attempts.save();


    if (auto* done = ui->tableTests->item(tableRow, 5))
        done->setText("Да");

    refreshAllStats();
}

void MainWindow::refreshAllStats()
{
    refreshStudentStats();
    fillStudentHistoryTable();
    refreshTeacherStats();
}

void MainWindow::refreshStudentStats()
{
    const auto mine = m_attempts.byUser(m_currentUser.login);

    const int attempts = mine.size();

    QStringList unique;
    for (const auto& a : mine)
        if (!unique.contains(a.testId)) unique << a.testId;

    const int completedTests = unique.size();

    double bestPct = 0.0;
    AttemptRecord last{};
    bool hasLast = false;

    for (const auto& a : mine) {
        const double pct = (a.maxScore > 0) ? (100.0 * a.score / a.maxScore) : 0.0;
        if (pct > bestPct) bestPct = pct;

        if (!hasLast || a.finishedAtIso > last.finishedAtIso) {
            last = a;
            hasLast = true;
        }
    }

    m_lblCompletedVal->setText(QString::number(completedTests));
    m_lblAllAttemptsVal->setText(QString::number(attempts));
    m_lblBestVal->setText(QString("%1%").arg(QString::number(bestPct, 'f', 0)));
    m_lblLastVal->setText(hasLast ? QString("%1 (%2/%3)").arg(last.title).arg(last.score).arg(last.maxScore) : "-");
}

void MainWindow::fillStudentHistoryTable()
{
    const auto mine = m_attempts.byUser(m_currentUser.login);

    ui->histTestsTable->clearContents();
    ui->histTestsTable->setRowCount(0);

    for (int i = mine.size() - 1; i >= 0; --i) {
        const auto& a = mine[i];

        const int row = ui->histTestsTable->rowCount();
        ui->histTestsTable->insertRow(row);

        ui->histTestsTable->setItem(row, 0, itemRO(a.finishedAtIso));
        ui->histTestsTable->setItem(row, 1, itemRO(a.title));
        ui->histTestsTable->setItem(row, 2, itemRO(QString("%1/%2").arg(a.score).arg(a.maxScore)));
        ui->histTestsTable->setItem(row, 3, itemRO(QString("%1/%2 сек").arg(a.timeSpentSec).arg(a.timeLimitSec)));
        ui->histTestsTable->setItem(row, 4, itemRO(a.timeout ? "Время вышло" : "Завершён"));
    }
}

void MainWindow::refreshTeacherStats()
{
    if (m_currentUser.role != "teacher")
        return;

    const QString testId = ui->cboxChooseTest->currentData().toString();
    const QString subj = ui->cboxSubject->currentData().toString();
    const QString diff = ui->cboxDiff->currentData().toString();

    ui->testAttemptsTable->clearContents();
    ui->testAttemptsTable->setRowCount(0);

    for (const auto& a : m_attempts.all()) {
        if (!testId.isEmpty() && a.testId != testId) continue;
        if (!subj.isEmpty() && a.subject != subj) continue;
        if (!diff.isEmpty() && a.difficulty != diff) continue;

        const int row = ui->testAttemptsTable->rowCount();
        ui->testAttemptsTable->insertRow(row);

        ui->testAttemptsTable->setItem(row, 0, itemRO(a.user));
        ui->testAttemptsTable->setItem(row, 1, itemRO(QString("%1/%2").arg(a.score).arg(a.maxScore)));
        ui->testAttemptsTable->setItem(row, 2, itemRO(QString("%1/%2 сек").arg(a.timeSpentSec).arg(a.timeLimitSec)));
        ui->testAttemptsTable->setItem(row, 3, itemRO(a.finishedAtIso));
        ui->testAttemptsTable->setItem(row, 4, itemRO(a.timeout ? "Время вышло" : "Завершён"));
    }
}
void MainWindow::deleteTest(const TestInfo &t)
{
    QFile file(t.jsonPath);
    file.remove();
    loadTestsFromJsonFiles();
}
