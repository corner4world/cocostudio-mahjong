
#include "GameOverDlg.h"
#include "LoadingScene.h"
#include "Utility.h"
#include "UIHelper.h"
#include "GameLogic.h"
#include "FvMask.h"
#include "GameLayer.h"

using namespace std;

GameOverDlg::GameOverDlg() : IDialog(), m_gameUI(nullptr)
{
    RegDialogCtrl("Button_Over_Close", m_btnClose);
    RegDialogCtrl("ImageView_Over_Result", m_pOverResultImage);
}

GameOverDlg::~GameOverDlg(){
}

void GameOverDlg::onEnter() {
    IDialog::onEnter();
    showResult();
}

void GameOverDlg::onUILoaded() {
    m_rootNode->setScale(0.5f);
    m_rootNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, 1.0f))); //动画
    m_rootNode->addChild(LayerColor::create(Color4B(0, 0, 0, 200)), -1);
    //
    m_btnClose->addClickEventListener([this](Ref* sender){
        DialogManager::shared()->closeAllDialog();
        m_gameUI->removeEffectNode("EffectNode");//胡牌不自动删除动画,重新开局的时候需要删除动画
        m_gameUI->m_pOperateNotifyGroup->removeAllChildren();
        m_gameUI->m_pOperateNotifyGroup->setVisible(false);
        GameEngine::GetGameEngine()->onGameStart();
//        GameEngine::GetGameEngine()->init();
//        Director::getInstance()->replaceScene(LoadingScene::create());
    });
}

