#ifndef __Game_Controller_H__
#define __Game_Controller_H__
#include "cocos2d.h"

class GameController
{
private:
	int if_speed_up;//�Ƿ����
	int if_pause;//�Ƿ���ͣ
	int all_clear;//�����Ƿ��Ѿ����
public:
	GameController();//���ó�ʼ������
	void resetGameController();//��ʼ������
	void changeSpeedUp();//�ı��Ƿ����
	void changePause();//�ı��Ƿ���ͣ
	int getSpeedUp();//��ü��ٲ���
	int getPause();//���ͣ�ٲ���
	void setPause(int pause);//����ͣ�ٲ���
	int getAllClear();//��ȡ�����Ƿ��Ѿ����
	void setAllClear(int isclear);//���ù����Ƿ����
	void continueGame();
};
#endif // __Game_Controller_H__