#include "PostgresCrudReportCountFixture.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> objFields {
    {"id_fixture", "id_fixture", true},
    {"region", "region", false},
    {"area", "area", false},
    {"city", "city", false},
    {"city_district", "city_district", false},
    {"settlement", "settlement", false},
    {"street", "street", false},
    {"house", "house", false},
    {"code_contract", "code_contract", false},
    {"code_fixture_type", "code_fixture_type", false},
    {"model_fixture_type", "model_fixture_type", false},
    {"code_installer", "code_installer", false},
    {"code_substation", "code_substation", false},
    {"code_height_type", "code_height_type", false},
    {"code_owner", "code_owner", false},
    {"count_fixture", "count_fixture", false},
    };

PostgresCrud<ReportCountFixture>::PostgresCrud() {
  setFields(objFields);
  setView("fixture_pkg_i.report_count_fixture_vw");
}

Reader<ReportCountFixture>::Shared PostgresCrud<ReportCountFixture>::parse(const QSqlRecord& record) const {
  auto reportCountFixture = ReportCountFixtureShared::create();
  reportCountFixture->setId(record.value(getFieldAlias("id_fixture")).value<ID>());
  reportCountFixture->setRegion(record.value(getFieldAlias("region")).toString());
  reportCountFixture->setArea(record.value(getFieldAlias("area")).toString());
  reportCountFixture->setCity(record.value(getFieldAlias("city")).toString());
  reportCountFixture->setCityDistrict(record.value(getFieldAlias("city_district")).toString());
  reportCountFixture->setSettlement(record.value(getFieldAlias("settlement")).toString());
  reportCountFixture->setStreet(record.value(getFieldAlias("street")).toString());
  reportCountFixture->setHouse(record.value(getFieldAlias("house")).toString());
  reportCountFixture->setCodeContract(record.value(getFieldAlias("code_contract")).toString());
  reportCountFixture->setCodeFixtureType(record.value(getFieldAlias("code_fixture_type")).toString());
  reportCountFixture->setCodeInstaller(record.value(getFieldAlias("code_installer")).toString());
  reportCountFixture->setCodeSubstation(record.value(getFieldAlias("code_substation")).toString());
  reportCountFixture->setCodeHeightType(record.value(getFieldAlias("code_height_type")).toString());
  reportCountFixture->setCodeOwner(record.value(getFieldAlias("code_owner")).toString());
  reportCountFixture->setCountFixture(record.value(getFieldAlias("count_fixture")).toInt());
  return reportCountFixture;
}

BindParamsType PostgresCrud<ReportCountFixture>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<ReportCountFixture>::getInsertParams(const Editor::Shared &roleright) const
{
  return BindParamsType();
}

BindParamsType PostgresCrud<ReportCountFixture>::getUpdateParams(const Editor::Shared &object) const
{
  return BindParamsType();
}

} // namespace PostgresqlGateway
} // namespace light
