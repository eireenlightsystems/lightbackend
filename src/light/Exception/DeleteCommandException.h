#ifndef DELETECOMMANDEXCEPTION_H
#define DELETECOMMANDEXCEPTION_H

#include "BadInputDataException.h"

namespace light {
class DeleteCommandException : public BadInputDataException
{
public:
  explicit DeleteCommandException(const QList<ID> ids);
  DeleteCommandException* clone() const override;
};
} // namespace light

#endif // DELETECOMMANDEXCEPTION_H
