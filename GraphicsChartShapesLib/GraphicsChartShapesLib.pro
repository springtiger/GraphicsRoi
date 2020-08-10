#-------------------------------------------------
#
# Project created by QtCreator 2017-08-06T13:30:53
#
#-------------------------------------------------

QT       += widgets charts

TARGET = GraphicsChartShapesLib
TEMPLATE = lib

DEFINES += GRAPHICSCHARTSHAPESLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graphicsChartItemEllipse.cpp \
    graphicsChartItemLineSegment.cpp \
    graphicsChartItemLine.cpp \
    graphicsChartItemRect.cpp \
    graphicsChartItemRectOrientation.cpp \
    graphicsChartItemLineOrientation.cpp \
    graphicsChartItemPolygon.cpp

HEADERS +=\
        graphicschartshapeslib_global.h \
    graphicsChartItemEllipse.h \
    graphicsChartItemEllipse_p.h \
    interfaceGraphicsChart.h \
    graphicsChartItemLineSegment.h \
    graphicsChartItemLineSegment_p.h \
    graphicsChartItemLine.h \
    graphicsChartItemLine_p.h \
    graphicsChartItemRect.h \
    graphicsChartItemRect_p.h \
    graphicsChartItemRectOrientation.h \
    graphicsChartItemRectOrientation_p.h \
    graphicsChartItemLineOrientation.h \
    graphicsChartItemLineOrientation_p.h \
    graphicsChartItemPolygon.h \
    graphicsChartItemPolygon_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/release/ -lGraphicsShapesLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/debug/ -lGraphicsShapesLib

INCLUDEPATH += $$PWD/../GraphicsShapesLib
DEPENDPATH += $$PWD/../GraphicsShapesLib


INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtWidgets/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtWidgets/$$[QT_VERSION]/QtWidgets
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui/$$[QT_VERSION]/QtGui
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION]/QtCore
