#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SessionOwner.h"

namespace light {

template <typename T, template <typename> class Crud>
class SelectableController : public SessionOwner
{
public:
  using Shared = QSharedPointer<T>;
  using SharedList = QList<Shared>;

  SelectableController() = default;
  ~SelectableController() = default;
  virtual SharedList sel(const QVariantHash& filters) const {
    auto crud = createCrud();
    return crud.sel(filters);
  }
  virtual SharedList sel(const IDList& ids) const {
    auto crud = createCrud();
    return crud.sel(ids);
  }

protected:
  Crud<T> createCrud() const {
    Crud<T> crud;
    crud.setSession(getSession());
    crud.setLoadChildren(false);
    return crud;
  }
};

template <typename T, template <typename> class Crud>
class EditableController : public SelectableController<T, Crud>
{
public:
  virtual IDList ins(const QList<QVariantHash>& params) = 0;
  virtual void upd(const QList<QVariantHash>& params) = 0;
  virtual void upd(ID id, const QVariantHash& param) = 0;
  virtual void del(const IDList& ids) const {
    auto crud = this->createCrud();
    auto objects = crud.sel(ids);
    crud.del(objects);
  }
};

template <typename T, template <typename> class Crud>
class EditableListController : public EditableController<T, Crud>
{
public:
  virtual void delFromList(ID listId, const IDList& ids) = 0;
  virtual void addToList(ID listId, const IDList& ids) = 0;
};

template <typename T, template <typename> class Crud>
class Controller : public SelectableController<T, Crud>
{
public:
  Controller() = default;
  ~Controller() override = default;
};

} // namespace light

#endif // CONTROLLER_H
