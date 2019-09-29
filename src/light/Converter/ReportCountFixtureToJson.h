#ifndef REPORTCOUNTFIXTURETOJSON_H
#define REPORTCOUNTFIXTURETOJSON_H


#include "ReportCountFixture.h"
#include "ToJsonConverter.h"

namespace light {

template <>
class ToJsonConverter<ReportCountFixture> : public ToJsonConverterTemplate<ReportCountFixture>
{
public:
  QJsonObject toJson(const ReportCountFixtureShared& reportCountFixture) const override;
};

} // namespace light

#endif // REPORTCOUNTFIXTURETOJSON_H
