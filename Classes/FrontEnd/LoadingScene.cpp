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
    loadHelper();
    loadGameSelection();

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
//缓存帮助界面图片
void LoadingScene::loadHelper() {
    //缓存数字
    cacheImage("HelperScene/num_-1.png");
    cacheImage("HelperScene/num_1.png");
    cacheImage("HelperScene/num_2.png");
    cacheImage("HelperScene/num_3.png");
    cacheImage("HelperScene/num_4.png");
    cacheImage("HelperScene/num_5.png");
    cacheImage("HelperScene/num_6.png");
    cacheImage("HelperScene/num_7.png");
    cacheImage("HelperScene/num_8.png");
    cacheImage("HelperScene/num_9.png");
    cacheImage("HelperScene/num_10.png");
    //缓存背景
    cacheImage("HelperScene/help_3-hd_bg.png");
    //缓存菜单按钮
    cacheImage("HelperScene/help_1-hd_67.PNG");
    cacheImage("HelperScene/help_1-hd_38.PNG");
    cacheImage("HelperScene/help_1-hd-33_normal.PNG");
    cacheImage("HelperScene/help_1-hd_33.PNG");
    cacheImage("HelperScene/help_1-hd_71_normal.PNG");
    cacheImage("HelperScene/help_1-hd_71.png");
    cacheImage("HelperScene/help_1-hd_66_normal.PNG");
    cacheImage("HelperScene/help_1-hd_66.PNG");
    //缓存帮助界面   
    cacheImage("HelperScene/help_3-hd_1.png");
    cacheImage("HelperScene/help_1-hd_73.PNG");
    cacheImage("HelperScene/help_3-hd_2.png");
    cacheImage("HelperScene/help_1-hd_4.PNG");
    cacheImage("HelperScene/help_3-hd_3.png");
    cacheImage("HelperScene/help_1-hd_50.PNG");
    cacheImage("HelperScene/help_3-hd_4.png");
    cacheImage("HelperScene/help_1-hd_65.PNG");
    cacheImage("HelperScene/help_1-hd_0.PNG");
    //缓存怪物界面
    cacheImage("HelperScene/help_3-hd_monster.png");
    cacheImage("HelperScene/help_1-hd_14.PNG");
    cacheImage("HelperScene/help_1-hd_1.PNG");
    cacheImage("HelperScene/help_1-hd_2.PNG");
    cacheImage("HelperScene/help_1-hd_3.PNG");
    cacheImage("HelperScene/help_1-hd_29.PNG");
    cacheImage("HelperScene/help_1-hd_39.PNG");
    //缓存炮台界面
    cacheImage("HelperScene/tower_1.png");
    cacheImage("HelperScene/tower_2.png");
    cacheImage("HelperScene/tower_3.png");
    cacheImage("HelperScene/tower_4.png");
    cacheImage("HelperScene/tower_5.png");
    cacheImage("HelperScene/tower_6.png");
    cacheImage("HelperScene/tower_7.png");
    cacheImage("HelperScene/tower_8.png");
    cacheImage("HelperScene/tower_9.png");
    cacheImage("HelperScene/tower_10.png");
}
//缓存游戏选择界面图片
void LoadingScene::loadGameSelection() {
    //加载背景
    cacheImage("GameSelectionScene/stages_bg-hd_0.PNG");
    //加载菜单
    cacheImage("GameSelectionScene/stages_bg-hd_42.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_33.PNG");
    //加载大关选择
    cacheImage("GameSelectionScene/page_no.png");
    cacheImage("GameSelectionScene/page_yes.png");
    cacheImage("GameSelectionScene/themescene1-hd_8.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_17.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_32.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_31.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_26.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_25.PNG");
    cacheImage("GameSelectionScene/themescene1-hd.png");
    cacheImage("GameSelectionScene/themescene2-hd.pvr_2.PNG");
    cacheImage("GameSelectionScene/Items03-hd.pvr_0.PNG");
    cacheImage("GameSelectionScene/themescene2-hd.pvr_0.PNG");
    cacheImage("GameSelectionScene/themescene1-hd_10.PNG");
    cacheImage("GameSelectionScene/themescene2-hd.pvr_1.PNG");
    cacheImage("GameSelectionScene/evaluate.png");
    cacheImage("GameSelectionScene/close_evaluate_normal.png");
    cacheImage("GameSelectionScene/close_evaluate_selected.png");
    cacheImage("GameSelectionScene/level_2_lock.png");
    cacheImage("GameSelectionScene/lock_btn_normal.png");
    cacheImage("GameSelectionScene/lock_btn_selected.png");
    cacheImage("GameSelectionScene/level_3_lock.png");
    //加载小关选择
    cacheImage("GameSelectionScene/BG_Left.PNG");
    cacheImage("GameSelectionScene/BG_Right.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_41.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_40.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_30.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_28.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_39.PNG");
    cacheImage("GameSelectionScene/total_waves.png");
    cacheImage("GameSelectionScene/Level_1.PNG");
    cacheImage("GameSelectionScene/Level_2.PNG");
    cacheImage("GameSelectionScene/Level_3.PNG");
    cacheImage("GameSelectionScene/Level_4.PNG");
    cacheImage("GameSelectionScene/Level_5.PNG");
    cacheImage("GameSelectionScene/Tower_1.PNG");
    cacheImage("GameSelectionScene/Tower_2.PNG");
    cacheImage("GameSelectionScene/Tower_3.PNG");
    cacheImage("GameSelectionScene/Tower_4.PNG");
    cacheImage("GameSelectionScene/Tower_5.PNG");
    cacheImage("GameSelectionScene/stages_bg-hd_31.PNG");
    cacheImage("GameSelectionScene/lock_image.png");
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