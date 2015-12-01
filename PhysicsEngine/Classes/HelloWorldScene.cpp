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
    
    auto sprite = Sprite::create("shana.png");
    sprite->setPosition(Point(visiableSize.width/2+origin.x,visiableSize.height/2+origin.y));
    auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(),PhysicsMaterial(100, 1, 50));
    sprite->setPhysicsBody(spriteBody);
    
    this->addChild(sprite);
    return true;
}
