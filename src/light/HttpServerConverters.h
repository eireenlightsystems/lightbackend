#ifndef HTTPSERVERCONVERTERS_H
#define HTTPSERVERCONVERTERS_H

#include "BaseJsonConverter.h"
#include "typedefs.h"

namespace light {

class JsonToFuxtureCommandBaseConverter : public BaseConverter
{
protected:
  template <typename T>
  T createAndBaseParse(const QJsonObject& object) const;
};

class FixtureLightLevelCommandsToJson : public BaseJsonConverter
{
public:
  ~FixtureLightLevelCommandsToJson() override = default;
  void convert(const FixtureLightLevelCommandSharedList& commands);
};

class JsonToFixtureLightLevelCommands : public JsonToFuxtureCommandBaseConverter
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

class JsonToFixtureLightSpeedCommands : public JsonToFuxtureCommandBaseConverter
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
