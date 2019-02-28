QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIGHT_PATH = ../../../src/light
include($$LIGHT_PATH/DeviceCommand/DeviceCommand.pri)
include($$LIGHT_PATH/global.pri)

HEADERS += \
    AbstractDeviceCommandTestWrapper.h

SOURCES +=  \
  tst_devicecommands.cpp \
    AbstractDeviceCommandTestWrapper.cpp

target.path = /opt/light/backend/bin/tests
!isEmpty(target.path): INSTALLS += target


