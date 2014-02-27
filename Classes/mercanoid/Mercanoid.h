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
	

	int ballLife = 10;
	void initGame();
	void addNewBallAtPosition(cocos2d::Point p);
	void spawnBars();
	cocos2d::Sprite* createBar();
	bool onContactBegin(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contact);
	cocos2d::PhysicsWorld* m_world;
	void processCollision(cocos2d::PhysicsBody *body);
	void ballHit();
	void removeBarFromBody(cocos2d::PhysicsBody *body);
	Ball* ball;
};
#endif // _MERCANOID_H_