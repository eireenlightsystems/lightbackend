#ifndef SPEEDTOLIGHTBASEDEVICECOMMAND_H
#define SPEEDTOLIGHTBASEDEVICECOMMAND_H

#include "FixtureCommand.h"

namespace light {
namespace CommandsScheduler {
class SpeedToLightBaseDeviceCommand : public FixtureCommand
{
public:
  SpeedToLightBaseDeviceCommand() = default;
  SpeedToLightBaseDeviceCommand(ulong gatewayId,
				quint8 firstNode,
				quint8 lastNode,
				quint8 deviceNumber,
				CommandNumber commandNumber);
  QByteArray getRawData() const override;
  void fromRawData(const QByteArray& rawData) override;

  quint8 getSpeed() const;
  void setSpeed(const quint8& value);

private:
  quint8 speed;
};
} // namespace CommandsScheduler
} // namespace light

#endif // SPEEDTOLIGHTBASEDEVICECOMMAND_H
