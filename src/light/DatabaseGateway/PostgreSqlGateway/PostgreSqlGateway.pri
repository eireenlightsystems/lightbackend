include($$PWD/PostgresQuery.pri)

INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/PostgresConnectionInfo.h \
    $$PWD/SqlDatabaseOwner.h \
    $$PWD/PostgresCrud.h \
    $$PWD/PostgresCrudNode.h \
    $$PWD/PostgresCrudContract.h \
    $$PWD/PostgresCrudGeograph.h \
    $$PWD/PostgresCrudEquipmentType.h \
    $$PWD/PostgresCrudNodeType.h \
    $$PWD/PostgresCrudContragent.h \
    $$PWD/PostgresCrudGatewayType.h \
    $$PWD/PostgresCrudGateway.h \
    $$PWD/PostgresCrudEquipmentOwner.h \
    $$PWD/PostgresCrudFixtureGroup.h \
    $$PWD/PostgresCrudFixtureGroupType.h \
    $$PWD/PostgresCrudFixtureType.h \
    $$PWD/PostgresCrudFixtureHeightType.h \
    $$PWD/PostgresCrudSubstation.h \
    $$PWD/PostgresCrudFixture.h \
    $$PWD/PostgresCrudFixtureCommand.h \
    $$PWD/PostgresCrudFixtureLightLevelCommand.h \
    $$PWD/PostgresCrudFixtureLightSpeedCommand.h \
    $$PWD/PostgresCrudFixtureGroupOwner.h \
    $$PWD/PostgresCrudGatewayContract.h \
    $$PWD/PostgresCrudSensor.h \
    $$PWD/PostgresCrudSensorType.h \
    $$PWD/PostgresCrudCompanyDepartment.h \
    $$PWD/PostgresCrudPerson.h \
    $$PWD/PostgresCrudContractType.h

SOURCES += \
    $$PWD/SqlDatabaseOwner.cpp \
    $$PWD/PostgresCrud.cpp \
    $$PWD/PostgresCrudNode.cpp \
    $$PWD/PostgresCrudContract.cpp \
    $$PWD/PostgresCrudGeograph.cpp \
    $$PWD/PostgresCrudEquipmentType.cpp \
    $$PWD/PostgresCrudNodeType.cpp \
    $$PWD/PostgresCrudContragent.cpp \
    $$PWD/PostgresCrudGatewayType.cpp \
    $$PWD/PostgresCrudGateway.cpp \
    $$PWD/PostgresCrudEquipmentOwner.cpp \
    $$PWD/PostgresCrudFixtureGroup.cpp \
    $$PWD/PostgresCrudFixtureGroupType.cpp \
    $$PWD/PostgresCrudFixtureType.cpp \
    $$PWD/PostgresCrudFixtureHeightType.cpp \
    $$PWD/PostgresCrudSubstation.cpp \
    $$PWD/PostgresCrudFixture.cpp \
    $$PWD/PostgresCrudFixtureCommand.cpp \
    $$PWD/PostgresCrudFixtureLightLevelCommand.cpp \
    $$PWD/PostgresCrudFixtureLightSpeedCommand.cpp \
    $$PWD/PostgresCrudFixtureGroupOwner.cpp \
    $$PWD/PostgresCrudGatewayContract.cpp \
    $$PWD/PostgresCrudSensor.cpp \
    $$PWD/PostgresCrudSensorType.cpp \
    $$PWD/PostgresCrudCompanyDepartment.cpp \
    $$PWD/PostgresCrudPerson.cpp \
    $$PWD/PostgresCrudContractType.cpp
