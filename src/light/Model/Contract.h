#ifndef CONTRACT_H
#define CONTRACT_H

#include "typedefs.h"

namespace light {
class Contract
{
public:
  Contract() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
};
} // namespace light

#endif // CONTRACT_H
