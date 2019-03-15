#include "SessionOwner.h"

namespace light {

SessionShared SessionOwner::getSession() const {
  return session;
}

void SessionOwner::setSession(const SessionShared& value) {
  session = value;
}

} // namespace light
