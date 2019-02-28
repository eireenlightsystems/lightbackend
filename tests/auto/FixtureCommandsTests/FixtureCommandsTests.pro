QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_fixturecommands.cpp

LIGHT_PATH = ../../../src/light
include($$LIGHT_PATH/Model/Model.pri)
include($$LIGHT_PATH/global.pri)

target.path = /opt/light/backend/bin/tests
!isEmpty(target.path): INSTALLS += target
