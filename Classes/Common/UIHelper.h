//
// Created by farmer on 2018/7/4.
//

#ifndef COCOSTUDIO_MAHJONG_UIHELPER_H
#define COCOSTUDIO_MAHJONG_UIHELPER_H

#include "Common.h"

using namespace cocos2d;

class UIHelper {

public:
    static ui::ImageView *createHandCardImageView(uint8_t cbViewID, uint8_t cbData);   //创建牌的ImageView
    static ui::ImageView *createDiscardCardImageView(uint8_t cbViewID, uint8_t cbData);//创建出牌的ImageView
    static std::string getDiscardCardImagePath(uint8_t cbViewID, uint8_t cbData);      //获取牌的图片路径
    static std::string getBackCardImagePath(uint8_t cbViewID, uint8_t cbData);         //获取牌背面的路径
    static std::string getHandCardImagePath(uint8_t cbViewID, uint8_t cbData);         //获取手上的牌图片路径

public:
    /**
     * 通过Tag查找子节点
     * */
    static Node *seekNodeByTag(Node *root, int tag);
    /**
     * 通过Name查找子节点
     * @param root
     * @param name
     * @return
     */
    static Node *seekNodeByName(Node *root, const std::string &name);

    /**
     * 获取子节点
     * @param root
     * @param name
     * @param children
     * @return
     */
    static std::vector<Node*>  getChildren(Node* root, const std::string& name , std::vector<Node*>& children);
};


#endif //COCOSTUDIO_MAHJONG_UIHELPER_H
