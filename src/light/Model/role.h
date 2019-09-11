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

  ID getContragentId() const;
  void setContragentId(const ID& value);

  QString getContragentCode() const;
  void setContragentCode(const QString& value);

  QString getContragentName() const;
  void setContragentName(const QString& value);

  QString getContragentInn() const;
  void setContragentInn(const QString& value);

  QString getContragentAdres() const;
  void setContragentAdres(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

  UserSharedList getUsers() const;
  void setUsers(const UserSharedList &value);
  void removeUser(ID userId);
  void addUser(const UserShared& user);

private:
  ID id{0};
  ID contragentId{0};
  QString contragentCode;
  QString contragentName;
  QString contragentInn;
  QString contragentAdres;
  QString name;
  QString comments;
  UserSharedList users;
};
} // namespace light

#endif // ROLE_H
