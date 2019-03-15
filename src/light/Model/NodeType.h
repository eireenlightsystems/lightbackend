#ifndef NODETYPE_H
#define NODETYPE_H

#include "EquipmentType.h"

namespace light {
class NodeType : public EquipmentType
{
public:
  NodeType() = default;

  double getHeight() const;
  void setHeight(double value);

  QString getComment() const;
  void setComment(const QString& value);

private:
  double height{0.0};
  QString comment;
};
} // namespace light

#endif // NODETYPE_H