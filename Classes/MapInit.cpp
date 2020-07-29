#include "MapInit.h"
#include "NinjaMove.h"
USING_NS_CC;

Scene* MapInit::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MapInit::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool MapInit::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _tileMap = TMXTiledMap::create("map/MiddleMap.tmx");
    addChild(_tileMap,0,100);
    
    TMXObjectGroup* group = _tileMap->getObjectGroup("objects");
    ValueMap spawnPoint = group->getObject("ninja");
    
    float x = spawnPoint["x"].asFloat();
    float y = spawnPoint["y"].asFloat();
    
    _player = Sprite::create("ninja.png");
    _player->setPosition(Vec2(x,y));
    addChild(_player, 2, 200);
    
    return true;
}
