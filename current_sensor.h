#include <Wire.h>
#include "./Adafruit_INA219.h"

extern "C" {
#include "utility/twi.h"
}

#ifndef _CURR_SENS_H
#define _CURR_SENS_H

#define TCAADDR 0x70

class current_sensor {
 public:
  current_sensor(uint8_t addr);
  current_sensor(uint8_t addr, bool on_is_true);

  bool isOn(void);
  bool Visible(void);
  uint8_t getAddress(void);
  float getCurrent_mA(void);
  float getZero(void);
  float getThreshold(void);
  float getCyclingLevel(void);
  float getLastRead(void);

  void setZero(float val);
  void setThreshold(float val);
  void setCyclingLevel(float val);
  void show(void);
  void hide(void);
  char name[10];
 private:
  void begin(void);
  void tcaselect(uint8_t);
  bool findDevices(void);
  void constructName(void);

  float current_zero = 0;
  float threshold = 0.3;
  float cycling_level = 0.4;
  float lastRead = 0;

  uint8_t address;
  Adafruit_INA219 device;
  bool on_equals_true = true;
  bool visible = true;
};
#endif
