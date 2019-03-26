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

struct Field
{
  QString name;
  QString alias;
  bool isId;
};

template <typename T>
class Reader : public SessionOwner
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  Reader() = default;
  ~Reader() override = default;

  virtual Shared selById(ID id) const {
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
      if (id == 1) {
	auto object = Shared::create();
	object->setId(id);
	result << object;
      } else {
	const BindParamsType bindParams{
	    {getIdPlaceholder(), id},
	};
	result << selBase(sql, bindParams);
      }
    }
    return result;
  }
  virtual SharedList sel(const QVariantHash& filters) const {
    return selBase(getSelectSql(), getSelectParams(filters));
  }

  QString getView() const {
    return view;
  }
  void setView(const QString& value) {
    view = value;
  }

  QString getIdPlaceholder() const {
    return QString(":%1").arg(idField.name);
  }

  QList<Field> getFields() const {
    return fields.values();
  }
  void setFields(const QList<Field>& newFields) {
    fields.clear();
    for (const Field& f : newFields) {
      if (f.isId) {
	idField = f;
      }
      fields[f.name] = f;
    }
  }

  virtual Shared parse(const QSqlRecord& record) const = 0;

  bool getLoadChildren() const {
    return loadChildren;
  }
  void setLoadChildren(bool value) {
    loadChildren = value;
  }

protected:
  virtual BindParamsType getSelectParams(const QVariantHash& filters) const {
    Q_UNUSED(filters)
    return BindParamsType();
  }
  virtual QString getSelectByIdSql() const {
    return QString("select %1 from %2 where %3 = :%3").arg(getSelectItems(), view, idField.name);
  }

  virtual QString getSelectSql() const {
    return QString("select %1 from %2").arg(getSelectItems(), view);
  }

  QString getSelectItems() const {
    QStringList selectItems;
    for (const auto& f : fields) {
      selectItems << QString("%1 as %2").arg(f.name, f.alias);
    }
    return selectItems.join(", ");
  }

  SharedList selBase(const QString& sql, const BindParamsType& params) const {
    auto parser = std::bind(&Reader<T>::parse, this, std::placeholders::_1);
    return select<SharedList>(sql, params, parser, this->getSession());
  }

  QString getIdAlias() const {
    return idField.alias;
  }
  QString getFieldAlias(const QString& value) const {
    return fields.value(value).alias;
  }

private:
  QString view;
  QHash<QString, Field> fields;
  Field idField;
  bool loadChildren{true};
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
