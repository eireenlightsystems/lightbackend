#ifndef USERRESTROUTER_H
#define USERRESTROUTER_H

#include "User.h"
#include "UserController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudUser.h"
#include "UserToJson.h"

namespace light {

template <>
class RestRouter<User> : public SimpleEditableRouter<User>
{
public:
  QString getName() const override {
    return "users";
  }
};

}

#endif // USERRESTROUTER_H
