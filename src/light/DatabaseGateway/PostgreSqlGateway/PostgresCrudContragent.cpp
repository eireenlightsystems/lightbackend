#include "PostgresCrudContragent.h"

#include <QSqlRecord>
#include <QVariant>

#include "PostgresCrudGeograph.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> contragentFields {
    {"id_contragent", "id_contragent", true},
    {"code", "code_contragent", false},
    {"name", "name_contragent", false},
    {"inn", "inn_contragent", false},
    {"comments", "comments_contragent", false},

    {"id_geograph", "id_geograph", false},
    {"code_geograph", "code_geograph", false},
};

PostgresCrud<Contragent>::PostgresCrud() {
  setFields(contragentFields);
  setView("contragent_pkg.contragent_vw");
}

Reader<Contragent>::Shared light::PostgresqlGateway::PostgresCrud<Contragent>::parse(const QSqlRecord& record) const {
  auto contragent = ContragentShared::create();
  contragent->setId(record.value(getIdAlias()).value<ID>());
  contragent->setCode(record.value(getFieldAlias("code")).toString());
  contragent->setName(record.value(getFieldAlias("name")).toString());
  contragent->setInn(record.value(getFieldAlias("inn")).toString());
  contragent->setComments(record.value(getFieldAlias("comments")).toString());

  PostgresCrud<Geograph> geographCrud;
  contragent->setGeograph(geographCrud.parse(record));

  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
