#include "SongList.h"
#include <cstddef>
#include "bn_array.h"

#include "../../assets/StartVideo.h"
#include "../../assets/TheSaddestStoryDancingVideo.h"
#include "../../assets/ProductVideo.h"
#include "../../assets/MagicalTragedyVideo.h"
#include "../../assets/IfYouBelieveItVideo.h"
#include "../../assets/IamNotHumanVideo.h"
#include "../../assets/ComfortVideo.h"

namespace SongList {
    const Song songList[] = {
        {
            .name = "The saddest story never told",
            .filename = "the_saddest_story_never_told.gsm",
            .length = 235,
            .getVideoFrame = TheSaddestStoryDancingVideo::getFrame,
            .videoFramesCount = TheSaddestStoryDancingVideo::framesCount,
        },
        {
            .name = "I am a product",
            .filename = "i_am_a_product.gsm",
            .length = 195,
            .getVideoFrame = ProductVideo::getFrame,
            .videoFramesCount = ProductVideo::framesCount,
        },
        {
            .name = "Magical tragedy aligned",
            .filename = "magical_tragedy_aligned.gsm",
            .length = 156,
            .getVideoFrame = MagicalTragedyVideo::getFrame,
            .videoFramesCount = MagicalTragedyVideo::framesCount,
        },
        {
            .name = "If you believe it will heal you",
            .filename = "if_you_believe_it_will_heal_you.gsm",
            .length = 324,
            .getVideoFrame = IfYouBelieveItVideo::getFrame,
            .videoFramesCount = IfYouBelieveItVideo::framesCount,
        },
        {
            .name = "I am not human but neither are you",
            .filename = "i_am_not_human_but_neither_are_you.gsm",
            .length = 232,
            .getVideoFrame = IamNotHumanVideo::getFrame,
            .videoFramesCount = IamNotHumanVideo::framesCount,
        },
        {
            .name = "Bonus track 1:My comfort characters commit suicide",
            .filename = "my_comfort_characters_commit_suicide.gsm",
            .length = 145,
            .getVideoFrame = ComfortVideo::getFrame,
            .videoFramesCount = ComfortVideo::framesCount,
        },
        {
            .name = "Bonus track 2: Battery acid",
            .filename = "battery_acid.gsm",
            .length = 176,
            .getVideoFrame = StartVideo::getFrame,
            .videoFramesCount = StartVideo::framesCount,
        },
    };

    const size_t songCount = sizeof(songList) / sizeof(Song);
}