#include "NodeType.h"

namespace light {

double NodeType::getHeight() const {
  return height;
}

void NodeType::setHeight(double value) {
  height = value;
}

QString NodeType::getComment() const {
  return comment;
}

void NodeType::setComment(const QString& value) {
  comment = value;
}

} // namespace light
