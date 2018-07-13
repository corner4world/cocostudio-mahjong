//
// Created by farmer on 2018/6/24.
//

#ifndef PROJ_ANDROID_GAMESCENEMANAGER_H
#define PROJ_ANDROID_GAMESCENEMANAGER_H

#include "cocos2d.h"

#define TAG_ALERT                     10000  //提示框层次

using namespace cocos2d;

class GameSceneManager {

public:
    /**
     * 获取GameSceneManager单例
     * @return
     */
    static GameSceneManager *getInstance();
    /**
     * 析构函数
     */
    ~GameSceneManager();

    /**
     * 获取当前场景
     * @return
     */
    Scene *getScene();

    /**
     * 获取可见区域大小
     * @return
     */
    cocos2d::Size getVisibleSize();

    /**
     * 结束游戏
     */
    void end();

private:
    /**
     * 构造函数
     */
    GameSceneManager();
};


#endif //PROJ_ANDROID_GAMESCENEMANAGER_H

