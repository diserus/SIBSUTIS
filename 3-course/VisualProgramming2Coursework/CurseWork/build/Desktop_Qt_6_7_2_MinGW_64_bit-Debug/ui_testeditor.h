/********************************************************************************
** Form generated from reading UI file 'testeditor.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTEDITOR_H
#define UI_TESTEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestEditor
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *sidePanel;
    QVBoxLayout *verticalLayout;
    QLabel *lblMenu;
    QPushButton *btnTests;
    QPushButton *btnStats;
    QSpacerItem *verticalSpacer;
    QLabel *lblUserName;
    QLabel *lblRole;
    QPushButton *btnLogout;
    QStackedWidget *stackedWidget;
    QWidget *testsPage;
    QVBoxLayout *verticalLayout_2;
    QWidget *filtersPanel;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lblTests;
    QLineEdit *edtTitle;
    QWidget *horizontalWidget;
    QHBoxLayout *bottomMenu;
    QPushButton *addQuestion;
    QPushButton *endTest;
    QWidget *statisticsPage;

    void setupUi(QMainWindow *TestEditor)
    {
        if (TestEditor->objectName().isEmpty())
            TestEditor->setObjectName("TestEditor");
        TestEditor->resize(800, 464);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        TestEditor->setWindowIcon(icon);
        TestEditor->setStyleSheet(QString::fromUtf8("/* ===== \320\221\320\220\320\227\320\220: \321\201\320\262\320\265\321\202\320\273\320\260\321\217 \321\202\320\265\320\274\320\260 ===== */\n"
"QMainWindow {\n"
"    background-color: #f5f7fb;\n"
"    font-family: \"Segoe UI\";\n"
"    font-size: 10pt;\n"
"    color: #1f2937;\n"
"}\n"
"\n"
"QWidget {\n"
"    color: #1f2937;\n"
"}\n"
"\n"
"QWidget#questionBody QCheckBox::indicator {\n"
"	width: 16px;\n"
"    height: 16px;\n"
"    border: 1px solid #0b5ed7;\n"
"    background-color: white;\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QWidget#questionBody QCheckBox::indicator:checked {\n"
"	background-color: #0b5ed7;\n"
"\n"
"}\n"
"\n"
"QPushButton#addQuestion{\n"
"	background-color:#22c55e;\n"
"	color: white;\n"
"}\n"
"\n"
"QPushButton#endTest {\n"
"	background-color: #0b5ed7;\n"
"	color: white;\n"
"}\n"
"\n"
"QWidget#questionsPanel QPushButton{\n"
"	background-color: #ef4444;\n"
"	color: white;\n"
"}\n"
"/* ===== \320\233\320\225\320\222\320\220\320\257 \320\237\320\220\320\235\320\225\320\233\320\254 ===== */\n"
""
                        "QWidget#sidePanel {\n"
"    background-color: #0b5ed7; \n"
"	border-left: none;      /* \321\201\320\270\320\275\320\270\320\271 */\n"
"    border-radius: 12px;\n"
"\n"
"}\n"
"QLabel#qHeaderLabel{\n"
"	/*color: red;*/\n"
"	font-size: 25pt;\n"
"}\n"
"QLabel#lblMenu {\n"
"    color: white;\n"
"    font-size: 20pt;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"QLabel#lblUserName,\n"
"QLabel#lblRole {\n"
"    color: rgba(255, 255, 255, 220);\n"
"    font-size: 10pt;\n"
"}\n"
"\n"
"/* \320\232\320\275\320\276\320\277\320\272\320\270 \320\274\320\265\320\275\321\216 */\n"
"QPushButton#btnTests,\n"
"QPushButton#btnStats,\n"
"QPushButton#btnLogout {\n"
"    background: transparent;\n"
"    color: white;\n"
"    border: none;\n"
"    text-align: center;\n"
"    padding: 10px 12px;\n"
"    border-radius: 8px;\n"
"    font-weight: 600;\n"
"    font-size: 12pt;\n"
"\n"
"}\n"
"QWidget#questionsPanel\n"
"{\n"
"	background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"}\n"
"/* Hover */\n"
"QP"
                        "ushButton#btnTests:hover,\n"
