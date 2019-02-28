#include "HttpServerConverters.h"

#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariant>

namespace light {

bool BaseConverter::getIdValid() const {
  return idValid;
}

void BaseConverter::setIdValid(bool value) {
  idValid = value;
}

QString BaseConverter::getErrorText() const {
  return errorText;
}

QJsonDocument BaseConverter::parseJson(const QByteArray& data) {
  QJsonParseError parseError;
  QJsonDocument jDoc = QJsonDocument::fromJson(data, &parseError);
  if (parseError.error != QJsonParseError::NoError) {
    qDebug() << parseError.errorString();
    setIdValid(false);
    setErrorText(parseError.errorString());
  }
  return jDoc;
}

template <typename T>
T BaseConverter::createAndBaseParse(const QJsonObject& object) const {
  auto command = T::create();
  command->setCommandId(object.value("commandId").toVariant().value<ID>());
  command->setFixtureId(object.value("fixtureId").toVariant().value<ID>());
  auto startDateTime = QDateTime::fromString(object.value("startDateTime").toString(), Qt::ISODate);
  command->setStartDateTime(startDateTime);
  return command;
}

void BaseConverter::setErrorText(const QString& value) {
  errorText = value;
}

QJsonDocument BaseJsonConverter::getJsonDocument() const {
  return jsonDocument;
}

void BaseJsonConverter::setJsonDocument(const QJsonDocument& value) {
  jsonDocument = value;
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

void IdsToJson::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid()) {
    setErrorText(data);
    return;
  }

  ids.clear();
  auto commandArray = jDoc.array();
  QList<ID> deleteCommands;
  for (const auto commandValue : commandArray) {
    auto id = commandValue.toVariant().value<qulonglong>();
    ids << id;
  }
}

QList<ID> IdsToJson::getIds() const {
  return ids;
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
