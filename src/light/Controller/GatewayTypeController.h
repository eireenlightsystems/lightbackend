#ifndef GATEWAYTYPECONTROLLER_H
#define GATEWAYTYPECONTROLLER_H

#include "Controller.h"
#include "GatewayType.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<GatewayType, Crud> : public EditableController<GatewayType, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<GatewayType, Crud>::ins(const QList<QVariantHash>& params) {
  GatewayTypeSharedList newGatewayTypes;
  for (const auto& param : params){
    auto newGatewayType = GatewayTypeShared::create();

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      newGatewayType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      newGatewayType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      newGatewayType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      newGatewayType->setComment(comment);
    }

    if (param.contains("communicationStandard")) {
      QString communicationStandard = param.value("communicationStandard").toString();
      newGatewayType->setCommunicationStandard(communicationStandard);
    }

    newGatewayTypes << newGatewayType;
  }

  Crud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());
  gatewayTypeCrud.save(newGatewayTypes);
  IDList result;
  std::transform(newGatewayTypes.begin(), newGatewayTypes.end(), std::back_inserter(result), [](const GatewayTypeShared& gatewayType) {
    return gatewayType->getId();
  });
  return result;
}

template <template <typename> class Crud>
void Controller<GatewayType, Crud>::upd(const QList<QVariantHash>& params) {
  GatewayTypeSharedList gatewayTypes;
  Crud<GatewayType> gatewayTypeCrud;
  gatewayTypeCrud.setSession(this->getSession());

  for (const auto& param : params){
    ID gatewayTypeId = param.value("id").value<ID>();
    auto gatewayType = gatewayTypeCrud.selById(gatewayTypeId);

    if (param.contains("code")) {
      QString code = param.value("code").toString();
      gatewayType->setCode(code);
    }

    if (param.contains("name")) {
      QString name = param.value("name").toString();
      gatewayType->setName(name);
    }

    if (param.contains("model")) {
      QString model = param.value("model").toString();
      gatewayType->setModel(model);
    }

    if (param.contains("comments")) {
      QString comment = param.value("comments").toString();
      gatewayType->setComment(comment);
    }

    if (param.contains("communicationStandard")) {
      QString communicationStandard = param.value("communicationStandard").toString();
      gatewayType->setCommunicationStandard(communicationStandard);
    }

    gatewayTypes << gatewayType;
  }

  gatewayTypeCrud.save(gatewayTypes);
}

template <template <typename> class Crud>
void Controller<GatewayType, Crud>::upd(ID id, const QVariantHash& param) {
  QVariantHash fullParam = param;
  fullParam["id"] = id;
  return upd({fullParam});
}

} // namespace light


#endif // GATEWAYTYPECONTROLLER_H
