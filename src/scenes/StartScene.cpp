#include "StartScene.h"

#include "../assets/StartVideo.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font_accent.h"
#include "../player/player.h"
#include "../savefile/SaveFile.h"
#include "../utils/Math.h"

#include "bn_blending.h"
#include "bn_keypad.h"
#include "bn_sprite_items_start_logo1.h"
#include "bn_sprite_items_start_logo2.h"
#include "bn_sprite_items_start_logo3.h"
#include "bn_sprite_items_start_logo4.h"

#define HORSE_X 40
#define HORSE_Y 90
#define BPM 85
#define BEAT_PREDICTION_WINDOW 100

StartScene::StartScene(const GBFS_FILE* _fs)
    : Scene(GameState::Screen::START, _fs),
      textGenerator(common_fixed_8x16_sprite_font),
      textGeneratorAccent(common_fixed_8x16_sprite_font_accent),
      menu(bn::unique_ptr{new Menu(textGenerator, textGeneratorAccent)}),
      songSelectMenu(bn::unique_ptr{new Menu(textGenerator, textGeneratorAccent)})
{
  updateVideo();
}

void StartScene::init() {
  bn::vector<Menu::Option, 10> options;
  options.push_back(Menu::Option{.text = "Play"});
  options.push_back(Menu::Option{.text = "Credits"});
  menu->start(options, false);

  if (!PlaybackState.isLooping) {
    player_playGSM("battery_acid.gsm");
    player_setLoop(true);
  }
}

void StartScene::update() {
  if (!credits) {
    menu->update();
    if (menu->hasConfirmedOption()) {
      auto confirmedOption = menu->receiveConfirmedOption();
      processMenuOption(confirmedOption);
    }
  }

  const int PER_MINUTE = 71583;            // (1/60000) * 0xffffffff
  int audioLag = SaveFile::data.audioLag;  // (0 on real hardware)
  int msecs = PlaybackState.msecs - audioLag + BEAT_PREDICTION_WINDOW;
  int beat = Math::fastDiv(msecs * BPM, PER_MINUTE);
  bool isNewBeat = beat != lastBeat;
  lastBeat = beat;
  if (isNewBeat && !credits)
    extraSpeed = 10;

  if (isNewBeat && !credits) {
    // horse->jump();
  }

  updateVideo();

  if (credits &&
      (int)PlaybackState.msecs - SaveFile::data.audioLag >= FINAL_SONG_LOOP) {
    setNextScreen(GameState::Screen::CREDITS);
  }
}

void StartScene::updateVideo() {
  background.reset();
  background = StartVideo::getFrame(videoFrame.floor_integer())
                   .create_bg((256 - Math::SCREEN_WIDTH) / 2,
                              (256 - Math::SCREEN_HEIGHT) / 2);
  background.get()->set_mosaic_enabled(true);
  extraSpeed = (bn::max(extraSpeed - 1, bn::fixed(0)));
  videoFrame += (1 + extraSpeed / 2) / 2;
  if (videoFrame >= 30)
    videoFrame = 0;

  auto alpha = 0.7 - bn::fixed(extraSpeed) / 20;
  if (alpha > 1)
    alpha = 1;
  if (alpha < 0)
    alpha = 0;
  bn::blending::set_transparency_alpha(alpha);
}

void StartScene::processMenuOption(int option) {
  BN_LOG(option);
  switch (option) {
    case 0: {  // Start
      menu->stop();
      menu->questionSound();

      bn::vector<Menu::Option, 10> options;
      options.push_back(Menu::Option{.text = "DDD"});
      options.push_back(Menu::Option{.text = "yyyy"});
      songSelectMenu->start(options, false);
      break;
    }
    case 1: {  // Credits
      player_playGSM("bonus.gsm");
      credits = true;
      break;
    }
    default: {
    }
  }
}

void StartScene::start() {
  setNextScreen(GameState::Screen::SELECTION);
}
