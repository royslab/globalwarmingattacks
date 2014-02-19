#include "Arcanoid.h"

USING_NS_CC;

Scene* Arcanoid::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -250));
	auto layer = Arcanoid::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool Arcanoid::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	initGame();

	return true;
}

void Arcanoid::initGame() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	addNewBallAtPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
}

void Arcanoid::addNewBallAtPosition(Point p)
{
	auto sprite = Sprite::create("arcanoid/ball.png");
	sprite->setTag(1);
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0.1,2,0.5));
	sprite->setPhysicsBody(body);
	
	sprite->setPosition(p);
	this->addChild(sprite);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(Arcanoid::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool Arcanoid::onContactBegin(EventCustom* event, const PhysicsContact& contactRef) {
	contactRef.getShapeA()->getBody()->applyForce(Vect(500, 500));
	contactRef.getShapeB()->getBody()->applyForce(Vect(500, 500));

	return true;
}