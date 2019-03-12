#include "FixtureType.h"

namespace light {

double FixtureType::getLenght() const {
  return lenght;
}

void FixtureType::setLenght(double value) {
  lenght = value;
}

double FixtureType::getWidth() const {
  return width;
}

void FixtureType::setWidth(double value) {
  width = value;
}

double FixtureType::getHeight() const {
  return height;
}

void FixtureType::setHeight(double value) {
  height = value;
}

double FixtureType::getWeight() const {
  return weight;
}

void FixtureType::setWeight(double value) {
  weight = value;
}

} // namespace light
