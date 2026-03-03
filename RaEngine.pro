QT       += core gui widgets 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    launcherdialog.cpp \
    projectwizarddialog.cpp \
    scripteditor.cpp

HEADERS += \
    mainwindow.h \
    launcherdialog.h \
    projectwizarddialog.h \
    scripteditor.h

RESOURCES += \
    resources.qrc

# إعدادات إضافية
target.path = /tmp/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target