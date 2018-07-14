//
// Created by farmer on 2018/7/4.
//

#include "UIHelper.h"
#include "GameCmd.h"
#include "FvMask.h"
#include "Utility.h"
#include "GameLogic.h"

/**
 * 根据Tag获取节点
 * @param root
 * @param tag
 * @return
 */
Node *UIHelper::seekNodeByTag(Node *root, int tag) {
    if (!root) {
        return nullptr;
    }
    if (root->getTag() == tag) {
        return root;
    }
    const auto &arrayRootChildren = root->getChildren();
    ssize_t length = arrayRootChildren.size();
    for (ssize_t i = 0; i < length; i++) {
        Node *child = dynamic_cast<Node *>(arrayRootChildren.at(i));
        if (child) {
            Node *res = seekNodeByTag(child, tag);
            if (res != nullptr) {
                return res;
            }
        }
    }
    return nullptr;
}

/**
 * 根据名字搜索节点
 * @param root
 * @param name
 * @return
 */
Node *UIHelper::seekNodeByName(Node *root, const std::string &name) {
    if (!root) {
        return nullptr;
    }
    if (root->getName() == name) {
        return root;
    }
    const auto &arrayRootChildren = root->getChildren();
    for (auto &subWidget : arrayRootChildren) {
        Node *child = dynamic_cast<Node *>(subWidget);
        if (child) {
            Node *res = seekNodeByName(child, name);
            if (res != nullptr) {
                return res;
            }
        }
    }
    return nullptr;
}

/**
 * 获取全部指定名字子节点
 * @param root
 * @param name
 * @param children
 * @return
 */
std::vector<Node *> UIHelper::getChildren(Node *root, const std::string &name, std::vector<Node *> &children) {
    if (!root) {
        return children;
    }
    if (root->getName() == name) {
        children.push_back(root);
    }
    const auto &arrayRootChildren = root->getChildren();
    for (auto &subWidget : arrayRootChildren) {
        Node *child = dynamic_cast<Node *>(subWidget);
        if (child) {
            getChildren(child, name, children);
        }
    }
    return children;
}



/**
 * 手上的牌
 * @param cbViewID
 * @param cbData
 * @return
 */
ui::ImageView *UIHelper::createHandCardImageView(uint8_t cbViewID, uint8_t cbData) {
    return ui::ImageView::create(getHandCardImagePath(cbViewID, cbData));
}

/**
 * 创建桌面的牌
 * @param cbViewID
 * @param cbData
 * @return
 */
ui::ImageView *UIHelper::createDiscardCardImageView(uint8_t cbViewID, uint8_t cbData) {
    return ui::ImageView::create(getDiscardCardImagePath(cbViewID, cbData));
}

/**
 * 桌面显示的牌
 * @param cbViewID
 * @param cbData
 * @return
 */
std::string UIHelper::getDiscardCardImagePath(uint8_t cbViewID, uint8_t cbData) {
    std::string strImagePath = "";
    switch (cbViewID) {
        case 0: {
            strImagePath = "res/GameLayer/Mahjong/2/mingmah_" + utility::toString(((cbData & MASK_COLOR)
                                                                                   >> 4) + 1, cbData & MASK_VALUE) + ".png";
            break;
        }
        case 1: {
            strImagePath = "res/GameLayer/Mahjong/3/mingmah_" + utility::toString(((cbData & MASK_COLOR)
                                                                                   >> 4) + 1, cbData & MASK_VALUE) + ".png";
            break;
        }
        case 2: {
            strImagePath = "res/GameLayer/Mahjong/2/mingmah_" + utility::toString(((cbData & MASK_COLOR)
                                                                                   >> 4) + 1, cbData & MASK_VALUE) + ".png";
            break;
        }
        case 3: {
            strImagePath = "res/GameLayer/Mahjong/1/mingmah_" + utility::toString(((cbData & MASK_COLOR)
                                                                                   >> 4) + 1, cbData & MASK_VALUE) + ".png";
            break;
        }
        default:
            break;
    }
    return strImagePath;
}

/**
 *
 * 背面
 * @param cbViewID
 * @param cbData
 * @return
 */
std::string UIHelper::getBackCardImagePath(uint8_t cbViewID, uint8_t) {
    std::string strImagePath = "";
    switch (cbViewID) {
        case 0: {
            strImagePath = "res/GameLayer/Mahjong/2/mingmah_00.png";
            break;
        }
        case 1: {
            strImagePath = "res/GameLayer/Mahjong/1/mingmah_00.png";
            break;
        }
        case 2: {
            strImagePath = "res/GameLayer/Mahjong/2/mingmah_00.png";
            break;
        }
        case 3: {
            strImagePath = "res/GameLayer/Mahjong/1/mingmah_00.png";
            break;
        }
        default:
            break;
    }
    return strImagePath;
}

/**
 * 手上的牌路径
 * @param cbViewID
 * @param cbData
 * @return
 */
std::string UIHelper::getHandCardImagePath(uint8_t cbViewID, uint8_t cbData) {
    std::string strImagePath = "";
    switch (cbViewID) {
        case 0: {
            strImagePath = "res/GameLayer/Mahjong/2/handmah_" + utility::toString(((cbData & MASK_COLOR)
                                                                                   >> 4) + 1, cbData & MASK_VALUE) + ".png";
            break;
        }
        case 1: {
            strImagePath = "res/GameLayer/Mahjong/hand_left.png";
            break;
        }
        case 2: {
            strImagePath = "res/GameLayer/Mahjong/hand_top.png";
            break;
        }
        case 3: {
            strImagePath = "res/GameLayer/Mahjong/hand_right.png";
            break;
        }
        default:
            break;
    }
    return strImagePath;
}
