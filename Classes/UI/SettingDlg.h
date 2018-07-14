//
// Created by farmer on 2018/7/8.
//  游戏设置层

#ifndef COCOSTUDIO_MAHJONG_SETLAYER_H
#define COCOSTUDIO_MAHJONG_SETLAYER_H

#include "IDialog.h"

class SettingDlg : public IDialog<Layer>
{
public:
    SettingDlg();
    virtual ~SettingDlg();
    CREATE_FUNC(SettingDlg);

    virtual void onEnter();

protected:
    virtual const char* csbName() const {return "res/SetLayer.csb";}
    virtual void onUILoaded();

private:
    Button* m_btnClose;
    ui::Slider * m_pSliderVolume;   //声音滑动条
};

#endif //COCOSTUDIO_MAHJONG_SETLAYER_H
