#include "DateTimeRange.h"

namespace light {
DateTimeRange::DateTimeRange() {
}

DateTimeRange::DateTimeRange(const QDateTime& from, const QDateTime& to) : from(from), to(to) {
}

QDateTime DateTimeRange::getFrom() const
{
  return from;
}

void DateTimeRange::setFrom(const QDateTime &value)
{
  from = value;
}

QDateTime DateTimeRange::getTo() const
{
  return to;
}

void DateTimeRange::setTo(const QDateTime &value)
{
  to = value;
}
} // namespace light
