#include "FixtureSwitchOnDeviceCommand.h"
#include "SpeedToLightBaseDeviceCommand.h"

#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

using namespace light::CommandsScheduler;

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  QTextStream inStream(stdin);
  QTextStream outStream(stdout);
  QByteArray rawData;
  while (!inStream.atEnd()) {
    QString line = inStream.readLine();
    if (line.length() < 4) {
      outStream << "line length too small '" << line << "'" << endl;
      continue;
    }
    CommandNumber commandNumber = static_cast<CommandNumber>(line[3].toLatin1());

    QByteArray rawData;
    rawData.append(line);
    QJsonObject jsonCommand;
    switch (commandNumber) {
      case CommandNumber::None: {
	qCritical() << "command number is none";
	break;
      }
      case CommandNumber::FixtureSwitchOn: {
	FixtureSwitchOnDeviceCommand command;
	command.fromRawData(rawData);
	jsonCommand["firstNode"] = command.getFirstNode();
	jsonCommand["lastNode"] = command.getLastNode();
	jsonCommand["deviceNumber"] = command.getDeviceNumber();
	jsonCommand["command"] = int(command.getCommandNumber());
	jsonCommand["workLevel"] = command.getWorkLevel();
	jsonCommand["standbyLevel"] = command.getStandbyLevel();
	break;
      }
      case CommandNumber::SpeedToLightUp:
      case CommandNumber::SpeedToLightDown: {
	SpeedToLightBaseDeviceCommand command;
	command.fromRawData(rawData);
	jsonCommand["firstNode"] = command.getFirstNode();
	jsonCommand["lastNode"] = command.getLastNode();
	jsonCommand["deviceNumber"] = command.getDeviceNumber();
	jsonCommand["command"] = int(command.getCommandNumber());
	jsonCommand["speed"] = command.getSpeed();
	break;
      }
      case CommandNumber::DeviceSwitchOff: {
	qCritical() << "Not inmlemented";
	break;
      }
    }
    QJsonDocument jsonDoc(jsonCommand);
    outStream << jsonDoc.toJson(QJsonDocument::Compact) << endl;
  }

  return 0;
}
