#ifndef BADINPUTDATAEXCEPTION_H
#define BADINPUTDATAEXCEPTION_H

#include "Exception.h"
#include "typedefs.h"

namespace light {
class BadInputDataException : public Exception
{
public:
  explicit BadInputDataException(const QString& errorText);
  BadInputDataException* clone() const override;
};
} // namespace light

#endif // BADINPUTDATAEXCEPTION_H
