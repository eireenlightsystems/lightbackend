#include "Exception.h"

namespace light {
Exception::Exception(const QString& errorText) : QException(), errorText(errorText) {
}

const char* Exception::what() const noexcept {
  return errorText.toStdString().c_str();
}

QString Exception::getErrorText() const {
  return errorText;
}

void Exception::setErrorText(const QString &value)
{
    errorText = value;
}
} // namespace light
