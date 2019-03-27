#ifndef BADCREDENTIALS_H
#define BADCREDENTIALS_H

#include "Exception.h"

namespace light {
class BadCredentialsException : public Exception
{
public:
  explicit BadCredentialsException();
  BadCredentialsException* clone() const override;
};
} // namespace light

#endif // BADCREDENTIALS_H
