#pragma once

#include "cocos2d.h"
#include "common/DialogText.h"

class NewGameScene : public cocos2d::Scene{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

private:
    // 图片相关
    const std::string bgBasePath;
    const int bgTotalCount=199;
    std::vector<std::string> bgImageList;//存储图片
    std::vector<std::string> dialogContentList; // 存储每一张图对应的对话
    int currentBgIndex;
    cocos2d::Sprite* currentBgSprite = nullptr; // 初始化空指针

    // 加载背景图路径列表
    void generateBgPathList();
    // 加载当前索引对应的背景图
    void loadCurrentBgImage();
    // 切换到下一张背景图
    void switchToNextBgImage();
    // 对话框成员变量
    DialogText* dialog = nullptr;

    // 在构造函数中初始化常量成员变量
    NewGameScene() : bgBasePath("NewGame/bg_"), bgTotalCount(199) {}

    CREATE_FUNC(NewGameScene);
};