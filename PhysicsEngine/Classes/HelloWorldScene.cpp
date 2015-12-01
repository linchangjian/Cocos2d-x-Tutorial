#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
    //设置重力加速度
    //	scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visiableSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto edgeBody = PhysicsBody::createEdgeBox(visiableSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visiableSize.width/2+origin.x,visiableSize.height/2+origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    
    this->addChild(edgeNode);
//    {
//        auto sprite = Sprite::create("shana.png");
//        sprite->setPosition(Point(visiableSize.width/2+origin.x,visiableSize.height/2+origin.y));
//        auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(0, 1, 0));
//        spriteBody->setCollisionBitmask(1);
//        spriteBody->setContactTestBitmask(true);
//        //设置是否是动态的物体
//        spriteBody->setDynamic(true);
//        sprite->setPhysicsBody(spriteBody);
//
//        this->addChild(sprite);
//    }
    
    {
        auto sprite = Sprite::create("shana.png");
        sprite->setPosition(Point(visiableSize.width/2+origin.x,visiableSize.height/2+ origin.y+200));
        auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(0, 1, 0));
        
        //提供角速度
        spriteBody->setAngularVelocity(400);
        //角速度衰减
        spriteBody->setAngularDamping(1);
        spriteBody->setAngularVelocityLimit(500);
        spriteBody->setCollisionBitmask(2);
        spriteBody->setContactTestBitmask(true);
        //设置是否是动态的物体
        spriteBody->setDynamic(true);
        sprite->setPhysicsBody(spriteBody);
        
        this->addChild(sprite);
    }
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    //check if the bodies have collided;
    if((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) ||
     (1 == b->getCollisionBitmask() && 2 == a->getCollisionBitmask()))
    {
           CCLOG("COLLISION HAS OCCURED");
        return true;
    }
       return false;
}
