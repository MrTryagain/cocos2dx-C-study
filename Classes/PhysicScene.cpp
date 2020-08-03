#include "PhysicScene.h"

USING_NS_CC;

Scene* PhysicScene::createScene()
{
    // 创建带物理引擎的世界场景
    auto scene = Scene::createWithPhysics();
    //获取初始化的物理世界对象
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = PhysicScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
    
}

bool PhysicScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //定义世界的边界是矩形盒子
    auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,5.0f);//创建物体对象
    auto edgeNode = Node::create();//边界节点对象
    edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));//设置节点对象位置
    edgeNode->setPhysicsBody(body);//设置与节点相关的物体对象
    this->addChild(edgeNode);//将节点对象添加到层
    auto listener = EventListenerTouchOneByOne::create();//设置单点监听器
    listener->onTouchBegan = CC_CALLBACK_2(PhysicScene::onTouchBeganCallback, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool PhysicScene::onTouchBeganCallback(Touch* touch,Event* event){
    log("点击");
    Vec2 location = touch->getLocation();
    addNewSpriteAtPosition(location);
//    addNewParticlePosition(location);
    return false;
}

//添加精灵
void PhysicScene::addNewSpriteAtPosition(Vec2 touchLocation)
{
    auto sp = Sprite::create("Ball.png");
    sp->setTag(1);
    //创建圈圈形状物体
    auto body = PhysicsBody::createCircle(sp->getContentSize().width/2);
    sp->setPhysicsBody(body);//设置与精灵关联
    sp->setPosition(touchLocation);
    log("%f,%f",touchLocation.x,touchLocation.y);
    this->addChild(sp);
    ParticleSystem* ps = ParticleFire::create();
    ps->setPosition(touchLocation);
    sp->addChild(ps);
}
//添加粒子特效
void PhysicScene::addNewParticlePosition(Vec2 location,Sprite* sprite){
//    ParticleSystem* ps = ParticleMeteor::create();
//    ps->setPosition(location);
//    log("%f,%f",location.x,location.y);
//    sprite->addChild(ps);//精灵添加粒子子节点
}
void PhysicScene::update(float dt){
    
}

//层退出
void PhysicScene::onExit()
{
    Layer::onExit();
    log("CrashDetection onExit");
    //注销所有监听器
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

