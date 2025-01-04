#include"Game/LevelLayer.h"
#include"Config/sound&music.h"
#include"Config/GameData.h"
#include"Game/GameScene.h"
#include"Game/enemy.h"
#include<algorithm>

USING_NS_CC;
using namespace std;
extern int if_speed_up;//�Ƿ����
extern int if_pause;//�Ƿ���ͣ
extern int game_money;//��Ǯ
extern int game_waves;//��ǰ����
extern int max_waves;//�ܲ���
extern char game_map[7][12];//������ͼ����
extern int tower_available[3];//�ɽ���������洢vector
extern pos carrot_position;
extern vector<LevelPath> levelPath;//��cocos�Դ�
extern vector<Enemy*> barrier;
extern vector<Enemy*> monster;

/*******************************  ������  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************************  Level_1_2  ***********************************/
Layer* LevelLayer::createLayer(int level)
{
    return LevelLayer::create(level);
}
//��ʼ��
bool LevelLayer::init(int level)
{
    if (!Layer::init()) {
        return false;
    }
    //��ȡ��Ļ��С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  ����ȫ�ֱ�����ʼ��  *******************/
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            game_map[i][j] = 0;
        }
    }
    //���½�Ǯ��ʾ
    game_money = 450;
    //���²�����ʾ
    game_waves = 0;
    max_waves = 15;
    string path;
    path = format("/Level/LevelMap_{}.txt", level);
    path = FileUtils::getInstance()->fullPathForFilename(path);
    auto file=fopen(path.c_str(), "r");
    fscanf(file, "%d%d%d", &tower_available[0], &tower_available[1], &tower_available[2]);
    /***********************  ����  ************************/
    string picture = format("/Level/Level_1_{}_bg.png", level);
    auto bg_image = Sprite::create(picture);
    if (bg_image == nullptr) {
        problemLoading(picture.c_str());
    }
    bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 + 5));
    this->addChild(bg_image);
    //���ֵ�
    auto start_point = Sprite::create("/Level/startPoint.PNG");
    if (start_point == nullptr) {
        problemLoading("'startPoint.PNG'");
    }
    int a = 0, b = 0;
    fscanf(file, "%d %d", &a, &b);
    pos start_position = { a,b };
    vec2 vec = trans_ij_to_xy(start_position);
    start_point->setPosition(Vec2(vec.x, vec.y));
    this->addChild(start_point);
    //��¼·��
    levelPath.clear();
    LevelPath temp;
    char c;
    int i = 0;
    fscanf(file, "%d", &i);
    for (int j = 0; j < i; j++) {
        fscanf(file, "%d %d %c", &a, &b, &c);
        temp = { {a,b},c };
        levelPath.push_back(temp);
        if (c != 'o') {
            game_map[a][b] = 1;
        }
        else {
            game_map[a][b] = 5;
            carrot_position = { a,b };
        }
    }

    return true;
}




