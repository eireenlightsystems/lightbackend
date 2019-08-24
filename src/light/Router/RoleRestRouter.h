#ifndef ROLERESTROUTER_H
#define ROLERESTROUTER_H

#include "Role.h"
#include "User.h"
#include "RoleController.h"
#include "RestRouter.h"
#include "SimpleEditableListRouter.h"
#include "PostgresCrudRole.h"
#include "RoleToJson.h"

namespace light {

template <>
class RestRouter<Role> : public SimpleEditableListRouter<Role>
{
public:
  QString getName() const override {
    return "roles";
  }

  QString getChildItemName() const override {
    return "users";
  }

  QHttpServerResponse getListItems(ID listId) override {
    return getListItemsHelper<UserInRole>(listId, "roleId");
  }
};

}

#endif // ROLERESTROUTER_H
