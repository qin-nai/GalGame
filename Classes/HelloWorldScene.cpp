#include "HelloWorldScene.h"
#include "audio/include/AudioEngine.h"
#include "CG/CGScene.h"
#include "Scene/NewGameScene.h"
#include "common/DialogText.h"
int bgMusicId;
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 当文件不存在时，打印有用的错误消息，而不是崩溃。
static void problemLoading(const char* filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// "初始化"阶段需完成实例的实例化操作。
bool HelloWorld::init()
{
    // 1. 先调用父类初始化方法
    if (!Scene::init()) { return false; }
    auto visibleSize = Director::getInstance()->getVisibleSize(); // 获取屏幕可见区域大小
    auto origin = Director::getInstance()->getVisibleOrigin(); // 屏幕原点（避免黑边）

    // 播放背景音乐（循环播放）
    bgMusicId = AudioEngine::play2d("./Audio/bg_music.mp3", true, 0.8f);

    //背景图
    auto sprite = Sprite::create("./Images/bg.png");
    if (sprite) {
        // 1. 设置背景图的锚点为屏幕中心（默认锚点是(0.5,0.5)，可以省略）
        sprite->setAnchorPoint(Vec2(0.5, 0.5));
        // 2. 把背景图放到屏幕正中心
        sprite->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

        // 3. 计算缩放比例，确保完全铺满
        float scaleX = visibleSize.width / sprite->getContentSize().width;
        float scaleY = visibleSize.height / sprite->getContentSize().height;
        float maxScale = std::max(scaleX, scaleY); // 取较大的缩放比例
        sprite->setScale(maxScale); // 应用缩放

        this->addChild(sprite, 0); // 添加到层（z轴0，底层）
    }

    //按键区图片及加载动画
    //开始游戏
    auto buttonArea1 = Sprite::create("./Images/UI_1.png"); buttonArea1->setTag(BTN_NEW_GAME); HelloWorld::buttonImage(buttonArea1, sprite, -170, 0.5f);
    //读取存档
    auto buttonArea2 = Sprite::create("./Images/UI_2.png"); buttonArea2->setTag(BTN_LOAD_GAME); HelloWorld::buttonImage(buttonArea2, sprite, -97, 0.58f);
    //继续游戏
    auto buttonArea3 = Sprite::create("./Images/UI_3.png"); buttonArea3->setTag(BTN_CONTINUE_GAME); HelloWorld::buttonImage(buttonArea3, sprite, -13, 0.63f);
    //流程图
    auto buttonArea4 = Sprite::create("./Images/UI_4.png"); buttonArea4->setTag(BTN_FLOW_CHART); HelloWorld::buttonImage(buttonArea4, sprite, 67, 0.71f);
    //鉴赏模式
    auto buttonArea5 = Sprite::create("./Images/UI_5.png"); buttonArea5->setTag(BTN_GALLERY_MODE); HelloWorld::buttonImage(buttonArea5, sprite, 148, 0.79f);
    //后日谈
    auto buttonArea6 = Sprite::create("./Images/UI_6.png"); buttonArea6->setTag(BTN_AFTER_STORY); HelloWorld::buttonImage(buttonArea6, sprite, 230, 0.87f);
    //系统设置
    auto buttonArea7 = Sprite::create("./Images/UI_7.png"); buttonArea7->setTag(BTN_SETTINGS); HelloWorld::buttonImage(buttonArea7, sprite, 315, 0.95f);
    // 8. 退出游戏的按钮
    auto buttonArea8 = Sprite::create("./Images/UI_8.png"); buttonArea8->setTag(BTN_EXIT_GAME); HelloWorld::buttonImage(buttonArea8, sprite, 410, 1.03f);

    return true;
}
void HelloWorld::buttonImage(Sprite* buttonArea, Sprite* sprite, int a, float b) {
    if (buttonArea) {
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Size bgSize = sprite->getContentSize();

        // 适配按键图片尺寸
        float scale = visibleSize.width / bgSize.width; // 用背景图的缩放比统一适配
        buttonArea->setScale(scale);
        Size btnSize = buttonArea->getContentSize() * scale; // 适配后的实际尺寸

        // 初始位置：完全在屏幕左侧外（x = -btnSize.width）
        buttonArea->setPosition(Vec2(-btnSize.width, visibleSize.height / 2 - a));
        this->addChild(buttonArea, 2); // z轴设为2，确保在背景之上

        // 3. 执行“延迟+左侧滑入”动画
        auto delay = DelayTime::create(b); // 延迟b秒等界面加载
        // 滑入目标位置
        auto moveTo = MoveTo::create(0.7f, Vec2(btnSize.width / 2 + 20, visibleSize.height / 2 - a));
        auto easeMove = EaseOut::create(moveTo, 1.3f); // 缓动效果更自然
        auto sequence = Sequence::create(delay, easeMove, nullptr);
        buttonArea->runAction(sequence);

        // 添加鼠标点击事件监听
        auto listener = EventListenerMouse::create();
        listener->onMouseDown = [this, buttonArea](Event* event) {
            EventMouse* e = static_cast<EventMouse*>(event);
            Vec2 touchPos = Vec2(e->getCursorX(), e->getCursorY());
            if (buttonArea->getBoundingBox().containsPoint(touchPos))
            {
                int buttonTag = buttonArea->getTag();
                onButtonClick(buttonTag);
            }
            };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, buttonArea);
    }
}
void HelloWorld::onButtonClick(int buttonTag)
{
    switch (buttonTag)
    {
    case BTN_NEW_GAME:
    {
        CCLOG("点击了【开始游戏】");
        // 结束音乐
        AudioEngine::stop(bgMusicId);
        // 切换场景
        auto NewgameScene = NewGameScene::createScene();
        // 淡入淡出效果
        auto transition = TransitionFade::create(0.5f, NewgameScene);
        // 替换当前场景并释放旧场景
        Director::getInstance()->replaceScene(transition);
        break;
    }
    case BTN_LOAD_GAME:
        CCLOG("点击了【读取存档】");
        // 执行读取存档逻辑
        break;
    case BTN_CONTINUE_GAME:
        CCLOG("点击了【继续游戏】");
        // 执行继续游戏逻辑
        break;
    case BTN_FLOW_CHART:
        CCLOG("点击了【流程图】");
        // 执行流程图逻辑
        break;
    case BTN_GALLERY_MODE:
        CCLOG("点击了【鉴赏模式】");
        // 执行鉴赏模式逻辑
        break;
    case BTN_AFTER_STORY:
        CCLOG("点击了【后日谈】");
        // 执行后日谈逻辑
        break;
    case BTN_SETTINGS:
        CCLOG("点击了【系统设置】");
        // 执行系统设置逻辑
        break;
    case BTN_EXIT_GAME:
        CCLOG("点击了【退出游戏】");
        // 执行退出游戏
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        exit(0);
#endif
        break;
    default:
        break;
    }
    CCLOG("按钮被点击了");
}