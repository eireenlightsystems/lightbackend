INCLUDEPATH +=  \
    $$PWD

HEADERS += \
    $$PWD/Exception.h \
    $$PWD/BadRequestException.h \
    $$PWD/InternalServerErrorException.h \
    $$PWD/BadInputDataException.h \
    $$PWD/MissingFixtureGatewayLinkException.h \
    $$PWD/DeleteCommandException.h \
    $$PWD/DatabaseException.h \
    $$PWD/NotImplementedException.h \
    $$PWD/BadCredentials.h

SOURCES +=  \
    $$PWD/Exception.cpp \
    $$PWD/BadRequestException.cpp \
    $$PWD/InternalServerErrorException.cpp \
    $$PWD/BadInputDataException.cpp \
    $$PWD/MissingFixtureGatewayLinkException.cpp \
    $$PWD/DeleteCommandException.cpp \
    $$PWD/DatabaseException.cpp \
    $$PWD/NotImplementedException.cpp \
    $$PWD/BadCredentials.cpp
