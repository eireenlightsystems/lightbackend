#include "BaseJsonConverter.h"

namespace light {

QJsonDocument BaseJsonConverter::getJsonDocument() const {
  return jsonDocument;
}

void BaseJsonConverter::setJsonDocument(const QJsonDocument& value) {
  jsonDocument = value;
}

} // namespace light
