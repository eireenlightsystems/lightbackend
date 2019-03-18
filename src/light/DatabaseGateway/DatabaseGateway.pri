INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/InMemoryDatabaseGateway.h \
    $$PWD/AbstractFixtureCommandGateway.h \
    $$PWD/CommandsController.h \
    $$PWD/SchedulerGateway.h \
    $$PWD/GatewayTypeDef.h

SOURCES += \
    $$PWD/InMemoryDatabaseGateway.cpp \
    $$PWD/AbstractFixtureCommandGateway.cpp \
    $$PWD/CommandsController.cpp \
    $$PWD/SchedulerGateway.cpp

include($$PWD/PostgreSqlGateway/PostgreSqlGateway.pri)
