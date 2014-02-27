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
	this->view = Sprite::create(skin);
	this->view->retain();

	auto body = PhysicsBody::createCircle(this->view->getContentSize().width / 2, PhysicsMaterial(0.1, 1, 0));
	body->applyImpulse(Vect(100000, 100000));
	body->setTag(Mercanoid::BALL_TAG);
	this->view->setPhysicsBody(body);

	return true;
}

Sprite *Ball::getView() {
	return this->view;
}

void Ball::setLife(int amount) {
	this->life = amount;
}

int Ball::getLife() {
	return this->life;
}

void Ball::collide(int damage) {
	this->life -= damage;
}