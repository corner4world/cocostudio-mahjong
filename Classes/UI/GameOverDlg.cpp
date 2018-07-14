
#include "GameOverDlg.h"
#include "LoadingScene.h"
#include "Utility.h"
#include "UIHelper.h"
#include "GameLogic.h"
#include "FvMask.h"

using namespace std;

GameOverDlg::GameOverDlg() : IDialog()
{
    RegDialogCtrl("Button_Over_Close", m_btnClose);
    RegDialogCtrl("ImageView_Over_Result", m_pOverResultImage);
}

GameOverDlg::~GameOverDlg(){
}

void GameOverDlg::onUILoaded() {
    m_rootNode->setScale(0.5f);
    m_rootNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, 1.0f))); //动画
    m_rootNode->addChild(LayerColor::create(Color4B(0, 0, 0, 200)), -1);
    //
    m_btnClose->addClickEventListener([this](Ref* sender){
        DialogManager::shared()->closeAllDialog();
        Director::getInstance()->replaceScene(LoadingScene::create());
    });
}


void GameOverDlg::onEnter() {
    IDialog::onEnter();
}
