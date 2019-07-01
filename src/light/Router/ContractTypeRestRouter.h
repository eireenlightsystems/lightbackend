#ifndef CONTRACTTYPERESTROUTER_H
#define CONTRACTTYPERESTROUTER_H

#include "ContractType.h"
#include "ContractTypeController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudContractType.h"
#include "ContractTypeToJson.h"

namespace light {

template <>
class RestRouter<ContractType> : public SimpleEditableRouter<ContractType>
{
public:
  QString getName() const override {
    return "contracts-types";
  }
};

} // namespace light

#endif // CONTRACTTYPERESTROUTER_H
