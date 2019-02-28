#include "DeleteCommandException.h"
namespace light {
DeleteCommandException::DeleteCommandException(const QList<ID> ids) : BadInputDataException("") {
  QStringList strings;
  std::transform(ids.cbegin(), ids.cend(), std::back_inserter(strings), [](ID id) { return QString::number(id); });
  setErrorText(QString("В наборе комманд на удаление есть выполненные команды(%1)").arg(strings.join(", ")));
}

DeleteCommandException* DeleteCommandException::clone() const {
  return new DeleteCommandException(*this);
}
} // namespace light
