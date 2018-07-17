
#ifndef COCOSTUDIO_MAHJONG_GameOverDlg_H
#define COCOSTUDIO_MAHJONG_GameOverDlg_H

#include "IDialog.h"
#include "GameCmd.h"
#include "IPlayer.h"

class GameLayer;

class GameOverDlg : public IDialog<Layer>
{
public:
    GameOverDlg();
    virtual ~GameOverDlg();
    CREATE_FUNC(GameOverDlg);

    virtual void onEnter();

    void setGameUI(GameLayer* game, const CMD_S_GameEnd& data) {
        m_gameUI = game;
        memcpy(&GameEnd, &data, sizeof(CMD_S_GameEnd));
    }

protected:
    virtual const char* csbName() const {return "res/GameOverLayer.csb";}
    virtual void onUILoaded();
    void showResult();

private:
    GameLayer* m_gameUI;
    CMD_S_GameEnd GameEnd;
    Button* m_btnClose;
    ui::ImageView *m_pOverResultImage;
};

#endif //COCOSTUDIO_MAHJONG_GameOverDlg_H
