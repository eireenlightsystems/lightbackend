#ifndef USER_H
#define USER_H

#include "typedefs.h"

namespace light {
class User
{
public:
  User() = default;

  ID getId() const;
  void setId(const ID& value);

  QString getLogin() const;
  void setLogin(const QString& value);

  QString getPassword() const;
  void setPassword(const QString& value);

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

  QString getComments() const;
  void setComments(const QString& value);

private:
  ID id{0};
  QString login;
  QString password;
  ID contragentId{0};
  QString contragentCode;
  QString contragentName;
  QString contragentInn;
  QString contragentAdres;
  QString comments;
};
} // namespace light

#endif // USER_H
