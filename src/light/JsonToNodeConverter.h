#ifndef JSONTONODECONVERTER_H
#define JSONTONODECONVERTER_H

#include "BaseConverter.h"
#include "NodeController.h"
#include "typedefs.h"

#include <QGeoCoordinate>

namespace light {

class JsonInsertParametersToNodeConverter : public BaseConverter
{
public:
  JsonInsertParametersToNodeConverter() = default;
  ~JsonInsertParametersToNodeConverter() override = default;
  void convert(const QByteArray& data);

  QList<NodeSaveParameters> getParameters() const;

protected:
  virtual NodeSaveParameters parse(const QJsonObject& jsonObject);

protected:
  QList<NodeSaveParameters> parameters;
};

class JsonUpdateParametersToNodeConverter : public JsonInsertParametersToNodeConverter
{
public:
  JsonUpdateParametersToNodeConverter() = default;
  ~JsonUpdateParametersToNodeConverter() override = default;

protected:
  NodeSaveParameters parse(const QJsonObject& jsonObject) override;
};

class JsonNodeCoordinatesConverter : public BaseConverter
{
public:
  JsonNodeCoordinatesConverter() = default;
  ~JsonNodeCoordinatesConverter() override = default;
  void convert(const QByteArray& data);

  QList<NodeCoordinateParameters> getParameters() const;

protected:
  NodeCoordinateParameters parse(const QJsonObject& jsonObject);

protected:
  QList<NodeCoordinateParameters> parameters;
};

} // namespace light

#endif // JSONTONODECONVERTER_H
