#include "PostgresCrudOwner.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <>
ContragentSharedList PostgresCrud<Contragent>::sel(const IDList& ids) const {
  ContragentSharedList result;
  const QString sql = "select id_contragent, code, name "
		      "from contragent_pkg.contragent_vw "
		      "where id_contragent = :id_contragent";
  for (auto id : ids) {
    const BindParamsType bindParams{
	{":id_contragent", id},
    };
    result << selBase(sql, bindParams);
  }
  return result;
}

template <>
ContragentShared PostgresCrud<Contragent>::parse(const QSqlRecord& record) const {
  auto contragent = ContragentShared::create();
  contragent->setId(record.value(0).value<ID>());
  contragent->setCode(record.value(1).toString());
  contragent->setName(record.value(2).toString());
  return contragent;
}

} // namespace PostgresqlGateway
} // namespace light
