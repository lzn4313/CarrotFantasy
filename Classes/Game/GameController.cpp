#include "Game/GameController.h"
USING_NS_CC;
using namespace cocos2d::ui;


GameController::GameController()
{
	resetGameController();
}
void GameController::resetGameController()
{
	if_speed_up = 0;
	if_pause = 0;
	all_clear = 0;
}
void GameController::continueGame()
{
    /*******************  菜单  **************************/
    auto options_menu = Menu::create();
    options_menu->setPosition(Vec2::ZERO);
    black_layer->addChild(options_menu);
    //继续游戏
    auto resume_btn = MenuItemImage::create("/GameScene/resume_normal.png", "/GameScene/resume_selected.png");
    resume_btn->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.3));
    resume_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        SoundManager::getInstance()->button_sound_effect();
        this->getParent()->removeChildByName("PlayingLevel");
        if (Facade::getInstance()->getLevelData()->getLevelSelection() == 1) {
            Facade::getInstance()->getLevelData()->setLevelSelection(Facade::getInstance()->getLevelData()->getLevelSelection() + 1);
            auto level_1_2 = LevelLayer::createLayer(Facade::getInstance()->getLevelData()->getLevelSelection());
            level_1_2->setName("PlayingLevel");
            this->getParent()->addChild(level_1_2, -3);
            this->getParent()->removeChildByName("EnemyCreate");
            auto enemycreate = EnemyCreate::create();
            enemycreate->setName("EnemyCreate");
            this->getParent()->addChild(enemycreate);
            static_cast<EnemyCreate*>(enemycreate)->SetLevel(Facade::getInstance()->getLevelData()->getLevelSelection());
            static_cast<EnemyCreate*>(enemycreate)->start();
            static_cast<GameScene*>(this->getParent())->reset_menu();
        }
        else if (Facade::getInstance()->getLevelData()->getLevelSelection() == 2) {
            log("To be continued");
            Director::getInstance()->replaceScene(GameSelectionScene::createScene());
        }
        });
    options_menu->addChild(resume_btn);
    //选择关卡
    auto return_btn = MenuItemImage::create("/GameScene/return_normal.png", "/GameScene/return_selected.png");
    return_btn->setPosition(Vec2(visibleSize.width * 0.35, visibleSize.height * 0.3));
    return_btn->setCallback([this, black_layer](Ref* psender) {//按钮回调事件，返回上一级
        SoundManager::getInstance()->button_sound_effect();
        Director::getInstance()->replaceScene(GameSelectionScene::createScene());
        });
    options_menu->addChild(return_btn);
}
void GameController::changeSpeedUp()
{
	if_speed_up = 1 - if_speed_up;
}
void GameController::changePause()
{
	if_pause = 1 - if_pause;
}
int GameController::getPause()
{
	return if_pause;
}
void GameController::setPause(int pause)
{
	if_pause = pause;
}
int GameController::getSpeedUp()
{
	return if_speed_up;
}
int GameController::getAllClear()
{
	return all_clear;
}
void GameController::setAllClear(int isclear)
{
	all_clear = isclear;
}
