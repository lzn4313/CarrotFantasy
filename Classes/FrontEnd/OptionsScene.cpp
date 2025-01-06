#include "FrontEnd/MenuScene.h"
#include "FrontEnd/OptionsScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "Config/sound&music.h"
#include"Config/GameData.h"
#include<string>

USING_NS_CC;
/**********************   OptionsScene类   ***********************************/
Scene* OptionsScene::createScene()
{
    return OptionsScene::create();
}
//初始化
bool OptionsScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize();

    initMenu();
    initLayers();
    //初始化状态为set
    currentState = new SetState();
    currentState->enter(this);

    return true;
}
//去主菜单
void OptionsScene::goto_menu(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    auto menu_scene = MenuScene::createScene();//创建菜单场景
    Director::getInstance()->replaceScene(TransitionSlideInB::create(0.3, menu_scene));//以从下向上滑动形式切换
}
//去选项页
void OptionsScene::goto_set(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    currentState->exit(this);
    currentState = new SetState();
    currentState->enter(this);
}
//去统计页
void OptionsScene::goto_statistics(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    currentState->exit(this);
    currentState = new StatisticsState();
    currentState->enter(this);
}
//去人员页
void OptionsScene::goto_person(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    currentState->exit(this);
    currentState = new PersonState();
    currentState->enter(this);
}
//初始化菜单按钮
void OptionsScene::initMenu() {
    auto menu_all = Menu::create();
    addChild(menu_all);  

    menu_all->setPosition(Vec2::ZERO);
    //返回主菜单的按钮（以MenuItemImage形式实现）
    auto home = MenuItemImage::create("OptionsScene/Btn_Return.PNG", "OptionsScene/Btn_ReturnLight.PNG", CC_CALLBACK_1(OptionsScene::goto_menu, this));
    home->setPosition(Vec2(visibleSize.width * 0.1,visibleSize.height * 0.9));
    menu_all->addChild(home);
    //set选项页按钮
    set_btn = MenuItemImage::create("OptionsScene/setting02-hd_45_normal.PNG", "OptionsScene/setting02-hd_45_normal.PNG", 
        "OptionsScene/setting02-hd_45.PNG", CC_CALLBACK_1(OptionsScene::goto_set, this));
    set_btn->setPosition(Vec2(visibleSize.width * 0.4, visibleSize.height * 0.925));
    menu_all->addChild(set_btn,1);
    //statistics选项页按钮
    statistics_btn = MenuItemImage::create("OptionsScene/setting02-hd_43_normal.PNG", "OptionsScene/setting02-hd_43_normal.PNG",
        "OptionsScene/setting02-hd_43.PNG", CC_CALLBACK_1(OptionsScene::goto_statistics, this));
    statistics_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.925));
    statistics_btn->setScale(1.4);
    menu_all->addChild(statistics_btn, 1);
    //person选项卡
    person_btn = MenuItemImage::create("OptionsScene/setting02-hd_48_normal.PNG", "OptionsScene/setting02-hd_48_normal.PNG",
        "OptionsScene/setting02-hd_48.PNG",CC_CALLBACK_1(OptionsScene::goto_person,this));
    person_btn->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.925));
    person_btn->setScale(1.4);
    menu_all->addChild(person_btn, 1);
}
//初始化三层内容
void OptionsScene::initLayers() {
    setLayer = SetLayer::create();
    statisticsLayer = StatisticsLayer::create();
    personLayer = PersonLayer::create();

    setLayer->setVisible(false);
    statisticsLayer->setVisible(false);
    personLayer->setVisible(false);

    addChild(setLayer, -1);
    addChild(statisticsLayer, -1);
    addChild(personLayer, -1);
}
/**************************   SetLayer类   ******************************/
cocos2d::Layer* SetLayer::createLayer()
{
    return SetLayer::create();
}
//初始化
bool SetLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize(); 
   
    initBackGround();
    initMenu();

    return true;
}
//关闭音效
void SetLayer::close_sound(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 0) {//若当前音效为关，则切换为打开
        UserDefault::getInstance()->setIntegerForKey("sound_effect", 1);
    }
    else if(UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1){//若当前音效为开，则切换为关
        UserDefault::getInstance()->setIntegerForKey("sound_effect", 0);
    }
}
//关闭bgm
void SetLayer::close_bgmusic(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 0) {//若当前bgm为关，则切换为打开，并播放bgm
        UserDefault::getInstance()->setIntegerForKey("bg_music", 1);
        AudioEngine::play2d("sound/CarrotFantasy.mp3", true, 0.5);
    }
    else if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {//若当前bgm为开，则切换为关闭，并关闭bgm
        UserDefault::getInstance()->setIntegerForKey("bg_music", 0);
        AudioEngine::stopAll();
    }
}
//重置游戏
void SetLayer::reset_game(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    //获取屏幕大小
    /*****************************  纯色层  ******************************************/
    auto black_layer = LayerColor::create(Color4B::BLACK);
    black_layer->setOpacity(85);
    this->getParent()->addChild(black_layer);

    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
        return true;
    };
    listener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
    /********************************  背景  *****************************************/
    auto reset_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/reset_image.png"));
    reset_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    reset_image->setScale(1.4);
    black_layer->addChild(reset_image);
    /********************************  按钮  ****************************************/
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);

    auto reset_yes_btn = MenuItemImage::create("OptionsScene/reset_yes_normal.png", "OptionsScene/reset_yes_selected.png");
    reset_yes_btn->setPosition(Vec2(visibleSize.width * 0.35,visibleSize.height * 0.5));
    reset_yes_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调函数
        SoundManager::getInstance()->button_sound_effect();//播放音效
        SaveManager::getInstance()->reset_data();//对存档数据进行重置操作
        this->getParent()->removeChild(black_layer);//删除当前层
        });
    reset_yes_btn->setScale(1.4);
    menu->addChild(reset_yes_btn);

    auto reset_no_btn = MenuItemImage::create("OptionsScene/reset_no_normal.png", "OptionsScene/reset_no_selected.png");
    reset_no_btn->setPosition(Vec2(visibleSize.width * 0.65,visibleSize.height * 0.5));
    reset_no_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调函数
        SoundManager::getInstance()->button_sound_effect();//播放音效
        this->getParent()->removeChild(black_layer);//关闭该层
        });
    reset_no_btn->setScale(1.4);
    menu->addChild(reset_no_btn);
    black_layer->addChild(menu);
}
//初始化背景
void SetLayer::initBackGround() {
    auto set = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/SettingBG1.PNG"));
    set->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(set);

    //其他背景
    auto sound_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_0.PNG"));
    sound_txt->setPosition(Vec2(visibleSize.width * 0.4,visibleSize.height * 0.7));
    this->addChild(sound_txt);

    auto bgmusic_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_2.PNG"));
    bgmusic_txt->setPosition(Vec2(visibleSize.width * 0.6,visibleSize.height * 0.7));
    this->addChild(bgmusic_txt);

    auto appeal_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_7.PNG"));
    appeal_txt->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(appeal_txt);

    auto weibo_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_12.PNG"));
    weibo_image->setPosition(Vec2(visibleSize.width * 0.4,visibleSize.height * 0.35));
    weibo_image->setScale(2);
    this->addChild(weibo_image);

    auto wechat_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_16.PNG"));
    wechat_image->setPosition(Vec2(visibleSize.width * 0.6,visibleSize.height * 0.35));
    wechat_image->setScale(2);
    this->addChild(wechat_image);
}
//初始化菜单
void SetLayer::initMenu() {
    /*********************************  选项层菜单  **************************************/
    auto set_menu = Menu::create();
    set_menu->setPosition(Vec2::ZERO);
    this->addChild(set_menu);
    //音效toggle
    auto sound_on_sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_6.PNG"));
    auto sound_on = MenuItemSprite::create(sound_on_sprite, sound_on_sprite);
    auto sound_off_sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_11.PNG"));
    auto sound_off = MenuItemSprite::create(sound_off_sprite, sound_off_sprite);
    MenuItemToggle* sound_toggle;
    if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {//根据当前音效是否打开决定渲染开关的图样是开还是关
        sound_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_sound, this), sound_on, sound_off, NULL);
    }
    else {
        sound_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_sound, this), sound_off, sound_on, NULL);
    }
    sound_toggle->setPosition(Vec2(visibleSize.width * 0.4,visibleSize.height * 0.6));
    set_menu->addChild(sound_toggle);
    ////背景音乐toggle
    auto bgmusic_on_sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_15.PNG"));
    auto bgmusic_on = MenuItemSprite::create(bgmusic_on_sprite, bgmusic_on_sprite);
    auto bgmusic_off_sprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_21.PNG"));
    auto bgmusic_off = MenuItemSprite::create(bgmusic_off_sprite, bgmusic_off_sprite);
    MenuItemToggle* bgmusic_toggle;
    if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {//根据当前bgm是否打开决定渲染开关的图样是开还是关
        bgmusic_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_bgmusic, this), bgmusic_on, bgmusic_off, NULL);
    }
    else {
        bgmusic_toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SetLayer::close_bgmusic, this), bgmusic_off, bgmusic_on, NULL);
    }
    bgmusic_toggle->setPosition(Vec2(visibleSize.width * 0.6,visibleSize.height * 0.6));
    set_menu->addChild(bgmusic_toggle);
    //重置游戏
    auto reset_game = MenuItemImage::create("OptionsScene/setting02-hd_55.PNG", "OptionsScene/setting02-hd_54.PNG", CC_CALLBACK_1(SetLayer::reset_game, this));
    reset_game->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.15));
    set_menu->addChild(reset_game);
}
/*************************   StatisticsLayer类  ****************************/
cocos2d::Layer* StatisticsLayer::createLayer()
{
    return StatisticsLayer::create();
}
//初始化
bool StatisticsLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize();

    initBackGround();
    initBg_1();
    initBg_2();
    initBg_3();
    initBg_4();
    initBg_5();
    initBg_6();
    initBg_7();
    return true;
}
//初始化背景
void StatisticsLayer::initBackGround() {
    auto statistics = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/SettingBG2.PNG"));
    statistics->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    addChild(statistics);
}
//初始化其他背景
void StatisticsLayer::initBg_1() {
    auto bg1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_22.PNG"));
    bg1->setPosition(Vec2(visibleSize.width * 0.5,visibleSize.height * 0.68));
    this->addChild(bg1);

    auto statistics_txt_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_23.PNG"));
    statistics_txt_1->setPosition(Vec2(visibleSize.width * 0.823,visibleSize.height * 0.68));
    this->addChild(statistics_txt_1);
    //根据存档数据中的冒险模式关卡输出统计数据
    std::string adventure_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("adventure_statistics"));
    auto adventure_statistics_label = Label::createWithTTF(adventure_statistics, "fonts/Marker Felt.ttf", 28);
    adventure_statistics_label->setAlignment(TextHAlignment::RIGHT);
    adventure_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    adventure_statistics_label->setPosition(Vec2(visibleSize.width * 0.77,visibleSize.height * 0.68));
    this->addChild(adventure_statistics_label);
}
void StatisticsLayer::initBg_2() {
    auto bg2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_27.PNG"));
    bg2->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.58));
    this->addChild(bg2);

    auto statistics_txt_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_23.PNG"));
    statistics_txt_2->setPosition(Vec2(visibleSize.width * 0.823, visibleSize.height * 0.58));
    this->addChild(statistics_txt_2);
    //根据存档数据中的隐藏关卡输出统计数据
    std::string hide_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("hide_statistics"));
    auto hide_statistics_label = Label::createWithTTF(hide_statistics, "fonts/Marker Felt.ttf", 28);
    hide_statistics_label->setAlignment(TextHAlignment::RIGHT);
    hide_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    hide_statistics_label->setPosition(Vec2(visibleSize.width * 0.77, visibleSize.height * 0.58));
    this->addChild(hide_statistics_label);
}
void StatisticsLayer::initBg_3() {
    auto bg3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_31.PNG"));
    bg3->setPosition(Vec2(visibleSize.width * 0.51,visibleSize.height * 0.49));
    this->addChild(bg3);

    auto statistics_txt_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_23.PNG"));
    statistics_txt_3->setPosition(Vec2(visibleSize.width * 0.823,visibleSize.height * 0.49));
    this->addChild(statistics_txt_3);
    //根据存档数据中的boss模式关卡输出统计数据
    std::string bosspattern_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("bosspattern_statistics"));
    auto bosspattern_statistics_label = Label::createWithTTF(bosspattern_statistics, "fonts/Marker Felt.ttf", 28);
    bosspattern_statistics_label->setAlignment(TextHAlignment::RIGHT);
    bosspattern_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    bosspattern_statistics_label->setPosition(Vec2(visibleSize.width * 0.77,visibleSize.height * 0.49));
    this->addChild(bosspattern_statistics_label);
}
void StatisticsLayer::initBg_4() {
    auto bg4 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_35.PNG"));
    bg4->setPosition(Vec2(visibleSize.width * 0.485,visibleSize.height * 0.41));
    this->addChild(bg4);
    //根据存档数据中的金币统计，输出统计数据
    std::string money_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("money_statistics"));
    auto money_statistics_label = Label::createWithTTF(money_statistics, "fonts/Marker Felt.ttf", 28);
    money_statistics_label->setAlignment(TextHAlignment::RIGHT);
    money_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    money_statistics_label->setPosition(Vec2(visibleSize.width * 0.85,visibleSize.height * 0.41));
    this->addChild(money_statistics_label);
}
void StatisticsLayer::initBg_5() {
    auto bg5 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_38.PNG"));
    bg5->setPosition(Vec2(visibleSize.width * 0.523,visibleSize.height * 0.32));
    this->addChild(bg5);
    //根据存档数据中的击败怪物个数统计，输出统计数据
    std::string monster_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("monster_statistics"));
    auto monster_statistics_label = Label::createWithTTF(monster_statistics, "fonts/Marker Felt.ttf", 28);
    monster_statistics_label->setAlignment(TextHAlignment::RIGHT);
    monster_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    monster_statistics_label->setPosition(Vec2(visibleSize.width * 0.85,visibleSize.height * 0.32));
    this->addChild(monster_statistics_label);
}
void StatisticsLayer::initBg_6() {
    auto bg6 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_42.PNG"));
    bg6->setPosition(Vec2(visibleSize.width * 0.534, visibleSize.height * 0.23));
    this->addChild(bg6);
    //根据存档数据中的击败boss个数，输出统计数据
    std::string boss_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("boss_statistics"));
    auto boss_statistics_label = Label::createWithTTF(boss_statistics, "fonts/Marker Felt.ttf", 28);
    boss_statistics_label->setAlignment(TextHAlignment::RIGHT);
    boss_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    boss_statistics_label->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.23));
    this->addChild(boss_statistics_label);
}
void StatisticsLayer::initBg_7() {
    auto bg7 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/setting02-hd_44.PNG"));
    bg7->setPosition(Vec2(visibleSize.width * 0.523,visibleSize.height * 0.14));
    this->addChild(bg7);
    //根据存档数据中的摧毁障碍物个数，输出统计数据
    std::string damage_statistics = std::to_string(UserDefault::getInstance()->getIntegerForKey("damage_statistics"));
    auto damage_statistics_label = Label::createWithTTF(damage_statistics, "fonts/Marker Felt.ttf", 28);
    damage_statistics_label->setAlignment(TextHAlignment::RIGHT);
    damage_statistics_label->setAnchorPoint(Vec2(1, 0.5));
    damage_statistics_label->setPosition(Vec2(visibleSize.width * 0.85,visibleSize.height * 0.14));
    this->addChild(damage_statistics_label);
}
/*************************  PersonLayer类  ********************************/
cocos2d::Layer* PersonLayer::createLayer()
{
    return PersonLayer::create();
}
//初始化
bool PersonLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize();

    initBackGround();

    return true;
}
//初始化背景
void PersonLayer::initBackGround() {
    //背景
    auto person = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("OptionsScene/SettingBG3.PNG"));
    person->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(person);
}