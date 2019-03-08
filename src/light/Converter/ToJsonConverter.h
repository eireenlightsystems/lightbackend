#ifndef TOJSONCONVERTER_H
#define TOJSONCONVERTER_H

#include "BaseJsonConverter.h"

#include <QJsonArray>
#include <QJsonObject>

namespace light {

template <typename T>
class ToJsonConverter : public BaseJsonConverter
{
public:
  using SharedObject = QSharedPointer<T>;
  using SharedObjectList = QList<SharedObject>;

  ToJsonConverter() = default;
  ~ToJsonConverter() override = default;
  void convert(const SharedObjectList& objects);

protected:
  QJsonObject toJson(const SharedObject& object) const;
};

template <typename T>
void ToJsonConverter<T>::convert(const SharedObjectList& objects) {
  QJsonArray jsonObjects;
  for (const auto& o : objects) {
    jsonObjects << toJson(o);
  }
  setJsonDocument(QJsonDocument(jsonObjects));
}
} // namespace light

#endif // TOJSONCONVERTER_H
