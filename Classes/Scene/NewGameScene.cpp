#include "NewGameScene.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;
using namespace cocos2d::experimental;
static const std::string bgBasePath = "NewGame/bg_";
static const int bgTotalCount = 199;

Scene* NewGameScene::createScene()
{
    return NewGameScene::create();
}

bool NewGameScene::init()
{
    if (!Scene::init()){
        return false;
    }

    // 生成背景图路径列表
    generateBgPathList();
    
    //播放音乐
    static const int bgMusicId = AudioEngine::play2d("./NewGameAudio/Audio1.mp3", true, 0.8f);

    // 加载第一张背景图
    loadCurrentBgImage();

    // 注册右键点击监听
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = [this](EventMouse* event){
            if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT)switchToNextBgImage();

            return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

   

    return true;
}

// 用循环生成背景图路径列表

void NewGameScene::generateBgPathList()
{
    bgImageList.clear();
    dialogContentList.clear(); // 清空对话列表

    // 读取TXT文件
    std::string txtPath = FileUtils::getInstance()->fullPathForFilename("dialogs.txt");
    if (FileUtils::getInstance()->isFileExist(txtPath))
    {
        std::string fileContent = FileUtils::getInstance()->getStringFromFile(txtPath);
        std::vector<std::string> lines;
        size_t pos = 0;
        // 按换行符拆分所有行
        while (pos < fileContent.size())
        {
            size_t end = fileContent.find('\n', pos);
            if (end == std::string::npos) end = fileContent.size();
            std::string line = fileContent.substr(pos, end - pos);
            // 过滤空行
            if (!line.empty()) lines.push_back(line);
            pos = end + 1;
        }

        // 按“角色行+对话行”的格式拆分（每2行对应一段对话）
        for (int i = 0; i + 1 < lines.size(); i += 2)
        {
            std::string roleLine = lines[i];     // 【角色名】
            std::string contentLine = lines[i + 1];// 对话内容
            // 存储为“角色名|对话内容”（用|分隔，方便后续拆分）
            dialogContentList.push_back(roleLine + "|" + contentLine);
        }
    }
    else
    {
        CCLOG("dialogs.txt不存在！");
        // 兜底：默认对话
        dialogContentList.push_back("【默认角色】|默认对话");
    }


    for (int i = 1; i <= bgTotalCount; ++i)
    {
        // 生成背景图路径（原有逻辑）
        char numStr[4];
        sprintf(numStr, "%03d", i);
        std::string path = bgBasePath + numStr + ".png";
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(path);
        bgImageList.push_back(fullPath);

        // 生成对应对话（示例：第i张图对应“这是第i段对话”）
        dialogContentList.push_back("这是第" + std::to_string(i) + "段对话");
    }
    currentBgIndex = 0;
}


// 加载当前索引对应的背景图
void NewGameScene::loadCurrentBgImage(){

    if (currentBgSprite)
    {
        currentBgSprite->removeFromParent();
    }

    currentBgSprite = Sprite::create(bgImageList[currentBgIndex]);
    if (currentBgSprite)
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();
        currentBgSprite->setContentSize(visibleSize);
        currentBgSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
        this->addChild(currentBgSprite, 0);
    }
    
    //添加标题
    auto sprite = Sprite::create("./title/title_1.1.png");
    if (sprite) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto origin = Director::getInstance()->getVisibleOrigin();

        // 1. 锚点设为左上角
        sprite->setAnchorPoint(Vec2(0, 1));
        // 2. 位置设为屏幕左上角
        sprite->setPosition(origin.x, origin.y + visibleSize.height-60);

        // 3. 缩放
        float scale = 0.3f;
        sprite->setScale(scale);

        this->addChild(sprite, 3); // 层级
    }

    // 对话框
    auto dialogLayer = DialogText::create();
    this->addChild(dialogLayer);
   
}

// 切换到下一张背景图
void NewGameScene::switchToNextBgImage()
{
    currentBgIndex = (currentBgIndex + 1) % bgImageList.size();
    loadCurrentBgImage();
}
