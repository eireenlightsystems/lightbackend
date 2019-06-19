#include "PostgresCrudPerson.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> personFields{
    {"id_contragent", "id_contragent_person", true},
    {"id_geograph_addr", "id_geograph_addr_person", true},
    {"code", "code_person", false},
    {"name", "name_person", false},
    {"inn", "inn_person", false},
    {"comments", "comments_person", false},
    {"name_first", "name_first_person", false},
    {"name_second", "name_second_person", false},
    {"name_third", "name_third_person", false},
};

PostgresCrud<Person>::PostgresCrud() {
  setFields(personFields);
  setView("person_pkg_i.person_vwf()");
  setInsertSql("select person_pkg_i.save(:action, :id_contragent, :id_geograph_addr, :code, :name, :inn, :comments, :name_first, :name_second, :name_third)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select person_pkg_i.del(:id)");
}

Reader<Person>::Shared PostgresCrud<Person>::parse(const QSqlRecord& record) const {
  auto person = PersonShared::create();
  person->setId(record.value(getFieldAlias("id_contragent")).value<ID>());
  person->setGeographId(record.value(getFieldAlias("id_geograph_addr")).value<ID>());
  person->setCode(record.value(getFieldAlias("code")).toString());
  person->setName(record.value(getFieldAlias("name")).toString());
  person->setInn(record.value(getFieldAlias("inn")).toString());
  person->setComments(record.value(getFieldAlias("comments")).toString());
  person->setNameFirst(record.value(getFieldAlias("name_first")).toString());
  person->setNameSecond(record.value(getFieldAlias("name_second")).toString());
  person->setNameThird(record.value(getFieldAlias("name_third")).toString());
  return person;
}


BindParamsType PostgresCrud<Person>::getSelectParams(const QVariantHash &filters) const
{
  return BindParamsType{};
}

BindParamsType PostgresCrud<Person>::getInsertParams(const Editor::Shared &person) const
{
  return BindParamsType{
      {":action", "ins"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", person->getGeographId()},
      {":code", person->getCode()},
      {":name", person->getName()},
      {":inn", person->getInn()},
      {":comments", person->getComments()},
      {":name_first", person->getNameFirst()},
      {":name_second", person->getNameSecond()},
      {":name_third", person->getNameThird()},
  };
}

BindParamsType PostgresCrud<Person>::getUpdateParams(const Editor::Shared &person) const
{
  return BindParamsType{
      {":action", "upd"},
      {":id_contragent", QVariant()},
      {":id_geograph_addr", person->getGeographId()},
      {":code", person->getCode()},
      {":name", person->getName()},
      {":inn", person->getInn()},
      {":comments", person->getComments()},
      {":name_first", person->getNameFirst()},
      {":name_second", person->getNameSecond()},
      {":name_third", person->getNameThird()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
