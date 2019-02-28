#ifndef HTTPSERVERCONVERTERS_H
#define HTTPSERVERCONVERTERS_H

#include "typedefs.h"

#include <QJsonDocument>

namespace light {

class BaseConverter
{
public:
  BaseConverter() = default;
  virtual ~BaseConverter() = default;

  bool getIdValid() const;
  QString getErrorText() const;

protected:
  QJsonDocument parseJson(const QByteArray& data);
  template <typename T>
  T createAndBaseParse(const QJsonObject& object) const;
  void setIdValid(bool value);
  void setErrorText(const QString& value);

private:
  bool idValid{true};
  QString errorText;
};

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

class FixtureLightLevelCommandsToJson : public BaseJsonConverter
{
public:
  ~FixtureLightLevelCommandsToJson() override = default;
  void convert(const FixtureLightLevelCommandSharedList& commands);
};

class JsonToFixtureLightLevelCommands : public BaseConverter
{
public:
  ~JsonToFixtureLightLevelCommands() override = default;
  void convert(const QByteArray& data);
  FixtureLightLevelCommandSharedList getLightLevelCommands() const;

private:
  FixtureLightLevelCommandSharedList lightLevelCommands;
};

class FixtureLightSpeedCommandsToJson : public BaseJsonConverter
{
public:
  ~FixtureLightSpeedCommandsToJson() override = default;
  void convert(const FixtureLightSpeedCommandSharedList& commands);
};

class JsonToFixtureLightSpeedCommands : public BaseConverter
{
public:
  ~JsonToFixtureLightSpeedCommands() override = default;
  void convert(const QByteArray& data);
  FixtureLightSpeedCommandSharedList getLightUpSpeedCommands() const;

private:
  FixtureLightSpeedCommandSharedList lightUpSpeedCommands;
};

class IdsToJson : public BaseConverter
{
public:
  ~IdsToJson() override = default;
  void convert(const QByteArray& data);
  QList<ID> getIds() const;

private:
  QList<ID> ids;
};
} // namespace light
#endif // HTTPSERVERCONVERTERS_H
