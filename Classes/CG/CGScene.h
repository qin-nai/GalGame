#pragma once
#ifndef CG_SCENE_H
#define CG_SCENE_H

#include "cocos2d.h"

class CGScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init() override;
    CREATE_FUNC(CGScene);

private:
    int CGAudio;
    cocos2d::Vector<cocos2d::SpriteFrame*> frames;
    void preloadAllFrames(); // 预加载所有帧
    // 播放CG动画
    void playCGAnimation();
    // 动画播放完成后的回调
    void onCGComplete();
};

#endif // CG_SCENE_H