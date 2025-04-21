#include "StartVideo.h"

#include "bn_array.h"

#include "bn_regular_bg_items_output_00001.h"
#include "bn_regular_bg_items_output_00002.h"
#include "bn_regular_bg_items_output_00003.h"
#include "bn_regular_bg_items_output_00004.h"
#include "bn_regular_bg_items_output_00005.h"
#include "bn_regular_bg_items_output_00006.h"
#include "bn_regular_bg_items_output_00007.h"
#include "bn_regular_bg_items_output_00008.h"
#include "bn_regular_bg_items_output_00009.h"
#include "bn_regular_bg_items_output_00010.h"
#include "bn_regular_bg_items_output_00011.h"
#include "bn_regular_bg_items_output_00012.h"
#include "bn_regular_bg_items_output_00013.h"
#include "bn_regular_bg_items_output_00014.h"
#include "bn_regular_bg_items_output_00015.h"
#include "bn_regular_bg_items_output_00016.h"
#include "bn_regular_bg_items_output_00017.h"
#include "bn_regular_bg_items_output_00018.h"
#include "bn_regular_bg_items_output_00019.h"
#include "bn_regular_bg_items_output_00020.h"
#include "bn_regular_bg_items_output_00021.h"
#include "bn_regular_bg_items_output_00022.h"
#include "bn_regular_bg_items_output_00023.h"
#include "bn_regular_bg_items_output_00024.h"
#include "bn_regular_bg_items_output_00025.h"
#include "bn_regular_bg_items_output_00026.h"
#include "bn_regular_bg_items_output_00027.h"
#include "bn_regular_bg_items_output_00028.h"
#include "bn_regular_bg_items_output_00029.h"
#include "bn_regular_bg_items_output_00030.h"

const bn::array<bn::regular_bg_item, 30> frames = {
    bn::regular_bg_items::output_00001,
    bn::regular_bg_items::output_00002,
    bn::regular_bg_items::output_00003,
    bn::regular_bg_items::output_00004,
    bn::regular_bg_items::output_00005,
    bn::regular_bg_items::output_00006,
    bn::regular_bg_items::output_00007,
    bn::regular_bg_items::output_00008,
    bn::regular_bg_items::output_00009,
    bn::regular_bg_items::output_00010,
    bn::regular_bg_items::output_00011,
    bn::regular_bg_items::output_00012,
    bn::regular_bg_items::output_00013,
    bn::regular_bg_items::output_00014,
    bn::regular_bg_items::output_00015,
    bn::regular_bg_items::output_00016,
    bn::regular_bg_items::output_00017,
    bn::regular_bg_items::output_00018,
    bn::regular_bg_items::output_00019,
    bn::regular_bg_items::output_00020,
    bn::regular_bg_items::output_00021,
    bn::regular_bg_items::output_00022,
    bn::regular_bg_items::output_00023,
    bn::regular_bg_items::output_00024,
    bn::regular_bg_items::output_00025,
    bn::regular_bg_items::output_00026,
    bn::regular_bg_items::output_00027,
    bn::regular_bg_items::output_00028,
    bn::regular_bg_items::output_00029,
    bn::regular_bg_items::output_00030
};

bn::regular_bg_item StartVideo::getFrame(unsigned frame) {
  return frames[frame];
}
