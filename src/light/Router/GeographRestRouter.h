#ifndef GEOGRAPHRESTROUTER_H
#define GEOGRAPHRESTROUTER_H

#include "Geograph.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "GeographToJson.h"

namespace light {

template <>
class RestRouter<Geograph> : public SimpleSelectableRouter<Geograph>
{
public:
  QString getName() const override {
    return "geographs";
  }
};

} // namespace light

#endif // GEOGRAPHRESTROUTER_H
