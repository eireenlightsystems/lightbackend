#ifndef PERSONCONTROLLER_H
#define PERSONCONTROLLER_H

#include "Controller.h"
#include "Person.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<Person, Crud> : public EditableController<Person, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Person, Crud>::ins(const QList<QVariantHash>& params) {
  PersonSharedList newPersons;
  for (const auto& param : params){
    auto newPerson = PersonShared::create();

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      newPerson->setGeographId(geographId);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newPerson->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newPerson->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      newPerson->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      newPerson->setComments(comments);
    }

    if (param.contains("nameFirst")) {
      QString nameFirst = param.value("nameFirst").toString();
      newPerson->setName(nameFirst);
    }

    if (param.contains("nameSecond")) {
      QString nameSecond = param.value("nameSecond").toString();
      newPerson->setName(nameSecond);
    }

    if (param.contains("nameThird")) {
      QString nameThird = param.value("nameThird").toString();
      newPerson->setName(nameThird);
    }

    newPersons << newPerson;
  }

  Crud<Person> personCrud;
  personCrud.setSession(this->getSession());
  personCrud.save(newPersons);
  IDList result;
  std::transform(newPersons.begin(), newPersons.end(), std::back_inserter(result), [](const PersonShared& person) {
    return person->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<Person, Crud>::upd(const QList<QVariantHash>& params) {
  PersonSharedList Persons;
  Crud<Person> PersonCrud;
  PersonCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID personId = param.value("id").value<ID>();
    auto person = PersonCrud.selById(personId);

    if (param.contains("geographId")) {
      ID geographId = param.value("geographId").value<ID>();
      person->setGeographId(geographId);
    }

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      person->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      person->setName(name);
    }

    if (param.contains("inn")) {
      QString inn = param.value("inn").toString();
      person->setInn(inn);
    }

    if (param.contains("comments")) {
      QString comments = param.value("comments").toString();
      person->setComments(comments);
    }

    if (param.contains("nameFirst")) {
      QString nameFirst = param.value("nameFirst").toString();
      person->setName(nameFirst);
    }

    if (param.contains("nameSecond")) {
      QString nameSecond = param.value("nameSecond").toString();
      person->setName(nameSecond);
    }

    if (param.contains("nameThird")) {
      QString nameThird = param.value("nameThird").toString();
      person->setName(nameThird);
    }

    Persons << person;
  }

  PersonCrud.save(Persons);
}

template <template <typename> class Crud>
void Controller<Person, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // PERSONCONTROLLER_H
