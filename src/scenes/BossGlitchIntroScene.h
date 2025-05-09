#ifndef BOSS_GLITCH_INTRO_SCENE_H
#define BOSS_GLITCH_INTRO_SCENE_H

#include "UIScene.h"

#include "../objects/Horse.h"
#include "../objects/glitch/Cerberus.h"

class BossGlitchIntroScene : public UIScene {
 public:
  BossGlitchIntroScene(const GBFS_FILE* _fs);

  void init() override;
  void update() override;

 private:
  bn::unique_ptr<Horse> horse;
  unsigned state = 0;
  int lastBeat = 0;
  int countdown = 0;
  bn::optional<bn::unique_ptr<Cerberus>> cerberus;

  void updateDialog();

 protected:
  void updateVideo() override;

  bool canSkipAutoWrite() override { return countdown == 0; }
};

#endif  // BOSS_GLITCH_INTRO_SCENE_H
