#ifndef __Game_Controller_H__
#define __Game_Controller_H__
#include "cocos2d.h"

class GameController
{
private:
	int if_speed_up;//是否加速
	int if_pause;//是否暂停
	int all_clear;//怪物是否已经清空
public:
	GameController();//调用初始化数据
	void resetGameController();//初始化数据
	void changeSpeedUp();//改变是否加速
	void changePause();//改变是否暂停
	int getSpeedUp();//获得加速参数
	int getPause();//获得停顿参数
	void setPause(int pause);//设置停顿参数
	int getAllClear();//获取怪物是否已经清空
	void setAllClear(int isclear);//设置怪物是否清空
	void continueGame();
};
#endif // __Game_Controller_H__