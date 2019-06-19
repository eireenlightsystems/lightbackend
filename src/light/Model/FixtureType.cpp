#include "FixtureType.h"

namespace light {

double FixtureType::getHeight() const {
  return height;
}

void FixtureType::setHeight(double value) {
  height = value;
}

double FixtureType::getWidth() const {
  return width;
}

void FixtureType::setWidth(double value) {
  width = value;
}

double FixtureType::getWeight() const {
  return weight;
}

void FixtureType::setWeight(double value) {
  weight = value;
}

double FixtureType::getLength() const {
  return length;
}

void FixtureType::setLength(double value) {
  length = value;
}


double FixtureType::getCountlamp() const {
  return countlamp;
}

void FixtureType::setCountlamp(double value) {
  countlamp = value;
}

double FixtureType::getPower() const {
  return power;
}

void FixtureType::setPower(double value) {
  power = value;
}

double FixtureType::getCos() const {
  return cos;
}

void FixtureType::setCos(double value) {
  cos = value;
}

double FixtureType::getIp() const {
  return ip;
}

void FixtureType::setIp(double value) {
  ip = value;
}

double FixtureType::getEfficiency() const {
  return efficiency;
}

void FixtureType::setEfficiency(double value) {
  efficiency = value;
}
} // namespace light
