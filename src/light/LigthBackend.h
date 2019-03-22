#ifndef LIGHTBACKEND_H
#define LIGHTBACKEND_H

#include "PostgresConnectionInfo.h"
#include "typedefs.h"

#include <QObject>

namespace light {

class LigthBackend : public QObject
{
  Q_OBJECT
public:
  explicit LigthBackend(QObject* parent = nullptr);
  void init();

  SessionShared getSession() const;

private:
  void initDatabase();
  PostgresConnectionInfo readConnectionInfoFromSettings() const;
  void initPostgres();

private:
  SessionShared session;
};

} // namespace light
#endif // LIGHTBACKEND_H
