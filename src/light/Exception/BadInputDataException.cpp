#include "BadInputDataException.h"

namespace light {
BadInputDataException::BadInputDataException(const QString& errorText) : Exception(errorText) {
}

BadInputDataException* BadInputDataException::clone() const {
  return new BadInputDataException(*this);
}

} // namespace light
