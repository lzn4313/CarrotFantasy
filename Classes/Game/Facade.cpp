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
}

Facade::Facade()
{
	this->gameMenu = nullptr;
	shop = new Shop();
	gamecontroller = new GameController();
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
