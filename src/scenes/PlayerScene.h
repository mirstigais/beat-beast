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

  void updateVideo();
  void start();
};

#endif  // PLAYER_SCENE_H
