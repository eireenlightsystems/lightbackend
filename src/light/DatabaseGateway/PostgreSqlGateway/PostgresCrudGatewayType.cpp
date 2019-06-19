#include "PostgresCrudGatewayType.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> gatewayTypeFields{
    {"id_equipment_type", "id_gateway_type", true},
    {"code", "code_gateway_type", false},
    {"name", "name_gateway_type", false},
    {"model", "model_gateway_type", false},
    {"comments", "comments_gateway_type", false},
    {"communications_standard", "communications_standard_gateway_type", false},
};

PostgresCrud<GatewayType>::PostgresCrud() {
  setFields(gatewayTypeFields);
  setView("gateway_type_pkg_i.gateway_type_vwf()");
  setInsertSql("select gateway_type_pkg_i.save(:action, :id_equipment_type, :code, :name, :model, :comments, :communications_standard)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select gateway_type_pkg_i.del(:id)");
}

Reader<GatewayType>::Shared PostgresCrud<GatewayType>::parse(const QSqlRecord& record) const {
  auto gatewayType = GatewayTypeShared::create();
  gatewayType->setId(record.value(getIdAlias()).value<ID>());
  gatewayType->setCode(record.value(getFieldAlias("code")).toString());
  gatewayType->setName(record.value(getFieldAlias("name")).toString());
  gatewayType->setModel(record.value(getFieldAlias("model")).toString());
  gatewayType->setComment(record.value(getFieldAlias("comments")).toString());
  gatewayType->setCommunicationStandard(record.value(getFieldAlias("communications_standard")).toString());
  return gatewayType;
}

BindParamsType PostgresCrud<GatewayType>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<GatewayType>::getInsertParams(const Editor::Shared &gatewayType) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_equipment_type", QVariant()},
      {":code", gatewayType->getCode()},
      {":name", gatewayType->getName()},
      {":model", gatewayType->getModel()},
      {":comments", gatewayType->getComment()},
      {":communications_standard", gatewayType->getCommunicationStandard()},
  };
}

BindParamsType PostgresCrud<GatewayType>::getUpdateParams(const Editor::Shared &gatewayType) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_equipment_type", gatewayType->getId()},
      {":code", gatewayType->getCode()},
      {":name", gatewayType->getName()},
      {":model", gatewayType->getModel()},
      {":comments", gatewayType->getComment()},
      {":communications_standard", gatewayType->getCommunicationStandard()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
