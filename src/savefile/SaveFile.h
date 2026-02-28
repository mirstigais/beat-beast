#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "bn_sram.h"

namespace SaveFile {

struct __attribute__((__packed__)) SaveFileData {
  // settings
  unsigned magicNumber;
  int audioLag;
  bool didCalibrate;
  bool rumble;
  bool bgBlink;
  unsigned char intensity;
  unsigned char contrast;
  unsigned char _padding1[3];
};

extern SaveFileData data;

bool initialize();
bool isValid();
void load();
void save();
void wipe();

}  // namespace SaveFile

#endif  // SAVEFILE_H
