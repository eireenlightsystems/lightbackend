#ifndef POSTGRESCRUDFIXTURECOMMAND_H
#define POSTGRESCRUDFIXTURECOMMAND_H

#include "FixtureCommand.h"
#include "PostgresCrud.h"

namespace light {
namespace PostgresqlGateway {

template <>
class PostgresCrud<FixtureCommand> : public Editor<FixtureCommand>
{
public:
  PostgresCrud();
  Shared selById(ID id) const override;
  SharedList sel() const override;
  SharedList sel(const IDList& ids) const override;
  SharedList sel(const QVariantHash& filters) const override;

  void save(const SharedList& objects) const override;
  void save(const Shared& object) const override;
  Shared parse(const QSqlRecord& record) const override;

protected:
  BindParamsType getSelectParams(const QVariantHash& filters) const override;
  BindParamsType getInsertParams(const Shared& object) const override;
  BindParamsType getUpdateParams(const Shared& object) const override;
};

template <>
class PostgresCrud<FixtureCommandStatus> : public Reader<FixtureCommandStatus>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

template <>
class PostgresCrud<FixtureCommandType> : public Reader<FixtureCommandType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

template <>
class PostgresCrud<FixtureLightLevelCommandType> : public Reader<FixtureLightLevelCommandType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

template <>
class PostgresCrud<FixtureLightSpeedCommandType> : public Reader<FixtureLightSpeedCommandType>
{
public:
  PostgresCrud();
  Shared parse(const QSqlRecord& record) const override;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUDFIXTURECOMMAND_H
