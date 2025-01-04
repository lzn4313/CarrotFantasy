#include "gameMap.h"

void GameMap::gameMapClear()
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 0; j++)
			game_map[i][j] = 0;
	}
}
void GameMap::towerMapClear()
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 12; j++) {
			tower_map[i][j] = nullptr;
		}
	}
}
void GameMap::clear() {
	towerMapClear();
	gameMapClear();
	levelPathClaer();
}
