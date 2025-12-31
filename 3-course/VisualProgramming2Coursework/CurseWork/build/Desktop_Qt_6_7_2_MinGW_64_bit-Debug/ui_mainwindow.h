/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
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
    QLabel *lblTests;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_3;
    QLineEdit *lineEdit_2;
    QLabel *lblSubject;
    QLabel *lblSearch;
    QComboBox *comboBox_4;
    QLabel *lblDifficult;
    QComboBox *comboBox_5;
    QLabel *label_6;
    QWidget *handleTestsPanel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddTest;
    QPushButton *btnImportTest;
    QPushButton *btnExportTest;
    QTableWidget *tableTests;
    QWidget *statisticsPage;
    QVBoxLayout *verticalLayout_9;
    QStackedWidget *stackedWidget_2;
    QWidget *studentStats;
    QVBoxLayout *verticalLayout_5;
    QLabel *lblStatistics;
    QHBoxLayout *horizontalLayout_3;
    QWidget *completedTestsWidget;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QWidget *allAttWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QWidget *bestResWidget;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_3;
    QWidget *lastAttWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_4;
    QLabel *lblTestHist;
    QTableWidget *histTestsTable;
    QWidget *teacherStats;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_5;
    QWidget *filtersTeacherPanel;
    QVBoxLayout *verticalLayout_11;
    QGridLayout *gridLayout_3;
    QComboBox *cboxSubject;
    QLabel *lblSearch_2;
    QLabel *lblSubject_2;
    QComboBox *cboxDiff;
    QLabel *lblDifficult_2;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *cboxChooseTest;
    QLabel *lblStudAttempts;
    QTableWidget *testAttemptsTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::GoHome));
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("/* ===== \320\221\320\220\320\227\320\220: \321\201\320\262\320\265\321\202\320\273\320\260\321\217 \321\202\320\265\320\274\320\260 ===== */\n"
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
"/* ===== \320\233\320\225\320\222\320\220\320\257 \320\237\320\220\320\235\320\225\320\233\320\254 ===== */\n"
"QWidget#sidePanel {\n"
"    background-color: #0b5ed7; \n"
"	border-left: none;      /* \321\201\320\270\320\275\320\270\320\271 */\n"
"    border-radius: 12px;\n"
"\n"
"}\n"
"\n"
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
"QPushButton#btnLog"
                        "out {\n"
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
"\n"
"/* Hover */\n"
"QPushButton#btnTests:hover,\n"
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
"   ui->btnTests->setProperty(\"act"
                        "ive\", true); style()->polish(ui->btnTests);\n"
"*/\n"
"QPushButton[active=\"true\"] {\n"
"    background-color: rgba(255, 255, 255, 55);\n"
"    border-left: 4px solid #ffffff;\n"
"    padding-left: 8px; /* \321\207\321\202\320\276\320\261\321\213 \320\272\320\276\320\274\320\277\320\265\320\275\321\201\320\270\321\200\320\276\320\262\320\260\321\202\321\214 border-left */\n"
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
"QLabe"
                        "l#lblSearch, \n"
"QLabel#lblSubject, \n"
"QLabel#lblDifficult{\n"
"    font-size: 12pt;\n"
"    font-weight: 500;\n"
"    color: #111827;\n"
"}\n"
"/* \320\237\320\276\320\273\321\217 \320\262\320\262\320\276\320\264\320\260 \320\270 \320\272\320\276\320\274\320\261\320\276\320\261\320\276\320\272\321\201\321\213 */\n"
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
"    subcontrol-position: top right;"
                        "\n"
"    width: 28px;\n"
"    border-left: 1px solid #e5e7eb;\n"
"    border-top-right-radius: 8px;\n"
"    border-bottom-right-radius: 8px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* \320\240\320\270\321\201\321\203\320\265\320\274 V-\321\201\321\202\321\200\320\265\320\273\320\272\321\203 \321\202\320\276\320\273\321\214\320\272\320\276 \321\200\320\260\320\274\320\272\320\260\320\274\320\270 */\n"
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
"    border-radius:"
                        " 12px;\n"
"    gridline-color: #eef2f7;\n"
"    selection-background-color: rgba(11, 94, 215, 35);\n"
"    selection-color: #111827;\n"
"}\n"
"\n"
"/* \320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\276\320\272 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
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
"    ba"
                        "ckground: transparent;\n"
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
"QScrollBar::handle:vertical:hover {\n"
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
"QPushButton#btnAddTest"
                        ",\n"
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
"}\n"
"QWidget#allAttWidget,\n"
"QWidget#bestResWidget,\n"
"QWidget#completedTestsWidget,\n"
"QWidget#lastAttWidget\n"
" {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12"
                        "px;\n"
"}\n"
"QLabel#lblTestHist{\n"
" font-size: 14pt;\n"
"    font-weight: 700;\n"
"    color: #111827;\n"
"	    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"\n"
"    border-radius: 12px;\n"
"\n"
"}\n"
"QLabel#lblStatistics{\n"
" font-size: 14pt;\n"
"    font-weight: 700;\n"
"    color: #111827;\n"
"	    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"\n"
"    border-radius: 12px;\n"
"\n"
"}\n"
"QWidget#filtersTeacherPanel{\n"
"	 background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"QLabel#lblSearch_2, \n"
"QLabel#lblSubject_2, \n"
"QLabel#lblDifficult_2{\n"
"    font-size: 12pt;\n"
"    font-weight: 500;\n"
"    color: #111827;\n"
"}\n"
"QLabel#lblStudAttempts{\n"
" font-size: 14pt;\n"
"    font-weight: 700;\n"
"    color: #111827;\n"
"	    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"\n"
"    border-radius: 12px;\n"
"}\n"
"QLabel#label_5{\n"
" font-size: 14pt;\n"
"    font-weight: 700;\n"
"    co"
                        "lor: #111827;\n"
"	    background-color: #ffffff;\n"
"    border: 1px solid #e5e7eb;\n"
"\n"
"    border-radius: 12px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(700, 0));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(9, -1, -1, -1);
        sidePanel = new QWidget(centralwidget);
        sidePanel->setObjectName("sidePanel");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidePanel->sizePolicy().hasHeightForWidth());
        sidePanel->setSizePolicy(sizePolicy);
        sidePanel->setMinimumSize(QSize(0, 0));
        sidePanel->setMaximumSize(QSize(200, 16777215));
        sidePanel->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(sidePanel);
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(9, 9, 9, -1);
        lblMenu = new QLabel(sidePanel);
        lblMenu->setObjectName("lblMenu");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblMenu->sizePolicy().hasHeightForWidth());
        lblMenu->setSizePolicy(sizePolicy1);
        lblMenu->setMinimumSize(QSize(0, 100));
        lblMenu->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(lblMenu);

        btnTests = new QPushButton(sidePanel);
        btnTests->setObjectName("btnTests");
        btnTests->setMinimumSize(QSize(0, 0));
        btnTests->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnTests);

        btnStats = new QPushButton(sidePanel);
        btnStats->setObjectName("btnStats");
        btnStats->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnStats);

        verticalSpacer = new QSpacerItem(20, 400, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        lblUserName = new QLabel(sidePanel);
        lblUserName->setObjectName("lblUserName");
        sizePolicy1.setHeightForWidth(lblUserName->sizePolicy().hasHeightForWidth());
        lblUserName->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lblUserName);

        lblRole = new QLabel(sidePanel);
        lblRole->setObjectName("lblRole");
        sizePolicy1.setHeightForWidth(lblRole->sizePolicy().hasHeightForWidth());
        lblRole->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lblRole);

        btnLogout = new QPushButton(sidePanel);
        btnLogout->setObjectName("btnLogout");
        btnLogout->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        verticalLayout->addWidget(btnLogout);


        horizontalLayout->addWidget(sidePanel);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        testsPage = new QWidget();
        testsPage->setObjectName("testsPage");
        sizePolicy2.setHeightForWidth(testsPage->sizePolicy().hasHeightForWidth());
        testsPage->setSizePolicy(sizePolicy2);
        testsPage->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_2 = new QVBoxLayout(testsPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        filtersPanel = new QWidget(testsPage);
        filtersPanel->setObjectName("filtersPanel");
        sizePolicy1.setHeightForWidth(filtersPanel->sizePolicy().hasHeightForWidth());
        filtersPanel->setSizePolicy(sizePolicy1);
        filtersPanel->setMinimumSize(QSize(0, 100));
        filtersPanel->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(filtersPanel);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lblTests = new QLabel(filtersPanel);
        lblTests->setObjectName("lblTests");

        verticalLayout_3->addWidget(lblTests);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        comboBox_3 = new QComboBox(filtersPanel);
        comboBox_3->setObjectName("comboBox_3");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(comboBox_3->sizePolicy().hasHeightForWidth());
        comboBox_3->setSizePolicy(sizePolicy3);
        comboBox_3->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        comboBox_3->setMouseTracking(true);

        gridLayout_2->addWidget(comboBox_3, 2, 2, 1, 2);

        lineEdit_2 = new QLineEdit(filtersPanel);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout_2->addWidget(lineEdit_2, 2, 0, 1, 1);

        lblSubject = new QLabel(filtersPanel);
        lblSubject->setObjectName("lblSubject");
        sizePolicy2.setHeightForWidth(lblSubject->sizePolicy().hasHeightForWidth());
        lblSubject->setSizePolicy(sizePolicy2);
        lblSubject->setMinimumSize(QSize(0, 0));
        lblSubject->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_2->addWidget(lblSubject, 1, 2, 1, 1);

        lblSearch = new QLabel(filtersPanel);
        lblSearch->setObjectName("lblSearch");
        sizePolicy2.setHeightForWidth(lblSearch->sizePolicy().hasHeightForWidth());
        lblSearch->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(lblSearch, 1, 0, 1, 1);

        comboBox_4 = new QComboBox(filtersPanel);
        comboBox_4->setObjectName("comboBox_4");
        sizePolicy3.setHeightForWidth(comboBox_4->sizePolicy().hasHeightForWidth());
        comboBox_4->setSizePolicy(sizePolicy3);
        comboBox_4->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout_2->addWidget(comboBox_4, 2, 4, 1, 1);

        lblDifficult = new QLabel(filtersPanel);
        lblDifficult->setObjectName("lblDifficult");
        sizePolicy2.setHeightForWidth(lblDifficult->sizePolicy().hasHeightForWidth());
        lblDifficult->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(lblDifficult, 1, 3, 1, 2);

        comboBox_5 = new QComboBox(filtersPanel);
        comboBox_5->setObjectName("comboBox_5");
        comboBox_5->setMinimumSize(QSize(200, 0));

        gridLayout_2->addWidget(comboBox_5, 2, 1, 1, 1);

        label_6 = new QLabel(filtersPanel);
        label_6->setObjectName("label_6");
        QFont font;
        font.setPointSize(12);
        label_6->setFont(font);

        gridLayout_2->addWidget(label_6, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout_2->addWidget(filtersPanel);

        handleTestsPanel = new QWidget(testsPage);
        handleTestsPanel->setObjectName("handleTestsPanel");
        sizePolicy2.setHeightForWidth(handleTestsPanel->sizePolicy().hasHeightForWidth());
        handleTestsPanel->setSizePolicy(sizePolicy2);
        handleTestsPanel->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_2 = new QHBoxLayout(handleTestsPanel);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        btnAddTest = new QPushButton(handleTestsPanel);
        btnAddTest->setObjectName("btnAddTest");
        btnAddTest->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        btnAddTest->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(btnAddTest);

        btnImportTest = new QPushButton(handleTestsPanel);
        btnImportTest->setObjectName("btnImportTest");
        btnImportTest->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_2->addWidget(btnImportTest);

        btnExportTest = new QPushButton(handleTestsPanel);
        btnExportTest->setObjectName("btnExportTest");
        btnExportTest->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_2->addWidget(btnExportTest);


        verticalLayout_2->addWidget(handleTestsPanel);

        tableTests = new QTableWidget(testsPage);
        if (tableTests->columnCount() < 5)
            tableTests->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableTests->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableTests->setObjectName("tableTests");
        sizePolicy2.setHeightForWidth(tableTests->sizePolicy().hasHeightForWidth());
        tableTests->setSizePolicy(sizePolicy2);
        tableTests->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        tableTests->setStyleSheet(QString::fromUtf8(""));
        tableTests->setShowGrid(true);
        tableTests->setSortingEnabled(false);
        tableTests->setColumnCount(5);
        tableTests->horizontalHeader()->setStretchLastSection(true);
        tableTests->verticalHeader()->setStretchLastSection(false);

        verticalLayout_2->addWidget(tableTests);

        stackedWidget->addWidget(testsPage);
        statisticsPage = new QWidget();
        statisticsPage->setObjectName("statisticsPage");
        verticalLayout_9 = new QVBoxLayout(statisticsPage);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        stackedWidget_2 = new QStackedWidget(statisticsPage);
        stackedWidget_2->setObjectName("stackedWidget_2");
        stackedWidget_2->setEnabled(true);
        studentStats = new QWidget();
        studentStats->setObjectName("studentStats");
        verticalLayout_5 = new QVBoxLayout(studentStats);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        lblStatistics = new QLabel(studentStats);
        lblStatistics->setObjectName("lblStatistics");

        verticalLayout_5->addWidget(lblStatistics);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        completedTestsWidget = new QWidget(studentStats);
        completedTestsWidget->setObjectName("completedTestsWidget");
        sizePolicy2.setHeightForWidth(completedTestsWidget->sizePolicy().hasHeightForWidth());
        completedTestsWidget->setSizePolicy(sizePolicy2);
        completedTestsWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_7 = new QVBoxLayout(completedTestsWidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label = new QLabel(completedTestsWidget);
        label->setObjectName("label");

        verticalLayout_7->addWidget(label);


        horizontalLayout_3->addWidget(completedTestsWidget);

        allAttWidget = new QWidget(studentStats);
        allAttWidget->setObjectName("allAttWidget");
        sizePolicy2.setHeightForWidth(allAttWidget->sizePolicy().hasHeightForWidth());
        allAttWidget->setSizePolicy(sizePolicy2);
        allAttWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_4 = new QVBoxLayout(allAttWidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(allAttWidget);
        label_2->setObjectName("label_2");

        verticalLayout_4->addWidget(label_2);


        horizontalLayout_3->addWidget(allAttWidget);

        bestResWidget = new QWidget(studentStats);
        bestResWidget->setObjectName("bestResWidget");
        sizePolicy2.setHeightForWidth(bestResWidget->sizePolicy().hasHeightForWidth());
        bestResWidget->setSizePolicy(sizePolicy2);
        bestResWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_6 = new QVBoxLayout(bestResWidget);
        verticalLayout_6->setObjectName("verticalLayout_6");
        label_3 = new QLabel(bestResWidget);
        label_3->setObjectName("label_3");

        verticalLayout_6->addWidget(label_3);


        horizontalLayout_3->addWidget(bestResWidget);

        lastAttWidget = new QWidget(studentStats);
        lastAttWidget->setObjectName("lastAttWidget");
        sizePolicy2.setHeightForWidth(lastAttWidget->sizePolicy().hasHeightForWidth());
        lastAttWidget->setSizePolicy(sizePolicy2);
        lastAttWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_8 = new QVBoxLayout(lastAttWidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        label_4 = new QLabel(lastAttWidget);
        label_4->setObjectName("label_4");

        verticalLayout_8->addWidget(label_4);


        horizontalLayout_3->addWidget(lastAttWidget);


        verticalLayout_5->addLayout(horizontalLayout_3);

        lblTestHist = new QLabel(studentStats);
        lblTestHist->setObjectName("lblTestHist");
        lblTestHist->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_5->addWidget(lblTestHist);

        histTestsTable = new QTableWidget(studentStats);
        if (histTestsTable->columnCount() < 5)
            histTestsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        histTestsTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        histTestsTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        histTestsTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        histTestsTable->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        histTestsTable->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        histTestsTable->setObjectName("histTestsTable");
        histTestsTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_5->addWidget(histTestsTable);

        stackedWidget_2->addWidget(studentStats);
        teacherStats = new QWidget();
        teacherStats->setObjectName("teacherStats");
        verticalLayout_10 = new QVBoxLayout(teacherStats);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(teacherStats);
        label_5->setObjectName("label_5");

        verticalLayout_10->addWidget(label_5);

        filtersTeacherPanel = new QWidget(teacherStats);
        filtersTeacherPanel->setObjectName("filtersTeacherPanel");
        sizePolicy2.setHeightForWidth(filtersTeacherPanel->sizePolicy().hasHeightForWidth());
        filtersTeacherPanel->setSizePolicy(sizePolicy2);
        filtersTeacherPanel->setMinimumSize(QSize(0, 0));
        filtersTeacherPanel->setMaximumSize(QSize(16777215, 100));
        verticalLayout_11 = new QVBoxLayout(filtersTeacherPanel);
        verticalLayout_11->setObjectName("verticalLayout_11");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        cboxSubject = new QComboBox(filtersTeacherPanel);
        cboxSubject->setObjectName("cboxSubject");
        sizePolicy3.setHeightForWidth(cboxSubject->sizePolicy().hasHeightForWidth());
        cboxSubject->setSizePolicy(sizePolicy3);
        cboxSubject->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        cboxSubject->setMouseTracking(true);

        gridLayout_3->addWidget(cboxSubject, 2, 2, 1, 2);

        lblSearch_2 = new QLabel(filtersTeacherPanel);
        lblSearch_2->setObjectName("lblSearch_2");
        sizePolicy2.setHeightForWidth(lblSearch_2->sizePolicy().hasHeightForWidth());
        lblSearch_2->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lblSearch_2, 1, 0, 1, 1);

        lblSubject_2 = new QLabel(filtersTeacherPanel);
        lblSubject_2->setObjectName("lblSubject_2");
        sizePolicy2.setHeightForWidth(lblSubject_2->sizePolicy().hasHeightForWidth());
        lblSubject_2->setSizePolicy(sizePolicy2);
        lblSubject_2->setMinimumSize(QSize(0, 0));
        lblSubject_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_3->addWidget(lblSubject_2, 1, 2, 1, 1);

        cboxDiff = new QComboBox(filtersTeacherPanel);
        cboxDiff->setObjectName("cboxDiff");
        sizePolicy3.setHeightForWidth(cboxDiff->sizePolicy().hasHeightForWidth());
        cboxDiff->setSizePolicy(sizePolicy3);
        cboxDiff->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout_3->addWidget(cboxDiff, 2, 4, 1, 1);

        lblDifficult_2 = new QLabel(filtersTeacherPanel);
        lblDifficult_2->setObjectName("lblDifficult_2");
        sizePolicy2.setHeightForWidth(lblDifficult_2->sizePolicy().hasHeightForWidth());
        lblDifficult_2->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(lblDifficult_2, 1, 3, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 2, 1, 1, 1);

        cboxChooseTest = new QComboBox(filtersTeacherPanel);
        cboxChooseTest->setObjectName("cboxChooseTest");

        gridLayout_3->addWidget(cboxChooseTest, 2, 0, 1, 1);


        verticalLayout_11->addLayout(gridLayout_3);


        verticalLayout_10->addWidget(filtersTeacherPanel);

        lblStudAttempts = new QLabel(teacherStats);
        lblStudAttempts->setObjectName("lblStudAttempts");

        verticalLayout_10->addWidget(lblStudAttempts);

        testAttemptsTable = new QTableWidget(teacherStats);
        if (testAttemptsTable->columnCount() < 5)
            testAttemptsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        testAttemptsTable->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        testAttemptsTable->setHorizontalHeaderItem(1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        testAttemptsTable->setHorizontalHeaderItem(2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        testAttemptsTable->setHorizontalHeaderItem(3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        testAttemptsTable->setHorizontalHeaderItem(4, __qtablewidgetitem14);
        testAttemptsTable->setObjectName("testAttemptsTable");
        testAttemptsTable->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_10->addWidget(testAttemptsTable);

        stackedWidget_2->addWidget(teacherStats);

        verticalLayout_9->addWidget(stackedWidget_2);

        stackedWidget->addWidget(statisticsPage);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblMenu->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        btnTests->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        btnStats->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        lblUserName->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        lblRole->setText(QCoreApplication::translate("MainWindow", "\320\240\320\276\320\273\321\214", nullptr));
        btnLogout->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        lblTests->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202\321\213", nullptr));
        lblSubject->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        lblSearch->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        lblDifficult->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\262\320\276\320\277\321\200\320\276\321\201\320\260", nullptr));
        btnAddTest->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        btnImportTest->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        btnExportTest->setText(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableTests->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableTests->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableTests->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableTests->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\320\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableTests->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\271\320\264\320\265\320\275", nullptr));
        lblStatistics->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\271\320\264\320\265\320\275\320\276 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\320\265\320\263\320\276 \320\277\320\276\320\277\321\213\321\202\320\276\320\272", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\233\321\203\321\207\321\210\320\270\320\271 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\273\320\265\320\264\320\275\321\217\321\217 \320\277\320\276\320\277\321\213\321\202\320\272\320\260", nullptr));
        lblTestHist->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\202\320\276\321\200\320\270\321\217 \321\202\320\265\321\201\321\202\320\276\320\262", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = histTestsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = histTestsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\321\201\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = histTestsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = histTestsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = histTestsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\320\270\321\201\321\202\320\270\320\272\320\260 \320\277\320\276 \321\202\320\265\321\201\321\202\321\203", nullptr));
        lblSearch_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \321\202\320\265\321\201\321\202", nullptr));
        lblSubject_2->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        lblDifficult_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\273\320\276\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        lblStudAttempts->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\277\321\213\321\202\320\272\320\270 \320\277\320\276 \321\202\320\265\321\201\321\202\321\203", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = testAttemptsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = testAttemptsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "\320\221\320\260\320\273\320\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = testAttemptsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = testAttemptsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "\320\224\320\260\321\202\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = testAttemptsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
