#ifndef COMPONENT_H
#define COMPONENT_H

#include "typedefs.h"

namespace light {
class Component
{
public:
  Component() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getName() const;
  void setName(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

private:
  ID id{0};
  QString name;
  QString comments;
};
} // namespace light

#endif // COMPONENT_H
