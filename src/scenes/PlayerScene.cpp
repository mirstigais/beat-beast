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

bool paused = false;

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
 	textGenerator.generate({-90, -10}, GameState::data.currentSong.name, songTextSprites);
}

void PlayerScene::update() {
	// updateVideo();
	updatePlayerCounter();

	if (bn::keypad::b_pressed()) {
		setNextScreen(GameState::Screen::START);
	}

	if (bn::keypad::a_pressed()) {
		if (paused)
		player_setPause(paused = false);
		else
		player_setPause(paused = !paused);
	}

	if (bn::keypad::right_pressed()) {
		size_t current_index = (GameState::data.currentSongIndex + 1) % SongList::songCount;
		setCurrentSong(current_index);
	}

	if (bn::keypad::left_pressed()) {
		size_t current_index = (GameState::data.currentSongIndex + SongList::songCount - 1) % SongList::songCount;
		setCurrentSong(current_index);
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
