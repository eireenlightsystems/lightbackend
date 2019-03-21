INCLUDEPATH +=  \
    $$PWD

HEADERS += \
  $$PWD/AbstractRestRouter.h \
  $$PWD/GeographRestRouter.h \
  $$PWD/GatewayRestRouter.h \
  $$PWD/NodeRestRouter.h \
  $$PWD/RestRouter.h \
  $$PWD/FixtureRestRouter.h \
  $$PWD/FixtureGroupRouter.h \
  $$PWD/TemplateRouter.h \
  $$PWD/SimpleEditableRouter.h \
  $$PWD/SimpleSelectableRouter.h \
    $$PWD/SimpleEditableListRouter.h \
    $$PWD/FixtureCommandRestRouter.h

SOURCES += \
  $$PWD/AbstractRestRouter.cpp \
  $$PWD/GeographRestRouter.cpp \
  $$PWD/GatewayRestRouter.cpp \
  $$PWD/NodeRestRouter.cpp \
  $$PWD/RestRouter.cpp \
  $$PWD/FixtureRestRouter.cpp \
  $$PWD/FixtureGroupRouter.cpp \
  $$PWD/TemplateRouter.cpp \
  $$PWD/SimpleEditableRouter.cpp \
  $$PWD/SimpleSelectableRouter.cpp \
    $$PWD/SimpleEditableListRouter.cpp \
    $$PWD/FixtureCommandRestRouter.cpp
