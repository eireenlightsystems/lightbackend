#ifndef DEVICEERRORCONTROLLER_H
#define DEVICEERRORCONTROLLER_H
#include "SharedTypes.h"
#include "DeviceMessageReceiverTypeDefs.h"

#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>

class QMqttClient;

namespace DeviceMessageReceiver {

class DeviceErrorSaver;
class MqttDeviceErrorSubscriber;

class DeviceErrorController : public QObject
{
  Q_OBJECT
public:
  explicit DeviceErrorController(QObject* parent = nullptr);

  QMqttClientShared getMqttCilent() const;
  void setMqttCilent(const QMqttClientShared& value);

  AbstractDeviceErrorSaverShared getDeviceErrorSaver() const;
  void setDeviceErrorSaver(const AbstractDeviceErrorSaverShared& value);

private slots:
  void onMqttConnected();
  void onDeviceErrorReceived(const DeviceError& error);

private:
  AbstractDeviceErrorSaverShared deviceErrorSaver;
  MqttDeviceErrorSubscriberShared errorSubscriber;
  QMqttClientShared mqttClient;
};
} // namespace light

#endif // DEVICEERRORCONTROLLER_H
