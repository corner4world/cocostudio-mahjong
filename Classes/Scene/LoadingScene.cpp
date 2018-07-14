
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

void LoadingScene::keyBackClicked() {
    if(DialogManager::shared()->isAnyDialogShown()) {
        DialogManager::shared()->closeCurrentDialog();
    } else {
        // TODO: 还在继续按下返回键，难道是想要退出游戏？
    }
}
