#include <avr/wdt.h>
#include "./current_sensor.h"

#define SENSOR_COUNT 8
#undef DEBUG
#define ONBOARD_LED 13

current_sensor* sensors[SENSOR_COUNT];
bool cycling = false;
int milliseconds = 0;
int dly = 0;

void setup() {
  wdt_disable();
#ifndef ESP8266
  while (!Serial);
#endif

  Serial.begin(9600);

#ifdef DEBUG
  Serial.println("Serial started");
#endif

  pinMode(ONBOARD_LED, OUTPUT);
  for (int i = 0; i < SENSOR_COUNT; i++) {
    sensors[i] = new current_sensor(i);
  }

  sensors[0]->hide();
  wdt_enable(WDTO_8S);
}


void loop() {
  bool on = false;
  for (int i = 0; i < SENSOR_COUNT; i++) {
    on |= sensors[i]->isOn();
  }

  // Delay to ignore blinks.
  if (!on) {
    milliseconds = 0;
  } else {
    if (milliseconds == 0) {
        milliseconds = millis();
    }
  }

  // Switch cycling state off or on, send JSON only once.
  if (on != cycling) {
    if ( ! cycling) {
      if ((millis() - milliseconds) > dly) {
        sendStartJSON();
      }
    } else {
      if (cycling) {
        sendStopJSON();
      }
    }
  }

  wdt_reset();
}

void sendStartJSON() {
  cycling = true;
  milliseconds = 0;
  digitalWrite(ONBOARD_LED, HIGH);
  Serial.print(F("{ \"Event\": {\"name\": \"cycle\", \"start\": 1"));
  for (int i = 0; i < SENSOR_COUNT; i++) {
    if (sensors[i]->Visible()) {
      char msg[256];
      char val[6];
      dtostrf(sensors[i]->getCurrent_mA(), 4, 2, val);
      sprintf(msg, ", \"%s\": %s", sensors[i]->name, val);
      Serial.print(msg);
    }
  }
  Serial.println(F("}}"));
}

void sendStopJSON() {
  cycling = false;
  milliseconds = 0;
  digitalWrite(ONBOARD_LED, LOW);
  Serial.print(F("{ \"Event\": {\"name\": \"cycle\", \"stop\": 1"));
  for (int i = 0; i < SENSOR_COUNT; i++) {
    if (sensors[i]->Visible()) {
      char msg[256];
      char val[6];
      dtostrf(sensors[i]->getCurrent_mA(), 4, 2, val);
      sprintf(msg, ", \"%s\": %s", sensors[i]->name, val);
      Serial.print(msg);
    }
  }
  Serial.println(F("}}"));
}
