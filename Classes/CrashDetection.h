
#ifndef __CRASHDETECTION_SCENE_H__
#define __CRASHDETECTION_SCENE_H__

#include "cocos2d.h"

class CrashDetection : public cocos2d::Layer
{
public:
    int a = 0;
    void onEnter();
    void onExit();
    cocos2d::Sprite* ball;
    cocos2d::PhysicsWorld* m_world;
    void setPhyWorld(cocos2d::PhysicsWorld* world) {m_world=world;};
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(CrashDetection);
};

#endif // __CRASHDETECTION_SCENE_H__


