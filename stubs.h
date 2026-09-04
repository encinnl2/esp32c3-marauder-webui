#pragma once
#ifndef STUBS_C3_H
#define STUBS_C3_H

#include <Arduino.h>
#include <LinkedList.h>

// Structs needed by WiFiScan and CommandLine
struct ssid {
    String ssid;
    bool selected;
};

struct AccessPoint {
    String ssid;
    uint8_t bssid[6];
    int channel;
    int rssi;
};

class Display {
  public:
    void setupDisplay() {}
    void main_run() {}
    void showCenteredText(const char*, int) {}
    void drawBitmap(...) {}
};
extern Display display_obj;

class SDInterface {
  public:
    bool init() { return false; }
    bool openFile(const char*, int) { return false; }
    void closeFile() {}
    size_t write(uint8_t*, size_t) { return 0; }
};
extern SDInterface sd_obj;

class GpsInterface {
  public:
    void setup() {}
    float getLat() { return 0.0; }
    float getLon() { return 0.0; }
};
extern GpsInterface gps_obj;

class BatteryInterface {
  public:
    int getBatteryPercent() { return 100; }
};
extern BatteryInterface battery_obj;

class EvilPortal {
  public:
    void setup() {}
    void main() {}
    void renderPage() {}
    void endPortal() {}
};
extern EvilPortal evil_portal_obj;

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

#endif // STUBS_C3_H
