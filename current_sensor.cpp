#include "current_sensor.h"

void current_sensor::begin() {
  tcaselect(address);
  device.begin();
  device.setCalibration_32V_Custom();
}

void current_sensor::tcaselect(uint8_t addr) {
  if (addr > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << addr);
  Wire.endTransmission();
}

float current_sensor::getZero(void) {
  return current_zero;
}

float current_sensor::getThreshold(void) {
  return threshold;
}

float current_sensor::getCyclingLevel(void) {
  return cycling_level;
}

void current_sensor::setZero(float val) {
  current_zero = val;
}

void current_sensor::setThreshold(float val) {
  threshold = val;
}

void current_sensor::setCyclingLevel(float val) {
  cycling_level = val;
}

float current_sensor::getCurrent_mA(void) {
  tcaselect(address);
  return device.getCurrent_mA();
}

bool current_sensor::isOn(void) {
  float current = getCurrent_mA();
  float diff = abs(current_zero - current);

  if (on_equals_true)
    return diff > cycling_level;
  else
    return diff < cycling_level;
}

void current_sensor::show(void) {
  visible = true;
}

void current_sensor::hide(void) {
  visible = false;
}

bool current_sensor::Visible(void) {
  return visible;
}

uint8_t current_sensor::getAddress(void) {
  return address;
}

current_sensor::current_sensor(uint8_t addr) {
  address = addr;
  Adafruit_INA219 device(0x40);
  begin();
}

current_sensor::current_sensor(uint8_t addr, bool on_is_true) {
  on_equals_true = on_is_true;
  Adafruit_INA219 device(0x40);
  begin();
}
