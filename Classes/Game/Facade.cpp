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
