#ifndef POSTGRESCRUD_H
#define POSTGRESCRUD_H

#include "SelectQuery.h"
#include "Session.h"
#include "typedefs.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <typename Query>
Query buildAndExecQuery(const QString& sql, const BindParamsType& bindParams, SessionShared session);

template <typename Query>
Query buildAndExecBatchQuery(const QString& sql, const BindParamsType& bindParams, SessionShared session);

template <typename Collection, typename ParseFunction>
Collection select(const QString& sql, const BindParamsType params, ParseFunction parseFunction, SessionShared session);

template <typename T>
class PostgresCrud
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  PostgresCrud() = default;
  ~PostgresCrud() = default;

  Shared selById(ID id) const;
  SharedList sel(const IDList& ids) const;
  template <typename... Args>
  SharedList sel(Args...) const;

  void save(const SharedList& objects) const;
  void save(const Shared& object) const;

  void del(const SharedList& objects) const;

  SessionShared getSession() const;
  void setSession(const SessionShared& value);

protected:
  SharedList selBase(const QString& sql, const BindParamsType& params) const;
  Shared parse(const QSqlRecord& record) const;
  void ins(const Shared& object) const;
  void upd(const Shared& object) const;

private:
  SessionShared session;
};

template <typename T>
typename PostgresCrud<T>::SharedList PostgresCrud<T>::selBase(const QString& sql, const BindParamsType& params) const {
  auto parser = std::bind(&PostgresCrud<T>::parse, this, std::placeholders::_1);
  return select<SharedList>(sql, params, parser, session);
}

template <typename T>
typename PostgresCrud<T>::Shared PostgresCrud<T>::selById(ID id) const {
  auto objects = sel(IDList{id});
  if (objects.count()) {
    return objects.first();
  }

  return Shared();
}

template <typename T>
void PostgresCrud<T>::save(const PostgresCrud::SharedList& objects) const {
  try {
    session->getDb().transaction();
    for (auto object : objects) {
      if (object->getId()) {
	upd(object);
      } else {
	ins(object);
      }
    }
    session->getDb().commit();
  } catch (...) {
    session->getDb().rollback();
    throw;
  }
}

template <typename T>
void PostgresCrud<T>::save(const Shared& object) const {
  save(SharedList{object});
}

template <typename T>
SessionShared PostgresCrud<T>::getSession() const {
  return session;
}

template <typename T>
void PostgresCrud<T>::setSession(const SessionShared& value) {
  session = value;
}

template <typename Query>
Query buildAndExecQuery(const QString& sql, const BindParamsType& bindParams, SessionShared session) {
  Query query(session->getDb());
  query.prepare(sql);
  query.bind(bindParams);
  query.exec();
  return query;
}

template <typename Query>
Query buildAndExecBatchQuery(const QString& sql, const BindParamsType& bindParams, SessionShared session) {
  Query query(session->getDb());
  query.prepare(sql);
  query.bind(bindParams);
  query.execBatch();
  return query;
}

template <typename Collection, typename ParseFunction>
Collection select(const QString& sql, const BindParamsType params, ParseFunction parseFunction, SessionShared session) {
  Collection result;
  auto query = buildAndExecQuery<SelectQuery>(sql, params, session);
  for (const auto& record : query) {
    result << parseFunction(record);
  }
  return result;
}

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUD_H