"QPushButton#btnStats:hover,\n"
"QPushButton#btnLogout:hover {\n"
"    background-color: rgba(255, 255, 255, 35);\n"
"}\n"
"\n"
"/* Pressed */\n"
"QPushButton#btnTests:pressed,\n"
"QPushButton#btnStats:pressed,\n"
"QPushButton#btnLogout:pressed {\n"
"    background-color: rgba(0, 0, 0, 25);\n"
"}\n"
"\n"
"/* \320\247\321\202\320\276\320\261\321\213 \320\274\320\276\320\266\320\275\320\276 \320\261\321\213\320\273\320\276 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\275\320\276 \320\277\320\276\320\264\321\201\320\262\320\265\321\202\320\270\321\202\321\214 \320\260\320\272\321\202\320\270\320\262\320\275\321\203\321\216 \320\272\320\275\320\276\320\277\320\272\321\203:\n"
"   ui->btnTests->setProperty(\"active\", true); style()->polish(ui->btnTests);\n"
"*/\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: rgba(255, 255, 255, 55);\n"
"    border-left: 4px solid #ffffff;\n"
"    padding-left: 8px; /* \321\207\321\202\320\276\320\261\321\213 \320\272"
                        "\320\276\320\274\320\277\320\265\320\275\321\201\320\270\321\200\320\276\320\262\320\260\321\202\321\214 border-left */\n"
"}\n"
"\n"
"/* ===== \320\236\320\221\320\233\320\220\320\241\320\242\320\254 \320\241\320\242\320\240\320\220\320\235\320\230\320\246 (\321\201\320\277\321\200\320\260\320\262\320\260) ===== */\n"
"QStackedWidget {\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* ===== \320\237\320\220\320\235\320\225\320\233\320\254 \320\244\320\230\320\233\320\254\320\242\320\240\320\236\320\222 ===== */\n"
"QWidget#filtersPanel {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"QLabel#lblTests {\n"
"    font-size: 14pt;\n"
"    font-weight: 700;\n"
"    color: #111827;\n"
"}\n"
"QLabel#lblSearch, \n"
"QLabel#lblSubject, \n"
"QLabel#lblDifficult{\n"
"    font-size: 12pt;\n"
"    font-weight: 500;\n"
"    color: #111827;\n"
"}\n"
"/* \320\237\320\276\320\273\321\217 \320\262\320\262\320\276\320\264\320\260 \320\270 \320\272\320\276\320\274"
                        "\320\261\320\276\320\261\320\276\320\272\321\201\321\213 */\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #d1d5db;\n"
"    border-radius: 8px;\n"
"    padding: 6px 10px;\n"
"    selection-background-color: #0b5ed7;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #0b5ed7;\n"
"}\n"
"\n"
"QComboBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #d1d5db;\n"
"    border-radius: 8px;\n"
"    padding: 6px 34px 6px 10px;  /* \321\201\320\277\321\200\320\260\320\262\320\260 \320\274\320\265\321\201\321\202\320\276 \320\277\320\276\320\264 \321\201\321\202\321\200\320\265\320\273\320\272\321\203 */\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 28px;\n"
"    border-left: 1px solid #e5e7eb;\n"
"    border-top-right-radius: 8px;\n"
"    border-bottom-right-radius: 8px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* \320\240\320\270\321\201\321\203\320\265\320\274 V-\321\201\321\202"
                        "\321\200\320\265\320\273\320\272\321\203 \321\202\320\276\320\273\321\214\320\272\320\276 \321\200\320\260\320\274\320\272\320\260\320\274\320\270 */\n"
"QComboBox::down-arrow {\n"
"    width: 7px;\n"
"    height: 7px;\n"
"    border-left: 2px solid #0b5ed7;\n"
"    border-bottom: 2px solid #0b5ed7;\n"
"    margin-right: 1px;\n"
"}\n"
"\n"
"/* Hover/focus */\n"
"QComboBox:hover {\n"
"    border: 1px solid #0b5ed7;\n"
"}\n"
"\n"
"QComboBox::drop-down:hover {\n"
"    background-color: rgba(11, 94, 215, 10);\n"
"}\n"
"\n"
"\n"
"/* ===== \320\242\320\220\320\221\320\233\320\230\320\246\320\220 \320\242\320\225\320\241\320\242\320\236\320\222 ===== */\n"
"QTableWidget {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"    gridline-color: #eef2f7;\n"
"    selection-background-color: rgba(11, 94, 215, 35);\n"
"    selection-color: #111827;\n"
"}\n"
"\n"
"/* \320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 \321\202\320\260\320\261\320\273\320"
                        "\270\321\206\321\213 */\n"
"QHeaderView::section {\n"
"    background-color: #f3f6fb;\n"
"    color: #111827;\n"
"    padding: 8px 10px;\n"
"    border: none;\n"
"    border-bottom: 1px solid #e5e7eb;\n"
"    font-weight: 600;\n"
"}\n"
"\n"
"/* \320\241\321\202\321\200\320\276\320\272\320\270 */\n"
"QTableWidget::item {\n"
"    padding: 6px 8px;\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget::item:hover {\n"
"    background-color: rgba(11, 94, 215, 18);\n"
"}\n"
"\n"
"/* \320\241\320\272\321\200\320\276\320\273\320\273\320\261\320\260\321\200 (\320\260\320\272\320\272\321\203\321\200\320\260\321\202\320\275\321\213\320\271, \321\201\320\270\320\275\320\270\320\271 \320\260\320\272\321\206\320\265\320\275\321\202) */\n"
"QScrollBar:vertical {\n"
"    background: transparent;\n"
"    width: 10px;\n"
"    margin: 6px 4px 6px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: rgba(11, 94, 215, 120);\n"
"    border-radius: 5px;\n"
"    min-height: 30px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertic"
                        "al:hover {\n"
"    background: rgba(11, 94, 215, 170);\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,\n"
"QScrollBar::sub-page:vertical {\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* ===== \320\241\320\242\320\220\320\242\320\243\320\241-\320\221\320\220\320\240 (\320\265\321\201\320\273\320\270 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\321\210\321\214) ===== */\n"
"QStatusBar {\n"
"    background-color: #ffffff;\n"
"    border-top: 1px solid #e5e7eb;\n"
"}\n"
"\n"
"QWidget#handleTestsPanel{\n"
"	 background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"}\n"
"QPushButton#btnAddTest,\n"
"QPushButton#btnDeleteTest,\n"
"QPushButton#btnExportTest,\n"
"QPushButton#btnImportTest{\n"
"    background-color: #0b5ed7; \n"
"    color: white;\n"
"	padding: 3px;\n"
"    border-radius: 8px;\n"
"    font-weight: 600;\n"
"    font-size: 10pt;\n"
"\n"
""
                        "}\n"
