#ifndef ROLERIGHT_H
#define ROLERIGHT_H


#include "typedefs.h"

namespace light {
class Roleright
{
public:
  Roleright() = default;

  ID getId() const;
  void setId(const ID& value);

  ID getComponentId() const;
  void setComponentId(const ID& value);

  ID getRoleId() const;
  void setRoleId(const ID& value);

  QString getComponentCode() const;
  void setComponentCode(const QString& value);

  QString getComponentName() const;
  void setComponentName(const QString& value);

  QString getComponentComments() const;
  void setComponentComments(const QString& value);

  QString getRoleName() const;
  void setRoleName(const QString& value);

  QString getRights() const;
  void setRights(const QString& value);

private:
  ID id{0};
  ID componentId{0};
  ID roleId{0};
  QString componentCode;
  QString componentName;
  QString componentComments;
  QString roleName;
  QString rights;
};
} // namespace light

#endif // ROLERIGHT_H
