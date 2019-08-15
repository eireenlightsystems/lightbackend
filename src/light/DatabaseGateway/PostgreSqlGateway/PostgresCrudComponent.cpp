#include "PostgresCrudComponent.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> objectFields {
    {"id_component", "id_component", true},
    {"name", "name_component", false},
    {"comments", "comments_component", false},
    };

PostgresCrud<Component>::PostgresCrud() {
  setFields(objectFields);
  setView("component_pkg_i.component_vwf()");
  setInsertSql("select component_pkg_i.save(:action, :id_component, :name, :comments)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select component_pkg_i.del(:id)");
}

Reader<Component>::Shared PostgresCrud<Component>::parse(const QSqlRecord& record) const {
  auto component = ComponentShared::create();
  component->setId(record.value(getFieldAlias("id_role")).value<ID>());
  component->setName(record.value(getFieldAlias("name")).toString());
  component->setComments(record.value(getFieldAlias("comments")).toString());
  return component;
}

BindParamsType PostgresCrud<Component>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<Component>::getInsertParams(const Editor::Shared &component) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_component", QVariant()},
      {":name", component->getName()},
      {":comments", component->getComments()},
      };
}

BindParamsType PostgresCrud<Component>::getUpdateParams(const Editor::Shared &component) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_component", component->getId()},
      {":name", component->getName()},
      {":comments", component->getComments()},
      };
}

} // namespace PostgresqlGateway
} // namespace light



