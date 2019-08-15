#ifndef ROLE_H
#define ROLE_H

#include "typedefs.h"

namespace light {
class Role
{
public:
  Role() = default;

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

#endif // ROLE_H
