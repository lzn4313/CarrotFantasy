#ifndef __Level_Data_H__
#define __Level_Data_H__

#include "cocos2d.h"

class LevelData
{
private:
    int carrot_hp;
    int game_waves;
    int level_selection;
    int max_waves;
    vector<Enemy*> monster;
    vector<Enemy*> barrier;
    int carrot_level;
    Enemy* destination;
    int tower_available[3];

public:
    // carrot_hp
    void setCarrotHp(int hp) {
        carrot_hp = hp;
    }

    int getCarrotHp() const {
        return carrot_hp;
    }

    // game_waves
    void setGameWaves(int waves) {
        game_waves = waves;
    }

    int getGameWaves() const {
        return game_waves;
    }

    // level_selection
    void setLevelSelection(int selection) {
        level_selection = selection;
    }

    // ���� tower_available ������ָ��λ�õ�ֵ
    void setTowerAvailable(int index, int value) {
        if (index >= 0 && index < 3) {
            tower_available[index] = value;
        }
    }

    // ��ȡ tower_available ������ָ��λ�õ�ֵ
    int getTowerAvailable(int index) const {
        if (index >= 0 && index < 3) {
            return tower_available[index];
        }
        return -1;  // ���� -1 ��Ϊ��Чֵ�����Ը�����Ҫ�޸ģ�
    }

    // �������� tower_available ����
    void setTowerAvailableArray(int array[3]) {
        for (int i = 0; i < 3; ++i) {
            tower_available[i] = array[i];
        }
    }

    // ��ȡ���� tower_available ���飨����һ���������ã�
    int* getTowerAvailableArray()  {
        return tower_available;
    }
    int getLevelSelection() const {
        return level_selection;
    }

    // max_waves
    void setMaxWaves(int waves) {
        max_waves = waves;
    }

    int getMaxWaves() const {
        return max_waves;
    }

    // monster (vector<Enemy*>)
    void setMonsters(const vector<Enemy*>& monsters) {
        monster = monsters;
    }

    const vector<Enemy*>& getMonsters() const {
        return monster;
    }

    // barrier (vector<Enemy*>)
    void setBarriers(const vector<Enemy*>& barriers) {
        barrier = barriers;
    }

    const vector<Enemy*>& getBarriers() const {
        return barrier;
    }

    // carrot_level
    void setCarrotLevel(int level) {
        carrot_level = level;
    }

    int getCarrotLevel() const {
        return carrot_level;
    }

    // destination (Enemy*)
    void setDestination(Enemy* dest) {
        destination = dest;
    }

    Enemy* getDestination() const {
        return destination;
    }

    void clear() {
        carrot_hp = 0;
        game_waves = 0;
        level_selection = 0;
        max_waves = 0;
        monster.clear();     // Clear the vector (delete all elements)
        barrier.clear();     // Clear the vector (delete all elements)
        carrot_level = 0;
        destination = nullptr; // Set the destination to nullptr
    }
};

#endif // __Level_Data_H__