"QPushButton#btnAddTest{\n"
"	background-color: rgb(34, 197, 94);\n"
"}\n"
"QPushButton#btnAddTest:hover{\n"
"	background-color: rgb(22, 163, 74);\n"
"}\n"
"QPushButton#btnDeleteTest{\n"
"	background-color: rgb(239, 68, 68);\n"
"}\n"
"QPushButton#btnDeleteTest:hover{\n"
"	background-color: rgb(220, 38, 38);\n"
"}\n"
"QPushButton#btnExportTest,\n"
"QPushButton#btnImportTest{\n"
"	background-color:rgb(249, 115, 22);\n"
"}\n"
"QPushButton#btnExportTest:hover,\n"
"QPushButton#btnImportTest:hover{\n"
"	background-color: rgb(234, 88, 12);\n"
"}"));
        centralwidget = new QWidget(TestEditor);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        sidePanel = new QWidget(centralwidget);
        sidePanel->setObjectName("sidePanel");
        sidePanel->setMinimumSize(QSize(180, 0));
        sidePanel->setMaximumSize(QSize(220, 16777215));
        verticalLayout = new QVBoxLayout(sidePanel);
        verticalLayout->setSpacing(8);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        lblMenu = new QLabel(sidePanel);
        lblMenu->setObjectName("lblMenu");
        lblMenu->setMinimumSize(QSize(0, 60));
        lblMenu->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lblMenu);

        btnTests = new QPushButton(sidePanel);
        btnTests->setObjectName("btnTests");
        btnTests->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnTests);

        btnStats = new QPushButton(sidePanel);
        btnStats->setObjectName("btnStats");
        btnStats->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnStats);

        verticalSpacer = new QSpacerItem(20, 200, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        lblUserName = new QLabel(sidePanel);
        lblUserName->setObjectName("lblUserName");

        verticalLayout->addWidget(lblUserName);

        lblRole = new QLabel(sidePanel);
        lblRole->setObjectName("lblRole");

        verticalLayout->addWidget(lblRole);

        btnLogout = new QPushButton(sidePanel);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnLogout);


        horizontalLayout->addWidget(sidePanel);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy);
        testsPage = new QWidget();
        testsPage->setObjectName("testsPage");
        verticalLayout_2 = new QVBoxLayout(testsPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        filtersPanel = new QWidget(testsPage);
        filtersPanel->setObjectName("filtersPanel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filtersPanel->sizePolicy().hasHeightForWidth());
        filtersPanel->setSizePolicy(sizePolicy1);
        filtersPanel->setMinimumSize(QSize(0, 80));
        verticalLayout_3 = new QVBoxLayout(filtersPanel);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        lblTests = new QLabel(filtersPanel);
        lblTests->setObjectName("lblTests");

        horizontalLayout_4->addWidget(lblTests);

        edtTitle = new QLineEdit(filtersPanel);
        edtTitle->setObjectName("edtTitle");

        horizontalLayout_4->addWidget(edtTitle);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(filtersPanel);

        horizontalWidget = new QWidget(testsPage);
        horizontalWidget->setObjectName("horizontalWidget");
        bottomMenu = new QHBoxLayout(horizontalWidget);
        bottomMenu->setObjectName("bottomMenu");
        addQuestion = new QPushButton(horizontalWidget);
        addQuestion->setObjectName("addQuestion");

        bottomMenu->addWidget(addQuestion);

        endTest = new QPushButton(horizontalWidget);
        endTest->setObjectName("endTest");

        bottomMenu->addWidget(endTest);


        verticalLayout_2->addWidget(horizontalWidget);

        stackedWidget->addWidget(testsPage);
        statisticsPage = new QWidget();
        statisticsPage->setObjectName("statisticsPage");
        stackedWidget->addWidget(statisticsPage);

        horizontalLayout->addWidget(stackedWidget);

        TestEditor->setCentralWidget(centralwidget);

        retranslateUi(TestEditor);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(TestEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TestEditor)
    {
        TestEditor->setWindowTitle(QCoreApplication::translate("TestEditor", "Test Editor", nullptr));
        lblMenu->setText(QCoreApplication::translate("TestEditor", "\320\234\320\265\320\275\321\216", nullptr));
        btnTests->setText(QCoreApplication::translate("TestEditor", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        btnStats->setText(QCoreApplication::translate("TestEditor", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        lblUserName->setText(QCoreApplication::translate("TestEditor", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        lblRole->setText(QCoreApplication::translate("TestEditor", "\320\240\320\276\320\273\321\214", nullptr));
        btnLogout->setText(QCoreApplication::translate("TestEditor", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        lblTests->setText(QCoreApplication::translate("TestEditor", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \321\202\320\265\321\201\321\202\320\260:", nullptr));
        addQuestion->setText(QCoreApplication::translate("TestEditor", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\276\320\277\321\200\320\276\321\201", nullptr));
        endTest->setText(QCoreApplication::translate("TestEditor", "\320\227\320\260\320\272\320\276\320\275\321\207\320\270\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestEditor: public Ui_TestEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTEDITOR_H
