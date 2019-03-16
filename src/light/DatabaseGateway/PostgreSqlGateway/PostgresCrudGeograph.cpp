#include "PostgresCrudGeograph.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<Geograph>::PostgresCrud() {
  setIdField("id_geograph");
  setFields(QStringList() << getIdField() << "code"
			  << "name"
			  << "fullname");
  setView("geograph_pkg.geograph_vw");
}

Reader<Geograph>::Shared PostgresCrud<Geograph>::parse(const QSqlRecord& record) const {
  auto geograph = GeographShared::create();
  geograph->setId(record.value(0).value<ID>());
  geograph->setCode(record.value(1).toString());
  geograph->setName(record.value(2).toString());
  geograph->setFullName(record.value(3).toString());
  return geograph;
}

} // namespace PostgresqlGateway
} // namespace light
