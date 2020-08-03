#ifndef __STRUCTURE_SCENE_H__
#define __STRUCTURE_SCENE_H__

#include "cocos2d.h"

#define MAX_COUNT 100

class Structure : public cocos2d::Layer
{
    cocos2d::__Array* list;
public:
    
    ~Structure();//析构函数
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Structure);
};

#endif // __STRUCTURE_SCENE_H__
