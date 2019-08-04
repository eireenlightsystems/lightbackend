#include "PostgresCrudPerson.h"

#include <QSqlRecord>
#include <QVariant>

#include "PostgresCrudContragent.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> personFields{
    {"id_contragent", "id_contragent", true},
    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
    {"name_geograph", "name_geograph", false},
    {"fullname_geograph", "fullname_geograph", false},
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
  setInsertSql("select person_pkg_i.save(:action, :id_contragent, :id_geograph, :code, :inn, :comments, :name_first, :name_second, :name_third)");
  setUpdateSql(getInsertSql());
  setDeleteSql("select person_pkg_i.del(:id)");
}

Reader<Person>::Shared PostgresCrud<Person>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  contragentCrud.setFields({
      {"id_contragent", "id_contragent", true},
      {"id_geograph", "id_geograph", false},
      {"code_geograph", "code_geograph", false},
      {"name_geograph", "name_geograph", false},
      {"fullname_geograph", "fullname_geograph", false},
      {"code", "code_person", false},
      {"name", "name_person", false},
      {"inn", "inn_person", false},
      {"comments", "comments_person", false},
  });
  const auto contragent = contragentCrud.parse(record);

  auto person = PersonShared::create(*contragent);

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
      {":id_geograph", person->getGeographId()},
      {":code", person->getCode()},
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
      {":id_contragent", person->getId()},
      {":id_geograph", person->getGeographId()},
      {":code", person->getCode()},
      {":inn", person->getInn()},
      {":comments", person->getComments()},
      {":name_first", person->getNameFirst()},
      {":name_second", person->getNameSecond()},
      {":name_third", person->getNameThird()},
  };
}

} // namespace PostgresqlGateway
} // namespace light
