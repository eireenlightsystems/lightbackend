#ifndef BASECONVERTER_H
#define BASECONVERTER_H

#include <QJsonDocument>
namespace light {

class BaseConverter
{
public:
  BaseConverter() = default;
  virtual ~BaseConverter() = default;

  bool getIdValid() const;
  QString getErrorText() const;

protected:
  QJsonDocument parseJson(const QByteArray& data);
  void setIdValid(bool value);
  void setErrorText(const QString& value);

private:
  bool idValid{true};
  QString errorText;
};
} // namespace light

#endif // BASECONVERTER_H
