#ifndef ROLEINCLUD_H
#define ROLEINCLUD_H


#include "typedefs.h"

namespace light {
class Roleinclud
{
public:
  Roleinclud() = default;

  ID getId() const;
  void setId(const ID& value);

  ID getRoleId() const;
  void setRoleId(const ID& value);

  ID getUserId() const;
  void setUserId(const ID& value);

private:
  ID id{0};
  ID roleId{0};
  ID userId{0};
};
} // namespace light

#endif // ROLEINCLUD_H
