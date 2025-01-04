#include"Game/GameScene.h"
#include "FrontEnd/GameSelectionScene.h"
#include "FrontEnd/MenuScene.h"
#include "FrontEnd/OptionsScene.h"
#include "FrontEnd/HelperScene.h"
#include "Config/sound&music.h"
#include "Config/GameData.h"
USING_NS_CC;
/*******************************  GameSelectionScene  ******************************/
Scene*  GameSelectionScene::createScene()
{
    return GameSelectionScene::create();
}
/*初始化*/
bool GameSelectionScene::init()
{
    /*初始化场景*/
    if (!Scene::init())
    {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize();

    initBackGround();
    initMenu();
    initBigLevelLayer();

    return true;
}
void GameSelectionScene::gotoHelper(Ref* psender) {
    SoundManager::getInstance()->button_sound_effect();//播放音效
    auto helper_scene = HelperScene::createScene();//创建帮助场景
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.2, helper_scene));//以消失形式切换
}
//初始化背景
void GameSelectionScene::initBackGround() {
    auto background_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/stages_bg-hd_0.PNG"));
    background_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    this->addChild(background_image);
}
//初始化菜单
void GameSelectionScene::initMenu() {
    auto menu = Menu::create();
    this->addChild(menu);
    menu->setPosition(Vec2::ZERO);
    //去帮助界面
    auto help_btn = MenuItemImage::create("GameSelectionScene/stages_bg-hd_42.PNG", "GameSelectionScene/stages_bg-hd_33.PNG",CC_CALLBACK_1(GameSelectionScene::gotoHelper,this));
    help_btn->setPosition(Vec2(visibleSize.width * 0.8,visibleSize.height * 0.95));
    menu->addChild(help_btn);
}
//初始化选择大关关卡
void GameSelectionScene::initBigLevelLayer() {
    auto biglevel = BigLevelLayer::createLayer();//创建选大关的Layer
    this->addChild(biglevel);//添加渲染
}
/*******************************  BigLevelLayer  ******************************/
cocos2d::Layer* BigLevelLayer::createLayer()
{
	return BigLevelLayer::create();
}
//初始化
bool BigLevelLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
    //获取屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();

    for (int i = 0; i < totalPage; i++) {
        pagesPoint[i] = -visibleSize.width * (i-1);
    }
    currentPage = 1;

    initPage();
    initMenu();
    initSlideLayer();
    initListener();
    return true;
}
//去评价界
void BigLevelLayer::goto_evaluate()
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    /************************  纯色层  *****************************/
    auto evaluate_layer = LayerColor::create(Color4B::BLACK);
    evaluate_layer->setPosition(Vec2::ZERO);
    evaluate_layer->setOpacity(85);
    this->addChild(evaluate_layer, 1);
    /************************  事件监听器  *****************************/
    auto listener2 = EventListenerTouchOneByOne::create();
    listener2->setSwallowTouches(true);//设置吞没，以确保必须按按钮才能返回上一页
    listener2->onTouchBegan = [evaluate_layer](Touch* touch, Event* event) {
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener2, evaluate_layer);

    /******************  背景  ***************************/
    auto evaluate_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/evaluate.png"));
    evaluate_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
    evaluate_layer->addChild(evaluate_image);
    /*******************  菜单  **************************/
    auto evaluate_menu = Menu::create();
    evaluate_menu->setPosition(Vec2::ZERO);
    evaluate_layer->addChild(evaluate_menu);
    //确认按钮
    auto ok_btn = MenuItemImage::create("GameSelectionScene/close_evaluate_normal.png", "GameSelectionScene/close_evaluate_selected.png");
    ok_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.25));
    ok_btn->setScale(1.4);
    ok_btn->setCallback([this, evaluate_layer](Ref* psender) {//按钮回调事件，返回上一级
        SoundManager::getInstance()->button_sound_effect();
        this->removeChild(evaluate_layer);
        });
    evaluate_menu->addChild(ok_btn);
}
//去天际
void BigLevelLayer::goto_level_1()
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    auto level_1_layer = Level_1_Layer::createLayer();//创建层，并加入
    this->getParent()->addChild(level_1_layer);
    this->removeFromParentAndCleanup(true);
}
//去丛林
void BigLevelLayer::goto_level_2()
{
    SoundManager::getInstance()->button_sound_effect();//播放音效

    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {//若当前丛林未解锁，则上锁提示
        /*****************************  纯色层  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  背景  *****************************************/
        auto level_2_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/level_2_lock.png"));
        level_2_lock->setPosition(Vec2(visibleSize.width / 2,
            visibleSize.height / 2));
        level_2_lock->setScale(1.4);
        black_layer->addChild(level_2_lock);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("GameSelectionScene/lock_btn_normal.png", "GameSelectionScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(visibleSize.width * 0.55,
            visibleSize.height * 0.4));
        lock_btn->setCallback([this, black_layer](Ref* psender) {
            SoundManager::getInstance()->button_sound_effect();
            this->removeChild(black_layer);
            });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer, 2);
    }
    else {
        ;//boss_pattern待开发
    }
}
//去沙漠
void BigLevelLayer::goto_level_3()
{
    SoundManager::getInstance()->button_sound_effect();//播放音效

    if (UserDefault::getInstance()->getIntegerForKey("level_3") == 0) {//若当前沙漠未解锁，则上锁提示

        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        /*****************************  纯色层  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
        };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  背景  *****************************************/
        auto level_3_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/level_3_lock.png"));
        level_3_lock->setPosition(Vec2(visibleSize.width / 2,
            visibleSize.height / 2));
        level_3_lock->setScale(1.4);
        black_layer->addChild(level_3_lock);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("GameSelectionScene/lock_btn_normal.png", "GameSelectionScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(visibleSize.width * 0.55,
            visibleSize.height * 0.4));
        lock_btn->setCallback([this, black_layer](Ref* psender) {
            SoundManager::getInstance()->button_sound_effect();
            this->removeChild(black_layer);
            });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer, 2);
    }
    else {
        ;//boss_pattern待开发
    }
}
void BigLevelLayer::goto_menu(Ref* psender) {
    SoundManager::getInstance()->button_sound_effect();//播放音效
    auto menu_scene = MenuScene::createScene();//创建主菜单对应Scene
    Director::getInstance()->replaceScene(TransitionFlipAngular::create(0.2, menu_scene));//以对角反转形式切换
}
//初始化页码
void BigLevelLayer::initPage() {
    auto page_0 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_no.png"));
    page_0->setScale(1.4);
    page_0->setPosition(Vec2(visibleSize.width * 0.47, visibleSize.height * 0.05));
    this->addChild(page_0);
    pageNum[0] = page_0;

    auto page_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_yes.png"));
    page_1->setScale(1.4);
    page_1->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.05));
    this->addChild(page_1);
    pageNum[1] = page_1;

    auto page_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_no.png"));
    page_2->setScale(1.4);
    page_2->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.05));
    this->addChild(page_2);
    pageNum[2] = page_2;

    auto page_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_no.png"));
    page_3->setScale(1.4);
    page_3->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.05));
    this->addChild(page_3);
    pageNum[3] = page_3;
}
//初始化菜单
void BigLevelLayer::initMenu() {
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0);
    //返回主菜单
    auto home_btn = MenuItemImage::create("GameSelectionScene/themescene1-hd_8.PNG", "GameSelectionScene/themescene1-hd_17.PNG", CC_CALLBACK_1(BigLevelLayer::goto_menu, this));
    home_btn->setPosition(Vec2(visibleSize.width * 0.2,
        visibleSize.height * 0.95));
    menu->addChild(home_btn);
    //向左翻页按钮
    auto left_btn = MenuItemImage::create("GameSelectionScene/themescene1-hd_32.PNG", "GameSelectionScene/themescene1-hd_31.PNG",CC_CALLBACK_0(BigLevelLayer::lastPage, this));
    left_btn->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height / 2));
    menu->addChild(left_btn);
    //向右翻页按钮
    auto right_btn = MenuItemImage::create("GameSelectionScene/themescene1-hd_26.PNG", "GameSelectionScene/themescene1-hd_25.PNG",CC_CALLBACK_0(BigLevelLayer::nextPage, this));
    right_btn->setPosition(Vec2(visibleSize.width * 0.9, visibleSize.height / 2));
    menu->addChild(right_btn);
}
//初始化滑动层
void BigLevelLayer::initSlideLayer() {
    slideLayer = Layer::create();
    this->addChild(slideLayer);

    evaluate = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene1-hd.png"));
    evaluate->setPosition(Vec2(visibleSize.width * (-0.5),visibleSize.height / 2));
    slideLayer->addChild(evaluate);
    //天际
    skyline = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene2-hd.pvr_2.PNG"));
    skyline->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.45));
    slideLayer->addChild(skyline);
    //天际关卡统计
    auto level_1_statistics_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Items03-hd.pvr_0.PNG"));
    level_1_statistics_image->setPosition(Vec2(visibleSize.width * 0.66,visibleSize.height * 0.11));
    slideLayer->addChild(level_1_statistics_image);

    auto level_1_statistics_txt = Label::createWithTTF(std::to_string(UserDefault::getInstance()->getIntegerForKey("level_1")) + "/9","fonts/Marker Felt.ttf", 20);
    level_1_statistics_txt->setPosition(Vec2(visibleSize.width * 0.66,visibleSize.height * 0.12));
    slideLayer->addChild(level_1_statistics_txt);
    //丛林
    jungle = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene2-hd.pvr_0.PNG"));
    jungle->setPosition(Vec2(visibleSize.width * 1.5,visibleSize.height * 0.45));
    slideLayer->addChild(jungle);
    //丛林关卡统计
    if (UserDefault::getInstance()->getIntegerForKey("level_2") == 0) {
        auto level_2_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene1-hd_10.PNG"));
        level_2_lock->setPosition(Vec2(visibleSize.width * 1.78,visibleSize.height * 0.2));
        slideLayer->addChild(level_2_lock);
    }
    else {
        //待开发
    }
    //沙漠
    desert = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene2-hd.pvr_1.PNG"));
    desert->setPosition(Vec2(visibleSize.width * 2.5,visibleSize.height * 0.45));
    slideLayer->addChild(desert);
    //沙漠关卡统计
    if (UserDefault::getInstance()->getIntegerForKey("level_3") == 0) {
        auto level_3_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/themescene1-hd_10.PNG"));
        level_3_lock->setPosition(Vec2(visibleSize.width * 2.78,visibleSize.height * 0.2));
        slideLayer->addChild(level_3_lock);
    }
    else {
        //待开发
    }
}
//初始化监听器
void BigLevelLayer::initListener() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);//设置事件吞没
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        Vec2 pos = slideLayer->convertTouchToNodeSpace(touch);
        //若触摸起始点在每一个图形的选择范围内则事件吞没
        if ((pos.x > evaluate->getPositionX() - evaluate->getContentSize().width / 2 &&
            pos.x< evaluate->getPositionX() + evaluate->getContentSize().width / 2 &&
            pos.y>evaluate->getPositionY() - evaluate->getContentSize().height / 2 &&
            pos.y < evaluate->getPositionY() + evaluate->getContentSize().height / 2)
            ||
            (pos.x > skyline->getPositionX() - skyline->getContentSize().width / 2 &&
                pos.x< skyline->getPositionX() + skyline->getContentSize().width / 2 &&
                pos.y>skyline->getPositionY() - skyline->getContentSize().height / 2 &&
                pos.y < skyline->getPositionY() + skyline->getContentSize().height / 2)
            ||
            (pos.x > jungle->getPositionX() - jungle->getContentSize().width / 2 &&
                pos.x< jungle->getPositionX() + jungle->getContentSize().width / 2 &&
                pos.y>jungle->getPositionY() - jungle->getContentSize().height / 2 &&
                pos.y < jungle->getPositionY() + jungle->getContentSize().height / 2)
            ||
            (pos.x > desert->getPositionX() - desert->getContentSize().width / 2 &&
                pos.x< desert->getPositionX() + desert->getContentSize().width / 2 &&
                pos.y>desert->getPositionY() - desert->getContentSize().height / 2 &&
                pos.y < desert->getPositionY() + desert->getContentSize().height / 2)
            ) {
            return true;
        }
            return false;
        };
    listener->onTouchMoved = [this](Touch* touch, Event* event) {//实现屏幕随触摸移动
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        slideLayer->setPositionX(slideLayer->getPositionX() + distance);
        };
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        float distance = touch->getLocation().x - touch->getStartLocation().x;//记录本次触摸的横向距离
        if (distance > visibleSize.width / 6) {//若大于六分之一屏幕距离，则视翻页成功，向左一页
            lastPage();
        }
        else if (distance < -visibleSize.width / 6) {//视为向右移动一页
            nextPage();
        }
        else {//若小于六分之一屏幕，视本次触摸为取消翻页或点击
            if (distance) {
                rollBack();
                return;
            }
            Vec2 pos = slideLayer->convertTouchToNodeSpace(touch);
            if (pos.x > evaluate->getPositionX() - evaluate->getContentSize().width / 2 &&
                pos.x< evaluate->getPositionX() + evaluate->getContentSize().width / 2 &&
                pos.y>evaluate->getPositionY() - evaluate->getContentSize().height / 2 &&
                pos.y < evaluate->getPositionY() + evaluate->getContentSize().height / 2) {
                goto_evaluate();
            }
            else if (pos.x > skyline->getPositionX() - skyline->getContentSize().width / 2 &&
                pos.x< skyline->getPositionX() + skyline->getContentSize().width / 2 &&
                pos.y>skyline->getPositionY() - skyline->getContentSize().height / 2 &&
                pos.y < skyline->getPositionY() + skyline->getContentSize().height / 2) {
                goto_level_1();
            }
            else if
                (pos.x > jungle->getPositionX() - jungle->getContentSize().width / 2 &&
                    pos.x< jungle->getPositionX() + jungle->getContentSize().width / 2 &&
                    pos.y>jungle->getPositionY() - jungle->getContentSize().height / 2 &&
                    pos.y < jungle->getPositionY() + jungle->getContentSize().height / 2) {
                goto_level_2();
            }
            else if
                (pos.x > desert->getPositionX() - desert->getContentSize().width / 2 &&
                    pos.x< desert->getPositionX() + desert->getContentSize().width / 2 &&
                    pos.y>desert->getPositionY() - desert->getContentSize().height / 2 &&
                    pos.y < desert->getPositionY() + desert->getContentSize().height / 2)
            {
                goto_level_3();
            }
        }
        };
    //将事件监听器加入事件分发器内
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,slideLayer);
}
//部分函数
void BigLevelLayer::lastPage() {
    if (currentPage==0) {
        rollBack();
        return;
    }
    pageNum[currentPage]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_no.png"));
    currentPage--;
    slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
    pageNum[currentPage]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_yes.png"));
    SoundManager::getInstance()->page_sound_effect();
}
void BigLevelLayer::nextPage() {
    if (currentPage == totalPage - 1) {
        rollBack();
        return;
    }
    pageNum[currentPage]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_no.png"));
    currentPage++;
    slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
    pageNum[currentPage]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/page_yes.png"));
    SoundManager::getInstance()->page_sound_effect();
}
void BigLevelLayer::rollBack() {
    slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
}
/********************************  Level_1_Layer  *********************************/
cocos2d::Layer* Level_1_Layer::createLayer()
{
    return Level_1_Layer::create();
}
//初始化
bool Level_1_Layer::init()
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    visibleSize = Director::getInstance()->getVisibleSize();

    for (int i = 0; i < totalPage; i++) {
        pagesPoint[i] = -visibleSize.width * i;
    }
    currentPage = 0;


    initBackGround();
    initMenu();
    initSlideLayer();
    initListener();

    return true;
}
//回到选大关界面
void Level_1_Layer::return_to_biglevel(Ref* psender)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    this->getParent()->addChild(BigLevelLayer::create());
    this->removeFromParent();//移除当前Layer
}
//天际第2关
void Level_1_Layer::gotoGameScene(Ref*psender,int level)
{
    SoundManager::getInstance()->button_sound_effect();//播放音效
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < level) {//若当前关未解锁，弹出提示
        /*****************************  纯色层  ******************************************/
        auto black_layer = LayerColor::create(Color4B::BLACK);
        black_layer->setOpacity(85);

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = [black_layer](Touch* touch, Event* event) {
            return true;
            };
        listener->setSwallowTouches(true);
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, black_layer);
        /********************************  背景  *****************************************/
        auto lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/lock_image.png"));
        lock->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
        lock->setScale(1.4);
        black_layer->addChild(lock);
        /********************************  按钮  ****************************************/
        auto menu = Menu::create();
        menu->setPosition(Vec2::ZERO);

        auto lock_btn = MenuItemImage::create("GameSelectionScene/lock_btn_normal.png", "GameSelectionScene/lock_btn_selected.png");
        lock_btn->setPosition(Vec2(visibleSize.width * 0.55,visibleSize.height * 0.4));
        lock_btn->setCallback([this, black_layer](Ref* psender) {
            SoundManager::getInstance()->button_sound_effect();
            this->removeChild(black_layer);
            });
        lock_btn->setScale(1.4);
        menu->addChild(lock_btn);
        black_layer->addChild(menu);

        this->addChild(black_layer, 2);
    }
    else {
        CCLOG("enter game %d", level);
        //level_selection = 2;
        //auto game_scene = GameScene::createScene();
        //Director::getInstance()->replaceScene(game_scene);
    }
}
//初始化背景
void Level_1_Layer::initBackGround() {
    auto bg_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/BG_Left.PNG"));
    bg_1->setPosition(Vec2(bg_1->getContentSize().width / 2,bg_1->getContentSize().height / 2));
    this->addChild(bg_1);

    auto bg_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/BG_Right.PNG"));
    bg_2->setPosition(Vec2(+visibleSize.width - bg_2->getContentSize().width / 2,bg_2->getContentSize().height / 2));
    this->addChild(bg_2);

}
//初始化菜单
void Level_1_Layer::initMenu() {
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    //返回选大关
    auto return_btn = MenuItemImage::create("GameSelectionScene/stages_bg-hd_41.PNG", "GameSelectionScene/stages_bg-hd_40.PNG",CC_CALLBACK_1(Level_1_Layer::return_to_biglevel, this));
    return_btn->setPosition(Vec2(visibleSize.width * 0.2,visibleSize.height * 0.95));
    menu->addChild(return_btn);
}
//初始化滑动层
void Level_1_Layer::initSlideLayer() {
    /**********************  滑动层设计  ***********************/
    //创建一个滑动层
    slideLayer = Layer::create();
    this->addChild(slideLayer);

    //可动层  随触摸动画移动
    move_layer = Layer::create();
    slideLayer->addChild(move_layer);
    //不可动层  在触摸确定翻页后直接移动
    static_layer = Layer::create();
    slideLayer->addChild(static_layer);

    //开始
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    auto level_btn = MenuItemImage::create("GameSelectionScene/stages_bg-hd_30.PNG", "GameSelectionScene/stages_bg-hd_28.PNG", "GameSelectionScene/stages_bg-hd_39.PNG", [this](Ref* psender) {gotoGameScene(this, currentPage + 1); });
    level_btn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.1));
    menu->addChild(level_btn);

    //共几波
    auto waves = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/total_waves.png"));
    waves->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.83));
    this->addChild(waves);

    /*************************  关卡level_1_1  **************************************/
    //图  背景图需滑动，加入可动层
    auto level_1_1_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Level_1.PNG"));
    level_1_1_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.54));
    move_layer->addChild(level_1_1_image);
    levels[0] = level_1_1_image;

    auto waves_1_txt = Label::createWithTTF("15", "fonts/Marker Felt.ttf", 24);
    waves_1_txt->setTextColor(Color4B::YELLOW);
    waves_1_txt->setPosition(Vec2(visibleSize.width * 0.6,visibleSize.height * 0.83));
    static_layer->addChild(waves_1_txt);
    //炮台类型  不需滑动，加入不可动层
    //瓶子
    auto tower_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_1.PNG"));
    tower_1->setPosition(Vec2(visibleSize.width / 2 - tower_1->getContentSize().width / 2,visibleSize.height * 0.23));
    static_layer->addChild(tower_1);
    //便便
    auto tower_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_2.PNG"));
    tower_2->setPosition(Vec2(visibleSize.width / 2 + tower_2->getContentSize().width / 2,visibleSize.height * 0.23));
    static_layer->addChild(tower_2);
    /*************************  关卡level_1_2  **************************************/
    //图 可动层
    auto level_1_2_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Level_2.PNG"));
    level_1_2_image->setPosition(Vec2(visibleSize.width * 1.5,visibleSize.height * 0.54));
    move_layer->addChild(level_1_2_image);
    levels[1] = level_1_2_image;
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 2) {//若未解锁，则渲染“锁”提示
        auto level_1_2_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/stages_bg-hd_31.PNG"));
        level_1_2_lock->setPosition(Vec2(visibleSize.width * 1.64,visibleSize.height * 0.4));
        move_layer->addChild(level_1_2_lock);
    }
    auto waves_2_txt = Label::createWithTTF("15", "fonts/Marker Felt.ttf", 24);
    waves_2_txt->setTextColor(Color4B::YELLOW);
    waves_2_txt->setPosition(Vec2(visibleSize.width * 1.6,visibleSize.height * 0.83));
    static_layer->addChild(waves_2_txt);
    //炮台类型 不可动层
    //瓶子
    auto tower_2_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_1.PNG"));
    tower_2_1->setPosition(Vec2(visibleSize.width * 1.5 - tower_2_1->getContentSize().width,visibleSize.height * 0.23));
    static_layer->addChild(tower_2_1);
    //便便
    auto tower_2_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_2.PNG"));
    tower_2_2->setPosition(Vec2(visibleSize.width * 1.5,visibleSize.height * 0.23));
    static_layer->addChild(tower_2_2);
    //星星
    auto tower_2_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_4.PNG"));
    tower_2_3->setPosition(Vec2(visibleSize.width * 1.5 + tower_2_3->getContentSize().width,visibleSize.height * 0.23));
    static_layer->addChild(tower_2_3);

    /*************************  关卡level_1_3  **************************************/
     //图 可动层
    auto level_1_3_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Level_3.PNG"));
    level_1_3_image->setPosition(Vec2(visibleSize.width * 2.5,visibleSize.height * 0.54));
    move_layer->addChild(level_1_3_image);
    levels[2] = level_1_3_image;
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 3) {//若未解锁，则渲染“锁”提示
        auto level_1_3_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/stages_bg-hd_31.PNG"));
        level_1_3_lock->setPosition(Vec2(visibleSize.width * 2.64,visibleSize.height * 0.4));
        move_layer->addChild(level_1_3_lock);
    }
    auto waves_3_txt = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 24);
    waves_3_txt->setTextColor(Color4B::YELLOW);
    waves_3_txt->setPosition(Vec2(visibleSize.width * 2.6,visibleSize.height * 0.83));
    static_layer->addChild(waves_3_txt);
    //炮台类型  不可动层
    //瓶子
    auto tower_3_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_1.PNG"));
    tower_3_1->setPosition(Vec2(visibleSize.width * 2.5 - tower_3_1->getContentSize().width,visibleSize.height * 0.23));
    static_layer->addChild(tower_3_1);
    //便便
    auto tower_3_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_2.PNG"));
    tower_3_2->setPosition(Vec2(visibleSize.width * 2.5,visibleSize.height * 0.23));
    static_layer->addChild(tower_3_2);
    //风扇
    auto tower_3_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_3.PNG"));
    tower_3_3->setPosition(Vec2(visibleSize.width * 2.5 + tower_3_3->getContentSize().width,visibleSize.height * 0.23));
    static_layer->addChild(tower_3_3);

    /*************************  关卡level_1_4  **************************************/
    //图
    auto level_1_4_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Level_4.PNG"));
    level_1_4_image->setPosition(Vec2(visibleSize.width * 3.5,visibleSize.height * 0.54));
    move_layer->addChild(level_1_4_image);
    levels[3] = level_1_4_image;
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 4) {//若未解锁，则渲染“锁”提示
        auto level_1_4_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/stages_bg-hd_31.PNG"));
        level_1_4_lock->setPosition(Vec2(visibleSize.width * 3.64,visibleSize.height * 0.4));
        move_layer->addChild(level_1_4_lock);
    }
    auto waves_4_txt = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 24);
    waves_4_txt->setTextColor(Color4B::YELLOW);
    waves_4_txt->setPosition(Vec2(visibleSize.width * 3.6,visibleSize.height * 0.83));
    static_layer->addChild(waves_4_txt);
    //炮台类型
    //便便
    auto tower_4_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_2.PNG"));
    tower_4_1->setPosition(Vec2(visibleSize.width * 3.5 - tower_4_1->getContentSize().width / 2,visibleSize.height * 0.23));
    static_layer->addChild(tower_4_1);
    //水晶塔
    auto tower_4_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_5.PNG"));
    tower_4_2->setPosition(Vec2(visibleSize.width * 3.5 + tower_4_2->getContentSize().width / 2,visibleSize.height * 0.23));
    static_layer->addChild(tower_4_2);
    /*************************  关卡level_1_5  **************************************/
    //图
    auto level_1_5_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Level_5.PNG"));
    level_1_5_image->setPosition(Vec2(visibleSize.width * 4.5,visibleSize.height * 0.54));
    move_layer->addChild(level_1_5_image);
    levels[4] = level_1_5_image;
    if (UserDefault::getInstance()->getIntegerForKey("level_1") < 5) {//若未解锁，则渲染“锁”提示
        auto level_1_5_lock = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/stages_bg-hd_31.PNG"));
        level_1_5_lock->setPosition(Vec2(visibleSize.width * 4.64,visibleSize.height * 0.4));
        move_layer->addChild(level_1_5_lock);
    }
    auto waves_5_txt = Label::createWithTTF("20", "fonts/Marker Felt.ttf", 24);
    waves_5_txt->setTextColor(Color4B::YELLOW);
    waves_5_txt->setPosition(Vec2(visibleSize.width * 4.6,visibleSize.height * 0.83));
    static_layer->addChild(waves_5_txt);
    //炮台类型
    //便便
    auto tower_5_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_2.PNG"));
    tower_5_1->setPosition(Vec2(visibleSize.width * 4.5 - tower_5_1->getContentSize().width / 2,visibleSize.height * 0.23));
    static_layer->addChild(tower_5_1);
    //星星
    auto tower_5_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("GameSelectionScene/Tower_4.PNG"));
    tower_5_2->setPosition(Vec2(visibleSize.width * 4.5 + tower_5_2->getContentSize().width / 2, visibleSize.height * 0.23));
    static_layer->addChild(tower_5_2);
}
//初始化监听器
void Level_1_Layer::initListener() {
    /***********************  滑动实现  *****************************/
    auto listener4 = EventListenerTouchOneByOne::create();
    listener4->onTouchBegan = [this](Touch* touch, Event* event) {
        return true;
        };
    listener4->onTouchMoved = [this](Touch* touch, Event* event) {//实现触摸滑动
        float distance = touch->getLocation().x - touch->getPreviousLocation().x;
        move_layer->setPositionX(move_layer->getPositionX() + distance);
        };
    listener4->onTouchEnded = [this](Touch* touch, Event* event) {
        //获取触摸移动横向距离
        float distance = touch->getLocation().x - touch->getStartLocation().x;
        if (distance > visibleSize.width / 6) {//若滑动大于六分之一屏幕，则视为滑动翻页
            lastPage();
        }
        else if (distance < -visibleSize.width / 6) {
            nextPage();
        }
        else {//若小于六分之一屏幕，则视为取消翻页或点击
            if (distance) {//若取消翻页，则回到滑动前的页码
                rollBack();
                return;
            }
            Vec2 pos = move_layer->convertTouchToNodeSpace(touch);
            for (int i = 0; i < totalPage; i++) {
                if (pos.x > levels[i]->getPositionX() - levels[i]->getContentSize().width / 2 &&
                    pos.x< levels[i]->getPositionX() + levels[i]->getContentSize().width / 2 &&
                    pos.y>levels[i]->getPositionY() - levels[i]->getContentSize().height / 2 &&
                    pos.y < levels[i]->getPositionY() + levels[i]->getContentSize().height / 2) {
                    gotoGameScene(slideLayer, currentPage+1);
                }
            }
        }
        };
    //将事件监听器加入事件分发器
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener4, move_layer);
}
void Level_1_Layer::lastPage() {
    if (currentPage==0) {
        rollBack();
        return;
    }
    SoundManager::getInstance()->page_sound_effect();
    currentPage--;
    move_layer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
    static_layer->setPosition(Vec2(pagesPoint[currentPage], static_layer->getPositionY()));
}
void Level_1_Layer::nextPage() {
    if (currentPage == totalPage - 1) {
        rollBack();
        return;
    }
    SoundManager::getInstance()->page_sound_effect();
    currentPage++;
    move_layer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
    static_layer->setPosition(Vec2(pagesPoint[currentPage], static_layer->getPositionY()));
}
void Level_1_Layer::rollBack() {
    move_layer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
}