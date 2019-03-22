#include "AbstractDeviceCommandTestWrapper.h"
#include "FixtureSwitchOnDeviceCommand.h"

#include <QtTest>
#include <SpeedToLightUpDeviceCommand.h>
#include <SpeedToLightDownDeviceCommand.h>
#include <QDebug>

Q_DECLARE_METATYPE(light::CommandsScheduler::CommandNumber)

class DeviceCommands : public QObject
{
  Q_OBJECT

public:
  DeviceCommands();
  ~DeviceCommands();

private slots:
  void initTestCase();
  void FixtureAbstractDeviceCommandSetter_data();
  void FixtureAbstractDeviceCommandSetter();

  void FixtureSwitchOnDeviceCommandSetter_data();
  void FixtureSwitchOnDeviceCommandSetter();

  void FixtureSwitchOnDeviceCommandRawData_data();
  void FixtureSwitchOnDeviceCommandRawData();

  void FixtureSpeedToLightBaseDeviceCommandSetter_data();
  void FixtureSpeedToLightBaseDeviceCommandSetter();

  void FixtureSpeedToLightBaseDeviceCommandRawData_data();
  void FixtureSpeedToLightBaseDeviceCommandRawData();
};

DeviceCommands::DeviceCommands() {
}

DeviceCommands::~DeviceCommands() {
}

void DeviceCommands::initTestCase() {
}

void DeviceCommands::FixtureAbstractDeviceCommandSetter_data() {
  QTest::addColumn<light::ID>("commandId");
  QTest::addColumn<QDateTime>("dateTime");
  QTest::addColumn<ulong>("gatewayId");
  QTest::addColumn<quint8>("firstNode");
  QTest::addColumn<quint8>("lastNode");
  QTest::addColumn<quint8>("deviceNumber");
  QTest::addColumn<light::CommandsScheduler::CommandNumber>("commandNumber");

  QTest::newRow("simple") << light::ID(1) << QDateTime::currentDateTime() << ulong(100) << quint8(1) << quint8(255)
			  << quint8(2) << light::CommandsScheduler::CommandNumber::SpeedToLightUp;
}

void DeviceCommands::FixtureAbstractDeviceCommandSetter() {
  QFETCH(light::ID, commandId);
  QFETCH(QDateTime, dateTime);
  QFETCH(ulong, gatewayId);
  QFETCH(quint8, firstNode);
  QFETCH(quint8, lastNode);
  QFETCH(quint8, deviceNumber);
  QFETCH(light::CommandsScheduler::CommandNumber, commandNumber);

  {
    AbstractDeviceCommandTestWrapper command1(gatewayId, firstNode, lastNode, deviceNumber, commandNumber);
    QVERIFY(command1.getGatewayId() == gatewayId);
    QVERIFY(command1.getFirstNode() == firstNode);
    QVERIFY(command1.getLastNode() == lastNode);
    QVERIFY(command1.getDeviceNumber() == deviceNumber);
    QVERIFY(command1.getCommandNumber() == commandNumber);
  }

  {
    AbstractDeviceCommandTestWrapper command2;
    command2.setId(commandId);
    command2.setDateTime(dateTime);
    command2.setGatewayId(gatewayId);
    command2.setFirstNode(firstNode);
    command2.setLastNode(lastNode);
    command2.setDeviceNumber(deviceNumber);
    command2.setCommandNumber(commandNumber);

    QVERIFY(command2.getId() == commandId);
    QVERIFY(command2.getDateTime() == dateTime);
    QVERIFY(command2.getGatewayId() == gatewayId);
    QVERIFY(command2.getFirstNode() == firstNode);
    QVERIFY(command2.getLastNode() == lastNode);
    QVERIFY(command2.getDeviceNumber() == deviceNumber);
    QVERIFY(command2.getCommandNumber() == commandNumber);
  }
}

