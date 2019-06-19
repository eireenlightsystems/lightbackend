#ifndef PERSONRESTROUTER_H
#define PERSONRESTROUTER_H

#include "Person.h"
#include "PersonController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudPerson.h"
#include "PersonToJson.h"

namespace light {

template <>
class RestRouter<Person> : public SimpleEditableRouter<Person>
{
public:
  QString getName() const override {
    return "persons";
  }
};

}

#endif // PERSONRESTROUTER_H
