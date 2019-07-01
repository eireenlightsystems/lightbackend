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

  ID getContractTypeId() const;
  void setContractTypeId(const ID& value);

  ID getSenderId() const;
  void setSenderId(const ID& value);

  ID getRecipientId() const;
  void setRecipientId(const ID& value);

  QString getContractTypeCode() const;
  void setContractTypeCode(const QString& value);

  QString getSenderCode() const;
  void setSenderCode(const QString& value);

  QString getRecipientCode() const;
  void setRecipientCode(const QString& value);

  QString getCode() const;
  void setCode(const QString& value);

  QString getName() const;
  void setName(const QString& value);

  QString getComments() const;
  void setComments(const QString& value);

private:
  ID id{0};
  ID contractTypeId{0};
  ID senderId{0};
  ID recipientId{0};
  QString contractTypeCode;
  QString senderCode;
  QString recipientCode;
  QString code;
  QString name;
  QString comments;
};
} // namespace light

#endif // CONTRACT_H
