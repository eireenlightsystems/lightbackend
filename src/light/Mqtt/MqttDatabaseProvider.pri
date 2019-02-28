INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/MqttDeviceErrorSubscriber.h \
    $$PWD/DeviceErrorController.h \
    $$PWD/DeviceErrorSaver.h \
    $$PWD/SharedTypes.h \
    $$PWD/MqttDeviceCommandPublisher.h \
    $$PWD/AbstractDeviceCommand.h \
    $$PWD/FixtureSwitchOnCommand.h \
    $$PWD/DeviceCommandsController.h \
    $$PWD/DeviceSwitchOffCommand.h \
    $$PWD/SpeedToLightUpCommand.h \
    $$PWD/SpeedToLightDownCommand.h \
    $$PWD/MqttDatabaseProvider.h \
    $$PWD/MqttDbProviderTypedefs.h \
    $$PWD/AbstractDatabaseGateway.h \
    $$PWD/InMemoryDatabaseGateway.h \
    $$PWD/CommandsScheduler.h

SOURCES += \
    $$PWD/MqttDeviceErrorSubscriber.cpp \
    $$PWD/DeviceErrorController.cpp \
    $$PWD/DeviceErrorSaver.cpp \
    $$PWD/MqttDeviceCommandPublisher.cpp \
    $$PWD/FixtureSwitchOnCommand.cpp \
    $$PWD/AbstractDeviceCommand.cpp \
    $$PWD/DeviceCommandsController.cpp \
    $$PWD/DeviceSwitchOffCommand.cpp \
    $$PWD/SpeedToLightUpCommand.cpp \
    $$PWD/SpeedToLightDownCommand.cpp \
    $$PWD/MqttDatabaseProvider.cpp \
    $$PWD/AbstractDatabaseGateway.cpp \
    $$PWD/InMemoryDatabaseGateway.cpp \
    $$PWD/CommandsScheduler.cpp
