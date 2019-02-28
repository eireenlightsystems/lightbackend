#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QException>

namespace light {
class Exception : public QException
{
public:
  explicit Exception(const QString& errorText);
  Exception(const Exception & other) = default;
  const char* what() const noexcept override;

  QString getErrorText() const;

protected:
  void setErrorText(const QString &value);

private:
  QString errorText;
};
} // namespace light

#endif // EXCEPTION_H
