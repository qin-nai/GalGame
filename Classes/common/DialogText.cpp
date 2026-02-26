#include "DialogText.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;

Scene* DialogText::createScene(){
    return DialogText::create();
}

bool DialogText::init(){
    //加载对话框
    DialogText::DialogImg("DialogText.png");

    //读取JSON对话



    //加载对话
    return true;
}

void DialogText::DialogImg(const char* DialogText)
{
    auto sprite = Sprite::create(DialogText);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 1. 锚点设为左上角
    sprite->setAnchorPoint(Vec2(0, 1));
    // 2. 位置设为屏幕左上角
    sprite->setPosition(origin.x, origin.y + visibleSize.height - 60);

    //// 3. 缩放
    
    //float scale = 0.3f;
    //sprite->setScale(scale);

    this->addChild(sprite, 3); // 层级
}

