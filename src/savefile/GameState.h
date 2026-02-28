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
  CREDITS
};

struct GameStateData {
  Screen currentScreen = Screen::START;
  SongList::Song currentSong = SongList::songList[0];
  int currentSongIndex = 0;

  bool isPlaying = false;
};

extern GameStateData data;

}  // namespace GameState

#endif  // GAME_STATE_H