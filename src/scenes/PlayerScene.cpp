#include "PlayerScene.h"

#include "../assets/StartVideo.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font_accent.h"
#include "../player/player.h"
#include "../savefile/SaveFile.h"
#include "../utils/Math.h"
#include "../objects/song/SongList.h"
#include "bn_keypad.h"

#define HORSE_X 40
#define HORSE_Y 90
#define BPM 85
#define BEAT_PREDICTION_WINDOW 100

PlayerScene::PlayerScene(const GBFS_FILE* _fs)
    : Scene(GameState::Screen::PLAYER, _fs),
      textGenerator(common_fixed_8x16_sprite_font),
      textGeneratorAccent(common_fixed_8x16_sprite_font_accent)
{
  updateVideo();
}

void PlayerScene::init() {
  if (!PlaybackState.isLooping) {
    SongList::Song currentSong = GameState::data.currentSong;
    player_playGSM(currentSong.filename);
    player_setLoop(true);
  }
}

void PlayerScene::update() {
  // updateVideo();
  if (bn::keypad::b_pressed()) {
      setNextScreen(GameState::Screen::START);
  }
}

void PlayerScene::updateVideo() {
  // background.reset();
  // background = StartVideo::getFrame(videoFrame.floor_integer())
  //                  .create_bg((256 - Math::SCREEN_WIDTH) / 2,
  //                             (256 - Math::SCREEN_HEIGHT) / 2);
  // background.get()->set_mosaic_enabled(true);
  // extraSpeed = (bn::max(extraSpeed - 1, bn::fixed(0)));
  // videoFrame += (1 + extraSpeed / 2) / 2;
  // if (videoFrame >= 30)
  //   videoFrame = 0;

  // auto alpha = 0.7 - bn::fixed(extraSpeed) / 20;
  // if (alpha > 1)
  //   alpha = 1;
  // if (alpha < 0)
  //   alpha = 0;
  // bn::blending::set_transparency_alpha(alpha);
}

void PlayerScene::start() {
//   setNextScreen(GameState::Screen::SELECTION);
}
