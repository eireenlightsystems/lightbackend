#include "ReportPowerFixtureToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<ReportPowerFixture>::toJson(const ReportPowerFixtureShared& reportPowerFixture) const {
  QJsonObject reportPowerFixtureJson;
  reportPowerFixtureJson["year"] = QJsonValue::fromVariant(reportPowerFixture->getYear());
  reportPowerFixtureJson["monthName"] = QJsonValue::fromVariant(reportPowerFixture->getMonthName());
  reportPowerFixtureJson["fixtureId"] = QJsonValue::fromVariant(reportPowerFixture->getFixtureId());
  reportPowerFixtureJson["hours"] = QJsonValue::fromVariant(reportPowerFixture->getHours());
  reportPowerFixtureJson["kw"] = QJsonValue::fromVariant(reportPowerFixture->getKw());
  reportPowerFixtureJson["rub"] = QJsonValue::fromVariant(reportPowerFixture->getRub());

  return reportPowerFixtureJson;
}

} // namespace light
