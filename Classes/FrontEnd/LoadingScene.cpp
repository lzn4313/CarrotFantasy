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
    schedule(CC_SCHEDULE_SELECTOR(LoadingScene::check), 1.0f);
    return true;
}
// 该代码处理加载资源的操作。
// 加载资源包括图片，声音等。
void LoadingScene::loadSource() {
    //设置存档地址（存档相关请跳转至GameData.h）
    FileUtils::getInstance()->setWritablePath(FileUtils::getInstance()->getDefaultResourceRootPath()+"../");
    //初始化存档数据
    SaveManager::getInstance()->init_data();

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    
    loadMenu();
    loadOptions();
    numberOfLoadedRes = 1;
}
//缓存菜单界面图片
void LoadingScene::loadMenu() {
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
}
//缓存设置界面图片
void LoadingScene::loadOptions() {
    //缓存设置界面所需图片
    cacheImage("OptionsScene/Btn_Return.PNG");
    cacheImage("OptionsScene/Btn_ReturnLight.PNG");
    cacheImage("OptionsScene/setting02-hd_45_normal.PNG");
    cacheImage("OptionsScene/setting02-hd_45.PNG");
    cacheImage("OptionsScene/setting02-hd_43_normal.PNG");
    cacheImage("OptionsScene/setting02-hd_43.PNG");
    cacheImage("OptionsScene/setting02-hd_48_normal.PNG");
    cacheImage("OptionsScene/setting02-hd_48.PNG");
    //设置层
    cacheImage("OptionsScene/SettingBG1.PNG");
    cacheImage("OptionsScene/setting02-hd_0.PNG");
    cacheImage("OptionsScene/setting02-hd_2.PNG");
    cacheImage("OptionsScene/setting02-hd_7.PNG");
    cacheImage("OptionsScene/setting02-hd_12.PNG");
    cacheImage("OptionsScene/setting02-hd_16.PNG");
    cacheImage("OptionsScene/setting02-hd_6.PNG");
    cacheImage("OptionsScene/setting02-hd_11.PNG");
    cacheImage("OptionsScene/setting02-hd_15.PNG");
    cacheImage("OptionsScene/setting02-hd_21.PNG");
    cacheImage("OptionsScene/setting02-hd_55.PNG");
    cacheImage("OptionsScene/setting02-hd_54.PNG");
    cacheImage("OptionsScene/reset_image.png");
    cacheImage("OptionsScene/reset_yes_normal.png");
    cacheImage("OptionsScene/reset_yes_selected.png");
    cacheImage("OptionsScene/reset_no_normal.png");
    cacheImage("OptionsScene/reset_no_selected.png");
    //统计层
    cacheImage("OptionsScene/SettingBG2.PNG");
    cacheImage("OptionsScene/setting02-hd_22.PNG");
    cacheImage("OptionsScene/setting02-hd_23.PNG");
    cacheImage("OptionsScene/setting02-hd_27.PNG");
    cacheImage("OptionsScene/setting02-hd_31.PNG");
    cacheImage("OptionsScene/setting02-hd_35.PNG");
    cacheImage("OptionsScene/setting02-hd_38.PNG");
    cacheImage("OptionsScene/setting02-hd_42.PNG");
    cacheImage("OptionsScene/setting02-hd_44.PNG");
    //人员层
    cacheImage("OptionsScene/SettingBG3.PNG");

}
void LoadingScene::check(float dt)
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
            AudioEngine::play2d("sound/CarrotFantasy.mp3", true, 0.5f);
        }
    }
}

//缓存图片，若找不到图片抛出异常
void LoadingScene::cacheImage(const std::string& filepath) {
    auto image = Director::getInstance()->getTextureCache()->addImage(filepath);
    std::string msg = "################################################################## problem while loading image " + filepath + "####################################################################";
    CCASSERT(image != nullptr, msg.c_str());
}