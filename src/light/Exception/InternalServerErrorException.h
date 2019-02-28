#ifndef INTERNALSERVERERROREXCEPTION_H
#define INTERNALSERVERERROREXCEPTION_H

#include "Exception.h"

namespace light {
class InternalServerErrorException : public Exception
{
public:
  explicit InternalServerErrorException(const QString& errorText);
  InternalServerErrorException* clone() const override;
  void raise() const override;
};
} // namespace light

#endif // INTERNALSERVERERROREXCEPTION_H
