
#ifndef _COCOSTUDIO_MAHJONG__AlertDlg__
#define _COCOSTUDIO_MAHJONG__AlertDlg__

#include "IDialog.h"

class AlertDlg : public IDialog<Layer>
{
public:
    AlertDlg();
    virtual ~AlertDlg();
    CREATE_FUNC(AlertDlg);

    //提示类型
    enum AlertTypeEnum {
        ENUM_ALERT = 0,    //一个确定按钮
        ENUM_CONFIRM = 1,    //确定按钮+取消按钮
    };
    void setAlertType(AlertTypeEnum typeEnum, bool autoClose = true);    //设置提示框类型
    void setText(std::string content ,std::string title = "提示");   //设置内容
    void setCallback(std::function<void()> yes, std::function<void()> no) {
        m_yes = yes;
        m_no = no;
    }
protected:
    virtual const char* csbName() const {return "res/AlertLayer.csb";}
	virtual void onUILoaded();

private:
    Button* m_btnYes;
    Button* m_btnNo;
    Button* m_btnOK;
    Text* m_title;
    ui::ScrollView* m_scrollView;
    Node* m_one;
    Node* m_two;
    std::function<void()> m_yes;
    std::function<void()> m_no;
};


#endif /* defined(_COCOSTUDIO_MAHJONG__AlertDlg__) */
