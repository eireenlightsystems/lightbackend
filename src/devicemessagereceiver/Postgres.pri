LIGHT_PATH=$$PWD/../light
EXCEPTION_PATH=$$LIGHT_PATH/Exception
POSTGRESQL_OBJECT_PATH=$$LIGHT_PATH/DatabaseGateway/PostgreSqlGateway

INCLUDEPATH += $$LIGHT_PATH $$EXCEPTION_PATH $$POSTGRESQL_OBJECT_PATH

HEADERS += \
    $$LIGHT_PATH/typedefs.h \
    $$POSTGRESQL_OBJECT_PATH/PostresConnectionInfo.h \
    $$POSTGRESQL_OBJECT_PATH/SqlQuery.h \
    $$POSTGRESQL_OBJECT_PATH/SelectQuery.h \
    $$POSTGRESQL_OBJECT_PATH/InsertQuery.h \
    $$POSTGRESQL_OBJECT_PATH/DeleteQuery.h \
    $$EXCEPTION_PATH/DatabaseException.h \
    $$EXCEPTION_PATH/Exception.h

SOURCES += \
    $$POSTGRESQL_OBJECT_PATH/SqlQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/SelectQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/InsertQuery.cpp \
    $$POSTGRESQL_OBJECT_PATH/DeleteQuery.cpp \
    $$EXCEPTION_PATH/DatabaseException.cpp \
    $$EXCEPTION_PATH/Exception.cpp
