#ifndef GEOGRAPHRESTROUTER_H
#define GEOGRAPHRESTROUTER_H

#include "Geograph.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"

namespace light {

template <>
class RestRouter<Geograph> : public SimpleSelectableRouter<Geograph>
{
public:
  constexpr static const char* path = "/api2/geograph";
};

} // namespace light

#endif // GEOGRAPHRESTROUTER_H
