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

light::PostgresqlGateway::PostgresCrud<Contragent>::PostgresCrud() {
  setFields(contragentFields);
  setView("contragent_pkg.contragent_vw");
}

Reader<Contragent>::Shared light::PostgresqlGateway::PostgresCrud<Contragent>::parse(const QSqlRecord& record) const {
  auto contragent = ContragentShared::create();
  contragent->setId(record.value(getIdAlias()).value<ID>());
  contragent->setCode(record.value(getFiledAlias("code_contragent")).toString());
  contragent->setName(record.value(getFiledAlias("name_contragent")).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
