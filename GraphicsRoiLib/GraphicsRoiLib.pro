#-------------------------------------------------
#
# Project created by QtCreator 2017-07-08T14:50:33
#
#-------------------------------------------------

QT       += core widgets concurrent

TARGET = GraphicsRoiLib
TEMPLATE = lib

DEFINES += GRAPHICSROILIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include($$PWD/view/view.pri)
include($$PWD/RoiPart/RoiPart.pri)
include($$PWD/Roi/Roi.pri)


HEADERS +=\
    graphicsroilib_global.h \
    backgroundsleeper.h

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


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/release/ -lGraphicsShapesLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../GraphicsShapesLib/debug/ -lGraphicsShapesLib
else:unix: LIBS += -L$$OUT_PWD/../GraphicsShapesLib/ -lGraphicsShapesLib

INCLUDEPATH += $$PWD/../GraphicsShapesLib
DEPENDPATH += $$PWD/../GraphicsShapesLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GraphicsShapesLib/release/libGraphicsShapesLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GraphicsShapesLib/debug/libGraphicsShapesLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GraphicsShapesLib/release/GraphicsShapesLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../GraphicsShapesLib/debug/GraphicsShapesLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../GraphicsShapesLib/libGraphicsShapesLib.a

RESOURCES += \
    resources.qrc

SOURCES += \
    backgroundsleeper.cpp
