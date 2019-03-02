#ifndef BASEJSONCONVERTER_H
#define BASEJSONCONVERTER_H

#include "BaseConverter.h"

namespace light {
class BaseJsonConverter : public BaseConverter
{
public:
  BaseJsonConverter() = default;
  ~BaseJsonConverter() override = default;

  QJsonDocument getJsonDocument() const;

protected:
  void setJsonDocument(const QJsonDocument& value);

private:
  QJsonDocument jsonDocument;
};
} // namespace light
#endif // BASEJSONCONVERTER_H