void GameOverDlg::showResult() {
    if (GameEnd.cbHuUser == 0x00) {
        m_pOverResultImage->loadTexture("res/GameOverLayer/result_draw.png");  //流局
    } else {
        m_pOverResultImage->loadTexture((GameEnd.lGameScore[m_gameUI->m_MeChairID] < 0) ? "res/GameOverLayer/result_lose.png" : "res/GameOverLayer/result_win.png");
    }
    //显示牌
    for (uint8_t i = 0; i < m_gameUI->m_CurPlayer; i++) {
        uint8_t cbViewID = m_gameUI->switchViewChairID(i);
        Node *pPlayerViewNode = UIHelper::seekNodeByName(m_rootNode, "PlayerView_" + utility::toString((int) cbViewID));
        ui::ImageView *pOverImgHead = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pPlayerViewNode, "ImageView_Over_Head")); //头像
        ui::Text *pOverScoreText = dynamic_cast<ui::Text *>(UIHelper::seekNodeByName(pPlayerViewNode, "Text_Over_Score"));       //分数
        pOverImgHead->loadTexture(utility::toString("res/GameLayer/im_defaulthead_", m_gameUI->m_Players[i]->getSex() == IPlayer::FEMALE ? 0 : 1, ".png"));    //设置头像
        pOverScoreText->setString(((GameEnd.lGameScore[i] >= 0) ? utility::toString("+", GameEnd.lGameScore[i]) : utility::toString(GameEnd.lGameScore[i])));
        ui::Layout *pOverHandCard = dynamic_cast<ui::Layout *>(UIHelper::seekNodeByName(pPlayerViewNode, "Panel_Over_Hand_Card"));
        pOverHandCard->removeAllChildren();
        ui::ImageView *pOverHuCard = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pPlayerViewNode, "ImageView_Over_Card"));  //胡的那张
        ui::ImageView *pOverHuFlag = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pPlayerViewNode, "ImageView_Over_Hu"));  //胡的那张
        pOverHuCard->setVisible(false);
        pOverHuFlag->setVisible(false);
        if (m_gameUI->m_cbBankerChair == i) { //庄
            ui::Layout *pOverPanelLeft = dynamic_cast<ui::Layout *>(UIHelper::seekNodeByName(pPlayerViewNode, "Panel_Over_Left"));
            ui::ImageView *pOverBanker = ui::ImageView::create("res/GameOverLayer/over_banker.png");
            pOverBanker->setAnchorPoint(Vec2(0.5, 0.5));
            pOverBanker->setPosition(Vec2(20, 96));
            pOverPanelLeft->addChild(pOverBanker);
        }

        uint8_t cbWeaveCount = GameEnd.cbWeaveCount[i];
        if (FvMask::HasAny(GameEnd.cbHuUser, _MASK_(i))) {
            //胡牌手上移除胡的那张牌
            GameLogic::removeCard(GameEnd.cbCardData[i], GameEnd.cbCardCount[i], &GameEnd.cbHuCard, 1);
            GameEnd.cbCardCount[i]--;
            pOverHuCard->loadTexture(UIHelper::getDiscardCardImagePath(0, GameEnd.cbHuCard));
            pOverHuCard->setVisible(true);
            pOverHuFlag->setVisible(true);
        }
        float x = 0;
        for (uint8_t j = 0; j < cbWeaveCount; j++) {   //组合数量
            CMD_WeaveItem weaveItem = GameEnd.WeaveItemArray[i][j];
            Node *pWeaveNode = NULL;
            if (weaveItem.cbWeaveKind == WIK_G) {
                pWeaveNode = CSLoader::createNode("res/Gang0.csb");
            }
            if (weaveItem.cbWeaveKind == WIK_P) {
                pWeaveNode = CSLoader::createNode("res/Peng0.csb");
            }
            pWeaveNode->setScale(0.6f, 0.6f);
            pWeaveNode->setPosition(Vec2(x, 0));
            const std::string &strImagePath = UIHelper::getDiscardCardImagePath(0, weaveItem.cbCenterCard);
            const std::string &strBackImagePath = UIHelper::getDiscardCardImagePath(0, weaveItem.cbCenterCard);
            ui::ImageView *pImageRight = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pWeaveNode, "Image_right"));
            ui::ImageView *pImageLeft = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pWeaveNode, "Image_left"));
            ui::ImageView *pImageCenter = dynamic_cast<ui::ImageView *>(UIHelper::seekNodeByName(pWeaveNode, "Image_center"));
            pImageRight->loadTexture(strImagePath);
            pImageCenter->loadTexture(strImagePath);
            pImageLeft->loadTexture(strImagePath);
            uint8_t wProvideViewID = m_gameUI->switchViewChairID(weaveItem.cbProvideUser);
            switch (cbViewID) {
                case 0:
                    switch (wProvideViewID) {
                        case 0: {
                            if (weaveItem.cbPublicCard == FALSE) {    //暗杠
                                pImageRight->loadTexture(strBackImagePath);
                                pImageLeft->loadTexture(strBackImagePath);
                            }
                            break;
                        }
                        case 1: {
                            pImageLeft->loadTexture(strBackImagePath);
                            break;
                        }
                        case 2: {
                            pImageCenter->loadTexture(strBackImagePath);
                            break;
                        }
                        case 3: {
                            pImageRight->loadTexture(strBackImagePath);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case 1:
                    switch (wProvideViewID) {
                        case 0: {
                            pImageRight->loadTexture(strBackImagePath);
                            break;
                        }
                        case 1: {
                            if (weaveItem.cbPublicCard == FALSE) {    //暗杠
                                pImageRight->loadTexture(strBackImagePath);
                                pImageLeft->loadTexture(strBackImagePath);
                            }
                            break;
                        }
                        case 2: {
                            pImageLeft->loadTexture(strBackImagePath);
                            break;
                        }
                        case 3: {
                            pImageCenter->loadTexture(strBackImagePath);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case 2:
                    switch (wProvideViewID) {
                        case 0: {
                            pImageCenter->loadTexture(strBackImagePath);
                            break;
                        }
                        case 1: {
                            pImageLeft->loadTexture(strBackImagePath);
                            break;
                        }
                        case 2: {
                            if (weaveItem.cbPublicCard == FALSE) {    //暗杠
                                pImageRight->loadTexture(strBackImagePath);
                                pImageLeft->loadTexture(strBackImagePath);
                            }
                            break;
                        }
                        case 3: {
                            pImageRight->loadTexture(strBackImagePath);
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                case 3:
                    switch (wProvideViewID) {
                        case 0: {
                            pImageRight->loadTexture(strBackImagePath);
                            break;
                        }
                        case 1: {
                            pImageCenter->loadTexture(strBackImagePath);
                            break;
                        }
                        case 2: {
                            pImageLeft->loadTexture(strBackImagePath);
                            break;
                        }
                        case 3: {
                            if (weaveItem.cbPublicCard == FALSE) {    //暗杠
                                pImageRight->loadTexture(strBackImagePath);
                                pImageLeft->loadTexture(strBackImagePath);
                            }
                            break;
                        }
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }

            pOverHandCard->addChild(pWeaveNode);
            x += 132;
        }
        for (int j = 0; j < MAX_COUNT - 1 - (3 * cbWeaveCount); j++) {
            ui::ImageView *pCard = UIHelper::createDiscardCardImageView(0, GameEnd.cbCardData[i][j]);
            pCard->setAnchorPoint(Vec2(0, 0));
            pCard->setPosition(Vec2(x, 0));
            pCard->setScale(0.6f, 0.6f);
            pOverHandCard->addChild(pCard);
            x += 43;
        }
    }
}

