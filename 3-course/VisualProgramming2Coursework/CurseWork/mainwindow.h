#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QLabel>
#include "logindialog.h"
#include "testeditor.h"
#include "attemptstore.h"
class QTableWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void applyUser(const AuthUser& u);

private:
    struct TestInfo {
        QString jsonPath;
        QString testId;
        QString title;
        QString subject;
        QString difficulty;
        QString author;
        QString topic;
        int anySingle = 0;
        int anyMulti = 0;
        int anyFree = 0;
        int timeLimitSec = 0;
    };

private:
    void setupUiLogic();
    void setupStudentStatLabels();

    void loadTestsFromJsonFiles();
    void rebuildFilterCombos();
    void applyTestFilters();
    void fillTestsTable(const QVector<TestInfo>& list);
    QString getTestJsonPath(QTableWidget* table, int row);
    void startAttempt(const TestInfo& t, int tableRow);
    void deleteTest(const TestInfo& t);
    void importTest();
    void exportSelectedTest();
    void setupQuestionTypeFilters();
    void filterTableByQuestionType(QTableWidget* table, int index);
    bool hasQuestionType(const QString& jsonPath, const QString& type);
    void refreshAllStats();
    void refreshStudentStats();
    void refreshTeacherStats();
    void fillStudentHistoryTable();

    QString diffRu(const QString& diffEn) const;

private:
    Ui::MainWindow *ui;
    AuthUser m_currentUser;

    TestEditor* m_editor = nullptr;

    QVector<TestInfo> m_allTests;
    QVector<TestInfo> m_filteredTests;

    AttemptStore m_attempts;

    QLabel* m_lblCompletedVal = nullptr;
    QLabel* m_lblAllAttemptsVal = nullptr;
    QLabel* m_lblBestVal = nullptr;
    QLabel* m_lblLastVal = nullptr;
};

#endif
