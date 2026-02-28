#include "SongList.h"
#include <cstddef>
#include "bn_array.h"

#include "../../assets/StartVideo.h"
#include "../../assets/DejoVideo.h"

namespace SongList {
    const Song songList[] = {
        {
            .name = "Battery acid",
            .filename = "battery_acid.gsm",
            .length = 120,
            .getVideoFrame = StartVideo::getFrame,
            .videoFramesCount = StartVideo::framesCount,
        },
        {
            .name = "I am not human but neither are you",
            .filename = "i_am_not_human_but_neither_are_you.gsm",
            .length = 120,
            .getVideoFrame = nullptr,
            .videoFramesCount = 0,
        },
        {
            .name = "If you believe it will heal you",
            .filename = "if_you_believe_it_will_heal_you.gsm",
            .length = 120,
            .getVideoFrame = DejoVideo::getFrame,
            .videoFramesCount = DejoVideo::framesCount,
        },
        {
            .name = "Magical tragedy aligned",
            .filename = "magical_tragedy_aligned.gsm",
            .length = 120,
            .getVideoFrame = nullptr,
            .videoFramesCount = 0,
        },
        {
            .name = "The saddest story never told",
            .filename = "the_saddest_story_never_told.gsm",
            .length = 120,
            .getVideoFrame = nullptr,
            .videoFramesCount = 0,
        },
    };

    const size_t songCount = sizeof(songList) / sizeof(Song);
}