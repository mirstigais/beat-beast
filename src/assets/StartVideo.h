#ifndef START_VIDEO_H
#define START_VIDEO_H

#include "bn_regular_bg_item.h"

namespace StartVideo {

constexpr unsigned framesCount = 30;

bn::regular_bg_item getFrame(unsigned frame);

}  // namespace StartVideo

#endif  // START_VIDEO_H
