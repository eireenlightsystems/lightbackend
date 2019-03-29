#include "DatasabeHelper.h"
#include "HttpRequestHelper.h"

#include <QtTest>

Q_DECLARE_METATYPE(QJsonObject*);

class Sensors : public QObject
{
  Q_OBJECT

public:
  Sensors();
  ~Sensors();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void post_data();
  void post();

  void postError_data();
  void postError();

  void get();

  void patch_data();
  void patch();

  void del();

private:
  //  const QString address = "31.134.167.47:8095";
  const QString address = "localhost:8085";
  const QString apiVersion = "/api/v1";
  const QString router = "sensors";
  HttpRequestHelper requestHelper;
  DatasabeHelper databaseHelper;
  QJsonObject jsonSensor1;
  QJsonObject jsonSensor2;
  QJsonObject jsonSensor3;

  const int BadRequest = 400;
};

Sensors::Sensors() {
}

Sensors::~Sensors() {
}

void Sensors::initTestCase() {
  requestHelper.setRouterPrefix(QString("http://%1%2").arg(address, apiVersion));
  requestHelper.setRoute(router);
  if (!databaseHelper.openDatabase("31.134.167.47", 5433, "light_db_dev", "lightbackend", "lightbackend"))
    QFAIL("database open fail");

  jsonSensor1["contractId"] = QJsonValue::fromVariant(qulonglong(4));
  jsonSensor1["sensorTypeId"] = QJsonValue::fromVariant(qulonglong(14));
  jsonSensor1["nodeId"] = QJsonValue::fromVariant(qulonglong(2));
  jsonSensor1["serialNumber"] = QString("s/n sensor1");
  jsonSensor1["comment"] = QString("sensor1 comment");

  jsonSensor2["contractId"] = QJsonValue::fromVariant(qulonglong(4));
  jsonSensor2["sensorTypeId"] = QJsonValue::fromVariant(qulonglong(14));
  jsonSensor2["nodeId"] = QJsonValue::fromVariant(qulonglong(2));
  jsonSensor2["serialNumber"] = QString("s/n sensor2");
  jsonSensor2["comment"] = QString("sensor2 comment");

  jsonSensor3["contractId"] = QJsonValue::fromVariant(qulonglong(4));
  jsonSensor3["sensorTypeId"] = QJsonValue::fromVariant(qulonglong(14));
  jsonSensor3["nodeId"] = QJsonValue::fromVariant(qulonglong(2));
  jsonSensor3["serialNumber"] = QString("s/n sensor3");
  jsonSensor3["comment"] = QString("sensor3 comment");
}

void Sensors::cleanupTestCase() {
}

void Sensors::get() {
  requestHelper.get();
  auto id = jsonSensor1["sensorId"].toVariant().toULongLong();
  auto jsonObject = requestHelper.getById(id);
  for (auto key : jsonSensor1.keys()) {
    QVERIFY(jsonSensor1.value(key) == jsonObject.value(key));
  }
}

void Sensors::post_data() {
  QTest::addColumn<QJsonObject*>("jsonSensor");

  QTest::newRow("sensor 1") << &jsonSensor1;
  QTest::newRow("sensor 2") << &jsonSensor2;
  QTest::newRow("sensor 3") << &jsonSensor3;
}

void Sensors::post() {
  QFETCH(QJsonObject*, jsonSensor);

  auto id = requestHelper.post(*jsonSensor);
  QVERIFY2(id != 0, "response id == 0");
  (*jsonSensor)["sensorId"] = QJsonValue::fromVariant(id);

  const QString table = "t.sensor";
  const QString idField = "id_sensor";
  const QList<QPair<QString, QString>> fieldColumns{
      {"contractId", "id_contract"},
      {"sensorTypeId", "id_equipment_type"},
      {"nodeId", "id_node"},
      {"serialNumber", "serial_number"},
      {"comment", "comments"},
  };
  for (auto pair : fieldColumns) {
    auto value = databaseHelper.extractValue(table, pair.second, idField, id);
    QVERIFY2(value == jsonSensor->value(pair.first), pair.first.toStdString().c_str());
  }
}

void Sensors::postError_data() {
  QTest::addColumn<QJsonObject>("jsonSensor");

  QJsonObject contractEmpty = jsonSensor1;
  contractEmpty.remove("sensorId");
  contractEmpty.remove("contractId");

  QJsonObject contractNotExistsEmpty = jsonSensor1;
  contractNotExistsEmpty.remove("sensorId");
  contractNotExistsEmpty["contractId"] = 999999;

  QJsonObject typeEmpty = jsonSensor1;
  typeEmpty.remove("sensorId");
  typeEmpty.remove("sensorTypeId");

  QJsonObject typeNotExistsEmpty = jsonSensor1;
  typeNotExistsEmpty.remove("sensorId");
  typeNotExistsEmpty["sensorTypeId"] = 999999;

  QJsonObject nodeNotExistsEmpty = jsonSensor1;
  nodeNotExistsEmpty.remove("sensorId");
  nodeNotExistsEmpty["nodeId"] = 999999;

  QTest::newRow("contractId is empty") << contractEmpty;
  QTest::newRow("sensorTypeId is empty") << typeEmpty;

  QTest::newRow("contract not exists") << contractNotExistsEmpty;
  QTest::newRow("sensor type not exists") << typeNotExistsEmpty;
  QTest::newRow("node not exists") << nodeNotExistsEmpty;
}

void Sensors::postError() {
  QFETCH(QJsonObject, jsonSensor);

  requestHelper.post(jsonSensor);
  auto statusCode = requestHelper.getLastStatusCode();
  QVERIFY2(statusCode == BadRequest, QString("status code is %1").arg(statusCode).toStdString().c_str());
}

void Sensors::patch_data() {
  QTest::addColumn<QJsonObject*>("jsonSensor");

  QTest::newRow("sensor 1") << &jsonSensor1;
  QTest::newRow("sensor 2") << &jsonSensor2;
  QTest::newRow("sensor 3") << &jsonSensor3;
}

void Sensors::patch() {
  QFETCH(QJsonObject*, jsonSensor);

  (*jsonSensor)["comment"] = jsonSensor->value("comment").toString() + " patched";
  (*jsonSensor)["serialNumber"] = jsonSensor->value("serialNumber").toString() + " patched";

  requestHelper.patch(*jsonSensor);

  const QString table = "t.sensor";
  const QString idField = "id_sensor";
  const QList<QPair<QString, QString>> fieldColumns{
      {"contractId", "id_contract"},
      {"sensorTypeId", "id_equipment_type"},
      {"nodeId", "id_node"},
      {"serialNumber", "serial_number"},
      {"comment", "comments"},
  };
  auto id = jsonSensor->value("sensorId").toVariant().toULongLong();
  for (auto pair : fieldColumns) {
    auto value = databaseHelper.extractValue(table, pair.second, idField, id);
    QVERIFY2(value == jsonSensor->value(pair.first).toVariant(), pair.first.toStdString().c_str());
  }
}

void Sensors::del() {
  auto id = jsonSensor1.value("sensorId").toVariant().toULongLong();
  requestHelper.del(id);
  auto ids = QList<qulonglong>{jsonSensor2.value("sensorId").toVariant().toULongLong(),
			       jsonSensor3.value("sensorId").toVariant().toULongLong()};
  requestHelper.del(ids);
}

QTEST_MAIN(Sensors)

#include "tst_sensors.moc"
