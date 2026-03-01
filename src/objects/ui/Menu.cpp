#include "Menu.h"

#include "../../assets/SpriteProvider.h"
#include "../../player/player_sfx.h"

#include "bn_keypad.h"

#define SFX_MOVE "menu_move.pcm"
#define SFX_CLICK "menu_click.pcm"
#define SFX_BACK "menu_back.pcm"
#define SFX_PAUSE "menu_pause.pcm"
#define SFX_QUESTION "menu_question.pcm"

Menu::Menu(bn::sprite_text_generator _normalTextGenerator,
           bn::sprite_text_generator _accentTextGenerator)
    : normalTextGenerator(_normalTextGenerator),
      accentTextGenerator(_accentTextGenerator),
      square(SpriteProvider::menu().create_sprite(0, 0)) {
  square.set_visible(false);
  square.set_z_order(-2);
  square.set_bg_priority(0);
}

void Menu::start(bn::vector<Option, 32> _options,
                 bool withSquare,
                 bool withBlending,
                 bn::fixed initialScale,
                 bn::fixed _targetScaleX,
                 bn::fixed _targetScaleY,
                 bn::fixed _positionX,
                 bn::fixed _positionY,
                 unsigned _selectedOption) {
  if ((int)_selectedOption >= _options.size())
    _selectedOption = _options.size() - 1;
  options = _options;
  selectedOption = _selectedOption;
  confirmedOption = -1;
  active = true;
  targetScaleX = _targetScaleX;
  targetScaleY = _targetScaleY;
  positionX = _positionX;
  positionY = _positionY;

  square.set_visible(withSquare);
  square.set_blending_enabled(withBlending);
  square.set_scale(initialScale);

  normalTextSprites.clear();
  accentTextSprites.clear();

  normalTextGenerator.set_z_order(-2);
  accentTextGenerator.set_z_order(-2);
  normalTextGenerator.set_bg_priority(0);
  accentTextGenerator.set_bg_priority(0);
  normalTextGenerator.set_center_alignment();
  accentTextGenerator.set_center_alignment();
  square.set_position(positionX, positionY);

  scrollOffset = 0;
  
  if ((int)selectedOption > maxVisibleOptions / 2) {
    scrollOffset = (int)selectedOption - maxVisibleOptions / 2;
    if (scrollOffset > (int)options->size() - maxVisibleOptions)
      scrollOffset = (int)options->size() - maxVisibleOptions;
  }
  if (scrollOffset < 0)
    scrollOffset = 0;

  draw();
  drawSelected();
  // refresh(); // draw() calls clear() so we don't need refresh() which just toggles visibility

}

void Menu::update() {
  if (square.horizontal_scale() < targetScaleX) {
    square.set_horizontal_scale(square.horizontal_scale() + 0.25);
    if (square.horizontal_scale() > targetScaleX)
      square.set_horizontal_scale(targetScaleX);
  }
  if (square.vertical_scale() < targetScaleY) {
    square.set_vertical_scale(square.vertical_scale() + 0.25);
    if (square.vertical_scale() > targetScaleY)
      square.set_vertical_scale(targetScaleY);
  }

  if (!hasStarted())
    return;

  // Scroll text
  textScrollTimer++;
  if (textScrollTimer > 20) {
    textScrollTimer = 0;
    textScrollCounter++;
    drawSelected();
  }

  if (bn::keypad::down_pressed()) {
    if ((int)selectedOption < options->size() - 1) {
      selectedOption++;
      if ((int)selectedOption >= scrollOffset + maxVisibleOptions) {
        scrollOffset++;
      }
      textScrollCounter = 0;
      player_sfx_play(SFX_MOVE);
      draw();
      drawSelected();
    } else if ((int)selectedOption == options->size() - 1) {
      selectedOption = 0;
      scrollOffset = 0;
      textScrollCounter = 0;
      player_sfx_play(SFX_MOVE);
      draw();
      drawSelected();
    }
  } else if (bn::keypad::up_pressed()) {
    if (selectedOption > 0) {
      selectedOption--;
      if ((int)selectedOption < scrollOffset) {
        scrollOffset--;
      }
      textScrollCounter = 0;
      player_sfx_play(SFX_MOVE);
      draw();
      drawSelected();
    } else if (selectedOption == 0) {
      selectedOption = options->size() - 1;
      scrollOffset = options->size() - maxVisibleOptions;
      if (scrollOffset < 0)
        scrollOffset = 0;
      textScrollCounter = 0;
      player_sfx_play(SFX_MOVE);
      draw();
      drawSelected();
    }
  } else if (bn::keypad::b_pressed()) {
    int bDefaultIndex = -1;
    for (int i = 0; i < options->size(); i++) {
      if (options->at(i).bDefault)
        bDefaultIndex = i;
    }
    if (bDefaultIndex > -1) {
      selectedOption = bDefaultIndex;
      // Recalculate scroll offset to center selection
      scrollOffset = selectedOption - maxVisibleOptions / 2;
      if (scrollOffset > (int)options->size() - maxVisibleOptions)
        scrollOffset = options->size() - maxVisibleOptions;
      if (scrollOffset < 0)
        scrollOffset = 0;

      textScrollCounter = 0;
      player_sfx_play(SFX_MOVE);
      draw();
      drawSelected();
    }
  } else if (bn::keypad::a_pressed()) {
    confirmedOption = selectedOption;
  }
}

