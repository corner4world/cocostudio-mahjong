
#ifndef __Qv__PlayScene__
#define __Qv__PlayScene__

#include "BaseScene.h"
#include "IDialog.h"

class PlayScene : public BaseScene
{
public:
    PlayScene();
    virtual ~PlayScene();

    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    virtual void keyBackClicked();

    CREATE_FUNC(PlayScene);
};

#endif /* defined(__Qv__PlayScene__) */
