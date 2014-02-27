#include "Ball.h"
#include "Mercanoid.h"

USING_NS_CC;

Ball* Ball::create(const std::string& skin)
{
	Ball *ball = new Ball();

	if (ball && ball->init(skin))
	{
		return ball;
	}
	CC_SAFE_DELETE(ball);
	return nullptr;
}

Ball::~Ball() {
	this->view->release();
}

bool Ball::init(const std::string& skin) {

	initView(skin);
	initLife();

	return true;
}

void Ball::initView(const std::string& skin) {
	this->view = Sprite::create(skin);
	this->view->retain();

	auto body = PhysicsBody::createCircle(this->view->getContentSize().width / 2, PhysicsMaterial(0.1, 1, 0));
	body->userData = this;
	body->applyImpulse(Vect(50000, 50000));
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

int Ball::getLife() {
	return this->life;
}

void Ball::collide(int damage) {
	this->life -= damage;
	updateLifeLabel();
	CCLOG("Ball life: %d", this->life);
}