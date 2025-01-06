#include "Config/sound&music.h"
USING_NS_CC;

SoundManager* SoundManager::soundManager = nullptr;
SoundManager::~SoundManager() {
	if (soundManager != nullptr) {
		delete soundManager;
	}
}
SoundManager* SoundManager::getInstance() {
	if (!soundManager) {
		soundManager = new SoundManager();
	}
	return soundManager;
}

//��ʼ���������ݣ�����������+��Ч��Ϊ��
void SoundManager::init_sound() {
	UserDefault::getInstance()->setIntegerForKey("sound_effect", 1);
	UserDefault::getInstance()->setIntegerForKey("bg_music", 1);
}
//���Ű�ť��Ч
void SoundManager::button_sound_effect() {
	//����Ч�򿪣��򲥷Ű�ť��Ч
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		AudioEngine::play2d("sound/button.mp3", false, 0.5f);
	}
}
//���ŷ�ҳ��Ч
void SoundManager::page_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷ŷ�ҳ��Ч
		AudioEngine::play2d("sound/page.mp3", false, 0.2f);
	}
}
//���Ž�����Ч
void SoundManager::build_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷Ž�����Ч
		AudioEngine::play2d("sound/build_tower.mp3", false, 1.0f);
	}
}
//���ų�����Ч
void SoundManager::sell_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷ų�����Ч
		AudioEngine::play2d("sound/sell_tower.mp3", false, 1.0f);
	}
}
//����������Ч
void SoundManager::uplevel_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷�������Ч
		AudioEngine::play2d("sound/uplevel_tower.mp3", false, 1.0f);
	}
}
//�������ǹ�����Ч
void SoundManager::star_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷����ǹ�����Ч
		AudioEngine::play2d("sound/star_atk.mp3", false, 1.0f);
	}
}
//����ƿ�ӹ�����Ч
void SoundManager::bottle_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷�ƿ�ӹ�����Ч
		AudioEngine::play2d("sound/bottle_atk.mp3", false, 1.0f);
	}
}
//���ŷ��ȹ�����Ч
void SoundManager::fan_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷ŷ��ȹ�����Ч
		AudioEngine::play2d("sound/fan_atk.mp3", false, 1.0f);
	}
}
//���Ŵ�㹥����Ч
void SoundManager::shit_atk_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷Ŵ�㹥����Ч
		AudioEngine::play2d("sound/shit_atk.mp3", false, 1.0f);
	}
}
//�����ܲ�������Ч
void SoundManager::carrot_eaten_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷��ܲ�������Ч
		AudioEngine::play2d("sound/carrot_eaten.mp3", false, 1.0f);
	}
}
//������ͨ��������Ч
void SoundManager::normal_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷���ͨ��������Ч
		AudioEngine::play2d("sound/Land112.mp3", false, 1.0f);
	}
}
//���ŷ��й�������Ч
void SoundManager::fly_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷ŷ��й�������Ч
		AudioEngine::play2d("sound/Fly162.mp3", false, 1.0f);
	}
}
//����boss������Ч
void SoundManager::boss_dead_sound_effect() {
	if (UserDefault::getInstance()->getIntegerForKey("sound_effect") == 1) {
		//����Ч�򿪣��򲥷�boss������Ч
		AudioEngine::play2d("sound/Fat141.mp3", false, 1.0f);
	}
}
