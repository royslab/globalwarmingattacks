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
	//ballsFactory = new BallsFactory();
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
	this->initUI();
	

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
		this->addNewBall(*touchPosition, versor, 20,1);
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

void Mercanoid::initUI() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto healBtn = MenuItemImage::create(
		"mercanoid/powerup_heal_static.png",
		"mercanoid/powerup_heal_press.png",
		CC_CALLBACK_1(Mercanoid::powerupHealCallback, this));

	auto multiBtn = MenuItemImage::create(
		"mercanoid/powerup_multi_static.png",
		"mercanoid/powerup_multi_press.png",
		CC_CALLBACK_1(Mercanoid::powerupMultiCallback, this));

	int healBtnX = origin.x + visibleSize.width - (healBtn->getContentSize().width / 2)-10;
	int healBtnY = origin.y + (healBtn->getContentSize().height / 2) + 10;
	healBtn->setPosition(Point(healBtnX, healBtnY));

	int multiBtnX = origin.x + visibleSize.width - healBtn->getContentSize().width - 20 - multiBtn->getContentSize().width / 2;
	int multiBtnY = origin.y + (multiBtn->getContentSize().height / 2) + 10;
	multiBtn->setPosition(Point(multiBtnX, multiBtnY));

	// BUTTONS MENU
	auto menu = Menu::create(healBtn, multiBtn, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

Ball* Mercanoid::addNewBall(Point position, Point impulse, int life, int tier)
{
	Ball *ball = this->ballsFactory->getBall(tier);
	ball->setPosition(position);
	ball->addImpulse(impulse);
	ball->setLife(life);
	Sprite *view = ball->getView();
	this->addChild(view);
	this->balls.pushBack(ball);

	return ball;
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
		destroyBall(ball);
	}
}

void Mercanoid::destroyBall(Ball *ball) {
	this->removeChild(ball->getView());
	this->balls.eraseObject(ball);
}

void Mercanoid::removeBarFromBody(PhysicsBody *body) {
	Node *node = body->getNode();
	body->removeFromWorld();
	this->removeChild(node, true);
}

void Mercanoid::powerupHealCallback(Object* pSender)
{
	for (auto ball : this->balls) {
		ball->addLife(10);
	}
}

void Mercanoid::powerupMultiCallback(Object* pSender)
{
	Vector<Ball*> tmp;
	tmp.pushBack(this->balls);


	for (auto ball : tmp) {
		PhysicsBody *body = ball->getView()->getPhysicsBody();
		Point ballPosition = ball->getView()->getPosition();
		Point ballVelocity = body->getVelocity();
		Point ballVelocityNorm = ballVelocity.normalize();
		// BALL 1
		Point ball1Position = body->getVelocity().normalize().rotate(Point(0, 1)) * (ball->getView()->getContentSize().width / 2);
		ball1Position = ball1Position + ball->getView()->getPosition();
		//Point ball1Position = ball->getView()->getPosition();
		Point vel1 = ballVelocity.rotate(Point(5, 2).normalize());
		Ball* ball1 = addNewBall(ball1Position, Point(), ball->getLife(),2);
		ball1->getView()->getPhysicsBody()->setVelocity(vel1);
		
		// BALL 1
		Point ball2Position = (ballVelocity.normalize().rotate(Point(0, -1)) * (ball->getView()->getContentSize().width / 2)) + ball->getView()->getPosition();
		//Point ball2Position = ball->getView()->getPosition();
		Point vel2 = ballVelocity.rotate(Point(5, -2).normalize());
		Ball* ball2 = addNewBall(ball2Position, Point(), ball->getLife(),2);
		ball2->getView()->getPhysicsBody()->setVelocity(vel2);

		this->destroyBall(ball);
	}
}

//TODO: Destroy balls vector on destruct