INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/PostgresDeviceErrorSaver.h \
    $$PWD/PostgresConnectionInfo.h \
    $$PWD/PostgresFixtureCommandGateway.h \
    $$PWD/PostgresFixtureLightLevelCommandGateway.h \
    $$PWD/PostgresFixtureLightSpeedCommandGateway.h \
    $$PWD/PostgresDeviceCommandGateway.h \
    $$PWD/SqlDatabaseOwner.h \
    $$PWD/PostgresFixtureGateway.h \
    $$PWD/PostgresFixtureCommandFacadeGateway.h \
    $$PWD/SelectQuery.h \
    $$PWD/InsertQuery.h \
    $$PWD/SqlQuery.h \
    $$PWD/QueryBuilder.h \
    $$PWD/UpdateQuery.h \
    $$PWD/DeleteQuery.h \
    $$PWD/PostgresNodeGateway.h

SOURCES += \
    $$PWD/PostgresDeviceErrorSaver.cpp \
    $$PWD/PostgresFixtureCommandGateway.cpp \
    $$PWD/PostgresFixtureLightLevelCommandGateway.cpp \
    $$PWD/PostgresFixtureLightSpeedCommandGateway.cpp \
    $$PWD/PostgresDeviceCommandGateway.cpp \
    $$PWD/SqlDatabaseOwner.cpp \
    $$PWD/PostgresFixtureGateway.cpp \
    $$PWD/PostgresFixtureCommandFacadeGateway.cpp \
    $$PWD/SelectQuery.cpp \
    $$PWD/InsertQuery.cpp \
    $$PWD/SqlQuery.cpp \
    $$PWD/UpdateQuery.cpp \
    $$PWD/DeleteQuery.cpp \
    $$PWD/PostgresNodeGateway.cpp
