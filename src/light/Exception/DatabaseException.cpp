#include "DatabaseException.h"

namespace light {
DatabaseException::DatabaseException(const QString& errorText) : Exception(errorText) {
}

DatabaseException* DatabaseException::clone() const {
  return new DatabaseException(*this);
}
} // namespace light
