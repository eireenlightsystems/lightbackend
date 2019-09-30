#ifndef REPORTCOUNTFIXTUREROUTER_H
#define REPORTCOUNTFIXTUREROUTER_H

#include "ReportCountFixture.h"
#include "ReportCountFixtureController.h"
#include "RestRouter.h"
#include "SimpleEditableRouter.h"
#include "PostgresCrudReportCountFixture.h"
#include "ReportCountFixtureToJson.h"

namespace light {

template <>
class RestRouter<ReportCountFixture> : public SimpleEditableRouter<ReportCountFixture>
{
public:
  QString getName() const override {
    return "report-count-fixtures";
  }
};

}

#endif // REPORTCOUNTFIXTUREROUTER_H
