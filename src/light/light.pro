QT -= gui
QT += httpserver sql

CONFIG += c++17 console
CONFIG -= app_bundle

win32: {
QMAKE_CXXFLAGS += -Wa,-mbig-obj
}

include(../3rdparty/qtservice/src/qtservice.pri)
include(./DatabaseGateway/DatabaseGateway.pri)
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
    typedefs.h \
    LigthBackend.h \
    Session.h \
    SessionOwner.h

SOURCES += \
    main.cpp \
    Service.cpp \
    HttpServer.cpp \
    LigthBackend.cpp \
    Session.cpp \
    SessionOwner.cpp

DISTFILES += \
    lightbackend.conf

target.path = /opt/light/backend/bin
INSTALLS += target

config.path = /opt/light/backend/bin
config.files = $$DISTFILES
INSTALLS += config
