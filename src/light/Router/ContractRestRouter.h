#ifndef CONTRACTRESTROUTER_H
#define CONTRACTRESTROUTER_H

#include "Contract.h"
#include "ContractController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudContract.h"
#include "ContractToJson.h"

namespace light {

template <>
class RestRouter<Contract> : public SimpleEditableRouter<Contract>
{
public:
  QString getName() const override {
    return "contracts";
  }
};

} // namespace light

#endif // CONTRACTRESTROUTER_H
