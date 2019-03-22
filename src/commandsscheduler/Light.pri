LIGHT_PATH=$$PWD/../light
EXCEPTION_PATH=$$LIGHT_PATH/Exception
DATEBASEGATEWAY_PATH=$$LIGHT_PATH/DatabaseGateway
POSTGRESQL_OBJECT_PATH=$$DATEBASEGATEWAY_PATH/PostgreSqlGateway
DEVICECOMMAND_PATH=$$LIGHT_PATH/DeviceCommand

MODEL_PATH=$$LIGHT_PATH/Model
#CONTROLLER_PATH=$$LIGHT_PATH/Controller

#include($$MODEL_PATH/Model.pri)
include($$POSTGRESQL_OBJECT_PATH/PostgresQuery.pri)

INCLUDEPATH += \
    $$LIGHT_PATH \
    $$DATEBASEGATEWAY_PATH \
    $$POSTGRESQL_OBJECT_PATH \
    $$EXCEPTION_PATH \
    $$MODEL_PATH \
    $$CONTROLLER_PATH

HEADERS += \
    $$LIGHT_PATH/typedefs.h \
    $$LIGHT_PATH/Session.h \
    $$LIGHT_PATH/SessionOwner.h \
    $$MODEL_PATH/CommandStatus.h \
#    $$CONTROLLER_PATH/Controller.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresCrud.h \
    $$POSTGRESQL_OBJECT_PATH/PostgresConnectionInfo.h \
    $$POSTGRESQL_OBJECT_PATH/SqlDatabaseOwner.h \
    $$EXCEPTION_PATH/NotImplementedException.h \
    $$EXCEPTION_PATH/DatabaseException.h \
    $$EXCEPTION_PATH/Exception.h \

SOURCES += \
    $$LIGHT_PATH/Session.cpp \
    $$LIGHT_PATH/SessionOwner.cpp \
    $$POSTGRESQL_OBJECT_PATH/SqlDatabaseOwner.cpp \
    $$EXCEPTION_PATH/NotImplementedException.cpp \
    $$EXCEPTION_PATH/DatabaseException.cpp \
    $$EXCEPTION_PATH/Exception.cpp
