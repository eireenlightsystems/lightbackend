#include "BaseConverter.h"

#include "typedefs.h"

#include <QDateTime>
#include <QDebug>
#include <QJsonObject>

namespace light {

bool BaseConverter::getIdValid() const {
  return idValid;
}

void BaseConverter::setIdValid(bool value) {
  idValid = value;
}

QString BaseConverter::getErrorText() const {
  return errorText;
}

QJsonDocument BaseConverter::parseJson(const QByteArray& data) {
  QJsonParseError parseError;
  QJsonDocument jDoc = QJsonDocument::fromJson(data, &parseError);
  if (parseError.error != QJsonParseError::NoError) {
    qDebug() << parseError.errorString();
    setIdValid(false);
    setErrorText(parseError.errorString());
  }
  return jDoc;
}

void BaseConverter::setErrorText(const QString& value) {
  errorText = value;
}

} // namespace light
