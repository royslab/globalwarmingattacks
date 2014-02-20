#include "Arcanoid.h"

USING_NS_CC;

Scene* Arcanoid::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
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
	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.5, 1, 0), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	this->spawnBars();
	this->addNewBallAtPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
}

void Arcanoid::addNewBallAtPosition(Point p)
{
	auto sprite = Sprite::create("arcanoid/ball.png");
	sprite->setTag(BALL_TAG);
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0.1,1,0));
	body->applyImpulse(Vect(50000, 50000));
	sprite->setPhysicsBody(body);
	
	sprite->setPosition(p);
	this->addChild(sprite);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(Arcanoid::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Arcanoid::spawnBars() {

	Size visibleSize = Director::getInstance()->getVisibleSize();

	int xPos = 10;
	int yPos = visibleSize.height - 20;

	for (int y = 0; y < 4; y++) {
		auto *bar = Sprite::create();
		for (int x = 0; x < 13; x++)
		{
			bar = this->createBar();

			if (x == 0) {
				xPos += bar->getContentSize().width * 0.5;
			}

			bar->setPosition(Point(xPos, yPos));
			xPos += bar->getContentSize().width;
			addChild(bar);
		}
		xPos = 10;
		yPos -= bar->getContentSize().height;
	}
}

Sprite *Arcanoid::createBar() {
	Sprite *sprite = Sprite::create("arcanoid/bar.png");
	sprite->setTag(BAR_TAG);
	Size size = Size(sprite->getContentSize().width, sprite->getContentSize().height);
	auto body = PhysicsBody::createBox(size, PhysicsMaterial(0.5, 1, 0));
	body->setDynamic(false);
	sprite->setPhysicsBody(body);

	return sprite;
}
bool Arcanoid::onContactBegin(EventCustom* event, const PhysicsContact& contactRef) {
	return true;
}