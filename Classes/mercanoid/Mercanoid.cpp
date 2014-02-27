#include "Mercanoid.h"

USING_NS_CC;

Scene* Mercanoid::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
	auto layer = Mercanoid::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool Mercanoid::init()
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

void Mercanoid::initGame() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.5, 1, 0), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	this->spawnBars();
	this->addNewBallAtPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(Mercanoid::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Mercanoid::addNewBallAtPosition(Point p)
{
	Ball *ball = Ball::create("mercanoid/ball.png");
	ball->getView()->setPosition(p);
	this->addChild(ball->getView());

	this->ball = ball;
	/*
	auto sprite = Sprite::create("mercanoid/ball.png");
	
	auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2, PhysicsMaterial(0.1,1,0));
	body->applyImpulse(Vect(100000, 100000));
	body->setTag(BALL_TAG);
	sprite->setPhysicsBody(body);
	
	sprite->setPosition(p);
	this->addChild(sprite);
	*/
}

void Mercanoid::spawnBars() {

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

Sprite *Mercanoid::createBar() {
	Sprite *sprite = Sprite::create("mercanoid/bar.png");
	
	Size size = Size(sprite->getContentSize().width, sprite->getContentSize().height);
	auto body = PhysicsBody::createBox(size, PhysicsMaterial(0.5, 1, 0));
	body->setTag(BAR_TAG);
	body->setDynamic(false);
	sprite->setPhysicsBody(body);

	return sprite;
}
bool Mercanoid::onContactBegin(EventCustom* event, const PhysicsContact& contact) {

	this->processCollision(contact.getShapeA()->getBody());
	this->processCollision(contact.getShapeB()->getBody());
	return true;
}

void Mercanoid::processCollision(PhysicsBody *body) {
	int tag = body->getTag();

	if (tag == BALL_TAG) {
		this->ballHit();
	}
	else if (tag == BAR_TAG) {
		removeBarFromBody(body);
	}
}

void Mercanoid::ballHit() {
	this->ballLife--;
	CCLOG("Ball life: %d", this->ballLife);
	if (this->ballLife == 0) {
		CCLOG("GAME OVER");
	}
}

void Mercanoid::removeBarFromBody(PhysicsBody *body) {
	Node *node = body->getNode();
	body->removeFromWorld();
	this->removeChild(node, true);
}