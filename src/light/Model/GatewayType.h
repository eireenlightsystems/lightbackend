#ifndef GATEWAYTYPE_H
#define GATEWAYTYPE_H

#include "EquipmentType.h"

namespace light {
class GatewayType : public EquipmentType
{
public:
  GatewayType() = default;

  QString getCommunicationStandard() const;
  void setCommunicationStandard(QString value);

private:
  QString communicationStandard;
};
} // namespace light

#endif // GATEWAYTYPE_H
