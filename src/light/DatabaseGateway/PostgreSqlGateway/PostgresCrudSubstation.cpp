#include "PostgresCrudSubstation.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

const QList<Field> substationFields{
    {"id_substation", "id_substation", true},
    {"code", "code_substation", false},
    {"name", "name_substation", false},
    {"power", "power_substation", false},
};

PostgresCrud<Substation>::PostgresCrud() {
  setFields(substationFields);
  setView("fixture_pkg_i.substation_vw");
}

Reader<Substation>::Shared PostgresCrud<Substation>::parse(const QSqlRecord& record) const {
  auto substation = SubstationShared::create();
  substation->setId(record.value(getIdAlias()).value<ID>());
  substation->setCode(record.value(getFiledAlias("code_substation")).toString());
  substation->setName(record.value(getFiledAlias("name_substation")).toString());
  substation->setPower(record.value(getFiledAlias("power_substation")).toDouble());
  return substation;
}

} // namespace PostgresqlGateway
} // namespace light
