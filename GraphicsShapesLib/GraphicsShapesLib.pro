#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T17:07:12
#
#-------------------------------------------------

QT       += widgets

TARGET = GraphicsShapesLib
TEMPLATE = lib

#CONFIG += staticlib
DEFINES += GRAPHICSSHAPESLIB_LIBRARY

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
    graphicsShapeItem.cpp \
    graphicsItemEllipse.cpp \
    graphicsItemLine.cpp \
    graphicsItemPath.cpp \
    graphicsItemPixmap.cpp \
    graphicsItemPolygon.cpp \
    graphicsItemRect.cpp \
    graphicsItemSimpleText.cpp \
    graphicsLayoutItemSimpleText.cpp \
    graphicsItemPoint.cpp

HEADERS +=\
        graphicsshapeslib_global.h \
    graphicsShapeItem.h \
    graphicsShapeItem_p.h \
    graphicsItemEllipse.h \
    graphicsItemEllipse_p.h \
    graphicsItemLine.h \
    graphicsItemLine_p.h \
    graphicsItemPath.h \
    graphicsItemPath_p.h \
    graphicsItemPixmap_p.h \
    graphicsItemPixmap.h \
    graphicsItemPolygon.h \
    graphicsItemPolygon_p.h \
    graphicsItemRect.h \
    graphicsItemRect_p.h \
    graphicsItemSimpleText.h \
    graphicsItemSimpleText_p.h \
    graphicsLayoutItemSimpleText.h \
    graphicsItemPoint.h \
    graphicsItemPoint_p.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtWidgets/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtWidgets/$$[QT_VERSION]/QtWidgets
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtGui/$$[QT_VERSION]/QtGui
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION]
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtCore/$$[QT_VERSION]/QtCore
