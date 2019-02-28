#ifndef NOTIMPLEMENTEDEXCEPTION_H
#define NOTIMPLEMENTEDEXCEPTION_H

#include "Exception.h"

namespace light {
class NotImplementedException : public Exception
{
public:
  explicit NotImplementedException(const QString& functionName);
  NotImplementedException* clone() const override;
};
} // namespace light

#endif // NOTIMPLEMENTEDEXCEPTION_H
