#ifndef BADREQUESTEXCEPTION_H
#define BADREQUESTEXCEPTION_H

#include "Exception.h"

namespace light {
class BadRequestException : public Exception
{
public:
  explicit BadRequestException(const QString& errorText);
  BadRequestException* clone() const override;
};
} // namespace light

#endif // BADREQUESTEXCEPTION_H
