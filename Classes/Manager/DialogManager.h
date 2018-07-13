

#ifndef COCOSTUDIO_MAHJONG_DialogManager__
#define COCOSTUDIO_MAHJONG_DialogManager__

#include "Common.h"

class DialogManager {
public:
	static DialogManager* shared();
	
	bool isAnyDialogShown();
	void showDialog(Node* dialog);
	void closeDialog(Node* dialog);
	void closeAllDialog();
    void closeCurrentDialog();
    CC_SYNTHESIZE_READONLY(Node*, m_currentDialog, CurrentDialog);
private:
	DialogManager();
    virtual ~DialogManager();
    CC_DISALLOW_COPY_AND_ASSIGN(DialogManager);

	int m_baseZOrder;
	std::vector<Node*> dialogList;
};


#endif /* defined(__Aliens__DialogManager__) */
