#ifndef FIXTURESWITCHONDEVICECOMMAND_H
#define FIXTURESWITCHONDEVICECOMMAND_H

#include "FixtureCommand.h"

namespace light {
namespace CommandsScheduler {
class FixtureSwitchOnDeviceCommand : public FixtureCommand
{
public:
  FixtureSwitchOnDeviceCommand();
  FixtureSwitchOnDeviceCommand(ulong gatewayId, quint8 firstNode, quint8 lastNode, quint8 deviceNumber);
  ~FixtureSwitchOnDeviceCommand() override = default;

  QByteArray getRawData() const override;
  void fromRawData(const QByteArray& rawData) override;

  quint8 getWorkLevel() const;
  void setWorkLevel(quint8 value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(quint8 value);

private:
  quint8 workLevel{0};
  quint8 standbyLevel{0};
};
} // namespace CommandsScheduler
} // namespace light

#endif // FIXTURESWITCHONDEVICECOMMAND_H
