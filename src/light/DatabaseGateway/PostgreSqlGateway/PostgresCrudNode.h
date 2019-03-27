#ifndef POSTGRESCRUDNODE_H
#define POSTGRESCRUDNODE_H

#include "Node.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<Node> : public Editor<Node>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;

protected:
  void ins(const Shared& node) const override;
  void upd(const Shared& node) const override;
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;

private:
  void saveChildren(const Shared& node) const;
  void saveFixtures(const Shared& node) const;
  IDList selectFixturesIds(ID nodeId) const;
  void insertFixtures(ID nodeId, const IDList& ids) const;
  void deleteFixtures(const IDList& ids) const;
  void updateFixturesNode(const IDList& fixturesIds, ID nodeId) const;

  void saveGateways(const Shared& node) const;
  IDList selectGatewaysIds(ID nodeId) const;
  void insertGateways(ID nodeId, const IDList& ids) const;
  void deleteGateways(const IDList& ids) const;
  void updateGatewaysNode(const IDList& gatewaysIds, ID nodeId) const;

  void saveSensors(const Shared& node) const;
  IDList selectSensorsIds(ID nodeId) const;
  void insertSensors(ID nodeId, const IDList& ids) const;
  void deleteSensors(const IDList& ids) const;
  void updateSensorsNode(const IDList& gatewaysIds, ID nodeId) const;

  template <typename Container>
  IDList extractIds(const Container& container) const;
  IDList selectIds(const QString& sql, const BindParamsType& params) const;
  void updateObjectNode(const QString& sql, const QString& idFieldName, const IDList& Ids, ID nodeId) const;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODE_H
