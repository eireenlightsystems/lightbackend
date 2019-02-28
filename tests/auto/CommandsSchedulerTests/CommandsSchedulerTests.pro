QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIGHT_PATH = ../../../src/light
DB_GATEWAY_PATH = $$LIGHT_PATH/DatabaseGateway

include($$LIGHT_PATH/global.pri)
include($$LIGHT_PATH/Model/Model.pri)

INCLUDEPATH += \
    $$LIGHT_PATH \
    $$DB_GATEWAY_PATH

HEADERS = \
    $$LIGHT_PATH/CommandsScheduler.h \
    $$DB_GATEWAY_PATH/SchedulerGateway.h \
    $$DB_GATEWAY_PATH/AbstractFixtureCommandGateway.h \
    TestSchedulerGateway.h

SOURCES +=  \
  $$LIGHT_PATH/CommandsScheduler.cpp \
  tst_commandsscheduler.cpp \
  $$DB_GATEWAY_PATH/SchedulerGateway.cpp \
  $$DB_GATEWAY_PATH/AbstractFixtureCommandGateway.cpp \
  TestSchedulerGateway.cpp

target.path = /opt/lightbackend/bin/tests
!isEmpty(target.path): INSTALLS += target

