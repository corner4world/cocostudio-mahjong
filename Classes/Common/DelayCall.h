//
// Created by farmer on 2018/7/8.
//

#ifndef COCOSTUDIO_MAHJONG_DELAYCALL_H
#define COCOSTUDIO_MAHJONG_DELAYCALL_H

#include "cocos2d.h"

using namespace cocos2d;

class DelayCall {
public:
    static void tick(float delta);
    static void add(std::function<void(void)> fun, float delay, int count = 1);
    static void clear();
};


#endif //COCOSTUDIO_MAHJONG_DELAYCALL_H
