#pragma once
#ifndef GAMEDATA_H
#define GAMEDATA_H

#include<string>
#include "cocos2d.h"
#include "Config/sound&music.h"
/*本游戏数据存储采用cocos自带的UserDefault进行存储，将会在保存地址生成对应的.xml文件，可以对数据进行获取和写入*/
class SaveManager {
private:
	static SaveManager* saveManager;
	SaveManager() {};
public:
	~SaveManager();
	static SaveManager* getInstance();
	void reset_data();
	void init_data();
};
#endif