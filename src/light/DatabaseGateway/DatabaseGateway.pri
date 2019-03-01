INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/InMemoryDatabaseGateway.h \
    $$PWD/AbstractDeviceErrorSaver.h \
    $$PWD/AbstractFixtureCommandGateway.h \
    $$PWD/CommandsController.h \
    $$PWD/SchedulerGateway.h \
    $$PWD/AbstractNodeGateway.h

SOURCES += \
    $$PWD/InMemoryDatabaseGateway.cpp \
    $$PWD/AbstractDeviceErrorSaver.cpp \
    $$PWD/AbstractFixtureCommandGateway.cpp \
    $$PWD/CommandsController.cpp \
    $$PWD/SchedulerGateway.cpp \
    $$PWD/AbstractNodeGateway.cpp

include($$PWD/PostgreSqlGateway/PostgreSqlGateway.pri)
