#ifndef COCOSTUDIO_MAHJONG_LoadingScene__
#define COCOSTUDIO_MAHJONG_LoadingScene__

#include "BaseScene.h"

class LoadingScene : public BaseScene
{
public:
    LoadingScene();
    virtual ~LoadingScene();

	virtual void onEnter();
	virtual void onExit();
    virtual bool init();
    virtual void keyBackClicked();

    CREATE_FUNC(LoadingScene);

};

#endif // COCOSTUDIO_MAHJONG_LoadingScene__
