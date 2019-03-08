#ifndef FROMJSONCONVERTER_H
#define FROMJSONCONVERTER_H

#include "BaseConverter.h"

#include <QJsonArray>
#include <QJsonObject>

namespace light {

template <typename T>
class FromJsonConverter : public BaseConverter
{
public:
  FromJsonConverter() = default;
  ~FromJsonConverter() override = default;
  void convert(const QByteArray& data);
  static T parse(const QJsonObject& jsonObject);

  QList<T> getParameters() const;

private:
  QList<T> parameters;
};

template <typename T>
void FromJsonConverter<T>::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid())
    return;

  if (jDoc.isArray()) {
    auto paramsArray = jDoc.array();
    for (const auto jsonValue : paramsArray) {
      auto jsonObject = jsonValue.toObject();
      parameters << parse(jsonObject);
    }
  } else {
    auto jsonObject = jDoc.object();
    parameters << parse(jsonObject);
  }
}

template <typename T>
QList<T> FromJsonConverter<T>::getParameters() const {
  return parameters;
}
} // namespace light

#endif // FROMJSONCONVERTER_H
