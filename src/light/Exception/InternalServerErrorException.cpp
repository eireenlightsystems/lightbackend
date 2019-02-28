#include "InternalServerErrorException.h"

namespace light {
InternalServerErrorException::InternalServerErrorException(const QString& errorText) : Exception(errorText) {
}

InternalServerErrorException* InternalServerErrorException::clone() const {
  return new InternalServerErrorException(*this);
}

void InternalServerErrorException::raise() const {
  throw *this;
}
} // namespace light
