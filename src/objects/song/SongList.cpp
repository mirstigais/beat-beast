#include "SongList.h"
#include <cstddef>

namespace SongList {
    const Song songList[] = {
        {
            "Battery acid",
            "battery_acid.gsm",
            120,
        },
        {
            "Another song",
            "lazer.gsm",
            120,
        },
    };

    const size_t songCount = sizeof(songList) / sizeof(Song);
}