
#ifndef __PHYSICSCENE_SCENE_H__
#define __PHYSICSCENE_SCENE_H__

#include "cocos2d.h"

class PhysicScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    void update(float dt);
    virtual bool init();
    virtual void onExit();
    bool onTouchBeganCallback(cocos2d::Touch* touch, cocos2d::Event* event);
    CREATE_FUNC(PhysicScene);
    void addNewSpriteAtPosition(cocos2d::Point p);
    void addNewParticlePosition(cocos2d::Vec2 p,cocos2d::Sprite* s);
};

#endif // __PHYSICSCENE_SCENE_H__

