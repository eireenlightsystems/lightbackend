#include "ReportCountFixtureToJson.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<ReportCountFixture>::toJson(const ReportCountFixtureShared& reportCountFixture) const {
  QJsonObject reportCountFixtureJson;
  reportCountFixtureJson["fixtureId"] = QJsonValue::fromVariant(reportCountFixture->getId());
  reportCountFixtureJson["region"] = reportCountFixture->getRegion();
  reportCountFixtureJson["area"] = reportCountFixture->getArea();
  reportCountFixtureJson["city"] = reportCountFixture->getCity();
  reportCountFixtureJson["cityDistrict"] = reportCountFixture->getCityDistrict();
  reportCountFixtureJson["settlement"] = reportCountFixture->getSettlement();
  reportCountFixtureJson["street"] = reportCountFixture->getStreet();
  reportCountFixtureJson["house"] = reportCountFixture->getHouse();
  reportCountFixtureJson["codeContract"] = reportCountFixture->getCodeContract();
  reportCountFixtureJson["codeFixtureType"] = reportCountFixture->getCodeFixtureType();
  reportCountFixtureJson["codeInstaller"] = reportCountFixture->getCodeInstaller();
  reportCountFixtureJson["codeSubstation"] = reportCountFixture->getCodeSubstation();
  reportCountFixtureJson["codeHeightType"] = reportCountFixture->getCodeHeightType();
  reportCountFixtureJson["codeOwner"] = reportCountFixture->getCodeOwner();
  reportCountFixtureJson["countFixture"] = reportCountFixture->getCountFixture();

  return reportCountFixtureJson;
}

} // namespace light