void Menu::stop() {
  square.set_visible(false);
  options.reset();
  normalTextSprites.clear();
  accentTextSprites.clear();
  confirmedOption = -1;
  active = false;
}

void Menu::pauseSound() {
  player_sfx_play(SFX_PAUSE);
}

void Menu::questionSound() {
  player_sfx_play(SFX_QUESTION);
}

void Menu::clickSound() {
  player_sfx_play(SFX_CLICK);
}

void Menu::backSound() {
  player_sfx_play(SFX_BACK);
}

void Menu::draw() {
  normalTextSprites.clear();

  int visibleCount = bn::min((int)options->size(), maxVisibleOptions);
  bn::fixed startY = -(visibleCount * 16 - 8) / 2 + 3;

  for (int i = 0; i < visibleCount; i++) {
    int optionIndex = scrollOffset + i;
    if (optionIndex >= options->size()) break;

    auto startSpriteIndex = normalTextSprites.size();
    
    bn::string<40> text = options->at(optionIndex).text;
    if (text.length() > 18) {
      bn::string<40> truncated;
      truncated.append(text.data(), 15);
      truncated.append("...");
      normalTextGenerator.generate(positionX, positionY + startY + i * 16,
                                 truncated, normalTextSprites);
    } else {
        normalTextGenerator.generate(positionX, positionY + startY + i * 16,
                                 text, normalTextSprites);
    }
    
    auto endSpriteIndex = normalTextSprites.size();
    options->at(optionIndex).startSpriteIndex = startSpriteIndex;
    options->at(optionIndex).endSpriteIndex = endSpriteIndex;
  }

  for (auto& sprite : normalTextSprites)
    sprite.set_mosaic_enabled(true);
}

void Menu::drawSelected() {
  accentTextSprites.clear();

  // Hide the normal text for the selected option if it's visible
  // We need to re-enable all normal sprites first because the selected option changes
  for (auto& sprite : normalTextSprites)
    sprite.set_visible(true);

  if ((int)selectedOption >= scrollOffset && (int)selectedOption < scrollOffset + maxVisibleOptions) {
     // Identify which normal sprites belong to the selected option
     // Since we regenerate normalTextSprites every draw(), we need to find the sprites
     // corresponding to the visual index of the selected option
     int visualIndex = (int)selectedOption - scrollOffset;
     // Re-calculate start/end indices based on how draw() generates them
     // This is tricky because draw() stores indices in the option, but options are refreshed.
     // Actually, draw() updates startSpriteIndex/endSpriteIndex in the options vector.
     // So we can check the selected option's indices.
     
     // IMPORTANT: The indices in options[] refer to the sprites in normalTextSprites.
     // Verify they are within bounds (they should be if draw() was called right before)
     int startIdx = options->at(selectedOption).startSpriteIndex;
     int endIdx = options->at(selectedOption).endSpriteIndex;
     
     for (int i = startIdx; i < endIdx && i < normalTextSprites.size(); i++) {
        normalTextSprites[i].set_visible(false);
     }

     int visibleCount = bn::min((int)options->size(), maxVisibleOptions);
     bn::fixed startY = -(visibleCount * 16 - 8) / 2 + 3;
     
     bn::string<40> text = options->at(selectedOption).text;
     
     if (text.length() > 18) {
        // Scrolling marquee
        bn::string<128> paddedText;
        paddedText.append(text);
        paddedText.append("   ");
        paddedText.append(text);
        paddedText.append("   ");
        bn::string_view paddedView(paddedText);
        int offset = textScrollCounter % (text.length() + 3);
        
        accentTextGenerator.generate(
            positionX, positionY + startY + visualIndex * 16,
            paddedView.substr(offset, 18), accentTextSprites);

     } else {
         accentTextGenerator.generate(
             positionX, positionY + startY + visualIndex * 16,
             text, accentTextSprites);
     }
      
     for (auto& sprite : accentTextSprites)
       sprite.set_mosaic_enabled(true);
  }
}

void Menu::refresh() {
  for (auto& sprite : normalTextSprites)
    sprite.set_visible(true);

  drawSelected();
}
