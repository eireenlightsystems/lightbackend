#include "PostgresCrudSubstation.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> substationFields{
    {"id_contragent", "id_substation", true},
    {"id_geograph_addr", "id_geograph_addr_substation", true},
    {"code_geograph", "code_geograph_substation", true},
    {"code", "code_substation", false},
    {"name", "name_substation", false},
    {"inn", "inn_substation", false},
    {"comments", "comments_substation", false},
    {"id_org_forms_type", "id_org_forms_type_substation", true},
    {"code_org_forms_type", "code_org_forms_type_substation", true},
    {"power", "power_substation", false},
};

PostgresCrud<Substation>::PostgresCrud() {
  setFields(substationFields);
  setView("substation_pkg_i.substation_vwf()");
  setInsertSql("select substation_pkg_i.save(:action, :id_contragent, :id_geograph_addr, :code, :name, :inn, :comments, :id_org_forms_type, :power)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select substation_pkg_i.del(:id)");
}

Reader<Substation>::Shared PostgresCrud<Substation>::parse(const QSqlRecord& record) const {
  auto substation = SubstationShared::create();
  substation->setId(record.value(getFieldAlias("id_contragent")).value<ID>());
  substation->setGeographId(record.value(getFieldAlias("id_geograph_addr")).value<ID>());
  substation->setGeographCode(record.value(getFieldAlias("code_geograph")).toString());
  substation->setCode(record.value(getFieldAlias("code")).toString());
  substation->setName(record.value(getFieldAlias("name")).toString());
  substation->setInn(record.value(getFieldAlias("inn")).toString());
  substation->setComments(record.value(getFieldAlias("comments")).toString());
  substation->setOrgFormId(record.value(getFieldAlias("id_org_forms_type")).value<ID>());
  substation->setOrgFormCode(record.value(getFieldAlias("code_org_forms_type")).toString());
  substation->setPower(record.value(getFieldAlias("power")).toDouble());
  return substation;
}

BindParamsType PostgresCrud<Substation>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<Substation>::getInsertParams(const Editor::Shared &substation) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", substation->getGeographId()},
      {":code", substation->getCode()},
      {":name", substation->getName()},
      {":inn", substation->getInn()},
      {":comments", substation->getComments()},
      {":id_org_forms_type", substation->getOrgFormId()},
      {":power", substation->getPower()},
  };
}

BindParamsType PostgresCrud<Substation>::getUpdateParams(const Editor::Shared &substation) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", substation->getGeographId()},
      {":code", substation->getCode()},
      {":name", substation->getName()},
      {":inn", substation->getInn()},
      {":comments", substation->getComments()},
      {":id_org_forms_type", substation->getOrgFormId()},
      {":power", substation->getPower()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
