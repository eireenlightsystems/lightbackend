#include "BadRequestException.h"

namespace light {
BadRequestException::BadRequestException(const QString& errorText) : Exception(errorText) {
}

BadRequestException* BadRequestException::clone() const {
  return new BadRequestException(*this);
}

} // namespace light
