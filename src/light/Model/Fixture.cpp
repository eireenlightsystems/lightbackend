#include "Fixture.h"

namespace light {
bool Fixture::getHasGatewayLink() const {
  return hasGatewayLink;
}

void Fixture::setHasGatewayLink(bool value) {
  hasGatewayLink = value;
}

ID Fixture::getId() const {
  return id;
}

void Fixture::setId(const ID& value) {
  id = value;
}

quint8 Fixture::getStandbyLevel() const {
  return standbyLevel;
}

void Fixture::setStandbyLevel(const quint8& value) {
  standbyLevel = value;
}

quint8 Fixture::getWorkLevel() const {
  return workLevel;
}

void Fixture::setWorkLevel(const quint8& value) {
  workLevel = value;
}

quint8 Fixture::getSpeedUp() const {
  return speedUp;
}

void Fixture::setSpeedUp(const quint8& value) {
  speedUp = value;
}

quint8 Fixture::getSpeedDown() const {
  return speedDown;
}

void Fixture::setSpeedDown(const quint8& value) {
  speedDown = value;
}
} // namespace light
