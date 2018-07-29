
#include "BaseScene.h"
#include "DialogManager.h"
#include "DelayCall.h"
#include "AlertDlg.h"

BaseScene::BaseScene() : m_androidEvent(nullptr)
{
    m_ntfMgr = __NotificationCenter::getInstance();
}

BaseScene::~BaseScene()
{
}

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    DelayCall::clear();
    if ( !Scene::init() )
    {
        return false;
	}
    Size sizeOverlayer = Director::getInstance()->getWinSize();
    Color4B bgColor(255, 255, 255, 255);
    LayerColor* maskColorLayer = LayerColor::create(bgColor, sizeOverlayer.width, sizeOverlayer.height);
    this->addChild(maskColorLayer);
    return true;
}

void BaseScene::onEnter() {
	Scene::onEnter();
    m_androidEvent = EventListenerKeyboard::create();
    m_androidEvent->setEnabled(true);
    m_androidEvent->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        log("Scene.onKeyReleased:%d", keyCode);
        event->stopPropagation();
        if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
            this->keyBackClicked();
        } else if(keyCode == EventKeyboard::KeyCode::KEY_MENU) {
            this->keyMenuClicked();
        }
    };
    this->_eventDispatcher->addEventListenerWithFixedPriority(m_androidEvent, 1);
    this->scheduleUpdate();
}

void BaseScene::onExit() {
    this->unscheduleUpdate();
    if(m_androidEvent) {
        this->_eventDispatcher->removeEventListener(m_androidEvent);
        m_androidEvent = nullptr;
    }
    m_ntfMgr->removeAllObservers(this);
    Scene::onExit();
}

void BaseScene::addEventListener(const std::string& name, SEL_CallFuncO theFunction) {
    m_ntfMgr->addObserver(this, theFunction, name, NULL);
}

void BaseScene::update(float delta) {
    Scene::update(delta);
    DelayCall::tick(delta);
}

void BaseScene::keyBackClicked() {
    AlertDlg* node = dynamic_cast<AlertDlg*>(DialogManager::shared()->getCurrentDialog());
    if(node == nullptr) {
        // 退出游戏
        auto alert = AlertDlg::create();
        alert->setAlertType(AlertDlg::ENUM_CONFIRM);
        alert->setCallback([]() {
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        }, []() {
            DialogManager::shared()->closeCurrentDialog();
        });
        alert->setText("退出游戏后，本局游戏将直接结束无法恢复，确定是否退出？");
        DialogManager::shared()->showDialog(alert);
    } else {
        DialogManager::shared()->closeCurrentDialog();
    }
}

void BaseScene::keyMenuClicked() {
}

void BaseScene::onBackBtnPressed(Ref*) {
    keyBackClicked();
}

void BaseScene::onMenuBtnPressed(Ref*) {
    keyMenuClicked();
}


