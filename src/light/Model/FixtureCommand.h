#ifndef FIXTURECOMMAND_H
#define FIXTURECOMMAND_H

#include "CommandStatus.h"
#include "typedefs.h"

#include <QDateTime>

namespace light {

class FixtureCommandStatus
{
public:
  FixtureCommandStatus() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
};

class FixtureCommandType
{
public:
  FixtureCommandType() = default;
  virtual ~FixtureCommandType() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getName() const;
  void setName(const QString& value);

private:
  ID id{0};
  QString name;
};

class FixtureCommand
{
public:
  FixtureCommand() = default;
  virtual ~FixtureCommand();

  ID getId() const;
  void setId(const ID& value);

  ID getFixtureId() const;
  void setFixtureId(const ID& value);

  QDateTime getStartDateTime() const;
  void setStartDateTime(const QDateTime& value);

  CommandStatus getStatus() const;
  void setStatus(const CommandStatus& value);

  bool getDeletable() const;

private:
  ID id{0};
  ID fixtureId{0};
  QDateTime startDateTime;
  CommandStatus status{CommandStatus::None};
};
} // namespace light

#endif // FIXTURECOMMAND_H
