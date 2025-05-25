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
        .name = "Another song",
        .filename = "lazer.gsm",
        .length = 120,
        },
    };

    const size_t songCount = sizeof(songList) / sizeof(Song);
}