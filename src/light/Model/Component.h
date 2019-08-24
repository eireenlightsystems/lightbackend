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

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

  QString getRights() const;
  void setRights(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
  QString comments;
  QString rights;
};
} // namespace light

#endif // COMPONENT_H
