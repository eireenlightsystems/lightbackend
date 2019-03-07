#ifndef JSONTOGATEWAYCONVERTER_H
#define JSONTOGATEWAYCONVERTER_H

#include "BaseConverter.h"
#include "GatewayController.h"

namespace light {

class JsonInsertParametersToGatewayConverter : public BaseConverter
{
public:
  JsonInsertParametersToGatewayConverter() = default;
  ~JsonInsertParametersToGatewayConverter() override = default;
  void convert(const QByteArray& data);

  QList<GatewaySaveParameters> getParameters() const;

protected:
  virtual GatewaySaveParameters parse(const QJsonObject& jsonObject);

protected:
  QList<GatewaySaveParameters> parameters;
};

class JsonUpdateParametersToGatewayConverter : public BaseConverter
{
public:
  JsonUpdateParametersToGatewayConverter() = default;
  ~JsonUpdateParametersToGatewayConverter() override = default;
  void convert(const QByteArray& data);

  QList<GatewaySaveParameters> getParameters() const;

protected:
  virtual GatewaySaveParameters parse(const QJsonObject& jsonObject);

protected:
  QList<GatewaySaveParameters> parameters;
};
} // namespace light

#endif // JSONTOGATEWAYCONVERTER_H
