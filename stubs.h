#pragma once
#ifndef STUBS_C3_H
#define STUBS_C3_H

#include <Arduino.h>
#include <LinkedList.h>

struct ssid {
  String essid;
  uint8_t channel;
  uint8_t bssid[6];
  bool selected;
};

struct AccessPoint {
  String essid;
  uint8_t channel;
  uint8_t bssid[6];
  bool selected;
  char beacon[2];
  int8_t rssi;
  LinkedList<uint16_t>* stations;
  uint16_t packets;
  uint8_t sec;
  bool wps;
  String man;
  bool has_msg_1;
  bool has_msg_2;
  bool has_msg_3;
  bool has_msg_4;
  uint32_t last_seen_ms;
};

class Display {
  public:
    void setupDisplay() {}
    void init() {}
    void main_run() {}
    void clearScreen() {}
    void showCenteredText(const char*, int) {}
    void drawBitmap(...) {}
    void setTextColor(...) {}
    void setCursor(int, int) {}
    void setTextSize(int) {}
    void print(String s) {}
    void println(String s) {}
    void setTextWrap(bool) {}
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
    void setAP(...) {}
    bool target_html_name = false;
    bool using_serial_html = false;
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

class MenuFunctions {
  public:
    void runSetup() {}
    void main() {}
    void addApToList(...) {}
    void loadFile() {}
    void buildBeaconInfoList() {}
    void buildProbeInfoList() {}
    void buildAiroNutList() {}
    void buildAnarchyInfoList() {}
    void changeChannel(int) {}
    void changeMenu(int) {}
    void changeMenu(void(*)()) {}
    void drawStatusBar() {}
    void clearAPsMenu() {}
    void clearSSIDsMenu() {}
    void infoMenu() {}
    void saveAPsMenu() {}
    void stopScan() {}
    void startScan(int) {}
    int current_menu = 0;
};
extern MenuFunctions menu_function_obj;

#endif // STUBS_C3_H
