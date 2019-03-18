#ifndef POSTGRESDEVICEERRORSAVER_H
#define POSTGRESDEVICEERRORSAVER_H

#include "AbstractDeviceErrorSaver.h"
#include "PostgresConnectionInfo.h"
#include "SharedTypes.h"

#include <QSqlDatabase>
#include <QString>

namespace DeviceMessageReceiver {
class PostgresDeviceErrorSaver : public AbstractDeviceErrorSaver
{
public:
  PostgresDeviceErrorSaver() = default;
  void saveError(const DeviceError& error) override;
  bool open(const light::PostgresConnectionInfo& connectionInfo);

private:
  ID findFixtureId(const DeviceError& error);
  void insertFixtureProblem(ID fixtureId, quint8 errorCode);

private:
  QSqlDatabase db;
};
} // namespace light

#endif // POSTGRESDEVICEERRORSAVER_H
