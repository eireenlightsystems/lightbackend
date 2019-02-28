#ifndef POSTGRESCONNECTIONINFO_H
#define POSTGRESCONNECTIONINFO_H

#include <QString>


namespace light {
struct PostgresConnectionInfo
{
  QString hostName;
  int port;
  QString databaseName;
  QString userName;
  QString password;
};
} // namespace light

#endif // POSTGRESCONNECTIONINFO_H
