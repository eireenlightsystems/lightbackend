#ifndef CONTRACTROUTER_H
#define CONTRACTROUTER_H

#include "Contract.h"
#include "RestRouter.h"
#include "SimpleSelectableRouter.h"
#include "ContractToJson.h"

namespace light {

template <>
class RestRouter<Contract> : public SimpleSelectableRouter<Contract>
{
public:
  QString getName() const override {
    return "contracts";
  }
};

} // namespace light

#endif // CONTRACTROUTER_H
