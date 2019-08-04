#ifndef GEOGRAPHFIASRESTROUTER_H
#define GEOGRAPHFIASRESTROUTER_H

#include "GeographFias.h"
#include "GeographFiasController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudGeographFias.h"
#include "GeographFiasToJson.h"

namespace light {

template <>
class RestRouter<GeographFias> : public SimpleEditableRouter<GeographFias>
{
public:
  QString getName() const override {
    return "geographfiases";
  }
};

} // namespace light

#endif // GEOGRAPHFIASRESTROUTER_H
