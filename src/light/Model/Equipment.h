#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "typedefs.h"

namespace light {
class Equipment
{
public:
  Equipment() = default;
  virtual ~Equipment() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getComment() const;
  void setComment(const QString& value);

  ContractShared getContract() const;
  ID getContractId() const;
  void setContract(const ContractShared& value);

  EquipmentOwnerShared getOwner() const;
  ID getOwnerId() const;
  void setOwner(const EquipmentOwnerShared& value);

  virtual GeographShared getGeograph() const = 0;
  ID getGeographId() const;

  QString getSerialNumber() const;
  void setSerialNumber(const QString& value);

private:
  ID id{0};
  QString serialNumber;
  QString comment;
  ContractShared contract;
  EquipmentOwnerShared owner;
};
} // namespace light

#endif // EQUIPMENT_H
