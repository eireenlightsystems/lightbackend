#ifndef FIXTUREHEIGHTTYPE_H
#define FIXTUREHEIGHTTYPE_H

#include "typedefs.h"

#include <QString>

namespace light {
class FixtureHeightType
{
public:
  FixtureHeightType() = default;

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  ID getId() const;
  void setId(const ID& value);

private:
  ID id{0};
  QString code;
  QString name;
};
} // namespace light

#endif // FIXTUREHEIGHTTYPE_H
