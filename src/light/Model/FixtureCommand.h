#ifndef FIXTURECOMMAND_H
#define FIXTURECOMMAND_H

#include "CommandStatus.h"
#include "typedefs.h"

#include <QDateTime>

namespace light {
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
