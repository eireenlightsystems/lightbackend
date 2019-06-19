INCLUDEPATH +=  \
    $$PWD

HEADERS += \
  $$PWD/AbstractRestRouter.h \
  $$PWD/RestRouter.h \
  $$PWD/GeographRestRouter.h \
  $$PWD/GatewayRestRouter.h \
  $$PWD/NodeRestRouter.h \
  $$PWD/FixtureRestRouter.h \
  $$PWD/FixtureGroupRouter.h \
  $$PWD/SimpleEditableRouter.h \
  $$PWD/SimpleSelectableRouter.h \
  $$PWD/SimpleEditableListRouter.h \
  $$PWD/FixtureCommandRestRouter.h \
    $$PWD/ContractRouter.h \
    $$PWD/ContainersRegistrationHelpers.h \
    $$PWD/SensorRouter.h \
    $$PWD/AuthRouter.h \
    $$PWD/NodeTypeRestRouter.h \
    $$PWD/SensorTypeRestRouter.h \
    $$PWD/GatewayTypeRestRouter.h \
    $$PWD/FixtureTypeRestRouter.h \
    $$PWD/CompanyDepartmentRestRouter.h \
    $$PWD/PersonRestRouter.h

SOURCES += \
  $$PWD/AbstractRestRouter.cpp \
  $$PWD/FixtureCommandRestRouter.cpp \
    $$PWD/AuthRouter.cpp
