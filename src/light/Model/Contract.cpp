#include "Contract.h"

namespace light {

ID Contract::getId() const {
  return id;
}

void Contract::setId(const ID& value) {
  id = value;
}

ID Contract::getContractTypeId() const {
  return contractTypeId;
}

void Contract::setContractTypeId(const ID& value) {
  contractTypeId = value;
}

ID Contract::getSenderId() const {
  return senderId;
}

void Contract::setSenderId(const ID& value) {
  senderId = value;
}

ID Contract::getRecipientId() const {
  return recipientId;
}

void Contract::setRecipientId(const ID& value) {
  recipientId = value;
}

QString Contract::getContractTypeCode() const {
  return contractTypeCode;
}

void Contract::setContractTypeCode(const QString& value) {
  contractTypeCode = value;
}

QString Contract::getSenderCode() const {
  return senderCode;
}

void Contract::setSenderCode(const QString& value) {
  senderCode = value;
}

QString Contract::getRecipientCode() const {
  return recipientCode;
}

void Contract::setRecipientCode(const QString& value) {
  recipientCode = value;
}

QString Contract::getCode() const {
  return code;
}

void Contract::setCode(const QString& value) {
  code = value;
}

QString Contract::getName() const {
  return name;
}

void Contract::setName(const QString& value) {
  name = value;
}

QString Contract::getComments() const {
  return comments;
}

void Contract::setComments(const QString& value) {
  comments = value;
}

} // namespace light

