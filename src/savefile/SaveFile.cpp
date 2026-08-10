#include "SaveFile.h"

#include "../player/player.h"
#include "../player/player_sfx.h"
#include "../utils/Rumble.h"

#include "../../butano/hw/include/bn_hw_core.h"

BN_DATA_EWRAM SaveFile::SaveFileData SaveFile::data;

static bool sram_available = true;

#define MAGIC_NUMBER 135795136

bool SaveFile::initialize() {
  // Do not require SRAM on this build. Keep settings in RAM with defaults.
  data.magicNumber = MAGIC_NUMBER;
  data.audioLag = 0;
  data.didCalibrate = false;
  data.rumble = true;
  data.bgBlink = false;
  data.intensity = 0;
  data.contrast = 0;
  for (int i = 0; i < 3; i++)
    data._padding1[i] = 0xEE;

  sram_available = false;
  return true;
}

bool SaveFile::available() {
  return sram_available;
}

bool SaveFile::isValid() {
  if (data.magicNumber != MAGIC_NUMBER)
    return false;
  if (data.audioLag < 0 || data.audioLag > 500)
    return false;
  if (data.intensity >= 5 || data.contrast >= 5)
    return false;
  if (data.intensity >= 5 || data.contrast >= 5)
    return false;

  return true;
}



void SaveFile::load() {
  if (sram_available) {
    bn::sram::read(data);
  }
}

void SaveFile::save() {
  if (sram_available) {
    bn::sram::write(data);
  }
}

void SaveFile::wipe() {
  data.magicNumber = 1;
  if (sram_available) {
    save();
  }

  player_stop();
  player_sfx_stop();
  RUMBLE_stop();

  bn::hw::core::reset();
}
