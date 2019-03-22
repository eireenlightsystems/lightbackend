#include "FixtureCommandToJson.h"

#include "FixtureCommand.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "NotImplementedException.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

template <>
QJsonObject ToJsonConverter<FixtureCommand>::toJson(const FixtureCommandShared& command) const {
  Q_UNUSED(command)
  throw NotImplementedException(Q_FUNC_INFO);
}

template <>
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

template <>
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
} // namespace light
