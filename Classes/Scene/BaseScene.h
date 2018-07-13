
#ifndef __COCOSTUDIO_MAHJONG__BaseScene__
#define __COCOSTUDIO_MAHJONG__BaseScene__

#include "Common.h"
#include "DialogManager.h"

class BaseScene : public Scene
{
public:
    BaseScene();
    virtual ~BaseScene();

    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    virtual void update(float delta);
    virtual void addEventListener(const std::string& name, SEL_CallFuncO);

    CREATE_FUNC(BaseScene);

protected:
    virtual void keyBackClicked();
    virtual void keyMenuClicked();

private:
    virtual void onBackBtnPressed(Ref*);
    virtual void onMenuBtnPressed(Ref*);

protected:
    __NotificationCenter*  m_ntfMgr;
    EventListenerKeyboard* m_androidEvent;
};

#endif /* defined(__COCOSTUDIO_MAHJONG__BaseScene__) */
