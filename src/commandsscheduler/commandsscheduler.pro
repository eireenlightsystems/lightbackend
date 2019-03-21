QT -= gui
QT +=  mqtt sql

CONFIG += c++17 console
CONFIG -= app_bundle

include(../3rdparty/qtservice/src/qtservice.pri)
include(./DeviceCommand/DeviceCommand.pri)
include(Light.pri)

unix: {
CONFIG(release, debug|release) {
DEFINES += LOG_TO_SYSLOG
}
}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    Service.h \
    SchedulerGateway.h \
    MqttDeviceCommandPublisher.h \
    CommandsSchedulerTypeDefs.h \
    CommandsSchedulerController.h

SOURCES += \
    main.cpp \
    Service.cpp \
    SchedulerGateway.cpp \
    MqttDeviceCommandPublisher.cpp \
    CommandsSchedulerController.cpp

target.path = /opt/light/backend/bin
INSTALLS += target
