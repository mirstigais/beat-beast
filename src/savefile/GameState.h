#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "SaveFile.h"
#include "../objects/song/SongList.h"

namespace GameState {

enum Screen {
  NO,
  OPENING,
  START,
  PLAYER,
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
  SongList::Song currentSong = SongList::songList[0];
  SaveFile::LevelProgress currentLevelProgress;

  bool newRecordHealth = false;
  bool newRecordDamage = false;
  bool newRecordSync = false;
  bool isPlaying = false;
};

void saveWin();

void saveDeath();

extern GameStateData data;

}  // namespace GameState

#endif  // GAME_STATE_H