#ifndef USERTOJSON_H
#define USERTOJSON_H

#include "User.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<User> : public ToJsonConverterTemplate<User>
{
public:
  QJsonObject toJson(const UserShared& user) const override;
};

template <>
class ToJsonConverter<UserInRole> : public ToJsonConverterTemplate<UserInRole>
{
public:
  QJsonObject toJson(const UserInRoleShared& userInRole) const override;
};

} // namespace light

#endif // USERTOJSON_H
