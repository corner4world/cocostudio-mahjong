//
// Created by farmer on 2018/6/24.
//

#include "GameSceneManager.h"
#include "LoadingScene.h"
#include "AlertDlg.h"

static GameSceneManager* s_pGameSceneManager = nullptr;

GameSceneManager* GameSceneManager::getInstance() {
    if(s_pGameSceneManager == nullptr) {
        s_pGameSceneManager = new GameSceneManager();
    }
    return s_pGameSceneManager;
}

GameSceneManager::GameSceneManager() {
    cocos2d::log("初始化 GameSceneManager");
}

GameSceneManager::~GameSceneManager() {
    cocos2d::log("释放 GameSceneManager");
}

Scene *GameSceneManager::getScene() {
    return Director::getInstance()->getRunningScene();
}

/**
 * 获取可视大小
 * @return
 */
cocos2d::Size GameSceneManager::getVisibleSize() {
    return Director::getInstance()->getVisibleSize();
}

/**
 * 结束游戏
 */
void GameSceneManager::end() {
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}



