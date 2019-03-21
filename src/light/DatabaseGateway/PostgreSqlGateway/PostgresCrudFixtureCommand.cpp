#include "PostgresCrudFixtureCommand.h"

#include "NotImplementedException.h"

namespace light {
namespace PostgresqlGateway {

PostgresCrud<FixtureCommand>::PostgresCrud() {
  setDeleteSql("select fixture_command_pkg_i.del(:id)");
}

Editor<FixtureCommand>::Shared PostgresCrud<FixtureCommand>::selById(ID id) const {
  Q_UNUSED(id)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel() const {
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel(const IDList& ids) const {
  Q_UNUSED(ids)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::SharedList PostgresCrud<FixtureCommand>::sel(const QVariantHash& filters) const {
  Q_UNUSED(filters)
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresCrud<FixtureCommand>::save(const Editor::SharedList& objects) const {
  Q_UNUSED(objects)
  throw NotImplementedException(Q_FUNC_INFO);
}

void PostgresCrud<FixtureCommand>::save(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

Editor<FixtureCommand>::Shared PostgresCrud<FixtureCommand>::parse(const QSqlRecord& record) const {
  Q_UNUSED(record)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getSelectParams(const QVariantHash& filters) const {
  Q_UNUSED(filters)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getInsertParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

BindParamsType PostgresCrud<FixtureCommand>::getUpdateParams(const Editor::Shared& object) const {
  Q_UNUSED(object)
  throw NotImplementedException(Q_FUNC_INFO);
}

} // namespace PostgresqlGateway
} // namespace light
