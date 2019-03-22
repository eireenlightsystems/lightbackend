#include "AbstractRestRouter.h"

#include <QJsonObject>

namespace light {

AbstractRestRouter::~AbstractRestRouter() {
}

QJsonDocument AbstractRestRouter::errorStringToJson(const char* error) {
  return errorStringToJson(QString(error));
}

QJsonDocument AbstractRestRouter::errorStringToJson(const QString& error) {
  QJsonObject errorObject;
  errorObject["message"] = error;
  QJsonDocument jsonDoc(errorObject);
  return jsonDoc;
}

} // namespace light
