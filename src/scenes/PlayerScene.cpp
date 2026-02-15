#include "PlayerScene.h"

#include "../assets/StartVideo.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font.h"
#include "../assets/fonts/common_fixed_8x16_sprite_font_accent.h"
#include "../player/player.h"
#include "../savefile/SaveFile.h"
#include "../utils/Math.h"
#include "../objects/song/SongList.h"
#include "bn_keypad.h"
#include "../player/PlaybackState.h"
#include "bn_sprite_text_generator.h"
#include "../objects/song/SongList.h"
// #include <../objects/song/SongList.h>

#define SCROLL_SPEED 0.5

PlayerScene::PlayerScene(const GBFS_FILE* _fs)
    : Scene(GameState::Screen::PLAYER, _fs),
      textGenerator(common_fixed_8x16_sprite_font),
      textGeneratorAccent(common_fixed_8x16_sprite_font_accent)
{
  updateVideo();
}

void PlayerScene::init() {
 	size_t current_index = GameState::data.currentSongIndex;
	setCurrentSong(current_index);
	// player_playGSM(currentSong.filename);


//   if (!PlaybackState.isLooping) {
//     player_playGSM(currentSong.filename);
//     player_setLoop(true);
//   }
}

void PlayerScene::setCurrentSong(size_t index) {
    GameState::data.currentSongIndex = index;
    GameState::data.currentSong = SongList::songList[index];
    player_playGSM(GameState::data.currentSong.filename);

    songTextSprites.clear();
    songTextOriginalX.clear();   // clear old original X positions
    songTextOriginalY.clear();

    int single_width = textGenerator.width(GameState::data.currentSong.name);
    
    if (single_width > 180) {
        // Continuous scrolling setup
        // Use larger buffer to avoid truncation of long names when duplicated
        bn::string<128> double_text(GameState::data.currentSong.name);
        double_text += "   ";
        
        // Calculate the cycle width based on the FIRST part of the string including spacing
        text_cycle_width = textGenerator.width(double_text);
        
        double_text += GameState::data.currentSong.name;
        textGenerator.generate({-90, -10}, double_text, songTextSprites);
        
        scroll_enabled = true;
    } else {
        // Static text
        textGenerator.generate({-90, -10}, GameState::data.currentSong.name, songTextSprites);
        text_cycle_width = 0;
        scroll_enabled = false;
    }

    // save each sprite's initial center X
    for (auto& s : songTextSprites) {
        songTextOriginalX.push_back(s.x());
        songTextOriginalY.push_back(s.y());
    }

    song_text_width = single_width;
    scroll_x = 0;
}

void PlayerScene::update() {
	// updateVideo();
	updatePlayerCounter();

	if (bn::keypad::b_pressed()) {
		setNextScreen(GameState::Screen::START);
	}

	if (bn::keypad::a_pressed()) {
		player_setPause(paused = !paused);
	}

	if (bn::keypad::right_pressed() || song_finished()) {
		size_t current_index = (GameState::data.currentSongIndex + 1) % SongList::songCount;
		setCurrentSong(current_index);
	}

	if (bn::keypad::left_pressed()) {
		size_t current_index = (GameState::data.currentSongIndex + SongList::songCount - 1) % SongList::songCount;
		setCurrentSong(current_index);
	}

    if(scroll_enabled && !paused)
    {
        scroll_x -= SCROLL_SPEED;

        if (scroll_x <= -text_cycle_width) {
            scroll_x += text_cycle_width;
        }

        for(int i = 0; i < songTextSprites.size(); ++i)
        {
            songTextSprites[i].set_x(songTextOriginalX[i] + scroll_x);
        }
    }
}

bn::string<32> format_hms(int h, int m, int s) {
    bn::string<32> result;
    if(h < 10) result += "0"; 
    result += bn::to_string<2>(h);
    result += ":";

    if(m < 10) result += "0";
    result += bn::to_string<2>(m);
    result += ":";

    if(s < 10) result += "0";
    result += bn::to_string<2>(s);

    return result;
}

void seconds_to_hms(uint32_t total_seconds, int& h, int& m, int& s) {
    h = total_seconds / 3600;
    int remainder = total_seconds % 3600;
    m = remainder / 60;
    s = remainder % 60;
}

void PlayerScene::updatePlayerCounter() {
	// Get current offset in bytes
	uint32_t cursor_bytes = player_getCursor();

	// Convert using the same scale factor (fixed-point)
	uint32_t elapsed_sec = fracumul(cursor_bytes, 1146880);
	uint32_t total_sec =  GameState::data.currentSong.length;

    if(elapsed_sec > 5999) {
        elapsed_sec = 5999;
    }

	int eh, em, es;
	int th, tm, ts;

	seconds_to_hms(elapsed_sec, eh, em, es);
	seconds_to_hms(total_sec, th, tm, ts);

	bn::string<32> elapsed_str = format_hms(eh, em, es);
	bn::string<32> total_str = format_hms(th, tm, ts);

	bn::string<64> time_string = elapsed_str + " / " + total_str;

	timeTextSprites.clear();
	textGeneratorAccent.generate({-90, 10}, time_string, timeTextSprites);
}

bool PlayerScene::song_finished() {
    return !player_isPlaying() && !paused;
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
