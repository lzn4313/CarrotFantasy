#include"Config/GameData.h"
#include"CCUserDefault.h"

USING_NS_CC;
SaveManager* SaveManager::saveManager = nullptr;
SaveManager::~SaveManager() {
	if (saveManager != nullptr) {
		delete saveManager;
	}
}
SaveManager* SaveManager::getInstance() {
	if (!saveManager) {
		saveManager = new SaveManager();
	}
	return saveManager;
}
//重置数据
void SaveManager::reset_data() {
	UserDefault::getInstance()->setBoolForKey("have_init", true);
	UserDefault::getInstance()->setIntegerForKey("adventure_statistics", 1);
	UserDefault::getInstance()->setIntegerForKey("hide_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("bosspattern_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("money_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("monster_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("boss_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("damage_statistics", 0);
	UserDefault::getInstance()->setIntegerForKey("level_1", 1);
	UserDefault::getInstance()->setIntegerForKey("level_2", 0);
	UserDefault::getInstance()->setIntegerForKey("level_3", 0);
	UserDefault::getInstance()->setIntegerForKey("if_boss_lock", 1);
	UserDefault::getInstance()->setIntegerForKey("if_nest_lock", 1);
}
//初始化存档数据
void SaveManager::init_data() {
	if (!UserDefault::getInstance()->getBoolForKey("have_init", false)) {
		//如果无存档，则重置存档数据，初始化声音数据；若有存档则不进行操作
		reset_data();
		SoundManager::getInstance()->init_sound();
	}
}
