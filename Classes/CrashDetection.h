#ifndef __CRASHDETECTION_SCENE_H__
#define __CRASHDETECTION_SCENE_H__

#include "cocos2d.h"

class CrashDetection : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onEnter();
    virtual void onExit();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CrashDetection);
    
    void addNewSpriteAtPosition(cocos2d::Point p);
    
};

#endif // __CRASHDETECTION_SCENE_H__

