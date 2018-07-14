
#include "AlertDlg.h"

using namespace std;

AlertDlg::AlertDlg() : IDialog(), m_yes(nullptr), m_no(nullptr)
{
    RegDialogCtrl("Button_Alert_OK", m_btnYes);
    RegDialogCtrl("Button_Alert_Cancel", m_btnNo);
    RegDialogCtrl("Text_Alert_Title", m_title);
    RegDialogCtrl("ScrollView_Alert_Content", m_scrollView);
    RegDialogCtrl("Panel_Button_Group_OK", m_one);
    RegDialogCtrl("Panel_Button_Group_Cancel", m_two);
}
//
AlertDlg::~AlertDlg(){
}

void AlertDlg::onUILoaded() {
    m_rootNode->setScale(0.5f);
    m_rootNode->runAction(EaseElasticOut::create(ScaleTo::create(0.5f, 1.0f, 1.0f))); //动画
    m_rootNode->addChild(LayerColor::create(Color4B(0, 0, 0, 200)), -1);
    m_btnYes->addClickEventListener([this](Ref* sender){
        if(m_yes) {
            m_yes();
        }
    });
    m_btnNo->addClickEventListener([this](Ref* sender){
        if(m_no) {
            m_no();
        }
    });
}

void AlertDlg::onEnter() {
	IDialog::onEnter();
}

/**
 * 设置Alert类型
 * @param typeEnum
 *  类型
 * @param autoClose
 *  点击按钮是否关闭窗口
 */
void AlertDlg::setAlertType(AlertDlg::AlertTypeEnum typeEnum, bool autoClose) {
    switch (typeEnum) {
        case AlertTypeEnum::ENUM_ALERT :
            m_one->setVisible(true);
            m_two->setVisible(false);
            break;
        case AlertTypeEnum::ENUM_CONFIRM:
            m_one->setVisible(false);
            m_two->setVisible(true);
            break;
    }
}

/**
 * 设置内容
 * @param content
 *  内容
 * @param title
 *  标题

 */
void AlertDlg::setText(std::string content, std::string title) {
    m_title->setString(title);
    m_scrollView->removeAllChildren();
    ui::Text *pContent = ui::Text::create(content, "Arial", 30);    //设置字体
    pContent->setTextColor(Color4B(Color3B(135, 73, 48)));
    pContent->setPosition(Point::ZERO);
    pContent->setAnchorPoint(Vec2(0, 1));
    pContent->setTextAreaSize(Size(m_scrollView->getContentSize().width, 0)); //实现高度自动调整
    pContent->ignoreContentAdaptWithSize(false);
    pContent->setTextVerticalAlignment(TextVAlignment::CENTER);
    pContent->setTextHorizontalAlignment(TextHAlignment::CENTER);
    float h1 = pContent->getContentSize().height;
    float h2 = m_scrollView->getContentSize().height;
    pContent->setPosition(Vec2(10, ((h2 > h1) ? h2 : h1) - 10));
    m_scrollView->addChild(pContent);
    m_scrollView->setInnerContainerSize(Size(m_scrollView->getContentSize().width, pContent->getContentSize().height + 10));
}


