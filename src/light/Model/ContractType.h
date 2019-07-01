#ifndef CONTRACTTYPE_H
#define CONTRACTTYPE_H

#include "typedefs.h"
namespace light {
class ContractType
{
public:
  ContractType() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

private:
  ID id{0};
  QString code;
  QString name;
  QString comments;
};
}
#endif // CONTRACTTYPE_H
