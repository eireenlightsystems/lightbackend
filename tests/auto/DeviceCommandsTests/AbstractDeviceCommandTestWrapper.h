#ifndef ABSTRACTDEVICECOMMANDTESTWRAPPER_H
#define ABSTRACTDEVICECOMMANDTESTWRAPPER_H

#include <AbstractDeviceCommand.h>

class AbstractDeviceCommandTestWrapper : public light::CommandsScheduler::AbstractDeviceCommand
{
public:
  AbstractDeviceCommandTestWrapper() = default;
  AbstractDeviceCommandTestWrapper(ulong gatewayId,
				   quint8 firstNode,
				   quint8 lastNode,
				   quint8 deviceNumber,
				   light::CommandsScheduler::CommandNumber commandNumber);
  void fromRawData(const QByteArray& rawData) override;
};

#endif // ABSTRACTDEVICECOMMANDTESTWRAPPER_H
