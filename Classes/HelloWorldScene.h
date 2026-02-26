#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
using namespace cocos2d;
using namespace std;
using namespace cocos2d::experimental;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 手动实现 static create () 方法。
    CREATE_FUNC(HelloWorld);
private:
    enum ButtonType
    {
        BTN_NEW_GAME = 1,            // 开始游戏
        BTN_LOAD_GAME,             // 读取存档
        BTN_CONTINUE_GAME,         // 继续游戏
        BTN_FLOW_CHART,            // 流程图
        BTN_GALLERY_MODE,      // 鉴赏模式
        BTN_AFTER_STORY,       // 后日谈
        BTN_SETTINGS,          // 系统设置
        BTN_EXIT_GAME          // 退出游戏
    };
    //加载时按钮位置
    void buttonImage(Sprite* buttonArea, Sprite* sprite, int a, float b);
    //按钮点击逻辑
    void onButtonClick(int buttonTag);
    
};

#endif // __HELLOWORLD_SCENE_H__
