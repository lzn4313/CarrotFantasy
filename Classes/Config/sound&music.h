#pragma once
#ifndef SOUND_H
#define SOUND_H
#include"AudioEngine.h"
#include"CCUserDefault.h"
class SoundManager {
private:
	static SoundManager* soundManager;
	SoundManager() {}
public:
	~SoundManager();
	static SoundManager* getInstance();
	void init_sound();
	void button_sound_effect();
	void page_sound_effect();
	void build_sound_effect();
	void sell_sound_effect();
	void uplevel_sound_effect();
	void star_atk_sound_effect();
	void bottle_atk_sound_effect();
	void fan_atk_sound_effect();
	void shit_atk_sound_effect();
	void carrot_eaten_sound_effect();
	void normal_dead_sound_effect();
	void fly_dead_sound_effect();
	void boss_dead_sound_effect();
};
#endif