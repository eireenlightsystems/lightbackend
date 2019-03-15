#ifndef JSONTOIDS_H
#define JSONTOIDS_H

#include "BaseConverter.h"
#include "typedefs.h"

namespace light {

class JsonToIds : public BaseConverter
{
public:
  ~JsonToIds() override = default;
  void convert(const QByteArray& data);
  QList<ID> getIds() const;

private:
  QList<ID> ids;
};
} // namespace light

#endif // JSONTOIDS_H
