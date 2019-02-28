#ifndef SELECTQUERY_H
#define SELECTQUERY_H

#include "SqlQuery.h"

#include <QSqlRecord>

namespace light {
namespace PostgresqlGateway {
class SelectQuery : public SqlQuery
{
public:
  explicit SelectQuery(const QSqlDatabase& db);

  class Iterator
  {
  public:
    Iterator() {
    }
    explicit Iterator(QSharedPointer<QSqlQuery> query) : query(query) {
      if (query)
	query->next();
    }
    Iterator(const Iterator& other) {
      query = other.query;
    }

    Iterator& operator=(const Iterator& other) {
      query = other.query;
      return *this;
    }

    Iterator& operator++() {
      if (query)
	query->next();
      return *this;
    }
    bool operator!=(const Iterator& other) {
      Q_UNUSED(other)
      return query->isActive() and query->isValid();
    }

    QSqlRecord operator*() const {
      return query->record();
    }

  private:
    QSharedPointer<QSqlQuery> query;
  };
  SelectQuery::Iterator begin();
  SelectQuery::Iterator end();
};
} // namespace PostgresqlGateway
} // namespace light

#endif // SELECTQUERY_H
