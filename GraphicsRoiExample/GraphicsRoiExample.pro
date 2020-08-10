#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T00:27:44
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicsRoiExample
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    mainwindow.cpp
#    cqchartview.cpp

HEADERS  += mainwindow.h
#    cqchartview.h


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/release/ -lGraphicsShapesLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/debug/ -lGraphicsShapesLib
else:unix: LIBS += -L$$OUT_PWD/../GraphicsShapesLib/ -lGraphicsShapesLib

INCLUDEPATH += $$PWD/../GraphicsShapesLib
DEPENDPATH += $$PWD/../GraphicsShapesLib


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsRoiLib/release/ -lGraphicsRoiLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsRoiLib/debug/ -lGraphicsRoiLib
else:unix: LIBS += -L$$OUT_PWD/../GraphicsRoiLib/ -lGraphicsRoiLib

INCLUDEPATH += $$PWD/../GraphicsRoiLib
DEPENDPATH += $$PWD/../GraphicsRoiLib

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsChartShapesLib/release/ -lGraphicsChartShapesLib
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsChartShapesLib/debug/ -lGraphicsChartShapesLib
#else:unix: LIBS += -L$$OUT_PWD/../GraphicsChartShapesLib/ -lGraphicsChartShapesLib

#INCLUDEPATH += $$PWD/../GraphicsChartShapesLib
#DEPENDPATH += $$PWD/../GraphicsChartShapesLib
