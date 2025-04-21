#include "OpeningScene.h"

#include "../assets/fonts/common_variable_8x16_sprite_font.h"
#include "../assets/fonts/common_variable_8x16_sprite_font_accent.h"
#include "../player/player.h"
#include "../utils/Math.h"

#include "bn_blending.h"
#include "bn_keypad.h"
#include "bn_regular_bg_items_splash_art.h"

#define WAIT 50

OpeningScene::OpeningScene(const GBFS_FILE* _fs)
    : Scene(GameState::Screen::START, _fs),
      background(bn::regular_bg_items::splash_art.create_bg(
          (256 - Math::SCREEN_WIDTH) / 2,
          (256 - Math::SCREEN_HEIGHT) / 2))
{
  background->set_blending_enabled(true);
  bn::blending::set_fade_alpha(0);
}

void OpeningScene::init() {
  wait = WAIT;
}

void OpeningScene::update() {
  if (bn::blending::fade_alpha() < 0.75) {
    bn::blending::set_fade_alpha(bn::blending::fade_alpha() + 0.005);
  }

  if (wait > 0)
    wait--;

  if (wait == 0 || bn::keypad::start_pressed())
    setNextScreen(GameState::Screen::START);
}
