#include "PostgresCrudSubstation.h"

#include <QSqlRecord>
#include <QVariant>

#include "PostgresCrudContragent.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> substationFields{
    {"id_contragent", "id_substation", true},
    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
    {"code", "code_substation", false},
    {"name", "name_substation", false},
    {"inn", "inn_substation", false},
    {"comments", "comments_substation", false},
    {"id_org_forms_type", "id_org_forms_type_substation", false},
    {"code_org_forms_type", "code_org_forms_type_substation", false},
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
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_substation", true},
      {"id_geograph", "id_geograph", false},
      {"code_geograph", "code_geograph", false},
      {"code", "code_substation", false},
      {"name", "name_substation", false},
      {"inn", "inn_substation", false},
      {"comments", "comments_substation", false},
  });
  const auto contragent = contragentCrud.parse(record);

  auto substation = SubstationShared::create(*contragent);

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
      {":id_contragent", substation->getId()},
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
