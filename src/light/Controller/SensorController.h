#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include "Controller.h"
#include "Sensor.h"

#include <QVariant>

namespace light {

template <template <typename> class Crud>
class Controller<Sensor, Crud> : public EditableController<Sensor, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
  IDList ins(const QList<QVariantHash>& params) override;
  void upd(const QList<QVariantHash>& params) override;
  void upd(ID id, const QVariantHash& param) override;
};

template <template <typename> class Crud>
IDList Controller<Sensor, Crud>::ins(const QList<QVariantHash> &params)
{

}

template <template <typename> class Crud>
void Controller<Sensor, Crud>::upd(const QList<QVariantHash> &params)
{

}

template <template <typename> class Crud>
void Controller<Sensor, Crud>::upd(ID id, const QVariantHash &param)
{

}

} // namespace light

#endif // SENSORCONTROLLER_H
