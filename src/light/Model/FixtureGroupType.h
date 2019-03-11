#ifndef FIXTUREGROUPTYPE_H
#define FIXTUREGROUPTYPE_H

#include "typedefs.h"

namespace light {

class FixtureGroupType
{
public:
  FixtureGroupType() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getName() const;
  void setName(const QString& value);

private:
  ID id{0};
  QString name;
};

} // namespace light

#endif // FIXTUREGROUPTYPE_H
