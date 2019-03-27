#ifndef AUTHROUTER_H
#define AUTHROUTER_H

#include "AbstractRestRouter.h"

namespace light {

class AuthRouter : public AbstractRestRouter
{
public:
  AuthRouter() = default;
  ~AuthRouter() override = default;
  void registerApi(QHttpServer& httpServer) const override;
  QString getName() const override;
};
} // namespace light

#endif // AUTHROUTER_H
