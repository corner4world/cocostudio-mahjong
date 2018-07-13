#include "WelcomeDlg.h"
#include "AlertDlg.h"
#include "GameSceneManager.h"
#include "PlayScene.h"

using namespace std;

WelcomeDlg::WelcomeDlg() : IDialog()
{
    RegDialogCtrl("Button_Logon", m_btnLogon);
}

WelcomeDlg::~WelcomeDlg(){
}

void WelcomeDlg::onUILoaded() {
    m_btnLogon->addClickEventListener([this](Ref* sender) {
        auto alert = AlertDlg::create();
        alert->setAlertType(AlertDlg::ENUM_ALERT);
        alert->setCallback([]() {
            DialogManager::shared()->closeAllDialog();
            Director::getInstance()->replaceScene(PlayScene::create());
        }, nullptr);
        alert->setText( "欢迎运行此游戏，此游戏是基于Cocos2d-X的开源单机麻将，\n"
                       "本游戏使用的资源全部收集自互联网，若侵犯了您的权益请联系我进行删除。\n"
                       "希望此游戏源码可以帮助更多的人快速入门使用CPP开发Cocos2d-X，"
                       "获取更多软件与游戏开发信息请关注我的博客：\n"
                       "https://www.xiyoufang.com" );
        DialogManager::shared()->showDialog(alert);
    });
}

void WelcomeDlg::onEnter()
{
	IDialog::onEnter();
}

