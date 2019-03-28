QT += testlib network httpserver sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

LIGHT_PATH = ../../../../src/light
POSTGRESQLGATEWAY_PATH=$$LIGHT_PATH/DatabaseGateway/PostgreSqlGateway

INCLUDEPATH+= \
  $$LIGHT_PATH \
  $$POSTGRESQLGATEWAY_PATH

HEADERS += \
#  $$LIGHT_PATH/HttpServer.h \
  $$POSTGRESQLGATEWAY_PATH/PostgresConnectionInfo.h \
    HttpRequestHelper.h \
    DatasabeHelper.h

SOURCES += tst_sensors.cpp \
#  $$LIGHT_PATH/HttpServer.cpp \
    HttpRequestHelper.cpp \
    DatasabeHelper.cpp

target.path = /opt/light/backend/bin/tests
!isEmpty(target.path): INSTALLS += target
