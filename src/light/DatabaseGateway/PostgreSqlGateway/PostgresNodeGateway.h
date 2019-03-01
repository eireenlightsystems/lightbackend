#ifndef POSTGRESNODEGATEWAY_H
#define POSTGRESNODEGATEWAY_H

#include "AbstractNodeGateway.h"
#include "SqlDatabaseOwner.h"

namespace light {
namespace PostgresqlGateway {
class PostgresNodeGateway : public SqlDatabaseOwner, public AbstractNodeGateway
{
public:
  PostgresNodeGateway() = default;
  NodeShared selectNode(ID id) override;
  NodeSharedList selectNodes(const QList<ID> &ids) override;
  void saveNode(const NodeShared &node) override;
  void saveNodes(const NodeSharedList &nodes) override;
  void deleteNode(const NodeShared &node) override;
  void deleteNodes(const NodeSharedList &nodes) override;

private:
  NodeSharedList selectBase(const QString& sql, const BindParamsType& params) const;
  NodeShared parseNode(const QSqlRecord& record) const;
};
} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESNODEGATEWAY_H
