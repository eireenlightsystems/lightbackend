#ifndef FIXTURE_H
#define FIXTURE_H

#include "Contract.h"
#include "Contragent.h"
#include "NodeChild.h"
#include "typedefs.h"

namespace light {

class FixtureContract : public Contract
{
public:
  FixtureContract() = default;
  explicit FixtureContract(const Contract& other) : Contract(other) {
  }
};

class FixtureOwner : public Contragent
{
public:
  FixtureOwner() = default;
  explicit FixtureOwner(const Contragent& other) : Contragent(other) {
  }
};

class FixtureInstaller : public Contragent
{
public:
  FixtureInstaller() = default;
  explicit FixtureInstaller(const Contragent& other) : Contragent(other) {
  }
};

class Fixture : public NodeChild
{
public:
  Fixture() = default;

  bool getHasGatewayLink() const;
  void setHasGatewayLink(bool value);

  quint8 getStandbyLevel() const;
  void setStandbyLevel(const quint8& value);

  quint8 getWorkLevel() const;
  void setWorkLevel(const quint8& value);

  quint8 getSpeedUp() const;
  void setSpeedUp(const quint8& value);

  quint8 getSpeedDown() const;
  void setSpeedDown(const quint8& value);

  SubstationShared getSubstation() const;
  ID getSubstationId() const;
  void setSubstation(const SubstationShared& value);

  ContragentShared getInstaller() const;
  ID getInstallerId() const;
  void setInstaller(const ContragentShared& value);

  FixtureHeightTypeShared getHeightType() const;
  ID getHeightTypeId() const;
  void setHeightType(const FixtureHeightTypeShared& value);

  FixtureTypeShared getType() const;
  ID getTypeId() const;
  void setType(const FixtureTypeShared& value);

  QString getComment() const;
  void setComment(const QString& value);

private:
  bool hasGatewayLink{false};
  quint8 standbyLevel{0};
  quint8 workLevel{0};
  quint8 speedUp{0};
  quint8 speedDown{0};
  FixtureTypeShared type;
  SubstationShared substation;
  ContragentShared installer;
  FixtureHeightTypeShared heightType;
  QString comment;
};
} // namespace light

#endif // FIXTURE_H
