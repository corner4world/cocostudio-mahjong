
#ifndef COCOSTUDIO_MAHJONG_GameOverDlg_H
#define COCOSTUDIO_MAHJONG_GameOverDlg_H

#include "IDialog.h"
#include "GameCmd.h"
#include "IPlayer.h"

class GameOverDlg : public IDialog<Layer>
{
public:
    GameOverDlg();
    virtual ~GameOverDlg();
    CREATE_FUNC(GameOverDlg);

    virtual void onEnter();

protected:
    virtual const char* csbName() const {return "res/GameOverLayer.csb";}
    virtual void onUILoaded();

private:
    Button* m_btnClose;
    ui::ImageView *m_pOverResultImage;
};

#endif //COCOSTUDIO_MAHJONG_GameOverDlg_H
