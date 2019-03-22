INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/AbstractDeviceCommand.h \
    $$PWD/FixtureSwitchOnDeviceCommand.h \
    $$PWD/SpeedToLightDownDeviceCommand.h \
    $$PWD/SpeedToLightUpDeviceCommand.h \
    $$PWD/SwitchOffDeviceCommand.h \
    $$PWD/SpeedToLightBaseDeviceCommand.h \
    $$PWD/FixtureCommand.h

SOURCES += \
    $$PWD/AbstractDeviceCommand.cpp \
    $$PWD/FixtureSwitchOnDeviceCommand.cpp \
    $$PWD/SpeedToLightDownDeviceCommand.cpp \
    $$PWD/SpeedToLightUpDeviceCommand.cpp \
    $$PWD/SwitchOffDeviceCommand.cpp \
    $$PWD/SpeedToLightBaseDeviceCommand.cpp \
    $$PWD/FixtureCommand.cpp
