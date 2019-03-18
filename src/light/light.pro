QT -= gui
QT += httpserver mqtt sql
CONFIG += c++17 console
CONFIG -= app_bundle

include(../3rdparty/qtservice/src/qtservice.pri)
include(./Mqtt/Mqtt.pri)
include(./DatabaseGateway/DatabaseGateway.pri)
include(./DeviceCommand/DeviceCommand.pri)
include(./Model/Model.pri)
include(./Exception/Exception.pri)
include(./Controller/Controller.pri)
include(./Router/Router.pri)
include(./Converter/Converter.pri)

unix: {
CONFIG(release, debug|release) {
DEFINES += LOG_TO_SYSLOG
}
}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    Service.h \
    HttpServer.h \
    CommandsScheduler.h \
    typedefs.h \
    LigthBackend.h \
    HttpServerConverters.h \
    DeviceCommandsController.h \
    Session.h \
    SessionOwner.h

SOURCES += \
    main.cpp \
    Service.cpp \
    HttpServer.cpp \
    CommandsScheduler.cpp \
    LigthBackend.cpp \
    HttpServerConverters.cpp \
    DeviceCommandsController.cpp \
    Session.cpp \
    SessionOwner.cpp

DISTFILES += \
    lightbackend.conf \
    commandscheduler.conf

target.path = /opt/light/backend/bin
INSTALLS += target

config.path = /opt/light/backend/bin
config.files = $$DISTFILES
INSTALLS += config
