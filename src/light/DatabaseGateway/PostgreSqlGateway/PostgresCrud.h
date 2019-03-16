#ifndef POSTGRESCRUD_H
#define POSTGRESCRUD_H

#include "DeleteQuery.h"
#include "InsertQuery.h"
#include "SelectQuery.h"
#include "Session.h"
#include "SessionOwner.h"
#include "UpdateQuery.h"
#include "typedefs.h"

#include <QSqlRecord>
#include <QVariant>

namespace light {
namespace PostgresqlGateway {

template <typename T>
class PostgresCrud;

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

template <typename T>
class Reader : public SessionOwner
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Reader() = default;
  ~Reader() override = default;

  Shared selById(ID id) const {
    auto objects = sel(IDList{id});
    if (objects.count()) {
      return objects.first();
    }

    return Shared();
  }
  virtual SharedList sel() const {
    return sel(QVariantHash());
  }
  virtual SharedList sel(const IDList& ids) const {
    SharedList result;
    const QString sql = getSelectByIdSql();
    for (auto id : ids) {
      const BindParamsType bindParams{
	  {getIdPlaceholder(), id},
      };
      result << selBase(sql, bindParams);
    }
    return result;
  }
  virtual SharedList sel(const QVariantHash& filters) const {
    return selBase(getSelectSql(), getSelectParams(filters));
  }

  QStringList getFields() const {
    return fields;
  }
  void setFields(const QStringList& value) {
    fields = value;
  }

  QString getIdField() const {
    return idField;
  }
  void setIdField(const QString& value) {
    idField = value;
  }

  QString getView() const {
    return view;
  }
  void setView(const QString& value) {
    view = value;
  }

  QString getIdPlaceholder() const {
    return QString(":%1").arg(idField);
  }

protected:
  virtual Shared parse(const QSqlRecord& record) const = 0;
  virtual BindParamsType getSelectParams(const QVariantHash& filters) const {
    Q_UNUSED(filters)
    return BindParamsType();
  }
  QString getSelectByIdSql() const {
    return QString("select %1 from %2 where %3 = :%3").arg(fields.join(", "), view, idField);
  }

  QString getSelectSql() const {
    return QString("select %1 from %2").arg(fields.join(", "), view);
  }

  SharedList selBase(const QString& sql, const BindParamsType& params) const {
    auto parser = std::bind(&Reader<T>::parse, this, std::placeholders::_1);
    return select<SharedList>(sql, params, parser, this->getSession());
  }

private:
  QStringList fields;
  QString idField;
  QString view;
};

template <typename T>
class Editor : public Reader<T>
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Editor() = default;
  ~Editor() override = default;

  virtual void save(const SharedList& objects) const {
    try {
      this->getSession()->getDb().transaction();
      for (auto object : objects) {
	if (object->getId()) {
	  upd(object);
	} else {
	  ins(object);
	}
      }
      this->getSession()->getDb().commit();
    } catch (...) {
      this->getSession()->getDb().rollback();
      throw;
    }
  }
  virtual void save(const Shared& object) const {
    save(SharedList{object});
  }
  virtual void del(const SharedList& objects) const {
    QVariantList bindIds;
    std::transform(objects.begin(), objects.end(), std::back_inserter(bindIds), [](const Shared& object) {
      return QVariant(object->getId());
    });
    BindParamsType bindParams{
	{":id", bindIds},
    };
    buildAndExecBatchQuery<DeleteQuery>(deleteSql, bindParams, this->getSession());
  }

  QString getDeleteSql() const {
    return deleteSql;
  }

  void setDeleteSql(const QString& value) {
    deleteSql = value;
  }

  QString getInsertSql() const {
    return insertSql;
  }

  void setInsertSql(const QString& value) {
    insertSql = value;
  }

  QString getUpdateSql() const {
    return updateSql;
  }

  void setUpdateSql(const QString& value) {
    updateSql = value;
  }

protected:
  virtual void ins(const Shared& object) const {
    auto query = buildAndExecQuery<InsertQuery>(insertSql, getInsertParams(object), this->getSession());
    object->setId(query.getInsertedId());
  }
  virtual void upd(const Shared& object) const {
    buildAndExecQuery<UpdateQuery>(updateSql, getUpdateParams(object), this->getSession());
  }
  virtual BindParamsType getInsertParams(const Shared& object) const = 0;
  virtual BindParamsType getUpdateParams(const Shared& object) const = 0;

private:
  QString deleteSql;
  QString insertSql;
  QString updateSql;
};

} // namespace PostgresqlGateway
} // namespace light

#endif // POSTGRESCRUD_H
