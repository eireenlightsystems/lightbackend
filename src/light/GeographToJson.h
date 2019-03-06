#ifndef GROGRAPHTOJSON_H
#define GROGRAPHTOJSON_H

#include "BaseJsonConverter.h"
#include "typedefs.h"

namespace light {
class GeographToJson : public BaseJsonConverter
{
public:
  GeographToJson() = default;
  ~GeographToJson() override = default;
  void convert(const GeographSharedList &geographs);
};
} // namespace light

#endif // GROGRAPHTOJSON_H
