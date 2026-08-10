#include "SpriteProvider.h"

#include "../savefile/GameState.h"

#include "bn_string.h"

#include "bn_sprite_items_wait.h"

bn::sprite_item SpriteProvider::menu() {
  return bn::sprite_items::wait;
}
