#ifndef __NINJAMOVE_SCENE_H__
#define __NINJAMOVE_SCENE_H__

#include "cocos2d.h"

class NinjaMove : public cocos2d::Layer
{
    cocos2d::TMXTiledMap* _tileMap;
    cocos2d::Sprite *_player;
    cocos2d::TMXLayer* _collidable;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual bool onTouchBeganCallback(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMovedCallback(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEndedCallback(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void setViewpointCenter(cocos2d::Vec2 position);
    // implement the "static create()" method manually
    CREATE_FUNC(NinjaMove);
};

#endif // __NINJAMOVE_SCENE_H__

