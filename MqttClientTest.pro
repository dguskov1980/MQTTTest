#-------------------------------------------------
#
# Project created by QtCreator 2024-03-12T11:21:56
#
#-------------------------------------------------
QT += quick
CONFIG += c++11

QT       += core network qmqtt
CONFIG += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MqttClientTest

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

SOURCES += \
        main.cpp \
        filepublisher.cpp \
     publisher_thread.cpp


HEADERS += \
    data.h \
    filepublisher.h \
    publisher_thread.h \
    subscriber.h
