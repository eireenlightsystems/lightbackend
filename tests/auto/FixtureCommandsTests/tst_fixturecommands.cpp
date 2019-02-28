#include "FixtureCommand.h"
#include "FixtureLightLevelCommand.h"
#include "FixtureLightSpeedCommand.h"

#include <QtTest>

class FixtureCommands : public QObject
{
  Q_OBJECT

public:
  FixtureCommands();
  ~FixtureCommands();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void fixtureCommand_data();
  void fixtureCommand();
  void fixtureLightLevelWorkLevelCommand_data();
  void fixtureLightLevelWorkLevelCommand();
  void fixtureLightLevelStandbyLevelCommand_data();
  void fixtureLightLevelStandbyLevelCommand();
  void fixtureLightLevelBothLevelCommand_data();
  void fixtureLightLevelBothLevelCommand();
};

FixtureCommands::FixtureCommands() {
}

FixtureCommands::~FixtureCommands() {
}

void FixtureCommands::initTestCase() {
}

void FixtureCommands::cleanupTestCase() {
}

void FixtureCommands::fixtureCommand_data() {
  QTest::addColumn<light::ID>("commandId");
  QTest::addColumn<light::ID>("fixtureId");
  QTest::addColumn<QDateTime>("startDateTime");

  QTest::newRow("simple") << light::ID(1) << light::ID(1) << QDateTime::currentDateTime();
}

void FixtureCommands::fixtureCommand() {
  QFETCH(light::ID, commandId);
  QFETCH(light::ID, fixtureId);
  QFETCH(QDateTime, startDateTime);

  {
    light::FixtureCommand command;
    command.setCommandId(commandId);
    command.setFixtureId(fixtureId);
    command.setStartDateTime(startDateTime);

    QVERIFY(command.getCommandId() == commandId);
    QVERIFY(command.getFixtureId() == fixtureId);
    QVERIFY(command.getStartDateTime() == startDateTime);
  }
}

void FixtureCommands::fixtureLightLevelWorkLevelCommand_data() {
  QTest::addColumn<quint8>("workLevel");
  QTest::addColumn<quint8>("standbyLevel");
  QTest::addColumn<quint8>("expectedWorkLevel");

  QTest::newRow("simple") << quint8(80) << quint8(40) << quint8(80);
  QTest::newRow("standby greater") << quint8(40) << quint8(80) << quint8(80);
  QTest::newRow("zero") << quint8(0) << quint8(0) << quint8(0);
  QTest::newRow("work greater 100%") << quint8(101) << quint8(100) << quint8(100);
}

void FixtureCommands::fixtureLightLevelWorkLevelCommand() {
  QFETCH(quint8, workLevel);
  QFETCH(quint8, standbyLevel);
  QFETCH(quint8, expectedWorkLevel);

  light::FixtureLightLevelCommand command;
  command.setWorkLevel(workLevel);
  command.setStandbyLevel(standbyLevel);

  QVERIFY(command.getWorkLevel() == expectedWorkLevel);
}

void FixtureCommands::fixtureLightLevelStandbyLevelCommand_data() {
  QTest::addColumn<quint8>("workLevel");
  QTest::addColumn<quint8>("standbyLevel");
  QTest::addColumn<quint8>("expectedStandbyLevel");

  QTest::newRow("simple") << quint8(80) << quint8(40) << quint8(40);
  QTest::newRow("standby greater") << quint8(40) << quint8(80) << quint8(40);
  QTest::newRow("zero") << quint8(0) << quint8(0) << quint8(0);
  QTest::newRow("standy greater 100%") << quint8(100) << quint8(250) << quint8(100);
}

void FixtureCommands::fixtureLightLevelStandbyLevelCommand() {
  QFETCH(quint8, workLevel);
  QFETCH(quint8, standbyLevel);
  QFETCH(quint8, expectedStandbyLevel);

  light::FixtureLightLevelCommand command;
  command.setStandbyLevel(standbyLevel);
  command.setWorkLevel(workLevel);

  QVERIFY(command.getStandbyLevel() == expectedStandbyLevel);
}

void FixtureCommands::fixtureLightLevelBothLevelCommand_data() {
  QTest::addColumn<quint8>("workLevel");
  QTest::addColumn<quint8>("standbyLevel");
  QTest::addColumn<quint8>("expectedWorkLevel");
  QTest::addColumn<quint8>("expectedStandbyLevel");

  QTest::newRow("simple") << quint8(80) << quint8(40) << quint8(80) << quint8(40);
  QTest::newRow("standby greater") << quint8(40) << quint8(80) << quint8(80) << quint8(80);
  QTest::newRow("zero") << quint8(0) << quint8(0) << quint8(0) << quint8(0);
  QTest::newRow("work greater 100%") << quint8(101) << quint8(0) << quint8(100) << quint8(0);
  QTest::newRow("standy greater 100%") << quint8(100) << quint8(250) << quint8(100) << quint8(100);
}

void FixtureCommands::fixtureLightLevelBothLevelCommand() {
  QFETCH(quint8, workLevel);
  QFETCH(quint8, standbyLevel);
  QFETCH(quint8, expectedWorkLevel);
  QFETCH(quint8, expectedStandbyLevel);

  light::FixtureLightLevelCommand command;
  command.setLevels(workLevel, standbyLevel);

  QVERIFY(command.getWorkLevel() == expectedWorkLevel);
  QVERIFY(command.getStandbyLevel() == expectedStandbyLevel);
}

QTEST_APPLESS_MAIN(FixtureCommands)

#include "tst_fixturecommands.moc"
