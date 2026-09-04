#pragma once
#ifndef FOXHUNTTARGET_H
#define FOXHUNTTARGET_H

#include <Arduino.h>

namespace marauder {
  bool foxHuntMacMatches(const uint8_t* target, const uint8_t* observed) { return false; }
  bool foxHuntShouldUpdateChannel(bool bluetooth, uint8_t channel) { return false; }
  bool foxHuntTargetIsStale(uint32_t now, uint32_t last_seen, uint32_t timeout) { return true; }
  uint8_t foxHuntNextChannel(uint8_t current, uint8_t maximum) { return 1; }
}

#endif
