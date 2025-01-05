#include"Game/LevelLayer.h"
#include"Config/sound&music.h"
#include"Config/GameData.h"
#include"Game/GameScene.h"
#include"Game/enemy.h"
#include<algorithm>
#include<format>
#include<string>
#include "Facade.h"

USING_NS_CC;
using namespace std;

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
            Facade::getInstance()->getGameMap()->setGameMap(i,j,0);
        }
    }
    //更新金钱显示
    Facade::getInstance()->getShop()->setGameMoney(450);
    //更新波数显示
    Facade::getInstance()->getLevelData()->setGameWaves(0);
    Facade::getInstance()->getLevelData()->setMaxWaves(15);
    string path;
    path = format("/Level/LevelMap_{}.txt", level);
    path = FileUtils::getInstance()->fullPathForFilename(path);
    auto file=fopen(path.c_str(), "r");
    fscanf(file, "%d%d%d", &Facade::getInstance()->getLevelData()->getTowerAvailableArray()[0], &Facade::getInstance()->getLevelData()->getTowerAvailableArray()[1], &Facade::getInstance()->getLevelData()->getTowerAvailableArray()[2]);
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
    Facade::getInstance()->getGameMap()->levelPathClaer();
    LevelPath temp;
    char c;
    int i = 0;
    fscanf(file, "%d", &i);
    for (int j = 0; j < i; j++) {
        fscanf(file, "%d %d %c", &a, &b, &c);
        temp = { {a,b},c };
        Facade::getInstance()->getGameMap()->setLevelPath(temp);
        if (c != 'o') {
            Facade::getInstance()->getGameMap()->setGameMap(a,b,1);
        }
        else {
            Facade::getInstance()->getGameMap()->setGameMap(a,b,5);
            Facade::getInstance()->getGameMap()->setCarrotPosition({a,b});
        }
    }

    return true;
}




