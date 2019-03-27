#include "FixtureToJson.h"

#include "Contract.h"
#include "ContractToJson.h"
#include "Contragent.h"
#include "ContragentToJson.h"
#include "Fixture.h"
#include "FixtureHeightType.h"
#include "FixtureType.h"
#include "Geograph.h"
#include "Node.h"
#include "Substation.h"

#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace light {

QJsonObject ToJsonConverter<Fixture>::toJson(const FixtureShared& fixture) const {
  QJsonObject fixtureJson;
  fixtureJson["fixtureId"] = QJsonValue::fromVariant(fixture->getId());
  fixtureJson["standbyLevel"] = fixture->getStandbyLevel();
  fixtureJson["workLevel"] = fixture->getStandbyLevel();
  fixtureJson["speedUp"] = fixture->getSpeedUp();
  fixtureJson["speedDown"] = fixture->getSpeedDown();
  fixtureJson["price"] = fixture->getSpeedDown();
  fixtureJson["comment"] = fixture->getComment();

  auto contract = fixture->getContract();
  if (contract) {
    fixtureJson["contractId"] = QJsonValue::fromVariant(contract->getId());
    fixtureJson["contractCode"] = contract->getCode();
  }

  auto type = fixture->getType();
  if (type) {
    fixtureJson["fixtureTypeId"] = QJsonValue::fromVariant(type->getId());
    fixtureJson["fixtureTypeCode"] = type->getCode();
    fixtureJson["fixtureTypeModel"] = type->getModel();
  }

  auto geograph = fixture->getGeograph();
  if (geograph) {
    fixtureJson["geographId"] = QJsonValue::fromVariant(geograph->getId());
    fixtureJson["geographCode"] = geograph->getCode();
  }

  auto installer = fixture->getInstaller();
  if (installer) {
    fixtureJson["installerId"] = QJsonValue::fromVariant(installer->getId());
    fixtureJson["installerCode"] = installer->getCode();
  }

  auto substation = fixture->getSubstation();
  if (substation) {
    fixtureJson["substationId"] = QJsonValue::fromVariant(substation->getId());
    fixtureJson["substationCode"] = substation->getCode();
  }

  auto heightType = fixture->getHeightType();
  if (heightType) {
    fixtureJson["heightTypeId"] = QJsonValue::fromVariant(heightType->getId());
    fixtureJson["heightTypeCode"] = heightType->getCode();
  }

  auto owner = fixture->getOwner();
  if (owner) {
    fixtureJson["ownerId"] = QJsonValue::fromVariant(owner->getId());
    fixtureJson["ownerCode"] = owner->getCode();
  }

  auto node = fixture->getNode();
  if (node) {
    fixtureJson["nodeId"] = QJsonValue::fromVariant(node->getId());
    fixtureJson["n_coordinate"] = node->getLatitude();
    fixtureJson["e_coordinate"] = node->getLongitude();
  }

  return fixtureJson;
}

QJsonObject ToJsonConverter<FixtureContract>::toJson(const FixtureContractShared& fixtureContract) const {
  ToJsonConverter<Contract> contractConverter;
  return contractConverter.toJson(fixtureContract.dynamicCast<Contract>());
}

QJsonObject ToJsonConverter<FixtureOwner>::toJson(const FixtureOwnerShared& fixtureOwner) const {
  ToJsonConverter<Contragent> contragentConverter;
  return contragentConverter.toJson(fixtureOwner.dynamicCast<Contragent>());
}

} // namespace light
