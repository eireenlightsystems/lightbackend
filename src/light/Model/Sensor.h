#ifndef SENSOR_H
#define SENSOR_H

#include "Contract.h"
#include "Contragent.h"
#include "NodeChild.h"
#include "typedefs.h"

namespace light {

class SensorContract : public Contract
{
public:
  SensorContract() = default;
  explicit SensorContract(const Contract& other) : Contract(other) {
  }
};

class SensorOwner : public Contragent
{
public:
  SensorOwner() = default;
  explicit SensorOwner(const Contragent& other) : Contragent(other) {
  }
};

class Sensor : public NodeChild
{
public:
  Sensor() = default;

  ID getId() const;
  void setId(const ID& value);

  SensorTypeShared getType() const;
  ID getTypeId() const;
  void setType(const SensorTypeShared& value);

private:
  ID id{0};
  SensorTypeShared type;
};
} // namespace light
#endif // SENSOR_H
