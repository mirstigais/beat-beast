#include "SpriteProvider.h"

#include "../savefile/GameState.h"

#include "bn_string.h"

#include "bn_sprite_items_menu.h"
#include "bn_sprite_items_progress.h"
#include "bn_sprite_items_wait.h"

bn::sprite_item SpriteProvider::menu() {
  return bn::sprite_items::menu;
}

bn::sprite_item SpriteProvider::wait() {
  return bn::sprite_items::wait;
}

bn::sprite_item SpriteProvider::progress() {
  return bn::sprite_items::progress;
}
