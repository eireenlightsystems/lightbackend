#ifndef COMMANDRESTROUTER_H
#define COMMANDRESTROUTER_H

#include "FixtureCommand.h"
#include "FixtureCommandController.h"
#include "PostgresCrudFixtureCommand.h"
#include "PostgresCrudFixtureLightLevelCommand.h"
#include "PostgresCrudFixtureLightSpeedCommand.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"

namespace light {

template <>
class RestRouter<FixtureCommand> : public SimpleEditableRouter<FixtureCommand>
{
public:
  constexpr static const char* path = "/api2/fixture-command";
  QHttpServerResponse get(ID id) override;
  QHttpServerResponse get(const QHttpServerRequest& req) override;
  QHttpServerResponse post(const QHttpServerRequest& req) const override;
  QHttpServerResponse patch(const QHttpServerRequest& req) const override;
  QHttpServerResponse patch(const QHttpServerRequest& req, ID id) const override;
};

template <typename T>
class FixtureCommandRouter : public SimpleEditableRouter<T>
{
public:
  QVariantHash parseUrlQuery(const QUrlQuery& urlQuery) const override {
    QVariantHash params;
    for (const auto& item : urlQuery.queryItems()) {
      const QStringList datetimes{"startDateTime", "endDateTime"};
      QVariant value;
      if (datetimes.contains(item.first)) {
	value = QDateTime::fromString(item.second, Qt::ISODate);
      } else {
	value = item.second.isEmpty() ? QVariant() : QVariant(item.second.toULongLong());
      }
      params[item.first] = value;
    }
    return params;
  }
};

template <>
class RestRouter<FixtureLightLevelCommand> : public FixtureCommandRouter<FixtureLightLevelCommand>
{
public:
  constexpr static const char* path = "/api2/fixture-lightlevel-command";
};

template <>
class RestRouter<FixtureLightSpeedCommand> : public FixtureCommandRouter<FixtureLightSpeedCommand>
{
public:
  constexpr static const char* path = "/api2/fixture-lightspeed-command";
};

} // namespace light

#endif // COMMANDRESTROUTER_H
