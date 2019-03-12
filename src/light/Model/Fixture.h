#ifndef FIXTURE_H
#define FIXTURE_H

#include "typedefs.h"

namespace light {
class Fixture
{
public:
  Fixture() = default;

  bool getHasGatewayLink() const;
  void setHasGatewayLink(bool value);

  ID getId() const;
  void setId(const ID& value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(const quint8& value);

  quint8 getWorkLevel() const;
  void setWorkLevel(const quint8& value);

  quint8 getSpeedUp() const;
  void setSpeedUp(const quint8& value);

  quint8 getSpeedDown() const;
  void setSpeedDown(const quint8& value);

  ContractShared getContract() const;
  ID getContractId() const;
  void setContract(const ContractShared& value);

  SubstationShared getSubstation() const;
  ID getSubstationId() const;
  void setSubstation(const SubstationShared& value);

  ContragentShared getInstaller() const;
  ID getInstallerId() const;
  void setInstaller(const ContragentShared& value);

  FixtureHeightTypeShared getHeightType() const;
  ID getHeightTypeId() const;
  void setHeightType(const FixtureHeightTypeShared& value);

  NodeShared getNode() const;
  ID getNodeId() const;
  void setNode(const NodeShared& value);

  double getLatitude() const;
  double getLongitude() const;

  GeographShared getGeograph() const;
  ID getGeographId() const;

  FixtureTypeShared getType() const;
  ID getTypeId() const;
  void setType(const FixtureTypeShared& value);

  ContragentShared getOwner() const;
  void setOwner(const ContragentShared& value);

  QString getComment() const;
  void setComment(const QString& value);

  double getPrice() const;
  void setPrice(double value);

private:
  ID id{0};
  bool hasGatewayLink{false};
  quint8 standbyLevel{0};
  quint8 workLevel{0};
  quint8 speedUp{0};
  quint8 speedDown{0};
  ContractShared contract;
  FixtureTypeShared type;
  SubstationShared substation;
  ContragentShared installer;
  FixtureHeightTypeShared heightType;
  NodeShared node;
  ContragentShared owner;
  double price{0.0};
  QString comment;
};
} // namespace light

#endif // FIXTURE_H
