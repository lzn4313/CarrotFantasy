#include "FrontEnd/LoadingScene.h"
#include "FrontEnd/MenuScene.h"
#include "AudioEngine.h"
#include "Config/GameData.h"
USING_NS_CC;


Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}


bool LoadingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    numberOfLoadedRes = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("LoadingScene/LoadBG.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);
    // 定时更新，用于检测资源是否被加载完成，如果加载完成才跳入到正真的欢迎页面。
    schedule(CC_SCHEDULE_SELECTOR(LoadingScene::logic), 1.0f);
    return true;
}
// 该代码处理加载资源的操作。
// 加载资源包括图片，声音等。
void LoadingScene::loadSource() {
    //设置存档地址（存档相关请跳转至GameData.h）
    FileUtils::getInstance()->setWritablePath(FileUtils::getInstance()->getDefaultResourceRootPath()+"../");
    //初始化存档数据
    init_data();

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    //缓存菜单界面所需图片
    cacheImage("MenuScene/MainBG.PNG");
    cacheImage("MenuScene/Cloud.PNG");
    cacheImage("MenuScene/Cloud2.PNG");
    cacheImage("MenuScene/FlyMonster.PNG");
    cacheImage("MenuScene/Leaf1.PNG");
    cacheImage("MenuScene/Leaf2.PNG");
    cacheImage("MenuScene/Leaf3.PNG");
    cacheImage("MenuScene/CarrotBody.PNG");
    cacheImage("MenuScene/MainTitle.PNG");
    cacheImage("MenuScene/Btn_Set.PNG");
    cacheImage("MenuScene/Btn_SetLight.PNG");
    cacheImage("MenuScene/Btn_Help.PNG");
    cacheImage("MenuScene/Btn_HelpLight.PNG");
    cacheImage("MenuScene/Btn_NormalModle.PNG");
    cacheImage("MenuScene/Btn_NormalModleLight.PNG");
    cacheImage("MenuScene/Btn_Boss.PNG");
    cacheImage("MenuScene/Btn_BossLight.PNG");
    cacheImage("MenuScene/lock.png");
    cacheImage("MenuScene/Btn_MonsterNest.PNG");
    cacheImage("MenuScene/Btn_MonsterNestLight.PNG");
    numberOfLoadedRes = 1;
}
void LoadingScene::logic(float dt)
{
    // 如果你愿意可以在这里通过监听numberOfLoadedRes的值来显示加载进度。
    if (0 == numberOfLoadedRes) {
        loadSource();
    }
    else if (1 == numberOfLoadedRes) {
        // 处理跳转动作。
        Director::getInstance()->replaceScene(MenuScene::createScene());
        //如果背景音乐开，则播放背景音乐
        if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {
            AudioEngine::play2d("/sound/CarrotFantasy.mp3", true, 0.5f);
        }
    }
}

//缓存图片，若找不到图片抛出异常
void LoadingScene::cacheImage(const std::string& filepath) {
    auto image = Director::getInstance()->getTextureCache()->addImage(filepath);
    std::string msg = "################################################################## problem while loading image " + filepath + "####################################################################";
    CCASSERT(image != nullptr, msg.c_str());
}