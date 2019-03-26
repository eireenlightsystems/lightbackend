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
    $$PWD/SensorRouter.h

SOURCES += \
  $$PWD/AbstractRestRouter.cpp \
  $$PWD/FixtureCommandRestRouter.cpp
