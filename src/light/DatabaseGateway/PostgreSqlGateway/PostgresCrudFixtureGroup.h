#ifndef POSTGRESCRUDFIXTUREGROUP_H
#define POSTGRESCRUDFIXTUREGROUP_H

#include "FixtureGroup.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureGroup> : public Editor<FixtureGroup>
{
public:
  PostgresCrud();

protected:
  Shared parse(const QSqlRecord& record) const override;
  SharedList sel(const IDList& ids) const override;
  SharedList sel(const QVariantHash& filters) const override;
  void ins(const Shared& object) const override;
  void upd(const Shared& object) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;

private:
  FixtureSharedList selectFixtures(const FixtureGroupShared& fixtureGroup) const;
  QSet<ID> selectCurrentFixtureIds(const FixtureGroupShared& fixtureGroup) const;
  void insertNewFixtureToGroup(const QSet<ID> idsToInsert, const FixtureGroupShared& fixtureGroup) const;
  void deleteFixtureFromGroup(const QSet<ID> idsToDelete, const FixtureGroupShared& fixtureGroup) const;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTUREGROUP_H
