QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIGHT_PATH = ../../../src/light
DATABASE_GATEWAY_PATH = $$LIGHT_PATH/DatabaseGateway
MODEL_PATH = $$LIGHT_PATH/Model
EXCEPTION_PATH = $$LIGHT_PATH/Exception
DEVICE_COMMAND_PATH = $$LIGHT_PATH/DeviceCommand

include($$MODEL_PATH/Model.pri)
include($$EXCEPTION_PATH/Exception.pri)
include($$DEVICE_COMMAND_PATH/DeviceCommand.pri)

INCLUDEPATH += $$LIGHT_PATH $$DATABASE_GATEWAY_PATH

HEADERS += \
  $$DATABASE_GATEWAY_PATH/CommandsController.h \
  $$DATABASE_GATEWAY_PATH/InMemoryDatabaseGateway.h \
  $$DATABASE_GATEWAY_PATH//AbstractFixtureCommandGateway.h

SOURCES +=  tst_commandscontroller.cpp \
  $$DATABASE_GATEWAY_PATH/CommandsController.cpp \
  $$DATABASE_GATEWAY_PATH/InMemoryDatabaseGateway.cpp \
  $$DATABASE_GATEWAY_PATH//AbstractFixtureCommandGateway.cpp

target.path = /opt/light/backend/bin/tests
!isEmpty(target.path): INSTALLS += target
