#ifndef __Level_1_2_LAYER_H__
#define __Level_1_2_LAYER_H__

#include "cocos2d.h"
#include "Game/GameScene.h"

struct LevelPath {
    pos point;
    char direction;
};


class LevelLayer : public cocos2d::Layer
{
public:
    //¹¹Ôìº¯Êý
    static cocos2d::Layer* createLayer(int);
    virtual bool init(int);

    static LevelLayer* create(int level) {
        LevelLayer* pRet = new(std::nothrow) LevelLayer(); if (pRet && pRet->init(level)) {
            pRet->autorelease(); return pRet;
        }
        else {
            delete pRet; pRet = nullptr; return nullptr;
        }
    };
};
#endif // __Level_1_2_LAYER_H__
