#include "Session.h"

namespace light {
Session::Session() {
}

QString Session::getName() const {
  return name;
}

void Session::setName(const QString& value) {
  name = value;
}

QSqlDatabase Session::getDb() const {
  return db;
}

void Session::setDb(const QSqlDatabase& value) {
  db = value;
}
} // namespace light
