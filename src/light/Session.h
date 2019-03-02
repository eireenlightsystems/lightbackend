#ifndef SESSION_H
#define SESSION_H

#include <QSqlDatabase>
#include <QString>

namespace light {
class Session
{
public:
  Session();

  QString getName() const;
  void setName(const QString& value);

  QSqlDatabase getDb() const;
  void setDb(const QSqlDatabase& value);

private:
  QString name;
  QSqlDatabase db;
};
} // namespace light

#endif // SESSION_H
