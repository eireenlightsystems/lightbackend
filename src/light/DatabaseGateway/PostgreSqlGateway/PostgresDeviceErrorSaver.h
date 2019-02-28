#ifndef POSTGRESDEVICEERRORSAVER_H
#define POSTGRESDEVICEERRORSAVER_H

#include "AbstractDeviceErrorSaver.h"
#include "PostgresConnectionInfo.h"
#include "SharedTypes.h"

#include <QSqlDatabase>
#include <QString>

namespace light {
class PostgresDeviceErrorSaver : public AbstractDeviceErrorSaver
{
public:
  PostgresDeviceErrorSaver() = default;
  void saveError(const DeviceError& error) override;
  bool open(const PostgresConnectionInfo& connectionInfo);

private:
  ID findFixtureId(const DeviceError& error);
  void insertFixtureProblem(ID fixtureId, quint8 errorCode);

private:
  QSqlDatabase db;
};
} // namespace light

#endif // POSTGRESDEVICEERRORSAVER_H
