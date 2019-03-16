#include "PostgresCrudContragent.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

light::PostgresqlGateway::PostgresCrud<Contragent>::PostgresCrud() {
  setIdField("id_contragent");
  setFields(QStringList() << getIdField() << "code"
			  << "name");
  setView("contragent_pkg.contragent_vw");
}

Reader<Contragent>::Shared light::PostgresqlGateway::PostgresCrud<Contragent>::parse(const QSqlRecord& record) const {
  auto contragent = ContragentShared::create();
  contragent->setId(record.value(0).value<ID>());
  contragent->setCode(record.value(1).toString());
  contragent->setName(record.value(2).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
