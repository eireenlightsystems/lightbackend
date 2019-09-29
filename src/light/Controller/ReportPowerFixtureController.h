#ifndef REPORTPOWERFIXTURECONTROLLER_H
#define REPORTPOWERFIXTURECONTROLLER_H

#include "Controller.h"
#include "ReportPowerFixture.h"

#include <QVariantHash>

namespace light {

template <template <typename> class Crud>
class Controller<ReportPowerFixture, Crud> : public EditableController<ReportPowerFixture, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
  void del(const IDList& ids) const override;
};

template <template <typename> class Crud>
IDList Controller<ReportPowerFixture, Crud>::ins(const QList<QVariantHash>& params) {
  IDList result;
  return result;
}

template <template <typename> class Crud>
void Controller<ReportPowerFixture, Crud>::upd(const QList<QVariantHash>& params) {
  Q_UNUSED(params)
}

template <template <typename> class Crud>
void Controller<ReportPowerFixture, Crud>::upd(ID id, const QVariantHash& param) {
  Q_UNUSED(id)
  Q_UNUSED(param)
}

template <template <typename> class Crud>
void Controller<ReportPowerFixture, Crud>::del(const IDList& ids) const {
  Q_UNUSED(ids)
}

} // namespace light

#endif // REPORTPOWERFIXTURECONTROLLER_H
