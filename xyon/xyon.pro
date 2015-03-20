TEMPLATE = app

QT += qml quick network multimedia

SOURCES += main.cpp \
    xyoncontroller.cpp \
    qobjectlistmodel.cpp \
    audioentry.cpp

RESOURCES += qml.qrc

QMAKE_CXXFLAGS += -std=c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    xyoncontroller.h \
    qobjectlistmodel.h \
    audioentry.h
