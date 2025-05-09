#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SaveFile.h"

namespace GameState {

enum Screen {
  NO,
  OPENING,
  START,
  SELECTION,
  STORY,
  TUTORIAL,
  DJ,
  WIZARD,
  RIFFER,
  GLITCH_INTRO,
  GLITCH,
  GLITCH_OUTRO,
  CREDITS
};

struct GameStateData {
  Screen currentScreen = Screen::START;
  bool isPlaying = false;
  SaveFile::LevelProgress currentLevelProgress;

  bool newRecordHealth = false;
  bool newRecordDamage = false;
  bool newRecordSync = false;
};

void saveWin();

void saveDeath();

extern GameStateData data;

}  // namespace GameState

#endif  // GAME_STATE_H
