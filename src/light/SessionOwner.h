#ifndef SESSIONOWNER_H
#define SESSIONOWNER_H

#include "Session.h"
#include "typedefs.h"

namespace light {

class SessionOwner
{
public:
  virtual ~SessionOwner() = default;
  SessionShared getSession() const;
  void setSession(const SessionShared& value);

private:
  SessionShared session;
};
} // namespace light

#endif // SESSIONOWNER_H
