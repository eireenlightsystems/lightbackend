#include "NotImplementedException.h"

namespace light {
NotImplementedException::NotImplementedException(const QString& functionName)
  : Exception(QString("%1 not emplemented").arg(functionName)) {
}

NotImplementedException* NotImplementedException::clone() const {
  return new NotImplementedException(*this);
}
} // namespace light
