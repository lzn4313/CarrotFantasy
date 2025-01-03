#pragma once
#ifndef GAMEDATA_H
#define GAMEDATA_H

#include<string>
#include "cocos2d.h"
#include "Config/sound&music.h"
/*����Ϸ���ݴ洢����cocos�Դ���UserDefault���д洢�������ڱ����ַ���ɶ�Ӧ��.xml�ļ������Զ����ݽ��л�ȡ��д��*/
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