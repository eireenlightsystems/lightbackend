#ifndef ABSTRACTDEVICEERRORSAVER_H
#define ABSTRACTDEVICEERRORSAVER_H

#include "SharedTypes.h"

namespace light {
namespace DeviceMessageReceiver {
class AbstractDeviceErrorSaver
{
public:
  virtual ~AbstractDeviceErrorSaver() = 0;
  virtual void saveError(const DeviceError& error) = 0;
};
} // namespace DeviceMessageReceiver
} // namespace light

#endif // ABSTRACTDEVICEERRORSAVER_H
