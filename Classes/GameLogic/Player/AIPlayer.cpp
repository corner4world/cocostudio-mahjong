//
// Created by farmer on 2018/7/5.
//
#include "Common.h"
#include "AIPlayer.h"

/**
 * AI玩家
 * @param sex
 * @param pGameEngineEventListener
 */
AIPlayer::AIPlayer(PlayerSex sex, IGameEngineEventListener *pGameEngineEventListener)
        : IPlayer(true, sex, pGameEngineEventListener) {
    pGameEngineEventListener->setIPlayer(this);
}

AIPlayer::~AIPlayer() {
    CC_SAFE_DELETE(m_pGameEngineEventListener);
}
