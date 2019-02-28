#include "CommandsScheduler.h"
#include "TestSchedulerGateway.h"

#include <QtTest>

class CommandsScheduler : public QObject
{
  Q_OBJECT

public:
  CommandsScheduler();
  ~CommandsScheduler();

private slots:
  void initTestCase();
  void cleanupTestCase();

  void updateTimer_data();
  void updateTimer();

private:
  QSharedPointer<light::SchedulerGateway> testSchedulerGateway;
  QSharedPointer<light::CommandsScheduler> scheduler;
  QSharedPointer<TestDeviceCommandGateway> deviceCommandGateway;
};

CommandsScheduler::CommandsScheduler() {
}

CommandsScheduler::~CommandsScheduler() {
}

void CommandsScheduler::initTestCase() {
  scheduler = QSharedPointer<light::CommandsScheduler>::create();
  deviceCommandGateway = QSharedPointer<TestDeviceCommandGateway>::create();
  testSchedulerGateway = QSharedPointer<light::SchedulerGateway>::create();
  testSchedulerGateway->setGateways({nullptr, nullptr, nullptr, deviceCommandGateway});
  scheduler->setSchedulerGateway(testSchedulerGateway);
}

void CommandsScheduler::cleanupTestCase() {
}

void CommandsScheduler::updateTimer_data() {
  QTest::addColumn<QDateTime>("dateTime");
  QTest::addColumn<QDateTime>("expectedDateTime");

  auto tomorrow = QDateTime::currentDateTime().addDays(1);
  QTest::newRow("begin") << tomorrow << tomorrow;
  QTest::newRow("greater than last") << tomorrow.addDays(1) << tomorrow.addDays(1);
  QTest::newRow("less than last") << tomorrow.addSecs(-1000) << tomorrow.addSecs(-1000);
  QTest::newRow("less than now") << tomorrow.addDays(-2) << tomorrow.addDays(-2);
}

void CommandsScheduler::updateTimer() {
  QFETCH(QDateTime, dateTime);
  QFETCH(QDateTime, expectedDateTime);

  deviceCommandGateway->setClosestDateTime(dateTime);
  scheduler->checkUpdates();

  QVERIFY(scheduler->getCheckCommandDateTime() == expectedDateTime);
}

QTEST_APPLESS_MAIN(CommandsScheduler)

#include "tst_commandsscheduler.moc"
