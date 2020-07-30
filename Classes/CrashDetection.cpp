#include "CrashDetection.h"

USING_NS_CC;

//extern const char* PHYSICSCONTACT_EVENT_NAME;

Scene* CrashDetection::createScene()
{
    //创建场景、添加层
    auto scene = Scene::createWithPhysics();
    PhysicsWorld* phyWorld = scene->getPhysicsWorld();
    phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = CrashDetection::create();
    scene->addChild(layer);
    return scene;
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
    
    PhysicsMaterial pm = {1,1,0.2};//物理属性，质量、弹性形变、摩擦力
    //PHYSICSBODY_MATERIAL_DEFAULT//默认物理属性参数
    //定义世界的边界
    auto body = PhysicsBody::createEdgeBox(visibleSize,pm,5.0f);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(body);
    this->addChild(edgeNode);

    //设置为单点触摸
//    auto listener = EventListenerTouchOneByOne::create();
//    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
//    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
//    listener->onTouchBegan = CC_CALLBACK_2(CrashDetection::onTouchBeganCallback, this);
    setTouchEnabled(true);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    return true;
}

//层进入
void CrashDetection::onEnter()
{
    Layer::onEnter();
    log("enter is ok");
    //注册监听器，响应碰撞检测事件
    auto listener = EventListenerPhysicsContact::create();
    log("listener is ok");
    listener->onContactBegin = [](PhysicsContact& contact)
    {
        //从接触点中取出互相接触的两个节点对象
        auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
        auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
        
        if (spriteA && spriteA->getTag() == 1
            && spriteB && spriteB->getTag() == 1)
        {
            spriteA->setColor(Color3B::YELLOW);
            spriteB->setColor(Color3B::YELLOW);
        }
        
        log("onContactBegin");
        return true;
    };
    
    listener->onContactPreSolve = [] (PhysicsContact& contact, PhysicsContactPreSolve& solve)
    {
        log("onContactPreSolve");
        return true;
    };
    
    listener->onContactPostSolve = [] (PhysicsContact& contact, const PhysicsContactPostSolve& solve)
    {
        log("onContactPostSolve");
    };
    
    listener->onContactSeparate = [](PhysicsContact& contact)
    {
        auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
        auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();
        
        if (spriteA && spriteA->getTag() == 1
            && spriteB && spriteB->getTag() == 1)
        {
            spriteA->setColor(Color3B::WHITE);
            spriteB->setColor(Color3B::WHITE);
        }
        log("onContactSeperate");
    };
    
    //设置事件优先级，值越小优先级越高
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener,1);
    
    
}
//层退出
void CrashDetection::onExit()
{
    Layer::onExit();
    log("CrashDetection onExit");
    //注销所有监听器
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}


bool CrashDetection::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 location = touch->getLocation();
    addNewSpriteAtPosition(location);
    return false;
}


void CrashDetection::addNewSpriteAtPosition(Vec2 p)
{
    auto sp = Sprite::create("Ball.png");
    sp->setTag(1);
    auto body = PhysicsBody::createBox(sp->getContentSize());
    //设置物体接触时能否触发EventListenerPhysicsContact中定义的碰撞检测事件
//    body->setContactTestBitmask(0x1);
//    body->setCategoryBitmask(0x2);//类别掩码
//    body->setCollisionBitmask(0x2);//碰撞掩码
    
    sp->setPhysicsBody(body);
    sp->setPosition(p);
    this->addChild(sp);
}

