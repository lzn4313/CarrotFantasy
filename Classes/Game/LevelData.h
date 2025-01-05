#ifndef __Level_Data_H__
#define __Level_Data_H__

#include "cocos2d.h"
#include "enemy.h"

class LevelData
{
private:
    int carrot_hp;
    int game_waves;
    int level_selection;
    int max_waves;
    int carrot_level;
    Enemy* destination;
    int tower_available[3];

public:
    // carrot_hp
    void setCarrotHp(int hp) {carrot_hp = hp;}
    int getCarrotHp() const {return carrot_hp;}
    // game_waves
    void setGameWaves(int waves) {game_waves = waves;}
    int getGameWaves() const {return game_waves;}
    // level_selection
    void setLevelSelection(int selection) {level_selection = selection;}
    // 获取整个 tower_available 数组（返回一个常量引用）
    int* getTowerAvailableArray() { return tower_available; }
    int getLevelSelection() const { return level_selection; }
    // max_waves
    void setMaxWaves(int waves) { max_waves = waves; }
    int getMaxWaves() const { return max_waves; }
    // carrot_level
    void setCarrotLevel(int level) { carrot_level = level; }
    int getCarrotLevel() const { return carrot_level; }
    // destination (Enemy*)
    void setDestination(Enemy* dest) { destination = dest; }
    Enemy* getDestination() const { return destination; }

    // 设置 tower_available 数组中指定位置的值
    void setTowerAvailable(int index, int value) {
        if (index >= 0 && index < 3) {
            tower_available[index] = value;
        }
    }
    // 获取 tower_available 数组中指定位置的值
    int getTowerAvailable(int index) const {
        if (index >= 0 && index < 3) {
            return tower_available[index];
        }
        return -1;  // 返回 -1 作为无效值（可以根据需要修改）
    }
    // 设置整个 tower_available 数组
    void setTowerAvailableArray(int array[3]) {
        for (int i = 0; i < 3; ++i) {
            tower_available[i] = array[i];
        }
    }

    void clear();
};

#endif // __Level_Data_H__