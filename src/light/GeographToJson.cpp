#include "GeographToJson.h"

#include "Geograph.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {
void GeographToJson::convert(const GeographSharedList& geographs) {
  QJsonArray jsonGeographs;
  for (const auto& geograph : geographs) {
    QJsonObject geographJson;
    geographJson["id"] = QJsonValue::fromVariant(geograph->getId());
    geographJson["code"] = geograph->getCode();
    geographJson["fullName"] = geograph->getFullName();

    jsonGeographs << geographJson;
  }
  setJsonDocument(QJsonDocument(jsonGeographs));
}
} // namespace light
