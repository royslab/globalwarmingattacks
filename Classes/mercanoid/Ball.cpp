#include "Ball.h"
#include "Mercanoid.h"
#include "BallDefinition.h"

USING_NS_CC;

Ball* Ball::create(BallDefinition* def)
{
	Ball *ball = new Ball();

	if (ball && ball->init(def))
	{
		ball->autorelease();
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}

Ball::~Ball() {
	this->view->release();
}

bool Ball::init(BallDefinition* def) {

	initView(def);
	initLife();

	return true;
}

void Ball::initView(BallDefinition* def) {
	this->view = Sprite::create(def->getAssetFile());
	this->view->retain();

	auto body = PhysicsBody::createCircle(def->getRadius(), PhysicsMaterial(0.1, 1, 0));
	body->userData = this;
	
	body->setTag(Mercanoid::BALL_TAG);
	this->view->setPhysicsBody(body);
}

void Ball::initLife() {
	lifeLabel = LabelBMFont::create();
	lifeLabel->setFntFile("fonts/west_england-64.fnt");
	this->view->addChild(lifeLabel);
	lifeLabel->setPosition(Point(0, 0));
	lifeLabel->setScale(0.5f);
}

void Ball::updateLifeLabel() {
	char str[4];
	sprintf(str, "%03d", this->life);
	lifeLabel->setString(str);
	lifeLabel->setPositionX(lifeLabel->getContentSize().width * 0.25f);
	lifeLabel->setPositionY(lifeLabel->getContentSize().height * 0.5f);
}

Sprite *Ball::getView() {
	return this->view;
}

void Ball::setLife(int amount) {
	this->life = amount;
	updateLifeLabel();
}

void Ball::addLife(int amount) {
	this->life += amount;
	updateLifeLabel();
}


int Ball::getLife() {
	return this->life;
}

void Ball::setPosition(cocos2d::Point position) {
	this->view->setPosition(position);
}

void Ball::addImpulse(cocos2d::Point impulse) {
	this->view->getPhysicsBody()->applyImpulse(Vect(impulse.x, impulse.y));
}

void Ball::collide(int damage) {
	this->life -= damage;
	updateLifeLabel();
	CCLOG("Ball life: %d", this->life);
}