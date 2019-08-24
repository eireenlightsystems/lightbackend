#ifndef POSTGRESCRUDROLE_H
#define POSTGRESCRUDROLE_H


#include "Role.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Role> : public Editor<Role>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
  SharedList sel(const IDList& ids) const override;
  SharedList sel(const QVariantHash& filters) const override;

protected:
  void ins(const Shared& object) const override;
  void upd(const Shared& object) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;

private:
  UserSharedList selectUsers(const RoleShared& role) const;
  QSet<ID> selectCurrentUserIds(const RoleShared& role) const;
  void insertNewUserToRole(const QSet<ID> idsToInsert, const RoleShared& role) const;
  void deleteUserFromRole(const QSet<ID> idsToDelete, const RoleShared& role) const;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDROLE_H
