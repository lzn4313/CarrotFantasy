#include "OptionController.h"

OptionController* OptionController::getInstance()
{
	if (optionController == nullptr) {
		optionController = new OptionController();
		return optionController;
	}
	else {
		return optionController;
	}
}
pos OptionController::getMouseTower()
{
	return Mouse.position;
}