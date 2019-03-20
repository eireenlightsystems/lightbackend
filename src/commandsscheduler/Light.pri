LIGHT_PATH=$$PWD/../light
EXCEPTION_PATH=$$LIGHT_PATH/Exception
DATEBASEGATEWAY_PATH=$$LIGHT_PATH/DatabaseGateway
POSTGRESQL_OBJECT_PATH=$$DATEBASEGATEWAY_PATH/PostgreSqlGateway
DEVICECOMMAND_PATH=$$LIGHT_PATH/DeviceCommand

MODEL_PATH=$$LIGHT_PATH/Model
include($$MODEL_PATH/Model.pri)
DEVICECOMMAND_PATH=$$LIGHT_PATH/DeviceCommand
include($$DEVICECOMMAND_PATH/DeviceCommand.pri)

INCLUDEPATH += $$LIGHT_PATH $$DATEBASEGATEWAY_PATH $$DEVICECOMMAND_PATH $$POSTGRESQL_OBJECT_PATH $$EXCEPTION_PATH

HEADERS += \
    $$LIGHT_PATH/typedefs.h \
    $$DATEBASEGATEWAY_PATH/AbstractFixtureCommandGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresConnectionInfo.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureCommandFacadeGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresDeviceCommandGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureLightSpeedCommandGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureLightLevelCommandGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureCommandGateway.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureGateway.h \
    $$POSTGRESQL_OBJECT_PATH/SqlQuery.h \
    $$POSTGRESQL_OBJECT_PATH/SelectQuery.h \
    $$POSTGRESQL_OBJECT_PATH/InsertQuery.h \
    $$POSTGRESQL_OBJECT_PATH/UpdateQuery.h \
    $$POSTGRESQL_OBJECT_PATH/DeleteQuery.h \
    $$POSTGRESQL_OBJECT_PATH/SqlDatabaseOwner.h \
    $$EXCEPTION_PATH/NotImplementedException.h \
    $$EXCEPTION_PATH/DatabaseException.h \
    $$EXCEPTION_PATH/Exception.h \


SOURCES += \
    $$DATEBASEGATEWAY_PATH/AbstractFixtureCommandGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresDeviceCommandGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureCommandFacadeGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureLightSpeedCommandGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureLightLevelCommandGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureCommandGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/PostgresFixtureGateway.cpp \
    $$POSTGRESQL_OBJECT_PATH/SqlQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/SelectQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/InsertQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/UpdateQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/DeleteQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/SqlDatabaseOwner.cpp \
    $$EXCEPTION_PATH/NotImplementedException.cpp \
    $$EXCEPTION_PATH/DatabaseException.cpp \
    $$EXCEPTION_PATH/Exception.cpp
