#include "PostgresDeviceErrorSaver.h"

#include "InsertQuery.h"
#include "SelectQuery.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace light {
namespace DeviceMessageReceiver {

bool PostgresDeviceErrorSaver::open(const light::PostgresConnectionInfo& connectionInfo) {
  db = QSqlDatabase::addDatabase("QPSQL", "errorsaver");
  db.setHostName(connectionInfo.hostName);
  db.setPort(connectionInfo.port);
  db.setDatabaseName(connectionInfo.databaseName);
  db.setUserName(connectionInfo.userName);
  db.setPassword(connectionInfo.password);
  if (!db.open()) {
    qCritical() << "database not open " << db.lastError().text();
    return false;
  }
  return true;
}

void PostgresDeviceErrorSaver::saveError(const DeviceError& error) {
  qDebug() << Q_FUNC_INFO << error.gatewayId << error.nodeNumber << error.deviceNumber << error.errorCode;
  db.transaction();
  ID fixtureId = findFixtureId(error);

  if (fixtureId == 0) {
    qCritical() << "fixture id not found";
    db.rollback();
    return;
  }

  insertFixtureProblem(fixtureId, error.errorCode);
  db.commit();
}

ID PostgresDeviceErrorSaver::findFixtureId(const DeviceError& error) {
  ID fixtureId = 0;
  const QString findFixtureIdSql = "select f.id_fixture "
				   "from t.gateway_node gn left join t.fixture f on f.id_node = gn.id_node "
				   "where gn.id_gateway = :id_gateway "
				   "and gn.num_node = :num_node "
				   "limit 1";
  light::PostgresqlGateway::SelectQuery findFixtureIdQuery(db);
  findFixtureIdQuery.prepare(findFixtureIdSql);
  findFixtureIdQuery.bind({
      {":id_gateway", error.gatewayId},
      {":num_node", error.nodeNumber},
  });
  findFixtureIdQuery.exec();
  auto it = findFixtureIdQuery.begin();
  auto record = *it;
  fixtureId = record.value(0).value<ID>();
  return fixtureId;
}

void PostgresDeviceErrorSaver::insertFixtureProblem(ID fixtureId, quint8 errorCode) {
  const QString insertProblemSql = "select problem_fixture_pkg_i.ins(:id_fixture, :error_code)";
  light::PostgresqlGateway::InsertQuery query(db);
  query.prepare(insertProblemSql);
  query.bind({
      {":id_fixture", fixtureId},
      {":error_code", int(errorCode)},
  });
  query.exec();
}
} // namespace DeviceMessageReceiver

} // namespace light
