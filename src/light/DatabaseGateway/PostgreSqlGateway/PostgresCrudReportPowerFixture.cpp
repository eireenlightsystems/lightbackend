#include "PostgresCrudReportPowerFixture.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

    const QList<Field> objFields {
	{"year", "year", false},
	{"month_name", "month_name", false},
	{"id_fixture", "id_fixture", false},
	{"hours", "hours", false},
	{"kw", "kw", false},
	{"rub", "rub", false},
	};

PostgresCrud<ReportPowerFixture>::PostgresCrud() {
  setFields(objFields);
  setView("command_switchon_pkg_i.fixture_month_result_vwf(null, null, null)");
}

Reader<ReportPowerFixture>::Shared PostgresCrud<ReportPowerFixture>::parse(const QSqlRecord& record) const {
  auto reportPowerFixture = ReportPowerFixtureShared::create();
  reportPowerFixture->setYear(record.value(getFieldAlias("year")).toInt());
  reportPowerFixture->setMonthName(record.value(getFieldAlias("month_name")).toString());
  reportPowerFixture->setFixtureId(record.value(getFieldAlias("id_fixture")).toInt());
  reportPowerFixture->setHours(record.value(getFieldAlias("hours")).toDouble());
  reportPowerFixture->setKw(record.value(getFieldAlias("kw")).toDouble());
  reportPowerFixture->setRub(record.value(getFieldAlias("rub")).toDouble());

  return reportPowerFixture;
}

BindParamsType PostgresCrud<ReportPowerFixture>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<ReportPowerFixture>::getInsertParams(const Editor::Shared &roleright) const
{
  return BindParamsType();
}

BindParamsType PostgresCrud<ReportPowerFixture>::getUpdateParams(const Editor::Shared &object) const
{
  return BindParamsType();
}

} // namespace PostgresqlGateway
} // namespace light

