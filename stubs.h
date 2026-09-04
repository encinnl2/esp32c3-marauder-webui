#pragma once
#ifndef STUBS_C3_H
#define STUBS_C3_H

// Minimal stubs for ESP32-C3 Marauder (no display / SD / GPS / Battery / Flipper LED)
#include <Arduino.h>

#ifndef HAS_SCREEN
class Display {
  public:
    void setupDisplay() {}
    void main_run() {}
    void showCenteredText(const char*, int) {}
    void drawBitmap(...) {}
};
extern Display display_obj;
#endif

#ifndef HAS_SD
class SDInterface {
  public:
    bool init() { return false; }
    bool openFile(const char*, int) { return false; }
    void closeFile() {}
    size_t write(uint8_t*, size_t) { return 0; }
};
extern SDInterface sd_obj;
#endif

#ifndef HAS_GPS
class GpsInterface {
  public:
    void setup() {}
    float getLat() { return 0.0; }
    float getLon() { return 0.0; }
};
extern GpsInterface gps_obj;
#endif

#ifndef HAS_BATTERY
class BatteryInterface {
  public:
    int getBatteryPercent() { return 100; }
};
extern BatteryInterface battery_obj;
#endif

class EvilPortal {
  public:
    void setup() {}
    void main() {}
    void renderPage() {}
    void endPortal() {}
};
extern EvilPortal evil_portal_obj;

#ifndef HAS_FLIPPER_LED
class flipperLED {
  public:
    void attackLED() {}
    void sniffLED() {}
    void offLED() {}
    void setup() {}
    void setMode(int) {}
};
extern flipperLED flipper_led;

class xiaoLED {
  public:
    void attackLED() {}
    void sniffLED() {}
    void offLED() {}
    void setup() {}
    void setMode(int) {}
};
extern xiaoLED xiao_led;

class stickcLED {
  public:
    void attackLED() {}
    void sniffLED() {}
    void offLED() {}
    void setup() {}
    void setMode(int) {}
};
extern stickcLED stickc_led;
#endif

#endif // STUBS_C3_H
