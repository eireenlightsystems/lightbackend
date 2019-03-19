QT -= gui
QT +=  mqtt sql

CONFIG += c++17 console
CONFIG -= app_bundle

include(../3rdparty/qtservice/src/qtservice.pri)
include(./Postgres.pri)

unix: {
CONFIG(release, debug|release) {
DEFINES += LOG_TO_SYSLOG
}
}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    Service.h \
    MqttDeviceErrorSubscriber.h \
    DeviceErrorController.h \
    AbstractDeviceErrorSaver.h \
    PostgresDeviceErrorSaver.h \
    SharedTypes.h \
    DeviceMessageReceiverTypeDefs.h

SOURCES += \
    main.cpp \
    Service.cpp \
    DeviceErrorController.cpp \
    AbstractDeviceErrorSaver.cpp \
    MqttDeviceErrorSubscriber.cpp \
    PostgresDeviceErrorSaver.cpp

DISTFILES += \
  devicemessagereceiver.conf \

target.path = /opt/light/backend/bin
INSTALLS += target

config.path = /opt/light/backend/bin
config.files = $$DISTFILES
INSTALLS += config
