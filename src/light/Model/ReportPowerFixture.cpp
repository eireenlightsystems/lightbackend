#include "ReportPowerFixture.h"

namespace light {

ID ReportPowerFixture::getId() const {
  return id;
}

void ReportPowerFixture::setId(const ID& value) {
  id = value;
}

int ReportPowerFixture::getYear() const {
  return year;
}

void ReportPowerFixture::setYear(const int value) {
  year = value;
}

QString ReportPowerFixture::getMonthName() const {
  return monthName;
}

void ReportPowerFixture::setMonthName(const QString& value) {
  monthName = value;
}

int ReportPowerFixture::getFixtureId() const {
  return fixtureId;
}

void ReportPowerFixture::setFixtureId(const int value) {
  fixtureId = value;
}

double ReportPowerFixture::getHours() const {
  return hours;
}

void ReportPowerFixture::setHours(const double value) {
  hours = value;
}

double ReportPowerFixture::getKw() const {
  return kw;
}

void ReportPowerFixture::setKw(const double value) {
  kw = value;
}

double ReportPowerFixture::getRub() const {
  return rub;
}

void ReportPowerFixture::setRub(const double value) {
  rub = value;
}
} // namespace light
