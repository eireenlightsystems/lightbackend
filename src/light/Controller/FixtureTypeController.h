#ifndef FIXTURETYPECONTROLLER_H
#define FIXTURETYPECONTROLLER_H

#include "Controller.h"
#include "FixtureType.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<FixtureType, Crud> : public EditableController<FixtureType, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<FixtureType, Crud>::ins(const QList<QVariantHash>& params) {
  FixtureTypeSharedList newFixtureTypes;
  for (const auto& param : params){
    auto newFixtureType = FixtureTypeShared::create();

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newFixtureType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newFixtureType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      newFixtureType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      newFixtureType->setComment(comment);
    }

    if (param.contains("height")) {
      double height = param.value("height").toDouble();
      newFixtureType->setHeight(height);
    }

    if (param.contains("width")) {
      double width = param.value("width").toDouble();
      newFixtureType->setWidth(width);
    }

    if (param.contains("weight")) {
      double weight = param.value("weight").toDouble();
      newFixtureType->setWeight(weight);
    }

    if (param.contains("length")) {
      double length = param.value("length").toDouble();
      newFixtureType->setLength(length);
    }

    if (param.contains("countlamp")) {
      double countlamp = param.value("countlamp").toDouble();
      newFixtureType->setCountlamp(countlamp);
    }

    if (param.contains("power")) {
      double power = param.value("power").toDouble();
      newFixtureType->setPower(power);
    }

    if (param.contains("cos")) {
      double cos = param.value("cos").toDouble();
      newFixtureType->setCos(cos);
    }

    if (param.contains("ip")) {
      double ip = param.value("ip").toDouble();
      newFixtureType->setIp(ip);
    }

    if (param.contains("efficiency")) {
      double efficiency = param.value("efficiency").toDouble();
      newFixtureType->setEfficiency(efficiency);
    }

    newFixtureTypes << newFixtureType;
  }

  Crud<FixtureType> fixtureTypeCrud;
  fixtureTypeCrud.setSession(this->getSession());
  fixtureTypeCrud.save(newFixtureTypes);
  IDList result;
  std::transform(newFixtureTypes.begin(), newFixtureTypes.end(), std::back_inserter(result), [](const FixtureTypeShared& fixtureType) {
    return fixtureType->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<FixtureType, Crud>::upd(const QList<QVariantHash>& params) {
  FixtureTypeSharedList fixtureTypes;
  Crud<FixtureType> fixtureTypeCrud;
  fixtureTypeCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID fixtureTypeId = param.value("id").value<ID>();
    auto fixtureType = fixtureTypeCrud.selById(fixtureTypeId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      fixtureType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      fixtureType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      fixtureType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      fixtureType->setComment(comment);
    }

    if (param.contains("height")) {
      double height = param.value("height").toDouble();
      fixtureType->setHeight(height);
    }

    if (param.contains("width")) {
      double width = param.value("width").toDouble();
      fixtureType->setWidth(width);
    }

    if (param.contains("weight")) {
      double weight = param.value("weight").toDouble();
      fixtureType->setWeight(weight);
    }

    if (param.contains("length")) {
      double length = param.value("length").toDouble();
      fixtureType->setLength(length);
    }

    if (param.contains("countlamp")) {
      double countlamp = param.value("countlamp").toDouble();
      fixtureType->setCountlamp(countlamp);
    }

    if (param.contains("power")) {
      double power = param.value("power").toDouble();
      fixtureType->setPower(power);
    }

    if (param.contains("cos")) {
      double cos = param.value("cos").toDouble();
      fixtureType->setCos(cos);
    }

    if (param.contains("ip")) {
      double ip = param.value("ip").toDouble();
      fixtureType->setIp(ip);
    }

    if (param.contains("efficiency")) {
      double efficiency = param.value("efficiency").toDouble();
      fixtureType->setEfficiency(efficiency);
    }

    fixtureTypes << fixtureType;
  }

  fixtureTypeCrud.save(fixtureTypes);
}

template <template <typename> class Crud>
void Controller<FixtureType, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light

#endif // FIXTURETYPECONTROLLER_H
