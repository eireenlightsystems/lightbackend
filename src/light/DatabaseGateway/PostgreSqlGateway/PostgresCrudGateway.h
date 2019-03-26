#ifndef POSTGRESCRUDGATEWAY_H
#define POSTGRESCRUDGATEWAY_H

#include "Gateway.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Gateway> : public Editor<Gateway>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  void ins(const Shared& gateway) const override;
  void upd(const Shared& gateway) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;

private:
  void saveChildNodes(const Shared& gateway) const;
  void insertNewChildNodes(const QSet<ID>& idsToInsert, const GatewayShared& gateway) const;
  void deleteChildNodes(const QSet<ID>& idsToDelete, const GatewayShared& gateway) const;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDGATEWAY_H
