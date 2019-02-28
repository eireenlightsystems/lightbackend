#ifndef FIXTURE_H
#define FIXTURE_H

#include "typedefs.h"

namespace light {
class Fixture
{
public:
  Fixture() = default;

  bool getHasGatewayLink() const;
  void setHasGatewayLink(bool value);

  ID getId() const;
  void setId(const ID& value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(const quint8& value);

  quint8 getWorkLevel() const;
  void setWorkLevel(const quint8& value);

  quint8 getSpeedUp() const;
  void setSpeedUp(const quint8& value);

  quint8 getSpeedDown() const;
  void setSpeedDown(const quint8& value);

private:
  ID id;
  bool hasGatewayLink{false};
  quint8 standbyLevel{0};
  quint8 workLevel{0};
  quint8 speedUp{0};
  quint8 speedDown{0};
};
} // namespace light

#endif // FIXTURE_H
