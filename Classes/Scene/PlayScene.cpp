
#include "PlayScene.h"
#include "PlayScene.h"
#include "DialogManager.h"
#include "GameLayer.h"

PlayScene::PlayScene() : BaseScene()
{
}

PlayScene::~PlayScene()
{
}

bool PlayScene::init()
{
    if ( !BaseScene::init() )
    {
        return false;
    }
    return true;
}

void PlayScene::onEnter()
{
    BaseScene::onEnter();
    this->addChild(GameLayer::create()->GetLayer());
}

void PlayScene::onExit()
{
    BaseScene::onExit();
}

void PlayScene::keyBackClicked() {
    if(DialogManager::shared()->isAnyDialogShown()) {
        DialogManager::shared()->closeCurrentDialog();
    } else {
        // TODO: 还在继续按下返回键，难道是想要退出游戏？
    }
}