void DeviceCommands::FixtureSwitchOnDeviceCommandSetter_data() {
  QTest::addColumn<QDateTime>("dateTime");
  QTest::addColumn<ulong>("gatewayId");
  QTest::addColumn<quint8>("firstNode");
  QTest::addColumn<quint8>("lastNode");
  QTest::addColumn<quint8>("deviceNumber");
  QTest::addColumn<quint8>("workLevel");
  QTest::addColumn<quint8>("standbyLevel");

  QTest::newRow("simple") << QDateTime::currentDateTime() << ulong(100) << quint8(1) << quint8(255)
			  << quint8(2) << quint8(99) << quint8(50);
}

void DeviceCommands::FixtureSwitchOnDeviceCommandSetter() {
  QFETCH(QDateTime, dateTime);
  QFETCH(ulong, gatewayId);
  QFETCH(quint8, firstNode);
  QFETCH(quint8, lastNode);
  QFETCH(quint8, deviceNumber);
  QFETCH(quint8, workLevel);
  QFETCH(quint8, standbyLevel);

  {
    light::CommandsScheduler::FixtureSwitchOnDeviceCommand command1(gatewayId, firstNode, lastNode, deviceNumber);
    QVERIFY(command1.getGatewayId() == gatewayId);
    QVERIFY(command1.getFirstNode() == firstNode);
    QVERIFY(command1.getLastNode() == lastNode);
    QVERIFY(command1.getDeviceNumber() == deviceNumber);
  }

  {
    light::CommandsScheduler::FixtureSwitchOnDeviceCommand command2;
    command2.setWorkLevel(workLevel);
    command2.setStandbyLevel(standbyLevel);

    QVERIFY(command2.getWorkLevel() == workLevel);
    QVERIFY(command2.getStandbyLevel() == standbyLevel);
  }
}

void DeviceCommands::FixtureSwitchOnDeviceCommandRawData_data() {
  QTest::addColumn<quint8>("firstNode");
  QTest::addColumn<quint8>("lastNode");
  QTest::addColumn<quint8>("deviceNumber");
  QTest::addColumn<quint8>("workLevel");
  QTest::addColumn<quint8>("standbyLevel");
  QTest::addColumn<QByteArray>("rawData");

  QTest::newRow("simple") << quint8(1) << quint8(255) << quint8(2) << quint8(99) << quint8(50)
			  << QByteArray("\x01\xff\x02\x03\x63\x32");
}

void DeviceCommands::FixtureSwitchOnDeviceCommandRawData() {
  QFETCH(quint8, firstNode);
  QFETCH(quint8, lastNode);
  QFETCH(quint8, deviceNumber);
  QFETCH(quint8, workLevel);
  QFETCH(quint8, standbyLevel);
  QFETCH(QByteArray, rawData);

  {
    light::CommandsScheduler::FixtureSwitchOnDeviceCommand command;
    command.setFirstNode(firstNode);
    command.setLastNode(lastNode);
    command.setDeviceNumber(deviceNumber);
    command.setWorkLevel(workLevel);
    command.setStandbyLevel(standbyLevel);
    QVERIFY(command.getRawData() == rawData);


  }

  {
    light::CommandsScheduler::FixtureSwitchOnDeviceCommand command;
    command.fromRawData(rawData);
    QVERIFY(command.getFirstNode() == firstNode);
    QVERIFY(command.getLastNode() == lastNode);
    QVERIFY(command.getDeviceNumber() == deviceNumber);
    QVERIFY(command.getWorkLevel() == workLevel);
    QVERIFY(command.getStandbyLevel() == standbyLevel);
  }
}

