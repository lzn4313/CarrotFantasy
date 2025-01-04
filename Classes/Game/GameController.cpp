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
