#ifndef DEVICEERRORCONTROLLER_H
#define DEVICEERRORCONTROLLER_H
#include "DeviceMessageReceiverTypeDefs.h"
#include "PostgresConnectionInfo.h"
#include "SharedTypes.h"

#include <QObject>
#include <QSharedPointer>
#include <QSqlDatabase>

class QMqttClient;

namespace DeviceMessageReceiver {

class DeviceErrorSaver;
class MqttDeviceErrorSubscriber;

struct MqttConnectionInfo
{
  QString hostName;
  quint16 port;
  QString clientId;
};

class DeviceErrorController : public QObject
{
  Q_OBJECT
public:
  explicit DeviceErrorController(QObject* parent = nullptr);
  void init();

private slots:
  void onMqttConnected();
  void onDeviceErrorReceived(const DeviceError& error);

private:
  void initSubscriber();
  void initDatabase();
  void initMqtt();
  light::PostgresConnectionInfo readConnectionInfoFromSettings() const;
  void initMqttClient(const MqttConnectionInfo &connectionInfo);
  MqttConnectionInfo readMqttConnectionInfoFromSettings() const;
  QString getSettingsPath() const;

private:
  PostgresDeviceErrorSaverShared deviceErrorSaver;
  MqttDeviceErrorSubscriberShared errorSubscriber;
  QMqttClientShared mqttClient;
};
} // namespace DeviceMessageReceiver

#endif // DEVICEERRORCONTROLLER_H
