#include <QCoreApplication>
#include <QJsonDocument>
#include <QTextStream>
#include <QDebug>
#include <QJsonObject>
#include <QDataStream>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream inStream(stdin);
    QByteArray rawData;
    rawData.append(inStream.readAll());

    QJsonParseError error;
    QJsonDocument jDoc = QJsonDocument::fromJson(rawData, &error);
    if(error.error != QJsonParseError::NoError) {
        qCritical() << error.errorString();
        return 1;
    }
    QJsonObject jObject = jDoc.object();
    quint16 gatewayId = static_cast<quint16>(jObject.value("gatewayId").toInt());
    quint8 nodeNumber = static_cast<quint8>(jObject.value("nodeNumber").toInt());
    quint8 deviceNumber = static_cast<quint8>(jObject.value("deviceNumber").toInt());
    quint8 errorCode = static_cast<quint8>(jObject.value("errorCode").toInt());

    QByteArray outputData;
    QDataStream ds(&outputData, QIODevice::WriteOnly);
    ds.setByteOrder(QDataStream::BigEndian);
    ds << gatewayId << nodeNumber << deviceNumber << errorCode;

    for(auto b : outputData) {
        std::cout << b;
    }
    return 0;
}
