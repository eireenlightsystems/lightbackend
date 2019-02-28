#define protected public
#define private public
#include "CommandsController.h"
#undef protected
#undef private

#include "DeleteCommandException.h"
#include "Fixture.h"
#include "FixtureLightLevelCommand.h"
#include "InMemoryDatabaseGateway.h"
#include "MissingFixtureGatewayLinkException.h"
#include "typedefs.h"

#include <QtTest>

Q_DECLARE_METATYPE(light::FixtureLightLevelCommandShared)
Q_DECLARE_METATYPE(light::FixtureCommandShared)

class CommandsController : public QObject
{
  Q_OBJECT

public:
  CommandsController();
  ~CommandsController();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void checkFixtureGatewayLinkFail_data();
  void checkFixtureGatewayLinkFail();

  void checkCommandBeforeDeleteFail_data();
  void checkCommandBeforeDeleteFail();

private:
  light::CommandsController commandController;
};

CommandsController::CommandsController() {
}

CommandsController::~CommandsController() {
}

void CommandsController::initTestCase() {
}

void CommandsController::cleanupTestCase() {
}

void CommandsController::checkFixtureGatewayLinkFail_data() {
  QTest::addColumn<light::FixtureLightLevelCommandSharedList>("lightLevelCommands");

  light::FixtureLightLevelCommandSharedList commands1;
  auto command1 = light::FixtureLightLevelCommandShared::create();
  command1->setFixtureId(1);
  commands1 << command1;

  light::FixtureLightLevelCommandSharedList commands2;
  auto command2 = light::FixtureLightLevelCommandShared::create();
  command2->setFixtureId(2);
  commands2 << command1 << command2;

  QTest::newRow("one fixture has gateway link") << commands1;
  QTest::newRow("one fixture has gateway link and one has not") << commands2;

  auto gateway = light::InMemoryDatabaseGatewayShared::create();
  auto fixture1 = light::FixtureShared::create();
  fixture1->setId(1);
  fixture1->setHasGatewayLink(false);
  gateway->saveFixture(fixture1);

  auto fixture2 = light::FixtureShared::create();
  fixture2->setId(2);
  fixture2->setHasGatewayLink(true);
  gateway->saveFixture(fixture2);
  commandController.setFixtureCommandGateway(gateway);
}

void CommandsController::checkFixtureGatewayLinkFail() {
  QFETCH(light::FixtureLightLevelCommandSharedList, lightLevelCommands);
  QVERIFY_EXCEPTION_THROWN(commandController.checkFixtureGatewayLink(lightLevelCommands),
			   light::MissingFixtureGatewayLinkException);
}

void CommandsController::checkCommandBeforeDeleteFail_data() {
  QTest::addColumn<light::FixtureCommandSharedList>("commands");

  light::FixtureCommandSharedList commands1;
  auto command1 = light::FixtureCommandShared::create();
  command1->setStatus(light::CommandStatus::Done);
  commands1 << command1;

  light::FixtureCommandSharedList commands2;
  auto command2 = light::FixtureCommandShared::create();
  command2->setStatus(light::CommandStatus::InQueue);
  commands2 << command2 << command1;

  QTest::newRow("one not deletable command") << commands1;
  QTest::newRow("one not deletable command and one deletable command") << commands2;
}

void CommandsController::checkCommandBeforeDeleteFail() {
  QFETCH(light::FixtureCommandSharedList, commands);
  QVERIFY_EXCEPTION_THROWN(commandController.checkCommandBeforeDelete(commands), light::DeleteCommandException);
}

QTEST_APPLESS_MAIN(CommandsController)

#include "tst_commandscontroller.moc"
