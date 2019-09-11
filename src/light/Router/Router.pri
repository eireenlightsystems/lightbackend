INCLUDEPATH +=  \
    $$PWD

HEADERS += \
  $$PWD/AbstractRestRouter.h \
    $$PWD/ComponentRestRouter.h \
    $$PWD/GeographFiasRestRouter.h \
  $$PWD/RestRouter.h \
  $$PWD/GeographRestRouter.h \
  $$PWD/GatewayRestRouter.h \
  $$PWD/NodeRestRouter.h \
  $$PWD/FixtureRestRouter.h \
  $$PWD/FixtureGroupRouter.h \
    $$PWD/RoleRestRouter.h \
    $$PWD/RolerightRestRouter.h \
  $$PWD/SimpleEditableRouter.h \
  $$PWD/SimpleSelectableRouter.h \
  $$PWD/SimpleEditableListRouter.h \
  $$PWD/FixtureCommandRestRouter.h \
    $$PWD/ContainersRegistrationHelpers.h \
    $$PWD/SensorRouter.h \
    $$PWD/AuthRouter.h \
    $$PWD/NodeTypeRestRouter.h \
    $$PWD/SensorTypeRestRouter.h \
    $$PWD/GatewayTypeRestRouter.h \
    $$PWD/FixtureTypeRestRouter.h \
    $$PWD/CompanyDepartmentRestRouter.h \
    $$PWD/PersonRestRouter.h \
    $$PWD/SubstationRestRouter.h \
    $$PWD/ContractRestRouter.h \
    $$PWD/ContractTypeRestRouter.h \
    $$PWD/UserRestRouter.h

SOURCES += \
  $$PWD/AbstractRestRouter.cpp \
  $$PWD/FixtureCommandRestRouter.cpp \
    $$PWD/AuthRouter.cpp
