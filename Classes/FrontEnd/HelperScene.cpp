#include "FrontEnd/MenuScene.h"
#include "FrontEnd/HelperScene.h"
#include"Config/sound&music.h"
USING_NS_CC;
/*****************************  HelperScene��  ***********************************************************/
cocos2d::Scene* HelperScene::createScene()
{
	return HelperScene::create();
}
//��ʼ��
bool HelperScene::init()
{
	if (!Scene::init()) {
		return false;
	}
	//��ȡ��Ļλ��
	visibleSize = Director::getInstance()->getVisibleSize();

	initBackGround();
	initMenu();
	initLayers();
	currentState = new HelpState();
	currentState->enter(this);

	return true;
}
//�������˵�
void HelperScene::goto_home(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//������Ч
	Scene* menu_scene = MenuScene::createScene();//�����˵�����
	Director::getInstance()->replaceScene(TransitionSlideInT::create(0.3, menu_scene));//�Դ������»�����ʽ�л�
}
//ȥ����ѡ��ҳ
void HelperScene::goto_help(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//������Ч
	currentState->exit(this);
	currentState = new HelpState();
	currentState->enter(this);
}
//ȥmonsterѡ��ҳ
void HelperScene::goto_monster(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//������Ч
	currentState->exit(this);
	currentState = new MonsterState();
	currentState->enter(this);
}
//ȥtowerѡ��ҳ
void HelperScene::goto_tower(Ref* psender)
{
	SoundManager::getInstance()->button_sound_effect();//������Ч
	currentState->exit(this);
	currentState = new TowerState();
	currentState->enter(this);
}
//��ʼ������
void HelperScene::initBackGround() {
	auto background_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_bg.png"));
	background_image->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background_image);
}
//��ʼ���˵�
void HelperScene::initMenu() {
	/**************************************************  �˵�  *****************************************************/
	auto menu_all = Menu::create();
	menu_all->setPosition(Vec2::ZERO);
	//�������˵��İ�ť����MenuItemImage��ʽʵ�֣�
	auto home = MenuItemImage::create("HelperScene/help_1-hd_67.PNG", "HelperScene/help_1-hd_38.PNG", CC_CALLBACK_1(HelperScene::goto_home, this));
	home->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.92));
	menu_all->addChild(home);
	this->addChild(menu_all);
	/***********************************************ѡ�****************************************************/
	//help��ť
	help_btn = MenuItemImage::create("HelperScene/help_1-hd-33_normal.PNG", "HelperScene/help_1-hd-33_normal.PNG", "HelperScene/help_1-hd_33.PNG",CC_CALLBACK_1(HelperScene::goto_help,this));
	help_btn->setPosition(Vec2(visibleSize.width * 0.31,visibleSize.height * 0.925));
	help_btn->setScale(1.4);
	menu_all->addChild(help_btn);
	//monster��ť
	monster_btn = MenuItemImage::create("HelperScene/help_1-hd_71_normal.PNG", "HelperScene/help_1-hd_71_normal.PNG", "HelperScene/help_1-hd_71.png",CC_CALLBACK_1(HelperScene::goto_monster, this));
	monster_btn->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.922));
	monster_btn->setScale(1.4);
	menu_all->addChild(monster_btn);
	//tower��ť
	tower_btn = MenuItemImage::create("HelperScene/help_1-hd_66_normal.PNG", "HelperScene/help_1-hd_66_normal.PNG", "HelperScene/help_1-hd_66.PNG", CC_CALLBACK_1(HelperScene::goto_tower, this));
	tower_btn->setPosition(Vec2(visibleSize.width * 0.69,visibleSize.height * 0.923));
	tower_btn->setScale(1.4);
	menu_all->addChild(tower_btn);
}
//��ʼ����
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
/*************************************** HelpLayer��  ******************************************/
cocos2d::Layer* HelpLayer::createLayer()
{
	return HelpLayer::create();
}
//��ʼ��
bool HelpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//��ȡ��Ļ��С
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
//��ʼ��������
void HelpLayer::initSlideLayer() {
	/**************************  ������  ********************************/
	//ʵ��ԭ������Ӧ�ļ�ҳ����ȫ����˳�������Ⱦ��ͨ���ƶ���ǰ���λ����ʵ�ַ�ҳЧ��
	slideLayer = Layer::create();
	slideLayer->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height * 0.9)));
	this->addChild(slideLayer);
	/**************************  ��һҳ  ******************************/
	auto help_1_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_1.png"));
	help_1_image->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.55));
	slideLayer->addChild(help_1_image);
	auto help_1_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_73.PNG"));
	help_1_txt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.22));
	slideLayer->addChild(help_1_txt);
	/**************************  �ڶ�ҳ  ******************************/
	auto help_2_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_2.png"));
	help_2_image->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_2_image);
	auto help_2_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_4.PNG"));
	help_2_txt->setPosition(Vec2(visibleSize.width * 1.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_2_txt);
	/**************************  ����ҳ  ******************************/
	auto help_3_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_3.png"));
	help_3_image->setPosition(Vec2(visibleSize.width * 2.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_3_image);
	auto help_3_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_50.PNG"));
	help_3_txt->setPosition(Vec2(visibleSize.width * 2.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_3_txt);
	/**************************  ����ҳ  ******************************/
	auto help_4_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_4.png"));
	help_4_image->setPosition(Vec2(visibleSize.width * 3.5, visibleSize.height * 0.55));
	slideLayer->addChild(help_4_image);
	auto help_4_txt = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_1-hd_65.PNG"));
	help_4_txt->setPosition(Vec2(visibleSize.width * 3.5, visibleSize.height * 0.22));
	slideLayer->addChild(help_4_txt);

	/***************************  ҳ��  ******************************/
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
//��ʼ��������
void HelpLayer::initListener() {
	/****************************  ����ʵ��  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (touch->getLocation().y < slideLayer->getContentSize().height) {
			return true;
		}
		return false;
		};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {//ʵ����Ļ���Ż�����Ч��
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		slideLayer->setPositionX(slideLayer->getPositionX() + distance);
		};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//��ȡ���δ����ƶ��ĺ������
		if (distance > visibleSize.width / 6) {//������������������֮һ��Ļ�����һ�������ѡ���л�����һҳ
			lastPage();
		}
		else if (distance < -visibleSize.width / 6) {//����������С��-����֮һ����Ļ���󻬣�����ѡ���л�����һҳ
			nextPage();
		}
		else {//����������С������֮һ��Ļ�����ӱ��λ���Ϊȡ�����������ö����ص�����֮ǰ��ҳ��
			rollBack();
		}
		};
	//��Ӵ������������¼��ַ�����
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slideLayer);
}
//��ҳ��ع�
void HelpLayer::lastPage() {
	if (currentPage == 0) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//���ŷ�ҳ��Ч
	currentPage--;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void HelpLayer::nextPage() {
	if (currentPage == totalPage-1) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//���ŷ�ҳ��Ч
	currentPage++;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void HelpLayer::rollBack() {
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
/**************************************  MonsterLayer��  ************************************/
cocos2d::Layer* MonsterLayer::createLayer()
{
	return MonsterLayer::create();
}
//��ʼ��
bool MonsterLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	//��ȡ��Ļ��С
	visibleSize = Director::getInstance()->getVisibleSize();
	initBackGround();

	return true;
}
//��ʼ������
void MonsterLayer::initBackGround() {
	//����
	auto bg_image = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/help_3-hd_monster.png"));
	bg_image->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.45));
	this->addChild(bg_image);

	//����
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
/*************************************  TowerLayer��  ***********************************/
cocos2d::Layer* TowerLayer::createLayer()
{
	return TowerLayer::create();
}
//��ʼ��
bool TowerLayer::init()
{
	if (!Layer::create()) {
		return false;
	}
	//��ȡ��Ļ��С
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
//��ʼ��������
void TowerLayer::initSlideLayer()
{
	/**************************  ������  ********************************/
	//ʵ��ԭ������Ӧ�ļ�ҳ����ȫ����˳�������Ⱦ��ͨ���ƶ���ǰ���λ����ʵ�ַ�ҳЧ��
	slideLayer = Layer::create();
	slideLayer->setContentSize(Size(Vec2(visibleSize.width, visibleSize.height * 0.9)));
	this->addChild(slideLayer);
	/**************************  ��1ҳ  ******************************/
	auto tower_1 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_1.png"));
	tower_1->setPosition(Vec2(visibleSize.width / 2,visibleSize.height * 0.5));
	slideLayer->addChild(tower_1);
	/**************************  ��2ҳ  ******************************/
	auto tower_2 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_2.png"));
	tower_2->setPosition(Vec2(visibleSize.width * 1.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_2);
	/**************************  ��3ҳ  ******************************/
	auto tower_3 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_3.png"));
	tower_3->setPosition(Vec2(visibleSize.width * 2.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_3);
	/**************************  ��4ҳ  ******************************/
	auto tower_4 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_4.png"));
	tower_4->setPosition(Vec2(visibleSize.width * 3.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_4);
	/**************************  ��5ҳ  ******************************/
	auto tower_5 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_5.png"));
	tower_5->setPosition(Vec2(visibleSize.width * 4.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_5);
	/**************************  ��6ҳ  ******************************/
	auto tower_6 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_6.png"));
	tower_6->setPosition(Vec2(visibleSize.width * 5.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_6);
	/**************************  ��7ҳ  ******************************/
	auto tower_7 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_7.png"));
	tower_7->setPosition(Vec2(visibleSize.width * 6.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_7);
	/**************************  ��8ҳ  ******************************/
	auto tower_8 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_8.png"));
	tower_8->setPosition(Vec2(visibleSize.width * 7.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_8);
	/**************************  ��9ҳ  ******************************/
	auto tower_9 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_9.png"));
	tower_9->setPosition(Vec2(visibleSize.width * 8.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_9);
	/**************************  ��10ҳ  ******************************/
	auto tower_10 = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("HelperScene/tower_10.png"));
	tower_10->setPosition(Vec2(visibleSize.width * 9.5,visibleSize.height * 0.5));
	slideLayer->addChild(tower_10);
	/***************************  ҳ��  ******************************/
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
//��ʼ��������
void TowerLayer::initListener() {
	/****************************  ����ʵ��  *****************************/
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [this](Touch* touch, Event* event) {
		if (touch->getLocation().y < slideLayer->getContentSize().height) {
			return true;
		}
		return false;
		};
	listener->onTouchMoved = [this](Touch* touch, Event* event) {//ʵ����Ļ���Ż�����Ч��
		float distance = touch->getLocation().x - touch->getPreviousLocation().x;
		slideLayer->setPositionX(slideLayer->getPositionX() + distance);
		};
	listener->onTouchEnded = [this](Touch* touch, Event* event) {
		float distance = touch->getLocation().x - touch->getStartLocation().x;//��ȡ���δ����ƶ��ĺ������
		if (distance > visibleSize.width / 6) {//������������������֮һ��Ļ�����һ�������ѡ���л�����һҳ
			lastPage();
		}
		else if (distance < -visibleSize.width / 6) {//����������С��-����֮һ����Ļ���󻬣�����ѡ���л�����һҳ
			nextPage();
		}
		else {//����������С������֮һ��Ļ�����ӱ��λ���Ϊȡ�����������ö����ص�����֮ǰ��ҳ��
			rollBack();
		}
		};
	//��Ӵ������������¼��ַ�����
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, slideLayer);
}
//��ҳ��ع�
void TowerLayer::lastPage() {
	if (currentPage == 0) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//���ŷ�ҳ��Ч
	currentPage--;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void TowerLayer::nextPage() {
	if (currentPage == totalPage - 1) {
		rollBack();
		return;
	}
	SoundManager::getInstance()->page_sound_effect();//���ŷ�ҳ��Ч
	currentPage++;
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}
void TowerLayer::rollBack() {
	slideLayer->runAction(MoveTo::create(0.1, Vec2(pagesPoint[currentPage], 0)));
	pageNum->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(numImage[currentPage]));
}