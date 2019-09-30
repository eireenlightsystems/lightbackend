#ifndef REPORTPOWERFIXTURETOJSON_H
#define REPORTPOWERFIXTURETOJSON_H


#include "ReportPowerFixture.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<ReportPowerFixture> : public ToJsonConverterTemplate<ReportPowerFixture>
{
public:
  QJsonObject toJson(const ReportPowerFixtureShared& reportPowerFixture) const override;
};

} // namespace light

#endif // REPORTPOWERFIXTURETOJSON_H
