#include "PostgresFixtureGateway.h"

#include "Fixture.h"
#include "NotImplementedException.h"
#include "UpdateQuery.h"

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

namespace light {
namespace PostgresqlGateway {
FixtureShared PostgresFixtureGateway::selectFixture(ID id) {
  auto fixtures = selectFixtures({id});
  if (fixtures.count()) {
    return fixtures.first();
  }

  return FixtureShared();
}

FixtureSharedList PostgresFixtureGateway::selectFixtures(const QList<ID>& ids) {
  FixtureSharedList result;
  const QString sql =
      "select id_fixture, flg_gatewaylink, work_level, standby_level, speed_zero_to_full, speed_full_to_zero "
      "from fixture_pkg_i.fixture_allinfo_vw "
      "where id_fixture = :id_fixture";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_fixture", id},
    };
    result << selectBase(sql, bindParams);
  }
  return result;
}

void PostgresFixtureGateway::saveFixture(const FixtureShared& fixture) {
  saveFixtures({fixture});
}

void PostgresFixtureGateway::saveFixtures(const FixtureSharedList& fixtures) {
  getDb().transaction();
  for (auto f : fixtures) {
    if (f->getId()) {
      updateFixture(f);
    } else {
      insertFixture(f);
    }
  }
  getDb().commit();
}

void PostgresFixtureGateway::deleteFixture(const FixtureShared& fixture) {
  /// FIXME not implemented
  Q_UNUSED(fixture)
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresFixtureGateway::deleteFixtures(const FixtureSharedList& fixtures) {
  /// FIXME not implemented
  Q_UNUSED(fixtures)
  throw NotImplementedException(Q_FUNC_INFO);
}

FixtureSharedList PostgresFixtureGateway::selectBase(const QString& sql, const BindParamsType& params) const {
  auto parser = std::bind(&PostgresFixtureGateway::parseFixture, this, std::placeholders::_1);
  return select<FixtureSharedList>(sql, params, parser);
}

FixtureShared PostgresFixtureGateway::parseFixture(const QSqlRecord& record) const {
  auto fixture = FixtureShared::create();
  fixture->setId(record.value(0).value<ID>());
  fixture->setHasGatewayLink(record.value(1).toBool());
  fixture->setWorkLevel(record.value(2).value<quint8>());
  fixture->setStandbyLevel(record.value(3).value<quint8>());
  fixture->setSpeedUp(record.value(4).value<quint8>());
  fixture->setSpeedDown(record.value(5).value<quint8>());
  return fixture;
}

void PostgresFixtureGateway::insertFixture(const FixtureShared& fixture) {
  /// FIXME not implemented
  Q_UNUSED(fixture);
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresFixtureGateway::updateFixture(const FixtureShared& fixture) {
  const QString sql = "select fixture_pkg_i.set_standby_level(:id_fixture, :standby_level), "
		      "fixture_pkg_i.set_work_level(:id_fixture, :work_level),"
		      "fixture_pkg_i.set_speed_zero_to_full(:id_fixture, :speed_zero_to_full),"
		      "fixture_pkg_i.set_speed_full_to_zero(:id_fixture, :speed_full_to_zero)";
  BindParamsType bindParams{
      {":id_fixture", fixture->getId()},
      {":standby_level", fixture->getStandbyLevel()},
      {":work_level", fixture->getWorkLevel()},
      {":speed_zero_to_full", fixture->getSpeedUp()},
      {":speed_full_to_zero", fixture->getSpeedDown()},
  };
  buildAndExecQuery<UpdateQuery>(sql, bindParams);
}

} // namespace PostgresqlGateway
} // namespace light
