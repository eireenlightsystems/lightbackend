#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include "Exception.h"

namespace light {
class DatabaseException : public Exception
{
public:
  explicit DatabaseException(const QString& errorText);
  DatabaseException* clone() const override;
};
} // namespace light

#endif // DATABASEEXCEPTION_H
