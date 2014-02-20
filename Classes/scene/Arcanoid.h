#ifndef  _ARCANOID_H_
#define  _ARCANOID_H_

#include "cocos2d.h"

class Arcanoid : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Arcanoid);
	void setPhyWorld(cocos2d::PhysicsWorld* world){ m_world = world; }
	
protected:
	static const int BALL_TAG = 1;
	static const int BAR_TAG = 2;

	void initGame();
	void addNewBallAtPosition(cocos2d::Point p);
	void spawnBars();
	cocos2d::Sprite* createBar();
	bool onContactBegin(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contactRef);
	cocos2d::PhysicsWorld* m_world;


};
#endif // _ARCANOID_H_