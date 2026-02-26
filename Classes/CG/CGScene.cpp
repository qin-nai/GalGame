#include "CGScene.h"
#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;

Scene* CGScene::createScene()
{
    return CGScene::create();
}

bool CGScene::init()
{
    if (!Scene::init()) return false;
    //预加载帧动画图片
    preloadAllFrames();
    // 初始化后立即播放CG动画
    playCGAnimation();
    return true;
}

void CGScene::playCGAnimation()
{
    CGAudio = AudioEngine::play2d("./Audio/CGAudio.mp3", true, 0.8f);
    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 30);
    // 播放一次后停止
    auto animate = Animate::create(animation);

    // 创建显示动画的精灵
    auto cgSprite = Sprite::create();
    cgSprite->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(cgSprite, 1);

    // 执行动画 + 播放完成后跳转场景
    auto sequence = Sequence::create(
        animate,
        CallFunc::create(CC_CALLBACK_0(CGScene::onCGComplete, this)),
        nullptr
    );
    cgSprite->runAction(sequence);
}

void CGScene::onCGComplete()
{
    // CG播放完成后，跳转到主界面
    AudioEngine::stop(CGAudio);
    auto mainScene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, mainScene));
}
void CGScene::preloadAllFrames()
{
    // 帧图片路径
    for (int i = 1; i <= 314; ++i)
    {
        // 拼接帧路径
        std::string framePath = StringUtils::format("CG_frames/frame_%05d.png", i);

        // 创建Sprite加载纹理（仅缓存）
        auto tempSprite = Sprite::create(framePath);
        if (tempSprite)
        {
            // 获取纹理对应的SpriteFrame并存入容器
            auto frame = SpriteFrame::createWithTexture(
                tempSprite->getTexture(),
                tempSprite->getTextureRect() // 纹理矩形（默认整图）
            );
            frames.pushBack(frame);
        }
        else
        {
            CCLOG("预加载失败：%s", framePath.c_str());
        }
    }
    CCLOG("所有帧预加载完成，共%d帧", frames.size());
}