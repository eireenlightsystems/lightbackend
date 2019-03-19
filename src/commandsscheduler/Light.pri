LIGHT_PATH=$$PWD/../light
DATEBASEGATEWAY_PATH=$$LIGHT_PATH/DatabaseGateway
DEVICECOMMAND_PATH=$$LIGHT_PATH/DeviceCommand
MODEL_PATH=$$LIGHT_PATH/Model
include($$MODEL_PATH/Model.pri)

INCLUDEPATH += $$LIGHT_PATH $$DATEBASEGATEWAY_PATH $$DEVICECOMMAND_PATH

HEADERS += \
    $$LIGHT_PATH/typedefs.h \
    $$DATEBASEGATEWAY_PATH/AbstractFixtureCommandGateway.h \
    $$DEVICECOMMAND_PATH/AbstractDeviceCommand.h

SOURCES += \
    $$DATEBASEGATEWAY_PATH/AbstractFixtureCommandGateway.cpp \
    $$DEVICECOMMAND_PATH/AbstractDeviceCommand.cpp
