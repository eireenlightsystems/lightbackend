#include "EquipmentType.h"
namespace light {

ID EquipmentType::getId() const {
  return id;
}

void EquipmentType::setId(const ID& value) {
  id = value;
}

QString EquipmentType::getCode() const {
  return code;
}

void EquipmentType::setCode(const QString& value) {
  code = value;
}

QString EquipmentType::getName() const {
  return name;
}

void EquipmentType::setName(const QString& value) {
  name = value;
}

QString EquipmentType::getModel() const {
  return model;
}

void EquipmentType::setModel(const QString& value) {
  model = value;
}

QString EquipmentType::getComment() const
{
    return comments;
}

void EquipmentType::setComment(const QString &value)
{
    comments = value;
}

} // namespace light
