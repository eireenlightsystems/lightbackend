#include "JsonToIds.h"

#include <QJsonArray>
#include <QVariant>

namespace light {

void JsonToIds::convert(const QByteArray& data) {
  QJsonDocument jDoc = parseJson(data);
  if (!getIdValid()) {
    setErrorText(data);
    return;
  }

  ids.clear();
  auto commandArray = jDoc.array();
  QList<ID> deleteCommands;
  for (const auto commandValue : commandArray) {
    auto id = commandValue.toVariant().value<qulonglong>();
    ids << id;
  }
}

QList<ID> JsonToIds::getIds() const {
  return ids;
}

} // namespace light
