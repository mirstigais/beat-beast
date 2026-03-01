#ifndef MENU_H
#define MENU_H

#include "bn_optional.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"
#include "bn_vector.h"

class Menu {
 public:
  bool isActive() const { return active; }

  struct Option {
    bn::string<40> text;
    bool bDefault = false;
    int startSpriteIndex = 0;
    int endSpriteIndex = 0;
  };

  Menu(bn::sprite_text_generator _normalTextGenerator,
       bn::sprite_text_generator _accentTextGenerator);

  void start(bn::vector<Option, 32> _options,
             bool withSquare = true,
             bool withBlending = false,
             bn::fixed initialScale = 1.5,
             bn::fixed _targetScaleX = 1.5,
             bn::fixed _targetScaleY = 1.5,
             bn::fixed _positionX = 0,
             bn::fixed _positionY = 0,
             unsigned _selectedOption = 0);
  void update();
  void stop();
  void pauseSound();
  void questionSound();
  void clickSound();
  void backSound();

  bool hasStarted() { return options.has_value(); }
  bool hasConfirmedOption() { return confirmedOption > -1; }
  int receiveConfirmedOption() {
    int option = confirmedOption;
    confirmedOption = -1;
    return option;
  }
  unsigned getSelectedOption() { return selectedOption; }

 private:
  bn::sprite_text_generator normalTextGenerator;
  bn::sprite_text_generator accentTextGenerator;
  bn::vector<bn::sprite_ptr, 96> normalTextSprites;
  bn::vector<bn::sprite_ptr, 64> accentTextSprites;
  bn::optional<bn::vector<Option, 32>> options;
  bn::sprite_ptr square;
  bool active = false;
  unsigned selectedOption = 0;
  int confirmedOption = -1;
  bn::fixed targetScaleX = 1.5;
  bn::fixed targetScaleY = 1.5;
  bn::fixed positionX = 0;
  bn::fixed positionY = 0;
  int scrollOffset = 0;
  int maxVisibleOptions = 5;
  int textScrollCounter = 0;
  int textScrollTimer = 0;

  void draw();
  void drawSelected();
  void refresh();
};

#endif  // MENU_H
