#ifndef REPORTPOWERFIXTURERESTROUTER_H
#define REPORTPOWERFIXTURERESTROUTER_H

#include "ReportPowerFixture.h"
#include "ReportPowerFixtureController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudReportPowerFixture.h"
#include "ReportPowerFixtureToJson.h"

namespace light {

template <>
class RestRouter<ReportPowerFixture> : public SimpleEditableRouter<ReportPowerFixture>
{
public:
  QString getName() const override {
    return "report-power-fixtures";
  }
};

}

#endif // REPORTPOWERFIXTURERESTROUTER_H
