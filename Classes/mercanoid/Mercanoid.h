#ifndef  _MERCANOID_H_
#define  _MERCANOID_H_

#include "cocos2d.h"
#include "Ball.h"

class Mercanoid : public cocos2d::Layer
{
public:
	static const int BALL_TAG = 1;
	static const int BAR_TAG = 2;

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Mercanoid);
	void setPhyWorld(cocos2d::PhysicsWorld* world){ m_world = world; }
	
protected:
	cocos2d::Point *touchPosition;
	cocos2d::PhysicsWorld* m_world;
	cocos2d::Vector<Ball*> balls;

	void initGame();
	void initListeners();
	void initUI();
	Ball* addNewBall(cocos2d::Point position, cocos2d::Point impulse, int life);
	void destroyBall(Ball *ball);
	void spawnBars();
	cocos2d::Sprite* createBar();
	bool onContactBegin(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact);
	void processCollision(cocos2d::PhysicsBody *body);
	void ballHit(Ball *ball);
	void removeBarFromBody(cocos2d::PhysicsBody *body);

	void powerupHealCallback(Object* pSender);
	void powerupMultiCallback(Object* pSender);
};
#endif // _MERCANOID_H_