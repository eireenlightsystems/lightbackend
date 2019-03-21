#ifndef FIXTURECOMMANDCONTROLLER_H
#define FIXTURECOMMANDCONTROLLER_H

#include "Controller.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"
#include "NotImplementedException.h"

#include <QVariant>

namespace light {
template <template <typename> class Crud>
class Controller<FixtureCommand, Crud> : public EditableController<FixtureCommand, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override {
    Q_UNUSED(params)
    throw NotImplementedException(Q_FUNC_INFO);
  }
  void upd(const QList<QVariantHash>& params) override {
    Q_UNUSED(params)
    throw NotImplementedException(Q_FUNC_INFO);
  }
  void upd(ID id, const QVariantHash& param) override {
    Q_UNUSED(id)
    Q_UNUSED(param)
    throw NotImplementedException(Q_FUNC_INFO);
  }
};

template <template <typename> class Crud>
class Controller<FixtureLightLevelCommand, Crud> : public EditableController<FixtureLightLevelCommand, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<FixtureLightLevelCommand, Crud>::ins(const QList<QVariantHash>& params) {
  FixtureLightLevelCommandSharedList newCommands;
  for (const auto& param : params) {
    auto newCommand = FixtureLightLevelCommandShared::create();
    if (param.contains("fixtureId")) {
      ID fixtureId = param.value("fixtureId").value<ID>();
      newCommand->setFixtureId(fixtureId);
    }

    if (param.contains("startDateTime")) {
      newCommand->setStartDateTime(param.value("startDateTime").toDateTime());
    }

    if (param.contains("workLevel")) {
      newCommand->setWorkLevel(param.value("workLevel").value<quint8>());
    }

    if (param.contains("standbyLevel")) {
      newCommand->setStandbyLevel(param.value("standbyLevel").value<quint8>());
    }
    newCommands << newCommand;
  }

  Crud<FixtureLightLevelCommand> lightLevelCommandCrud;
  lightLevelCommandCrud.setSession(this->getSession());
  lightLevelCommandCrud.save(newCommands);
  IDList ids;
  std::transform(newCommands.begin(),
		 newCommands.end(),
		 std::back_inserter(ids),
		 [](const FixtureLightLevelCommandShared& command) { return command->getId(); });
  return ids;
}

template <template <typename> class Crud>
void Controller<FixtureLightLevelCommand, Crud>::upd(const QList<QVariantHash>& params) {
  Crud<FixtureLightLevelCommand> lightLevelCommandCrud;
  lightLevelCommandCrud.setSession(this->getSession());

  FixtureLightLevelCommandSharedList commands;
  for (const auto& param : params) {
    ID commandId = param.value("commandId").value<ID>();
    auto command = lightLevelCommandCrud.selById(commandId);
    if (param.contains("fixtureId")) {
      ID fixtureId = param.value("fixtureId").value<ID>();
      command->setFixtureId(fixtureId);
    }

    if (param.contains("startDateTime")) {
      command->setStartDateTime(param.value("startDateTime").toDateTime());
    }

    if (param.contains("workLevel")) {
      command->setWorkLevel(param.value("workLevel").value<quint8>());
    }

    if (param.contains("standbyLevel")) {
      command->setStandbyLevel(param.value("standbyLevel").value<quint8>());
    }
    commands << command;
  }

  lightLevelCommandCrud.save(commands);
}

template <template <typename> class Crud>
void Controller<FixtureLightLevelCommand, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["commandId"] = id;
  return upd({fullParam});
}

template <template <typename> class Crud>
class Controller<FixtureLightSpeedCommand, Crud> : public EditableController<FixtureLightSpeedCommand, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<FixtureLightSpeedCommand, Crud>::ins(const QList<QVariantHash>& params) {
  FixtureLightSpeedCommandSharedList newCommands;
  for (const auto& param : params) {
    auto newCommand = FixtureLightSpeedCommandShared::create();
    if (param.contains("fixtureId")) {
      ID fixtureId = param.value("fixtureId").value<ID>();
      newCommand->setFixtureId(fixtureId);
    }

    if (param.contains("startDateTime")) {
      newCommand->setStartDateTime(param.value("startDateTime").toDateTime());
    }

    if (param.contains("speedDirectionId")) {
      auto directionType =
	  FixtureLightSpeedCommand::FixtureLightSpeedDirectionType(param.value("speedDirectionId").toInt());
      newCommand->setDirectionType(directionType);
    }

    if (param.contains("speed")) {
      newCommand->setSpeed(param.value("standbyLevel").value<quint8>());
    }
    newCommands << newCommand;
  }

  Crud<FixtureLightSpeedCommand> lightSpeedCommandCrud;
  lightSpeedCommandCrud.setSession(this->getSession());
  lightSpeedCommandCrud.save(newCommands);
  IDList ids;
  std::transform(newCommands.begin(),
		 newCommands.end(),
		 std::back_inserter(ids),
		 [](const FixtureLightSpeedCommandShared& command) { return command->getId(); });
  return ids;
}

template <template <typename> class Crud>
void Controller<FixtureLightSpeedCommand, Crud>::upd(const QList<QVariantHash>& params) {
  Crud<FixtureLightSpeedCommand> lightSpeedCommandCrud;
  lightSpeedCommandCrud.setSession(this->getSession());

  FixtureLightSpeedCommandSharedList commands;
  for (const auto& param : params) {
    ID commandId = param.value("commandId").value<ID>();
    auto command = lightSpeedCommandCrud.selById(commandId);
    if (param.contains("fixtureId")) {
      ID fixtureId = param.value("fixtureId").value<ID>();
      command->setFixtureId(fixtureId);
    }

    if (param.contains("startDateTime")) {
      command->setStartDateTime(param.value("startDateTime").toDateTime());
    }

    if (param.contains("speedDirectionId")) {
      auto directionType =
	  FixtureLightSpeedCommand::FixtureLightSpeedDirectionType(param.value("speedDirectionId").toInt());
      command->setDirectionType(directionType);
    }

    if (param.contains("speed")) {
      command->setSpeed(param.value("standbyLevel").value<quint8>());
    }
    commands << command;
  }

  lightSpeedCommandCrud.save(commands);
}

template <template <typename> class Crud>
void Controller<FixtureLightSpeedCommand, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["commandId"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // FIXTURECOMMANDCONTROLLER_H
