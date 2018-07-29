
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
    this->addChild(GameLayer::create());
}

void PlayScene::onExit()
{
    BaseScene::onExit();
}

