
#include "LoadingScene.h"
#include "WelcomeDlg.h"

USING_NS_CC;

LoadingScene::LoadingScene() : BaseScene()
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
    if ( !BaseScene::init() )
    {
        return false;
	}
    return true;
}

void LoadingScene::onEnter()
{
    BaseScene::onEnter();
    this->addChild(WelcomeDlg::create());
}

void LoadingScene::onExit()
{
	BaseScene::onExit();
}

