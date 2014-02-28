#include "Mercanoid.h"

USING_NS_CC;

Scene* Mercanoid::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	this->touchPosition = new Point();
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
	this->initListeners();
	

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_2(Mercanoid::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void Mercanoid::initListeners() {
	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch* touch, Event* event){
		Point pos = this->convertTouchToNodeSpace(touch);
		this->touchPosition->x = pos.x;
		this->touchPosition->y = pos.y;

		return true;
	};

	listener->onTouchEnded = [&](Touch* touch, Event* event){
		//
		Point endPosition = this->convertTouchToNodeSpace(touch);

		Point versor = endPosition - *this->touchPosition;
		versor = versor.normalize();
		versor.x *= 50000;
		versor.y *= 50000;
		this->addNewBall(*touchPosition, versor, 20);
		/*if (!this->blocked) {
			

			int movedDistance = endPosition.x - this->touchPosition->x;
			int movedDirection = (fabsf(movedDistance) > Capcha::MIN_DRAG_DISTANCE) ? fabsf(movedDistance) / movedDistance : 0;

			if (this->ruleSecuence[currSecuenceIndex] == movedDirection) {
				currSecuenceIndex++;
				this->unschedule(schedule_selector(Capcha::timesUp));
				this->scheduleOnce(schedule_selector(Capcha::timesUp), IDLE_TIME);

				if (currSecuenceIndex == RULE_SECUENCE_LENGTH) {
					this->blocked = true;
					this->unschedule(schedule_selector(Capcha::timesUp));
					this->capchaSucceed();

				}
			}
			else
			{
				this->timesUp(0);
			}
		}*/
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Mercanoid::addNewBall(Point position, Point impulse, int life)
{
	Ball *ball = Ball::create("mercanoid/ball.png");
	ball->setPosition(position);
	ball->addImpulse(impulse);
	ball->setLife(life);
	ball->retain();
	Sprite *view = ball->getView();
	this->addChild(view);
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
		Ball* ball = (Ball*) body->userData;
		this->ballHit(ball);
	}
	else if (tag == BAR_TAG) {
		removeBarFromBody(body);
	}
}

void Mercanoid::ballHit(Ball *ball) {
	ball->collide(1);
	if (ball->getLife() <= 0) {
		this->removeChild(ball->getView());
		ball->release();
	}
}

void Mercanoid::removeBarFromBody(PhysicsBody *body) {
	Node *node = body->getNode();
	body->removeFromWorld();
	this->removeChild(node, true);
}