#include "SongList.h"
#include <cstddef>
#include "bn_array.h"

namespace SongList {
    const Song songList[] = {
        {
            .name = "Battery acid",
            .filename = "battery_acid.gsm",
            .length = 120,
        },
        {
            .name = "I am not human but neither are you",
            .filename = "i_am_not_human_but_neither_are_you.gsm",
            .length = 120,
        },
        {
            .name = "If you believe it will heal you",
            .filename = "if_you_believe_it_will_heal_you.gsm",
            .length = 120,
        },
        {
            .name = "Magical tragedy aligned",
            .filename = "magical_tragedy_aligned.gsm",
            .length = 120,
        },
        {
            .name = "The saddest story never told",
            .filename = "the_saddest_story_never_told.gsm",
            .length = 120,
        },
    };

    const size_t songCount = sizeof(songList) / sizeof(Song);
}