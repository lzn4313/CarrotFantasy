#include "FrontEnd/LoadingScene.h"
#include "FrontEnd/MenuScene.h"
#include "AudioEngine.h"
#include "Config/GameData.h"
USING_NS_CC;


Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}


bool LoadingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    numberOfLoadedRes = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("LoadingScene/LoadBG.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);
    // ��ʱ���£����ڼ����Դ�Ƿ񱻼�����ɣ����������ɲ����뵽����Ļ�ӭҳ�档
    schedule(CC_SCHEDULE_SELECTOR(LoadingScene::logic), 1.0f);
    return true;
}
// �ô��봦�������Դ�Ĳ�����
// ������Դ����ͼƬ�������ȡ�
void LoadingScene::loadSource() {
    //���ô浵��ַ���浵�������ת��GameData.h��
    FileUtils::getInstance()->setWritablePath(FileUtils::getInstance()->getDefaultResourceRootPath()+"../");
    //��ʼ���浵����
    init_data();

    auto spriteFrameCache = SpriteFrameCache::getInstance();
    //����˵���������ͼƬ
    cacheImage("MenuScene/MainBG.PNG");
    cacheImage("MenuScene/Cloud.PNG");
    cacheImage("MenuScene/Cloud2.PNG");
    cacheImage("MenuScene/FlyMonster.PNG");
    cacheImage("MenuScene/Leaf1.PNG");
    cacheImage("MenuScene/Leaf2.PNG");
    cacheImage("MenuScene/Leaf3.PNG");
    cacheImage("MenuScene/CarrotBody.PNG");
    cacheImage("MenuScene/MainTitle.PNG");
    cacheImage("MenuScene/Btn_Set.PNG");
    cacheImage("MenuScene/Btn_SetLight.PNG");
    cacheImage("MenuScene/Btn_Help.PNG");
    cacheImage("MenuScene/Btn_HelpLight.PNG");
    cacheImage("MenuScene/Btn_NormalModle.PNG");
    cacheImage("MenuScene/Btn_NormalModleLight.PNG");
    cacheImage("MenuScene/Btn_Boss.PNG");
    cacheImage("MenuScene/Btn_BossLight.PNG");
    cacheImage("MenuScene/lock.png");
    cacheImage("MenuScene/Btn_MonsterNest.PNG");
    cacheImage("MenuScene/Btn_MonsterNestLight.PNG");
    numberOfLoadedRes = 1;
}
void LoadingScene::logic(float dt)
{
    // �����Ը�����������ͨ������numberOfLoadedRes��ֵ����ʾ���ؽ��ȡ�
    if (0 == numberOfLoadedRes) {
        loadSource();
    }
    else if (1 == numberOfLoadedRes) {
        // ������ת������
        Director::getInstance()->replaceScene(MenuScene::createScene());
        //����������ֿ����򲥷ű�������
        if (UserDefault::getInstance()->getIntegerForKey("bg_music") == 1) {
            AudioEngine::play2d("/sound/CarrotFantasy.mp3", true, 0.5f);
        }
    }
}

//����ͼƬ�����Ҳ���ͼƬ�׳��쳣
void LoadingScene::cacheImage(const std::string& filepath) {
    auto image = Director::getInstance()->getTextureCache()->addImage(filepath);
    std::string msg = "################################################################## problem while loading image " + filepath + "####################################################################";
    CCASSERT(image != nullptr, msg.c_str());
}