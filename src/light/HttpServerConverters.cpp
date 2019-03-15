#include "HttpServerConverters.h"

#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

template <typename T>
T JsonToFuxtureCommandBaseConverter::createAndBaseParse(const QJsonObject& object) const {
  auto command = T::create();
  command->setCommandId(object.value("commandId").toVariant().value<ID>());
  command->setFixtureId(object.value("fixtureId").toVariant().value<ID>());
  auto startDateTime = QDateTime::fromString(object.value("startDateTime").toString(), Qt::ISODate);
  command->setStartDateTime(startDateTime);
  return command;
}

void FixtureLightLevelCommandsToJson::convert(const FixtureLightLevelCommandSharedList& commands) {
  QJsonArray jsonCommands;
  for (const auto& c : commands) {
    QJsonObject command;
    command["commandId"] = QJsonValue::fromVariant(c->getCommandId());
    command["statusId"] = c->getStatus();
    command["startDateTime"] = c->getStartDateTime().toString("yyyy-MM-dd hh:mm");
    command["workLevel"] = c->getWorkLevel();
    command["standbyLevel"] = c->getStandbyLevel();

    jsonCommands << command;
  }

  setJsonDocument(QJsonDocument(jsonCommands));
}

void JsonToFixtureLightLevelCommands::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid())
    return;

  lightLevelCommands.clear();
  auto commandArray = jDoc.array();
  for (const auto commandValue : commandArray) {
    auto commandJson = commandValue.toObject();
    auto command = createAndBaseParse<FixtureLightLevelCommandShared>(commandJson);
    command->setWorkLevel(commandJson.value("workLevel").toVariant().value<quint8>());
    command->setStandbyLevel(commandJson.value("standbyLevel").toVariant().value<quint8>());
    lightLevelCommands << command;
  }
}

FixtureLightLevelCommandSharedList JsonToFixtureLightLevelCommands::getLightLevelCommands() const {
  return lightLevelCommands;
}

void JsonToFixtureLightSpeedCommands::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid())
    return;

  lightUpSpeedCommands.clear();
  auto commandArray = jDoc.array();
  for (const auto commandValue : commandArray) {
    auto commandJson = commandValue.toObject();
    auto command = createAndBaseParse<FixtureLightSpeedCommandShared>(commandJson);
    auto directionType =
	FixtureLightSpeedCommand::FixtureLightSpeedDirectionType(commandJson.value("speedDirectionId").toInt());
    command->setDirectionType(directionType);
    command->setSpeed(commandJson.value("speed").toVariant().value<quint8>());
    lightUpSpeedCommands << command;
  }
}

FixtureLightSpeedCommandSharedList JsonToFixtureLightSpeedCommands::getLightUpSpeedCommands() const {
  return lightUpSpeedCommands;
}

void FixtureLightSpeedCommandsToJson::convert(const FixtureLightSpeedCommandSharedList& commands) {
  QJsonArray jsonCommands;
  for (const auto& c : commands) {
    QJsonObject command;
    command["commandId"] = QJsonValue::fromVariant(c->getCommandId());
    command["statusId"] = c->getStatus();
    command["startDateTime"] = c->getStartDateTime().toString("yyyy-MM-dd hh:mm");
    command["speedDirectionId"] = static_cast<int>(c->getDirectionType());
    command["speed"] = c->getSpeed();
    jsonCommands << command;
  }

  setJsonDocument(QJsonDocument(jsonCommands));
}

} // namespace light
