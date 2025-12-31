QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attemptstore.cpp \
    authservice.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qquestionwidget.cpp \
    registerdialog.cpp \
    testeditor.cpp \
    testrundialog.cpp \
    userrepository.cpp

HEADERS += \
    PasswordHasher.h \
    attemptstore.h \
    authservice.h \
    logindialog.h \
    mainwindow.h \
    qquestionwidget.h \
    registerdialog.h \
    testeditor.h \
    testrundialog.h \
    userrepository.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    testeditor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
