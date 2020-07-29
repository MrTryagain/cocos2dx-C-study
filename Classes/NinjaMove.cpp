#include "NinjaMove.h"
#include <SimpleAudioEngine.h>
USING_NS_CC;

Scene* NinjaMove::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NinjaMove::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool NinjaMove::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();//设置单点监听器
    listener->setSwallowTouches(false);//触摸重叠层时不冲突
    //回调函数
    listener->onTouchBegan = CC_CALLBACK_2(NinjaMove::onTouchBeganCallback, this);
    listener->onTouchMoved = CC_CALLBACK_2(NinjaMove::onTouchMovedCallback, this);
    listener->onTouchEnded = CC_CALLBACK_2(NinjaMove::onTouchEndedCallback, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    _tileMap = TMXTiledMap::create("map/MiddleMap.tmx");//创建瓦片地图对象
    addChild(_tileMap,0,100);//添加地图进层
    
    TMXObjectGroup* group = _tileMap->getObjectGroup("objects");//获取瓦片地图的所有对象
    ValueMap spawnPoint = group->getObject("ninja");//从所有对象中获取ninja对象，返回值是ValueMap，是一种键值对结构
    
    float x = spawnPoint["x"].asFloat();//spawnPoint["x"]获取x轴坐标，返回值是value类型，通过asfloat()转换成int类型
    float y = spawnPoint["y"].asFloat();
    
    _player = Sprite::create("ninja.png");
    _player->setPosition(Vec2(x,y));
    addChild(_player, 2, 200);
    
    setViewpointCenter(_player->getPosition());//地图滚动
    
    _collidable = _tileMap->getLayer("collidable");//获取碰撞检测层
    _collidable->setVisible(false);//设置为不可见

    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);//绑定层监控
    return true;
}

bool NinjaMove::onTouchBeganCallback(Touch* touch, Event* event)
{
    
    log("onTouchBegan");
    return true;
}

void NinjaMove::onTouchMovedCallback(Touch *touch, Event *event)
{
    log("onTouchMoved");
}

void NinjaMove::onTouchEndedCallback(Touch *touch, Event *event)
{
    log("onTouchEnded");
    //获得OpenGL坐标
    Vec2 touchLocation = touch->getLocation();
    Vec2 playerPos = _player->getPosition();//获取ninja的当前位置
    Vec2 diff = touchLocation - playerPos;//触摸点和ninja的距离差
    
    if (abs(diff.x) > abs(diff.y)) {//abs 取绝对值
        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width; //以像素为单位得出一块的宽度和高度
            _player->runAction(FlipX::create(false)); //精灵翻转为原始状态
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
            _player->runAction(FlipX::create(true)); //精灵水平翻转
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += _tileMap->getTileSize().height;
        } else {
            playerPos.y -= _tileMap->getTileSize().height;
        }
    }
    log("playerPos (%f ,%f) ",playerPos.x,playerPos.y);
    this->setPlayerPosition(playerPos);//更新ninja坐标
}
void NinjaMove::setPlayerPosition(Vec2 position)
{
    //从像素点坐标转化为瓦片坐标
    Vec2 tileCoord =  this->tileCoordFromPosition(position);
    //获得瓦片的GID
    int tileGid = _collidable->getTileGIDAt(tileCoord);
    
    if (tileGid > 0) {
        Value prop = _tileMap->getPropertiesForGID(tileGid);
        ValueMap propValueMap = prop.asValueMap();
        
        std::string collision = propValueMap["Collidable"].asString();
        
        if (collision == "true") { //碰撞检测成功
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");
            return;
        }
    }
    //移动精灵
    _player->setPosition(position);
}

Vec2 NinjaMove::tileCoordFromPosition(Vec2 pos)
{
    int x = pos.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - pos.y) / _tileMap->getTileSize().height;
    return Vec2(x,y);
}
void NinjaMove::setViewpointCenter(Vec2 position)
{
    log("setViewpointCenter");
    
    log("position (%f ,%f) ",position.x,position.y);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();//屏幕大小
    //可以防止，视图左边超出屏幕之外。
    int x = MAX(position.x, visibleSize.width / 2);
    int y = MAX(position.y, visibleSize.height / 2);
    //可以防止，视图右边超出屏幕之外。
    x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width)
            - visibleSize.width / 2);//地图宽度-屏幕宽度的一半
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height)
            - visibleSize.height/2);
    
    //getTileSize().width/height分别以像素为单位得出一块的宽度和高度。
    //getMapSize().width/height分别得出在x轴方向上总的块数，在y轴方向上总的块数
    //屏幕中心点
    Vec2 pointA = Vec2(visibleSize.width/2, visibleSize.height/2);
    //使精灵处于屏幕中心，移动地图目标位置
    Vec2 pointB = Vec2(x, y); //获取移动地图目标位置
    log("目标位置 (%f ,%f) ",pointB.x,pointB.y);
    
    //地图移动偏移量
    Vec2 offset =pointA - pointB;
    log("offset (%f ,%f) ",offset.x, offset.y);
    this->setPosition(offset);
    
}
