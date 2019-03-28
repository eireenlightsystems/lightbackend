#include "DatasabeHelper.h"
#include "HttpRequestHelper.h"

#include <QtTest>

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

  void get();
  // void path();
  void del();

private:
  const QString address = "31.134.167.47:8095";
  const QString apiVersion = "/api/v1";
  const QString router = "sensors";
  HttpRequestHelper requestHelper;
  DatasabeHelper databaseHelper;
  QList<qulonglong> insertedIds;
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
}

void Sensors::cleanupTestCase() {
}

void Sensors::get() {
  requestHelper.get();
  if (insertedIds.count()) {
    auto jsonObject = requestHelper.getById(insertedIds.first());
    QVERIFY(jsonObject.value("sensorId").toVariant().toULongLong() == insertedIds.first());
  }
}

void Sensors::post_data() {
  QTest::addColumn<qulonglong>("contractId");
  QTest::addColumn<qulonglong>("sensorTypeId");
  QTest::addColumn<qulonglong>("nodeId");
  QTest::addColumn<QString>("serialNumber");
  QTest::addColumn<QString>("comment");

  QTest::newRow("simple 1") << qulonglong(4) << qulonglong(14) << qulonglong(2) << QString("s/n my 300")
			    << QString("comment");
  QTest::newRow("simple 2") << qulonglong(4) << qulonglong(14) << qulonglong(2) << QString("s/n my 301")
			    << QString("comment");
  QTest::newRow("simple 3") << qulonglong(4) << qulonglong(14) << qulonglong(2) << QString("s/n my 302")
			    << QString("comment");
}

void Sensors::post() {
  QFETCH(qulonglong, contractId);
  QFETCH(qulonglong, sensorTypeId);
  QFETCH(qulonglong, nodeId);
  QFETCH(QString, serialNumber);
  QFETCH(QString, comment);

  QJsonObject object;
  object["contractId"] = QJsonValue::fromVariant(contractId);
  object["sensorTypeId"] = QJsonValue::fromVariant(sensorTypeId);
  object["nodeId"] = QJsonValue::fromVariant(nodeId);
  object["serialNumber"] = serialNumber;
  object["comment"] = comment;

  auto id = requestHelper.post(object);
  QVERIFY2(id != 0, "response id == 0");
  insertedIds << id;

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
    QVERIFY2(value == object.value(pair.first), pair.first.toStdString().c_str());
  }
}

void Sensors::del() {
  if (insertedIds.count()) {
    requestHelper.del(insertedIds.first());
    insertedIds.removeFirst();
    if (insertedIds.count()) {
      requestHelper.del(insertedIds);
    }
  }
}

QTEST_MAIN(Sensors)

#include "tst_sensors.moc"
