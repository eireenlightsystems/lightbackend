#ifndef TOJSONCONVERTER_H
#define TOJSONCONVERTER_H

#include "BaseJsonConverter.h"

#include <QJsonArray>
#include <QJsonObject>

namespace light {

template <typename T>
class ToJsonConverter;

template <typename T>
class ToJsonConverterTemplate : public BaseJsonConverter
{
public:
  using SharedObject = QSharedPointer<T>;
  using SharedObjectList = QList<SharedObject>;

  ToJsonConverterTemplate() = default;
  ~ToJsonConverterTemplate() override = default;
  void convert(const SharedObjectList& objects);

protected:
  virtual QJsonObject toJson(const SharedObject& object) const = 0;
};

template <typename T>
void ToJsonConverterTemplate<T>::convert(const SharedObjectList& objects) {
  QJsonArray jsonObjects;
  for (const auto& o : objects) {
    jsonObjects << toJson(o);
  }
  setJsonDocument(QJsonDocument(jsonObjects));
}
} // namespace light

#endif // TOJSONCONVERTER_H
