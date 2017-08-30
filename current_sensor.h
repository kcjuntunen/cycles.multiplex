#include <Wire.h>
#include "./Adafruit_INA219.h"

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

  void setZero(float val);
  void setThreshold(float val);
  void setCyclingLevel(float val);
  void show(void);
  void hide(void);
 private:
  void begin(void);
  void tcaselect(uint8_t);

  float current_zero = 0;
  float threshold = 0.1;
  float cycling_level = 0.4;

  uint8_t address;
  Adafruit_INA219 device;
  bool on_equals_true = true;
  bool visible = true;
};
#endif
