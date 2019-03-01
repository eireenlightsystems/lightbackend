#ifndef EQUIPMENTTYPE_H
#define EQUIPMENTTYPE_H

#include "typedefs.h"

namespace light {
class EquipmentType
{
public:
  EquipmentType() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getModel() const;
  void setModel(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
  QString model;
};
} // namespace light

#endif // EQUIPMENTTYPE_H
