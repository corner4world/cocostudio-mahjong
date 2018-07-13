
#include "BaseScene.h"
#include "DialogManager.h"

static DialogManager* s_theDialogManager = nullptr;

DialogManager* DialogManager::shared() {
	if(s_theDialogManager == nullptr) {
		s_theDialogManager = new DialogManager();
	}
	return s_theDialogManager;
}

DialogManager::DialogManager()
: m_baseZOrder(1000000)
, m_currentDialog(nullptr)
{
}

DialogManager::~DialogManager() {
}

bool DialogManager::isAnyDialogShown() {
	return (m_currentDialog != nullptr);
}

void DialogManager::showDialog(Node* dialog) {
	if(!dialog) return;
	m_baseZOrder++;
	if(m_currentDialog != nullptr) {
		dialogList.push_back(m_currentDialog);
		m_currentDialog->setVisible(false);
        m_currentDialog->setPositionX(20000);
	}
	m_currentDialog = dialog;
	m_currentDialog->setLocalZOrder(m_baseZOrder);
	CC_SAFE_RETAIN(m_currentDialog);
	auto scene = Director::getInstance()->getRunningScene();
	if(scene) {
		scene->addChild(m_currentDialog, m_baseZOrder, m_baseZOrder);
	}
}

void DialogManager::closeDialog(Node* dialog) {
	if(!dialog) return;
	if(m_currentDialog == dialog) {
		closeCurrentDialog();
	} else {
		std::vector<Node*>::iterator iter = dialogList.begin();
		while(iter != dialogList.end()) {
			if(*iter == dialog) {
				dialogList.erase(iter);
				dialog->setVisible(false);
				dialog->removeFromParent();
				CC_SAFE_RELEASE_NULL(dialog);
				break;
			}
			iter++;
		}
	}
}

void DialogManager::closeAllDialog() {
	std::vector<Node*>::iterator iter = dialogList.begin();
	while(iter != dialogList.end()) {
		(*iter)->setVisible(false);
		(*iter)->removeFromParent();
		CC_SAFE_RELEASE_NULL(*iter);
		iter++;
	}
	dialogList.clear();
	if(m_currentDialog != nullptr) {
		m_currentDialog->setVisible(false);
		m_currentDialog->removeFromParent();
		CC_SAFE_RELEASE_NULL(m_currentDialog);
	}
}

void DialogManager::closeCurrentDialog() {
	if(m_currentDialog == nullptr) {
		return;
	}
	m_currentDialog->setVisible(false);
	m_currentDialog->removeFromParent();
	CC_SAFE_RELEASE_NULL(m_currentDialog);
	if(!dialogList.empty()) {
		m_currentDialog = dialogList.at(dialogList.size() - 1);
		dialogList.pop_back();
        m_currentDialog->setVisible(true);
        m_currentDialog->setPositionX(0);
	}
}



