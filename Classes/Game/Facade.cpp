#include "Facade.h"

using namespace cocos2d;
using namespace std;
Facade* Facade::facade = nullptr;

Facade* Facade::getInstance()
{
	if (facade == nullptr) {
		facade=  new Facade();
		return facade;
	}
	else {
		return facade;
	}
}
void Facade::startGame()
{
	gameScene->reset_menu();
	gamecontroller->setPause(1);
	gameMenu->start();
	shop->setGameMoney(450);
}
void Facade::pause()
{
	gamecontroller->changePause();
}
void Facade::speedUp()
{
	gamecontroller->changeSpeedUp();
}
void Facade::win()
{
	gamecontroller->setPause(1);
	/*******************************  数据更新  *****************************/
	UserDefault::getInstance()->setIntegerForKey("money_statistics", UserDefault::getInstance()->getIntegerForKey("money_statistics") + shop->getTotalMoney());
	UserDefault::getInstance()->setIntegerForKey("monster_statistics", UserDefault::getInstance()->getIntegerForKey("monster_statistics") + totalData->getTotalMonster());
	UserDefault::getInstance()->setIntegerForKey("boss_statistics", UserDefault::getInstance()->getIntegerForKey("boss_statistics") + totalData->getTotalBoss());
	UserDefault::getInstance()->setIntegerForKey("damage_statistics", UserDefault::getInstance()->getIntegerForKey("damage_statistics") +totalData->getTotalBarrier());
	/************************  获胜  ******************************/
	UserDefault::getInstance()->setIntegerForKey("adventure_statistics", levelData->getLevelSelection() + 1);
	UserDefault::getInstance()->setIntegerForKey("level_1", levelData->getLevelSelection() + 1);
	gamecontroller->continueGame();
}
void Facade::lose()
{
	gamecontroller->setPause(1);
	/*******************************  数据更新  *****************************/
	UserDefault::getInstance()->setIntegerForKey("money_statistics", UserDefault::getInstance()->getIntegerForKey("money_statistics") + shop->getTotalMoney());
	UserDefault::getInstance()->setIntegerForKey("monster_statistics", UserDefault::getInstance()->getIntegerForKey("monster_statistics") + totalData->getTotalMonster());
	UserDefault::getInstance()->setIntegerForKey("boss_statistics", UserDefault::getInstance()->getIntegerForKey("boss_statistics") + totalData->getTotalBoss());
	UserDefault::getInstance()->setIntegerForKey("damage_statistics", UserDefault::getInstance()->getIntegerForKey("damage_statistics") + totalData->getTotalBarrier());
	gamecontroller->continueGame();
}
void Facade::buyTower(int tag,int money)
{
	shop->getNewTower(tag,money);
	gameMenu->build(OptionController->getInstance()->getMouseTower(), tag, shop->getNewTower(tag, money));
}
void Facade::sellTower(Tower * tower)
{
	shop->sellTower(tower);
}
void Facade::clear()
{
	this->gameMenu = nullptr;
	gameMap->clear();
	shop = nullptr;
	gamecontroller = nullptr;
	totalData = nullptr;
	levelData = nullptr;
}

Facade::Facade()
{
	this->gameMenu = nullptr;
	shop = new Shop();
	gamecontroller = new GameController();
	totalData = new TotalData();
}

Shop* Facade::getShop()
{
	return shop;
}

GameController* Facade::getGameController()
{
	return gamecontroller;
}

Layer* Facade::getGameMenu(int level)
{
	if(gameMenu ==nullptr)
		gameMenu = GameMenu::createLayer();
	return gameMenu;
}
TotalData* Facade::getTotalData()
{
	return totalData;
}
LevelData* Facade::getLevelData()
{
	return levelData;
}
