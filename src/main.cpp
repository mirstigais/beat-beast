#include "assets/SpriteProvider.h"
#include "player/player.h"
#include "player/player_sfx.h"
#include "savefile/SaveFile.h"
#include "scenes/CreditsScene.h"
#include "scenes/StartScene.h"
#include "scenes/OpeningScene.h"
#include "scenes/PlayerScene.h"
#include "utils/Rumble.h"
#include "utils/gbfs/gbfs.h"

#include "bn_bg_palettes.h"
#include "bn_bgs_mosaic.h"
#include "bn_blending.h"
#include "bn_core.h"
#include "bn_optional.h"
#include "bn_sprite_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprites_mosaic.h"
#include "bn_unique_ptr.h"

static const GBFS_FILE* fs = find_first_gbfs_file(0);
bn::optional<bn::unique_ptr<Scene>> scene;

void ISR_VBlank();
bn::unique_ptr<Scene> setNextScene(GameState::Screen nextScreen);
bool hasMainMusic(GameState::Screen screen);
void transitionToNextScene();

void update() {
  bn::core::update();
  player_update(0, [](unsigned current) {});
  player_sfx_update();
}

int main() {
  RUMBLE_init();
  bn::core::init(ISR_VBlank);

  BN_ASSERT(fs != NULL,
            "GBFS file not found.\nUse the ROM that ends with .out.gba!");

  bool isNewSave = SaveFile::initialize();
  if (isNewSave) {
    bool isNewSaveAgain = SaveFile::initialize();
    BN_ASSERT(!isNewSaveAgain,
              "SRAM is not working! Check your emulator settings.");
  }

  player_init();
  player_sfx_init();

  GameState::data.currentScreen = GameState::Screen::OPENING;
  scene = setNextScene(GameState::Screen::OPENING);
  scene->get()->init();

  while (true) {
    scene->get()->update();

    if (scene->get()->hasNextScreen())
      transitionToNextScene();

    update();
  }
}

BN_CODE_IWRAM void ISR_VBlank() {
  player_onVBlank();
  player_sfx_onVBlank();
  bn::core::default_vblank_handler();
}

bn::unique_ptr<Scene> setNextScene(GameState::Screen nextScreen) {
  auto intensity = bn::fixed(SaveFile::data.intensity) / 10;
  auto contrast = bn::fixed(SaveFile::data.contrast) / 10;
  bn::bg_palettes::set_intensity(intensity);
  bn::sprite_palettes::set_intensity(intensity);
  bn::bg_palettes::set_contrast(contrast);
  bn::sprite_palettes::set_contrast(contrast);
  bn::bg_palettes::set_hue_shift_intensity(0);
  bn::sprite_palettes::set_hue_shift_intensity(0);
  GameState::data.currentScreen = nextScreen;

  switch (nextScreen) {
    case GameState::Screen::OPENING:
      return bn::unique_ptr{(Scene*)new OpeningScene(fs)};
    case GameState::Screen::START:
      return bn::unique_ptr{(Scene*)new StartScene(fs)};
    case GameState::Screen::PLAYER:
      return bn::unique_ptr{(Scene*)new PlayerScene(fs)};
    case GameState::Screen::CREDITS:
      return bn::unique_ptr{(Scene*)new CreditsScene(fs)};
    default: {
      BN_ERROR("Next screen not found?");
      return bn::unique_ptr{(Scene*)new StartScene(fs)};
    }
  }
}

bool hasMainMusic(GameState::Screen screen) {
  return screen == GameState::Screen::START;
}

void transitionToNextScene() {
  RUMBLE_stop();

  auto currentScreen = scene->get()->getScreen();
  auto nextScreen = scene->get()->getNextScreen();

  bn::bg_palettes::set_fade_intensity(0);
  bn::sprite_palettes::set_fade_intensity(0);
  bn::fixed alpha = 0;
  for (int i = 0; i < 10; i++) {
    alpha += 0.1;
    bn::bg_palettes::set_fade_intensity(alpha);
    bn::sprite_palettes::set_fade_intensity(alpha);

    update();
  }

  scene.reset();
  update();

  bool keepMusic = (hasMainMusic(currentScreen) && hasMainMusic(nextScreen)) ||
                   nextScreen == GameState::Screen::CREDITS;
  if (keepMusic) {
    player_setPause(false);
  } else {
    player_stop();
    PlaybackState.msecs = 0;
  }
  player_sfx_stop();
  bn::bgs_mosaic::set_stretch(0);
  bn::sprites_mosaic::set_stretch(0);
  bn::blending::restore();

  scene = setNextScene(nextScreen);
  scene->get()->init();
  update();

  for (int i = 0; i < 10; i++) {
    alpha -= 0.1;
    bn::bg_palettes::set_fade_intensity(alpha);
    bn::sprite_palettes::set_fade_intensity(alpha);

    scene->get()->update();
    update();
  }
}
