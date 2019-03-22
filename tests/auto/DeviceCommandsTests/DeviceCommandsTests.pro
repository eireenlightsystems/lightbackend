QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIGHT_PATH = ../../../src/light
COMMANDSSCHEDULER_PATH = ../../../src/commandsscheduler
include($$COMMANDSSCHEDULER_PATH/DeviceCommand/DeviceCommand.pri)
include($$LIGHT_PATH/global.pri)

INCLUDEPATH += \
    $$LIGHT_PATH/Model \
    $$COMMANDSSCHEDULER_PATH

HEADERS += \
    AbstractDeviceCommandTestWrapper.h \
    $$COMMANDSSCHEDULER_PATH/SchedulerFixture.h

SOURCES +=  \
    tst_devicecommands.cpp \
    AbstractDeviceCommandTestWrapper.cpp \
    $$COMMANDSSCHEDULER_PATH/SchedulerFixture.cpp

target.path = /opt/light/backend/bin/tests
!isEmpty(target.path): INSTALLS += target


