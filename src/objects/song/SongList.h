#include <cstddef>
#ifndef SONG_LIST_H
#define SONG_LIST_H

#include "bn_regular_bg_item.h"

namespace SongList {
    #define MAX_NAME_LEN 40

    struct Song {
        char name[MAX_NAME_LEN];
        char filename[MAX_NAME_LEN];
        int length;
        bn::regular_bg_item (*getVideoFrame)(unsigned);
        unsigned videoFramesCount;
    };

    extern const Song songList[];
    extern const size_t songCount;
}

#endif // SONG_LIST_H
