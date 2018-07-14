//
// Created by farmer on 2018/7/8.
//

#include "SettingDlg.h"
#include "GameConfig.h"

using namespace std;

SettingDlg::SettingDlg() : IDialog(), m_btnClose(nullptr), m_pSliderVolume(nullptr)
{
    RegDialogCtrl("Button_Close", m_btnClose);
    RegDialogCtrl("Slider_Volume", m_pSliderVolume);
}
SettingDlg::~SettingDlg(){
}

void SettingDlg::onUILoaded() {
    m_rootNode->setScale(0.5f);
    m_rootNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, 1.0f))); //动画
    m_rootNode->addChild(LayerColor::create(Color4B(0, 0, 0, 200)), -1);
    m_btnClose->addClickEventListener([this](Ref* sender){
        GameConfig::getInstance()->saveConfig();    //关闭前保存配置
        DialogManager::shared()->closeCurrentDialog();
    });
    m_pSliderVolume->setMaxPercent(100);
    m_pSliderVolume->setPercent(static_cast<int>(GameConfig::getInstance()->m_EffectsVolume * 100));
    //滑块移动事件
    m_pSliderVolume->addEventListener([this](Ref*, ui::Slider::EventType type) {
        switch (type) {
            case ui::Slider::EventType::ON_PERCENTAGE_CHANGED : {    //滑动条变化
                int currPercent = m_pSliderVolume->getPercent();    //当前百分比
                int maxPercent = m_pSliderVolume->getMaxPercent();  //最大百分比
                GameConfig::getInstance()->m_EffectsVolume = (float) currPercent / (float) maxPercent;
                break;
            }
            default:
                break;
        }
    });
}

void SettingDlg::onEnter() {
    IDialog::onEnter();
}
