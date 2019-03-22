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
    MqttDeviceCommandPublisher.h \
    CommandsSchedulerTypeDefs.h \
    CommandsSchedulerController.h \
    AbstractDeviceCommandPostgresCrud.h \
    FixtureSwitchOnDeviceCommandPostgresCrud.h \
    SchedulerFixture.h \
    SpeedToLightBaseDeviceCommandPostgresCrud.h

SOURCES += \
    main.cpp \
    Service.cpp \
    MqttDeviceCommandPublisher.cpp \
    CommandsSchedulerController.cpp \
    AbstractDeviceCommandPostgresCrud.cpp \
    FixtureSwitchOnDeviceCommandPostgresCrud.cpp \
    SchedulerFixture.cpp \
    SpeedToLightBaseDeviceCommandPostgresCrud.cpp

DISTFILES += \
    commandsscheduler.conf

target.path = /opt/light/backend/bin
INSTALLS += target

config.path = /opt/light/backend/bin
config.files = $$DISTFILES
INSTALLS += config
