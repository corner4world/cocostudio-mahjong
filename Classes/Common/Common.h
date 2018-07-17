
#ifndef COCOSTUDIO_MAHJONG_Common_h
#define COCOSTUDIO_MAHJONG_Common_h

// 系统级
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <stdint.h>

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::ui;
using namespace cocostudio;
using namespace cocostudio::timeline;

// 识别是不是64位编译
#if defined(__x86_64__) || defined(__LP64__) || defined(__amd64)
    #define IS_BUILD_FOR_64_BIT     1
#endif


#endif
