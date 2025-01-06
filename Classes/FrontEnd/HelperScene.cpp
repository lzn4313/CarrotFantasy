#include "FrontEnd/MenuScene.h"
#include "FrontEnd/HelperScene.h"
#include"Config/sound&music.h"
USING_NS_CC;
/*****************************  HelperScene类  ***********************************************************/
cocos2d::Scene* HelperScene::createScene()
{
	return HelperScene::create();
}
//初始化
bool HelperScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	//获取屏幕位置
	visibleSize = Director::getInstance()->getVisibleSize();

	initBackGround();
	initMenu();
	initLayers();
	currentState = new HelpState();
	currentState->enter(this);

	return true;
}
//返回主菜单
void HelperScene::goto_home(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//播放音效
	Scene* menu_scene = MenuScene::createScene();//创建菜单场景
	Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, menu_scene));//以从上向下滑动方式切换
}
//去帮助选项页
void HelperScene::goto_help(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//播放音效
	currentState->exit(this);
	currentState = new HelpState();
	currentState->enter(this);
}
//去monster选项页
void HelperScene::goto_monster(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//播放音效
	currentState->exit(this);
	currentState = new MonsterState();
	currentState->enter(this);
}
//去tower选项页
void HelperScene::goto_tower(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//播放音效
	currentState->exit(this);
	currentState = new TowerState();
	currentState->enter(this);
}
//初始化背景
void HelperScene::initBackGround() {
	auto background_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_bg.png"));
	background_image->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background_image);
}
//初始化菜单
void HelperScene::initMenu() {
	/**************************************************  菜单  *****************************************************/
	auto menu_all = Menu::create();
	menu_all->setPosition(Vec2::ZERO);
	//返回主菜单的按钮（以MenuItemImage形式实现）
	auto home = MenuItemImage::create("HelperScene/help_1-hd_67.PNG", "HelperScene/help_1-hd_38.PNG", CC_CALLBACK_1(HelperScene::goto_home, this));
	home->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.92));
	menu_all->addChild(home);
	this->addChild(menu_all);
	/***********************************************选项卡****************************************************/
	//help按钮
	help_btn = MenuItemImage::create("HelperScene/help_1-hd-33_normal.PNG", "HelperScene/help_1-hd-33_normal.PNG", "HelperScene/help_1-hd_33.PNG",CC_CALLBACK_1(HelperScene::goto_help,this));
	help_btn->setPosition(Vec2(visibleSize.width * 0.31,visibleSize.height * 0.925));
	help_btn->setScale(1.4);
	menu_all->addChild(help_btn);
	//monster按钮
	monster_btn = MenuItemImage::create("HelperScene/help_1-hd_71_normal.PNG", "HelperScene/help_1-hd_71_normal.PNG", "HelperScene/help_1-hd_71.png",CC_CALLBACK_1(HelperScene::goto_monster, this));
	monster_btn->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.922));
	monster_btn->setScale(1.4);
	menu_all->addChild(monster_btn);
	//tower按钮
	tower_btn = MenuItemImage::create("HelperScene/help_1-hd_66_normal.PNG", "HelperScene/help_1-hd_66_normal.PNG", "HelperScene/help_1-hd_66.PNG", CC_CALLBACK_1(HelperScene::goto_tower, this));
	tower_btn->setPosition(Vec2(visibleSize.width * 0.69,visibleSize.height * 0.923));
	tower_btn->setScale(1.4);
	menu_all->addChild(tower_btn);
}
//初始化层
void HelperScene::initLayers() {
	helpLayer = HelpLayer::create();
	helpLayer->removeAllChildrenWithCleanup(true);
	monsterLayer = MonsterLayer::create();
	towerLayer = TowerLayer::create();
	towerLayer->removeAllChildrenWithCleanup(true);

	helpLayer->setVisible(false);
	monsterLayer->setVisible(false);
	towerLayer->setVisible(false);

	addChild(helpLayer);
	addChild(monsterLayer);
	addChild(towerLayer);
}
/*************************************** HelpLayer类  ******************************************/
cocos2d::Layer* HelpLayer::createLayer()
{
	return HelpLayer::create();
}
//初始化
bool HelpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//获取屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < totalPage; i++) {
		pagesPoint[i] = -visibleSize.width * i;
		numImage[i] = "HelperScene/num_" + std::to_string(i+1) + ".png";
	}
	currentPage = 0;

	initSlideLayer();
	initListener();

	return true;
}
//初始化滑动层
void HelpLayer::initSlideLayer() {
	/**************************  滑动层  ********************************/
	//实现原理，将对应的几页内容全部按顺序横向渲染，通过移动当前层的位置来实现翻页效果
	slideLayer = Layer::create();
	slideLayer->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height * 0.9)));
	this->addChild(slideLayer);
	/**************************  第一页  ******************************/
	auto help_1_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_1.png"));
	help_1_image->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55));
	slideLayer->addChild(help_1_image);
	auto help_1_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_73.PNG"));
	help_1_txt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.22));
	slideLayer->addChild(help_1_txt);
	/**************************  第二页  ******************************/
	auto help_2_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_2.png"));
	help_2_image->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_2_image);
	auto help_2_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_4.PNG"));
	help_2_txt->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_2_txt);
	/**************************  第三页  ******************************/
	auto help_3_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_3.png"));
	help_3_image->setPosition(Vec2(visibleSize.width * 2.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_3_image);
	auto help_3_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_50.PNG"));
	help_3_txt->setPosition(Vec2(visibleSize.width * 2.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_3_txt);
	/**************************  第四页  ******************************/
	auto help_4_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_4.png"));
	help_4_image->setPosition(Vec2(visibleSize.width * 3.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_4_image);
	auto help_4_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_65.PNG"));
	help_4_txt->setPosition(Vec2(visibleSize.width * 3.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_4_txt);

	/***************************  页码  ******************************/
	auto page_num_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_0.PNG"));
	page_num_image->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.06));
	this->addChild(page_num_image);
	auto num_divide = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_-1.png"));
	num_divide->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.062));
	this->addChild(num_divide);
	num_divide->setScale(1.4);
	auto num_4 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_4.png"));
	num_4->setPosition(Vec2(visibleSize.width / 2 + num_4->getContentSize().width * 2, visibleSize.height * 0.062));
	this->addChild(num_4);
	num_4->setScale(1.4);
	pageNum = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_1.png"));
	pageNum->setScale(1.4);
	pageNum->setPosition(Vec2(visibleSize.width / 2 - pageNum->getContentSize().width * 3, visibleSize.height * 0.062));
	this->addChild(pageNum);
}
//初始化监听器
void HelpLayer::initListener() {
	/****************************  滑动实现  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (touch->getLocation().y < slideLayer->getContentSize().height) {
			return true;
		}
		return false;
		};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {//实现屏幕跟着滑动的效果
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		slideLayer->setPositionX(slideLayer->getPositionX() + distance);
		};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//获取本次触摸移动的横向距离
		if (distance > visibleSize.width / 6) {//如果滑动距离大于六分之一屏幕（向右滑），则选择切换到左一页
			lastPage();
		}
		else if (distance < -visibleSize.width / 6) {//若滑动距离小于-六分之一个屏幕（左滑），则选择切换到右一页
			nextPage();
		}
		else {//若滑动距离小于六分之一屏幕，则视本次滑动为取消滑动，利用动画回到滑动之前的页码
			rollBack();
		}
		};
	//添加触摸监听器到事件分发器内
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slideLayer);
}
//翻页与回滚
void HelpLayer::lastPage() {
	if (currentPage == 0) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//播放翻页音效
	currentPage--;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void HelpLayer::nextPage() {
	if (currentPage == totalPage-1) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//播放翻页音效
	currentPage++;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void HelpLayer::rollBack() {
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
/**************************************  MonsterLayer类  ************************************/
cocos2d::Layer* MonsterLayer::createLayer()
{
	return MonsterLayer::create();
}
//初始化
bool MonsterLayer::init()
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
void MonsterLayer::initBackGround() {
	//背景
	auto bg_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_monster.png"));
	bg_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.45));
	this->addChild(bg_image);

	//文字
	auto little_monster_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_14.PNG"));
	little_monster_txt->setPosition(Vec2(visibleSize.width * 0.2,visibleSize.height * 0.45));
	this->addChild(little_monster_txt);

	auto fly_monster_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_1.PNG"));
	fly_monster_txt->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.45));
	this->addChild(fly_monster_txt);

	auto boss_monster_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_2.PNG"));
	boss_monster_txt->setPosition(Vec2(visibleSize.width * 0.8,visibleSize.height * 0.45));
	this->addChild(boss_monster_txt);

	auto blood_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_3.PNG"));
	blood_1->setPosition(Vec2(visibleSize.width * 0.336,visibleSize.height * 0.285));
	this->addChild(blood_1);
	auto blood_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_3.PNG"));
	blood_2->setPosition(Vec2(visibleSize.width * 0.645,visibleSize.height * 0.285));
	this->addChild(blood_2);

	auto speed_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_29.PNG"));
	speed_1->setPosition(Vec2(visibleSize.width * 0.336,visibleSize.height * 0.355));
	this->addChild(speed_1);
	auto speed_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_29.PNG"));
	speed_2->setPosition(Vec2(visibleSize.width * 0.645,visibleSize.height * 0.355));
	this->addChild(speed_2);

	auto txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_39.PNG"));
	txt->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.2));
	this->addChild(txt);
}
/*************************************  TowerLayer类  ***********************************/
cocos2d::Layer* TowerLayer::createLayer()
{
	return TowerLayer::create();
}
//初始化
bool TowerLayer::init()
{
	if (!Layer::create()) {
		return false;
	}
	//获取屏幕大小
	visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < totalPage; i++) {
		pagesPoint[i] = -visibleSize.width * i;
		numImage[i] = "HelperScene/num_" + std::to_string(i + 1) + ".png";
	}
	currentPage = 0;

	initSlideLayer();
	initListener();
	return true;
}
//初始化滑动层
void TowerLayer::initSlideLayer()
{
	/**************************  滑动层  ********************************/
	//实现原理，将对应的几页内容全部按顺序横向渲染，通过移动当前层的位置来实现翻页效果
	slideLayer = Layer::create();
	slideLayer->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height * 0.9)));
	this->addChild(slideLayer);
	/**************************  第1页  ******************************/
	auto tower_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_1.png"));
	tower_1->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.5));
	slideLayer->addChild(tower_1);
	/**************************  第2页  ******************************/
	auto tower_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_2.png"));
	tower_2->setPosition(Vec2(visibleSize.width * 1.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_2);
	/**************************  第3页  ******************************/
	auto tower_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_3.png"));
	tower_3->setPosition(Vec2(visibleSize.width * 2.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_3);
	/**************************  第4页  ******************************/
	auto tower_4 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_4.png"));
	tower_4->setPosition(Vec2(visibleSize.width * 3.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_4);
	/**************************  第5页  ******************************/
	auto tower_5 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_5.png"));
	tower_5->setPosition(Vec2(visibleSize.width * 4.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_5);
	/**************************  第6页  ******************************/
	auto tower_6 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_6.png"));
	tower_6->setPosition(Vec2(visibleSize.width * 5.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_6);
	/**************************  第7页  ******************************/
	auto tower_7 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_7.png"));
	tower_7->setPosition(Vec2(visibleSize.width * 6.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_7);
	/**************************  第8页  ******************************/
	auto tower_8 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_8.png"));
	tower_8->setPosition(Vec2(visibleSize.width * 7.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_8);
	/**************************  第9页  ******************************/
	auto tower_9 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_9.png"));
	tower_9->setPosition(Vec2(visibleSize.width * 8.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_9);
	/**************************  第10页  ******************************/
	auto tower_10 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_10.png"));
	tower_10->setPosition(Vec2(visibleSize.width * 9.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_10);
	/***************************  页码  ******************************/
	auto page_num_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_0.PNG"));
	page_num_image->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.06));
	this->addChild(page_num_image);
	auto num_divide = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_-1.png"));
	num_divide->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.062));
	this->addChild(num_divide);
	num_divide->setScale(1.4);
	auto num_10 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_10.png"));
	num_10->setPosition(Vec2(visibleSize.width / 2 + num_10->getContentSize().width,
visibleSize.height * 0.062));
	this->addChild(num_10);
	num_10->setScale(1.4);
	pageNum = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/num_1.png"));
	pageNum->setScale(1.4);
	pageNum->setPosition(Vec2(visibleSize.width / 2 - pageNum->getContentSize().width * 3,visibleSize.height * 0.062));
	this->addChild(pageNum);
}
//初始化监听器
void TowerLayer::initListener() {
	/****************************  滑动实现  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (touch->getLocation().y < slideLayer->getContentSize().height) {
			return true;
		}
		return false;
		};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {//实现屏幕跟着滑动的效果
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		slideLayer->setPositionX(slideLayer->getPositionX() + distance);
		};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//获取本次触摸移动的横向距离
		if (distance > visibleSize.width / 6) {//如果滑动距离大于六分之一屏幕（向右滑），则选择切换到左一页
			lastPage();
		}
		else if (distance < -visibleSize.width / 6) {//若滑动距离小于-六分之一个屏幕（左滑），则选择切换到右一页
			nextPage();
		}
		else {//若滑动距离小于六分之一屏幕，则视本次滑动为取消滑动，利用动画回到滑动之前的页码
			rollBack();
		}
		};
	//添加触摸监听器到事件分发器内
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slideLayer);
}
//翻页与回滚
void TowerLayer::lastPage() {
	if (currentPage == 0) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//播放翻页音效
	currentPage--;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void TowerLayer::nextPage() {
	if (currentPage == totalPage - 1) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//播放翻页音效
	currentPage++;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void TowerLayer::rollBack() {
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}