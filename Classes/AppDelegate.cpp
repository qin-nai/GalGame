#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "CG/CGScene.h"
// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif


USING_NS_CC;
//开发时标准尺寸
static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
//小屏设备
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
//平板设备
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
//高清大屏设备
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化导演
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        //初始化窗口及最大化窗口
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        // 1. 创建默认窗口
        glview = GLViewImpl::createWithRect(
            "MyGame",
            cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height),
            1.0f,
            false
        );
        // 2. 通过窗口标题找HWnd（窗口标题要和createWithRect的第一个参数一致）
        HWND hWnd = FindWindowA(NULL, "MyGame");
        if (hWnd) {
            LONG style = GetWindowLong(hWnd, GWL_STYLE);
            style |= WS_OVERLAPPEDWINDOW; // 启用最大化/还原
            SetWindowLong(hWnd, GWL_STYLE, style);
            SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);
        }
#else
        glview = GLViewImpl::createWithRect(
            "MyGame",
            cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height),
            1.0f,
            false
        );
#endif
        director->setOpenGLView(glview);
    }
    //FPS
#if 0
    // 显示帧率开启
    director->setDisplayStats(true);
    // 设置帧率。若未调用此功能，默认值为 1.0/60。
    director->setAnimationInterval(1.0f / 60);
#endif

    // 设置设计分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // 如果该帧的高度大于中等尺寸的高度。
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
    }
    // 如果框架的高度大于小号尺寸的高度。
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
    }
    // 如果框架的高度小于中号尺寸的高度。
    else
    {
        director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
    }

    register_all_packages();

    // 启动CG场景
    auto scene = CGScene::createScene();
    director->runWithScene(scene);

    return true;
}

// 当应用处于非活跃状态时，将调用此函数。请注意，接听电话时也会触发该函数。
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// 当应用再次处于活跃状态时，将调用此函数。
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
