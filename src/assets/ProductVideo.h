#ifndef PRODUCT_VIDEO
#define PRODUCT_VIDEO

#include "bn_regular_bg_item.h"

namespace ProductVideo {

constexpr unsigned framesCount = 250;

bn::regular_bg_item getFrame(unsigned frame);

}

#endif
