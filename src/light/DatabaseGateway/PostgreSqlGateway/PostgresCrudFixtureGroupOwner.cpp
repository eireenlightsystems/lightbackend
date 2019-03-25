#include "PostgresCrudFixtureGroupOwner.h"

#include "PostgresCrudContragent.h"

namespace light {
namespace PostgresqlGateway {

const QList<Field> gatewayTypeFields{
    {"id_owner", "id_contragent", true},
    {"code_owner", "code_contragent", false},
    {"name_owner", "name_contragent", false},
};

PostgresCrud<FixtureGroupOwner>::PostgresCrud() {
  setFields(gatewayTypeFields);
  setView("fixture_group_pkg_i.owner_vw");
}

Reader<FixtureGroupOwner>::Shared PostgresCrud<FixtureGroupOwner>::parse(const QSqlRecord& record) const {
  PostgresCrud<Contragent> contragentCrud;
  auto contragent = contragentCrud.parse(record);
  FixtureGroupOwnerShared fixtureGroupOwner = FixtureGroupOwnerShared::create(*contragent);
  return fixtureGroupOwner;
}

} // namespace PostgresqlGateway
} // namespace light
