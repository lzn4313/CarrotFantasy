#pragma once
#include "GameScene.h"
#include "Tower.h"
#include "LevelLayer.h"


class GameMap {
private:
	char game_map[7][12];//������ͼ����
	pos carrot_position;//��¼�ܲ�λ��
	Tower* tower_map[7][12];//�����������Ϣ������
	vector<LevelPath> levelPath;
public:
	void clear();
	void gameMapClear();
	void towerMapClear();
	void levelPathClaer() { levelPath.clear(); }

	const char getGameMap(int i,int j) { return game_map[i][j]; }
	void setGameMap(int i, int j, char k) { game_map[i][j] = k; };
	
    Tower* getTowerMap(int i,int j) { return tower_map[i][j]; }
	void setTowerMap(int i, int j, Tower* k) { tower_map[i][j] = k; }

	
	const vector<LevelPath>& getLevelPath() const { return levelPath; }
	void setLevelPath(const LevelPath& path) { levelPath.push_back(path); }
	
	pos getCarrotPosition() const { return carrot_position; }
	void setCarrotPosition(pos position) { carrot_position = position; }
};