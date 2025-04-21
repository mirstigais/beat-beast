#ifndef OPENING_SCENE_H
#define OPENING_SCENE_H

#include "Scene.h"

class OpeningScene : public Scene {
 public:
  OpeningScene(const GBFS_FILE* _fs);

  void init() override;
  void update() override;

 private:
  bn::optional<bn::regular_bg_ptr> background;
  int wait = 0;
  int index = -1;

  void addLine();
};

#endif  // OPENING_SCENE_H
