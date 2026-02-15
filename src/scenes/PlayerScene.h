#ifndef PLAYER_SCENE_H
#define PLAYER_SCENE_H

#include "Scene.h"

class PlayerScene : public Scene {
 public:
  PlayerScene(const GBFS_FILE* _fs);

  void init() override;
  void update() override;

 private:
  bn::optional<bn::regular_bg_ptr> background;
  bn::vector<bn::sprite_ptr, 64> textSprites;
  bn::sprite_text_generator textGenerator;
  bn::sprite_text_generator textGeneratorAccent;
  bn::fixed videoFrame = 0;
  bn::fixed extraSpeed = 0;
  bn::vector<bn::sprite_ptr, 96> songTextSprites;
  bn::vector<bn::sprite_ptr, 32> timeTextSprites;
  bn::vector<bn::fixed, 96> songTextOriginalX;
  bn::vector<bn::fixed, 96> songTextOriginalY;


  int text_cycle_width = 0;

  bool paused = false;
  bool scroll_enabled = false;
  bn::fixed scroll_x = 0;
  int song_text_width = 0;

  void updateVideo();
  void start();
  void updatePlayerCounter();
  void setCurrentSong(size_t index);
  bool song_finished();
};

#endif  // PLAYER_SCENE_H
