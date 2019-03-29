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
  SessionShared getSession(const QString& token) const;
  bool isLoggedIn(const QString& token) const;
  QString login(const QString& login, const QString& password);
  void logout(const QString& token);

private:
  PostgresConnectionInfo readConnectionInfoFromSettings() const;
  void openConnection();

private:
  QHash<QString, SessionShared> sessions;
  SessionShared session;
  PostgresConnectionInfo connectionInfo;
};

} // namespace light
#endif // LIGHTBACKEND_H