void DeviceCommands::FixtureSpeedToLightBaseDeviceCommandSetter_data() {
  QTest::addColumn<light::CommandsScheduler::CommandNumber>("commandNumber");
  QTest::addColumn<ulong>("gatewayId");
  QTest::addColumn<quint8>("firstNode");
  QTest::addColumn<quint8>("lastNode");
  QTest::addColumn<quint8>("deviceNumber");
  QTest::addColumn<quint8>("speed");

  QTest::newRow("simple") << light::CommandsScheduler::CommandNumber::SpeedToLightUp << ulong(100) << quint8(1) << quint8(255) << quint8(2)
			  << quint8(77);
}

void DeviceCommands::FixtureSpeedToLightBaseDeviceCommandSetter() {
  QFETCH(light::CommandsScheduler::CommandNumber, commandNumber);
  QFETCH(ulong, gatewayId);
  QFETCH(quint8, firstNode);
  QFETCH(quint8, lastNode);
  QFETCH(quint8, deviceNumber);
  QFETCH(quint8, speed);

  {
    light::CommandsScheduler::SpeedToLightBaseDeviceCommand command1(gatewayId, firstNode, lastNode, deviceNumber, commandNumber);
    QVERIFY(command1.getCommandNumber() == commandNumber);
    QVERIFY(command1.getGatewayId() == gatewayId);
    QVERIFY(command1.getFirstNode() == firstNode);
    QVERIFY(command1.getLastNode() == lastNode);
    QVERIFY(command1.getDeviceNumber() == deviceNumber);
  }

  {
    light::CommandsScheduler::SpeedToLightUpDeviceCommand command;
    QVERIFY(command.getCommandNumber() == light::CommandsScheduler::CommandNumber::SpeedToLightUp);
  }

  {
    light::CommandsScheduler::SpeedToLightDownDeviceCommand command;
    QVERIFY(command.getCommandNumber() == light::CommandsScheduler::CommandNumber::SpeedToLightDown);
  }

  {
    light::CommandsScheduler::SpeedToLightBaseDeviceCommand command2;
    command2.setCommandNumber(commandNumber);
    command2.setSpeed(speed);

    QVERIFY(command2.getSpeed() == speed);
  }
}

void DeviceCommands::FixtureSpeedToLightBaseDeviceCommandRawData_data()
{
  QTest::addColumn<light::CommandsScheduler::CommandNumber>("commandNumber");
  QTest::addColumn<quint8>("firstNode");
  QTest::addColumn<quint8>("lastNode");
  QTest::addColumn<quint8>("deviceNumber");
  QTest::addColumn<quint8>("speed");
  QTest::addColumn<QByteArray>("rawData");

  QTest::newRow("simple") << light::CommandsScheduler::CommandNumber::SpeedToLightUp << quint8(1) << quint8(255) << quint8(2) << quint8(99)
			  << QByteArray("\x01\xff\x02\x01\x63");
}

void DeviceCommands::FixtureSpeedToLightBaseDeviceCommandRawData()
{
  QFETCH(light::CommandsScheduler::CommandNumber, commandNumber);
  QFETCH(quint8, firstNode);
  QFETCH(quint8, lastNode);
  QFETCH(quint8, deviceNumber);
  QFETCH(quint8, speed);
  QFETCH(QByteArray, rawData);

  {
    light::CommandsScheduler::SpeedToLightBaseDeviceCommand command;
    command.setCommandNumber(commandNumber);
    command.setFirstNode(firstNode);
    command.setLastNode(lastNode);
    command.setDeviceNumber(deviceNumber);
    command.setSpeed(speed);
    QVERIFY(command.getRawData() == rawData);
  }

  {
    light::CommandsScheduler::SpeedToLightBaseDeviceCommand command;
    command.fromRawData(rawData);
    QVERIFY(command.getCommandNumber() == commandNumber);
    QVERIFY(command.getFirstNode() == firstNode);
    QVERIFY(command.getLastNode() == lastNode);
    QVERIFY(command.getDeviceNumber() == deviceNumber);
    QVERIFY(command.getSpeed() == speed);
  }
}

QTEST_APPLESS_MAIN(DeviceCommands)

#include "tst_devicecommands.moc"
