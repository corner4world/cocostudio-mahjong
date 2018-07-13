
#ifndef COCOSTUDIO_MAHJONG_IDialog__
#define COCOSTUDIO_MAHJONG_IDialog__

#include "Common.h"
#include "DialogManager.h"

#define RegDialogCtrl(NAME, MEMBERVARIABLE)     registerCtrl(NAME, (Node**)&(this->MEMBERVARIABLE))

template<typename T = Layer>
class IDialog : public T
{
public:
	IDialog() : T()
	, m_rootNode(nullptr)
    , m_rootAction(nullptr)
	, m_nAutoScaleRate(1.0f)
    , m_canClosebyBackBtn(true)
	{
		m_ntfMgr = __NotificationCenter::getInstance();
    }

    virtual ~IDialog() {
		this->clear();
    }

    virtual bool init() {
        bool ret = T::init();
        if(ret) {
			return this->loadfile();
        }
        return ret;
    }

	bool loadfile() {
        std::string fileName = csbName();
		this->m_rootNode = CSLoader::createNode(fileName);
		if(this->m_rootNode) {
            this->m_rootAction = CSLoader::createTimeline(fileName);
			this->addChild(this->m_rootNode, 1);
			//log("------------bindNodeByName------------");
			this->bindNodeByName(this->m_rootNode);
			this->onUILoaded();
			return true;
		}
		return false;
	}

	float getAutoScaleRate() const {return this->m_nAutoScaleRate;}

	virtual void onEnter() {
		T::onEnter();
		//this->m_ntfMgr->addObserver(this, callfuncO_selector(IDialog::onBackBtnPressed), EVENT_KEY_BACK_CLICK, NULL);
	}

	virtual void onExit() {
		this->m_ntfMgr->removeAllObservers(this);
		T::onExit();
	}

	virtual void dispose() {
		this->setVisible(false);
		this->removeFromParent();
	}

	virtual void addEventListener(const std::string& name, SEL_CallFuncO theFunction){
		this->m_ntfMgr->addObserver(this, theFunction, name, NULL);
	}

	virtual void androidKeyBackClicked() {
		DialogManager::shared()->closeDialog(this);
	}

	void onBackBtnPressed(Ref*) {
		this->androidKeyBackClicked();
	}

    CC_SYNTHESIZE_READONLY(bool, m_canClosebyBackBtn, CanClosebyBackBtn);
	
protected:
    virtual const char* csbName() const = 0;

    virtual void onUILoaded() {}

    Node* getChildByName(const char* name) const {
        Node* ret = NULL;
        if(name) {
            std::map<std::string, Node*>::const_iterator iter = this->m_allCtrl.find(name);
            if(iter != this->m_allCtrl.end()) {
                return iter->second;
            }
        }
        return ret;
    }

protected:
    bool registerCtrl(const char* name, Node** ctrl) {
        if(this->m_regCtrl.find(name) == this->m_regCtrl.end()) {
            *ctrl = nullptr;
            this->m_regCtrl.insert(std::make_pair(name, ctrl));
            return true;
        }
        return false;
    }

private:
	void bindNodeByName(Node* node) {
		if(node == nullptr) return;
		std::string name = node->getName();
		//log("%s", name.c_str());
		if(!name.empty()) {
            if(name == "m_bgColorPanel") {
                m_bgColorPanel = dynamic_cast<Layout*>(node);
                if(m_bgColorPanel) {
                    cocos2d::Size sizeOverlayer = Director::getInstance()->getWinSize();
                    m_bgColorPanel->cocos2d::Node::setPosition(0,0);
                    m_bgColorPanel->setContentSize(sizeOverlayer);
                }
            }
			this->m_allCtrl.insert(std::make_pair(name, node));
			std::map<std::string, Node**>::iterator iter = this->m_regCtrl.find(name);
			if(iter != this->m_regCtrl.end()) {
				Node** ctrl = iter->second;
				if(*ctrl != node) {
					*ctrl = node;
				}
			}
		}
		long count = node->getChildrenCount();
		if(count > 0) {
			Vector<Node*>& childs = node->getChildren();
			for(long i = 0; i < count; ++i) {
				Node* child = childs.at(i);
				this->bindNodeByName(child);
			}
		}
	}

    void clear() {
        this->m_regCtrl.clear();
		this->m_allCtrl.clear();
    }

protected:
	__NotificationCenter* m_ntfMgr;
	Node* m_rootNode;
    ActionTimeline* m_rootAction;
	float m_nAutoScaleRate;
    Layout* m_bgColorPanel;
	int m_offsetY;

private:
    std::map<std::string, Node*>  m_allCtrl;
	std::map<std::string, Node**> m_regCtrl;
};

#endif
