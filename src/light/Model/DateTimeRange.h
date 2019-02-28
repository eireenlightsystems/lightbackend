#ifndef DATETIMERANGE_H
#define DATETIMERANGE_H

#include <QDateTime>

namespace light {
class DateTimeRange
{
public:
  DateTimeRange();
  DateTimeRange(const QDateTime& from, const QDateTime& to);

  QDateTime getFrom() const;
  void setFrom(const QDateTime& value);

  QDateTime getTo() const;
  void setTo(const QDateTime& value);

private:
  QDateTime from;
  QDateTime to;
};
} // namespace light

#endif // DATETIMERANGE_H
