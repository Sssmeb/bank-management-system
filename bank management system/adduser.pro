#-------------------------------------------------
#
# Project created by QtCreator 2018-06-17T15:35:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adduser
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        adduser.cpp \
    mainwindow.cpp \
    admlogin.cpp \
    userlogin.cpp \
    admmain.cpp \
    usermain.cpp \
    admsearch.cpp \
    admatm.cpp \
    usersave.cpp \
    userget.cpp \
    usermassage.cpp \
    admrecord.cpp \
    recordinfo.cpp

HEADERS += \
        adduser.h \
    mainwindow.h \
    admlogin.h \
    userlogin.h \
    admmain.h \
    usermain.h \
    admsearch.h \
    admatm.h \
    usersave.h \
    userget.h \
    usermassage.h \
    admrecord.h \
    recordinfo.h

FORMS += \
        adduser.ui \
    mainwindow.ui \
    admlogin.ui \
    userlogin.ui \
    admmain.ui \
    usermain.ui \
    admsearch.ui \
    admatm.ui \
    usersave.ui \
    userget.ui \
    usermassage.ui \
    admrecord.ui \
    recordinfo.ui

RESOURCES += \
    picture.qrc
