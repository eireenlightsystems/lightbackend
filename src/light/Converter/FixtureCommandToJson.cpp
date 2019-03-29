#include "FixtureCommandToJson.h"

#include "FixtureCommand.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "NotImplementedException.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<FixtureCommand>::toJson(const FixtureCommandShared& command) const {
  Q_UNUSED(command)
  throw NotImplementedException(Q_FUNC_INFO);
}

QJsonObject
ToJsonConverter<FixtureLightLevelCommand>::toJson(const FixtureLightLevelCommandShared& lightLevelCommand) const {
  QJsonObject commandJson;
  commandJson["commandId"] = QJsonValue::fromVariant(lightLevelCommand->getId());
  commandJson["statusId"] = lightLevelCommand->getStatus();
  commandJson["startDateTime"] = lightLevelCommand->getStartDateTime().toString("yyyy-MM-dd hh:mm");
  commandJson["workLevel"] = lightLevelCommand->getWorkLevel();
  commandJson["standbyLevel"] = lightLevelCommand->getStandbyLevel();
  return commandJson;
}

QJsonObject
ToJsonConverter<FixtureLightSpeedCommand>::toJson(const FixtureLightSpeedCommandShared& lightSpeedCommand) const {
  QJsonObject commandJson;
  commandJson["commandId"] = QJsonValue::fromVariant(lightSpeedCommand->getId());
  commandJson["statusId"] = lightSpeedCommand->getStatus();
  commandJson["startDateTime"] = lightSpeedCommand->getStartDateTime().toString("yyyy-MM-dd hh:mm");
  commandJson["speedDirectionId"] = static_cast<int>(lightSpeedCommand->getDirectionType());
  commandJson["speed"] = lightSpeedCommand->getSpeed();
  return commandJson;
}

QJsonObject ToJsonConverter<FixtureCommandType>::toJson(const FixtureCommandTypeShared& type) const {
  QJsonObject commandTypeJson;
  commandTypeJson["id"] = QJsonValue::fromVariant(type->getId());
  commandTypeJson["name"] = type->getName();
  return commandTypeJson;
}

QJsonObject
ToJsonConverter<FixtureLightLevelCommandType>::toJson(const FixtureLightLevelCommandTypeShared& type) const {
  ToJsonConverter<FixtureCommandType> typeConverter;
  return typeConverter.toJson(type.dynamicCast<FixtureCommandType>());
}

QJsonObject
ToJsonConverter<FixtureLightSpeedCommandType>::toJson(const FixtureLightSpeedCommandTypeShared& type) const {
  ToJsonConverter<FixtureCommandType> typeConverter;
  return typeConverter.toJson(type.dynamicCast<FixtureCommandType>());
}

QJsonObject ToJsonConverter<FixtureCommandStatus>::toJson(const FixtureCommandStatusShared& status) const {
  QJsonObject commandStatusJson;
  commandStatusJson["id"] = QJsonValue::fromVariant(status->getId());
  commandStatusJson["name"] = status->getName();
  return commandStatusJson;
}

} // namespace light
