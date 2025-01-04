#include"Game/LevelLayer.h"
#include"Config/sound&music.h"
#include"Config/GameData.h"
#include"Game/GameScene.h"
#include"Game/enemy.h"
#include<algorithm>

USING_NS_CC;
using namespace std;
extern int if_speed_up;//是否加速
extern int if_pause;//是否暂停
extern int game_money;//金钱
extern int game_waves;//当前波数
extern int max_waves;//总波数
extern char game_map[7][12];//辅助地图数组
extern int tower_available[3];//可建造防御塔存储vector
extern pos carrot_position;
extern vector<LevelPath> levelPath;//非cocos自带
extern vector<Enemy*> barrier;
extern vector<Enemy*> monster;

/*******************************  错误处理  ************************************/
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}
/**********************************  Level_1_2  ***********************************/
Layer* LevelLayer::createLayer(int level)
{
    return LevelLayer::create(level);
}
//初始化
bool LevelLayer::init(int level)
{
    if (!Layer::init()) {
        return false;
    }
    //获取屏幕大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /***********************  部分全局变量初始化  *******************/
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 12; j++) {
            game_map[i][j] = 0;
        }
    }
    //更新金钱显示
    game_money = 450;
    //更新波数显示
    game_waves = 0;
    max_waves = 15;
    string path;
    path = format("/Level/LevelMap_{}.txt", level);
    path = FileUtils::getInstance()->fullPathForFilename(path);
    auto file=fopen(path.c_str(), "r");
    fscanf(file, "%d%d%d", &tower_available[0], &tower_available[1], &tower_available[2]);
    /***********************  背景  ************************/
    string picture = format("/Level/Level_1_{}_bg.png", level);
    auto bg_image = Sprite::create(picture);
    if (bg_image == nullptr) {
        problemLoading(picture.c_str());
    }
    bg_image->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 + 5));
    this->addChild(bg_image);
    //出怪点
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
    //记录路径
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




