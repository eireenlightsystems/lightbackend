#include "Exception.h"

#include <iostream>

namespace light {
Exception::Exception(const QString& errorText) : QException(), errorText(errorText) {
}

const char* Exception::what() const noexcept {
  char *newString = new char[errorText.length()];
  strcpy(newString, errorText.toStdString().c_str());
  return newString;
}

QString Exception::getErrorText() const {
  return errorText;
}

void Exception::setErrorText(const QString &value)
{
    errorText = value;
}
} // namespace light
