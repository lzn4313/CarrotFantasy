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
<<<<<<< Updated upstream
	this->gameMenu = nullptr;
	gameMap->clear();
=======
	gameMenu = nullptr;
	shop = nullptr;
	gamecontroller = nullptr;
	totalData = nullptr;
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
Layer* Facade::getGameMenu(int level)
{
	if(gameMenu ==nullptr)
		gameMenu = GameMenu::createLayer();
	return gameMenu;
}
=======
TotalData* Facade::getTotalData()
{
	return totalData;
}
>>>>>>> Stashed changes
