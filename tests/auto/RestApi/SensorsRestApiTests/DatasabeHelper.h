#ifndef DATASABEHELPER_H
#define DATASABEHELPER_H

#include <QSqlDatabase>
#include <QVariant>

class DatasabeHelper
{
public:
  DatasabeHelper();
  bool openDatabase(const QString& hostName,
		    int port,
		    const QString& databaseName,
		    const QString& username,
		    const QString& password);
  QVariant extractValue(const QString& table, const QString& field, const QString& idField, qulonglong id);

private:
  QSqlDatabase db;
};

#endif // DATASABEHELPER_H
