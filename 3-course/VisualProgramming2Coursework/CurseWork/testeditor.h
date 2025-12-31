#ifndef TESTEDITOR_H
#define TESTEDITOR_H

#include <QMainWindow>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class TestEditor; }
QT_END_NAMESPACE

class QScrollArea;
class QVBoxLayout;
class QQuestionWidget;

class TestEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestEditor(QWidget *parent = nullptr);
    ~TestEditor();
    void setAuthor(const QString& author) {m_author = author;}
private slots:
    void onAddQuestionClicked();
    void removeQuestionWidget(QQuestionWidget *w);
    void onEndTestClicked();
signals:
    void finished(bool saved, const QString& filename);
private:
    Ui::TestEditor *ui;
    QString m_author = "default";
    QScrollArea  *scrollQuestions = nullptr;
    QWidget      *questionContainer = nullptr;
    QVBoxLayout  *questionLayout = nullptr;
protected:
    void closeEvent(QCloseEvent* e) override;
};

#endif
