#include "PostgresCrudSubstation.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

PostgresCrud<Substation>::PostgresCrud() {
  setIdField("id_substation");
  setFields(QStringList() << getIdField() << "code"
			  << "name"
			  << "power");
  setView("fixture_pkg_i.substation_vw");
}

Reader<Substation>::Shared PostgresCrud<Substation>::parse(const QSqlRecord& record) const {
  auto substation = SubstationShared::create();
  substation->setId(record.value(0).value<ID>());
  substation->setCode(record.value(1).toString());
  substation->setName(record.value(2).toString());
  substation->setPower(record.value(3).toDouble());
  return substation;
}

} // namespace PostgresqlGateway
} // namespace light
