QT -= gui
QT += httpserver mqtt sql
CONFIG += c++11 console
CONFIG -= app_bundle

include(../3rdparty/qtservice/src/qtservice.pri)
include(./Mqtt/Mqtt.pri)
include(./DatabaseGateway/DatabaseGateway.pri)
include(./DeviceCommand/DeviceCommand.pri)
include(./Model/Model.pri)
include(./Exception/Exception.pri)
include(./Controller/Controller.pri)
include(./Router/Router.pri)

unix: {
CONFIG(release, debug|release) {
DEFINES += LOG_TO_SYSLOG
}
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Service.h \
    HttpServer.h \
    CommandsScheduler.h \
    DeviceErrorController.h \
    SharedTypes.h \
    typedefs.h \
    LigthBackend.h \
    HttpServerConverters.h \
    DeviceCommandsController.h \
    NodeToJson.h \
    BaseConverter.h \
    BaseJsonConverter.h \
    Session.h \
    JsonToNodeConverter.h \
    NodeTypeToJson.h \
    GeographToJson.h \
    GatewayOwnerToJson.h \
    GatewayTypeToJson.h \
    GatewayToJson.h \
    JsonToGatewayConverter.h

SOURCES += \
    main.cpp \
    Service.cpp \
    HttpServer.cpp \
    CommandsScheduler.cpp \
    DeviceErrorController.cpp \
    LigthBackend.cpp \
    HttpServerConverters.cpp \
    DeviceCommandsController.cpp \
    NodeToJson.cpp \
    BaseConverter.cpp \
    BaseJsonConverter.cpp \
    Session.cpp \
    JsonToNodeConverter.cpp \
    NodeTypeToJson.cpp \ 
    GeographToJson.cpp \
    GatewayOwnerToJson.cpp \
    GatewayTypeToJson.cpp \
    GatewayToJson.cpp \
    JsonToGatewayConverter.cpp

DISTFILES += \
    lightbackend.conf \
    commandscheduler.conf \
    mqttcommandreceiver.conf

target.path = /opt/light/backend/bin
INSTALLS += target

config.path = /opt/light/backend/bin
config.files = $$DISTFILES
INSTALLS += config
