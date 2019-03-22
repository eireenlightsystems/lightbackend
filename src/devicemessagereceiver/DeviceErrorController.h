#ifndef DEVICEERRORCONTROLLER_H
#define DEVICEERRORCONTROLLER_H
#include "DeviceMessageReceiverTypeDefs.h"
#include "SharedTypes.h"

#include <QObject>
#include <QSharedPointer>

class QMqttClient;

namespace light {
namespace DeviceMessageReceiver {

class DeviceErrorSaver;
class MqttDeviceErrorSubscriber;

class DeviceErrorController : public QObject
{
  Q_OBJECT
public:
  explicit DeviceErrorController(QObject* parent = nullptr);

  AbstractDeviceErrorSaverShared getDeviceErrorSaver() const;
  void setDeviceErrorSaver(const AbstractDeviceErrorSaverShared& value);

  MqttDeviceErrorSubscriberShared getErrorSubscriber() const;
  void setErrorSubscriber(const MqttDeviceErrorSubscriberShared& value);

private slots:
  void onDeviceErrorReceived(const DeviceError& error);

private:
  AbstractDeviceErrorSaverShared deviceErrorSaver;
  MqttDeviceErrorSubscriberShared errorSubscriber;
};
} // namespace DeviceMessageReceiver
} // namespace light

#endif // DEVICEERRORCONTROLLER_H
