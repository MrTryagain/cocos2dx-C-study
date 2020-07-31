#include "CrashDetection.h"
#include <iostream>
USING_NS_CC;

//extern const char* PHYSICSCONTACT_EVENT_NAME;

Scene* CrashDetection::createScene()
{
    //创建场景、添加层
    auto scene = Scene::createWithPhysics();
    PhysicsWorld* phyWorld = scene->getPhysicsWorld();
    //phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//debug模式，物体周围有红色线条
    auto layer = CrashDetection::create();
    scene->addChild(layer);
    return scene;
}
void CrashDetection::onEnter(){
    Layer::onEnter();
    log("onEnter");
    
    auto listener = EventListenerPhysicsContact::create();
    if(listener)
        log("创建碰撞监听器成功");
    listener->onContactBegin = [this](PhysicsContact& contact)
    {
        auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
        auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
        a++;
        log("碰撞了%d次",a);
        return true;
    };
    
    listener->onContactPreSolve = [] (PhysicsContact& contact,
                                      PhysicsContactPreSolve& solve) {
        return true;
    };
    
    listener->onContactPostSolve = [] (PhysicsContact& contact,
                                       const PhysicsContactPostSolve& solve) {
    };
    
    listener->onContactSeparate = [](PhysicsContact& contact) {
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
                                                                                     listener, 1);
    
}

// on "init" you need to initialize your instance
bool CrashDetection::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto ball1 = Sprite::create("Ball.png");
    ball1->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    PhysicsBody* ballBody1 = PhysicsBody::createCircle(ball1->getContentSize().width/2);//创建小球物理body
    ballBody1->getShape(0)->setRestitution(1.0f);//设置球1弹性形变，getShape(0)调用形状0，可以有多个形状
    ballBody1->getShape(0)->setFriction(0.0f);//设置球1摩擦力
    ballBody1->getShape(0)->setDensity(1.0f);//设置球1密度
    ballBody1->setGravityEnable(false);//设置重力
    Vect force = Vect(500000.0f,500000.0f);
    ballBody1->applyImpulse(force);//产生推力
    ballBody1->setContactTestBitmask(0xFFFFFFFF);//设置能否出发碰撞监听
    ball1->setPhysicsBody(ballBody1);//球1body添加进精灵
    ball1->setTag(1);
    ParticleSystem* particle1 = ParticleMeteor::create();
    ball1->addChild(particle1);
    this->addChild(ball1);
    
    auto ball2 = Sprite::create("Ball.png");
    ball2->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    PhysicsBody* ballBody2 = PhysicsBody::createCircle(ball1->getContentSize().width/2);//创建小球物理body
    ballBody2->getShape(0)->setRestitution(1.0f);//设置球1弹性形变，getShape(0)调用形状0，可以有多个形状
    ballBody2->getShape(0)->setFriction(0.0f);//设置球1摩擦力
    ballBody2->getShape(0)->setDensity(1.0f);//设置球1密度
    ballBody2->setGravityEnable(false);//设置重力
    Vect force2 = Vect(-500000.0f,-500000.0f);
    ballBody2->applyImpulse(force2);//产生推力
    ballBody2->setContactTestBitmask(0xFFFFFFFF);
    ball2->setPhysicsBody(ballBody2);//球1body添加进精灵
    ball2->setTag(1);
    this->addChild(ball2);
    
    auto ball3 = Sprite::create("Ball.png");
    ball3->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    PhysicsBody* ballBody3 = PhysicsBody::createCircle(ball3->getContentSize().width/2);//创建小球物理body
    ballBody3->getShape(0)->setRestitution(1.0f);//设置球1弹性形变，getShape(0)调用形状0，可以有多个形状
    ballBody3->getShape(0)->setFriction(0.0f);//设置球1摩擦力
    ballBody3->getShape(0)->setDensity(1.0f);//设置球1密度
    ballBody3->setGravityEnable(false);//设置重力
    Vect force3 = Vect(500000.0f,500000.0f);
    ballBody3->applyImpulse(force3);//产生推力
    ballBody3->setContactTestBitmask(0xFFFFFFFF);
    ball3->setPhysicsBody(ballBody3);//球1body添加进精灵
    ball3->setTag(1);
    this->addChild(ball3);
    
    Sprite* edgeSpace=Sprite::create();//创建边界精灵
    //创建边界物理body
    PhysicsBody* boundBody=PhysicsBody::createEdgeBox(
                                                      visibleSize,
                                                      PHYSICSBODY_MATERIAL_DEFAULT,
                                                      3);
    boundBody->getShape(0)->setFriction(0.0f);  
    boundBody->getShape(0)->setRestitution(1.0f);
    
    edgeSpace->setPhysicsBody(boundBody);//将边界物理body添加进精灵
    edgeSpace->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    this->addChild(edgeSpace);
    edgeSpace->setTag(0);
    return true;
}
void CrashDetection::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    log("移除所有监听器");
}
