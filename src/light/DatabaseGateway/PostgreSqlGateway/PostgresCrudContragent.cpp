#include "PostgresCrudContragent.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> contragentFields {
    {"id_contragent", "id_contragent", true},
    {"code", "code_contragent", false},
    {"name", "name_contragent", false},
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
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
