#ifndef __Option_Controller_H__
#define __Option_Controller_H__
#include "cocos2d.h"
#include "Tower.h"
#include "OptionController.h"
#include "Facade.h"

class OptionController
{
private:

public:
	OptionController* optionController;
	OptionController* getInstance();
	pos getMouseTower();
};
#endif // __Option_Controller_H__

