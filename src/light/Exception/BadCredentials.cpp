#include "BadCredentials.h"

namespace light {

BadCredentialsException::BadCredentialsException() : Exception("") {
}

BadCredentialsException* BadCredentialsException::clone() const {
  return new BadCredentialsException(*this);
}

} // namespace light
