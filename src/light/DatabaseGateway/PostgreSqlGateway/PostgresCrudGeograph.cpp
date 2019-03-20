#include "PostgresCrudGeograph.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> geographFields {
    {"id_geograph", "id_geograph", true},
    {"code", "code_geograph", false},
    {"name", "name_geograph", false},
    {"fullname", "fullname_geograph", false},
};

PostgresCrud<Geograph>::PostgresCrud() {
  setFields(geographFields);
  setView("geograph_pkg.geograph_vw");
}

Reader<Geograph>::Shared PostgresCrud<Geograph>::parse(const QSqlRecord& record) const {
  auto geograph = GeographShared::create();
  geograph->setId(record.value(getIdAlias()).value<ID>());
  geograph->setCode(record.value(getFieldAlias("code")).toString());
  geograph->setName(record.value(getFieldAlias("name")).toString());
  geograph->setFullName(record.value(getFieldAlias("fullname")).toString());
  return geograph;
}

} // namespace PostgresqlGateway
} // namespace light
