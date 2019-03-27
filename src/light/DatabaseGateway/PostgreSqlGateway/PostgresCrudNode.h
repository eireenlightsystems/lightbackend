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
  void saveChildren();
  void saveFixtures();
  void insertFixtures();
  void deleteFixtures();
  void saveGateways();
  void insertGateways();
  void deleteGateways();
  void saveSensors();
  void insertSensors();
  void deleteSensors();
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDNODE_H
