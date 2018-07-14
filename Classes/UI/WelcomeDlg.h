#ifndef __COCOSTUDIO_MAHJONG__WelcomeDlg__
#define __COCOSTUDIO_MAHJONG__WelcomeDlg__

#include "IDialog.h"

class WelcomeDlg : public IDialog<Layer>
{
public:
    WelcomeDlg();
    virtual ~WelcomeDlg();
    CREATE_FUNC(WelcomeDlg);

    virtual void onEnter();

protected:
    virtual const char* csbName() const {return "res/HelloLayer.csb";}
	virtual void onUILoaded();
	
private:
    Button* m_btnLogon;
};


#endif /* defined(__COCOSTUDIO_MAHJONG__WelcomeDlg__) */
