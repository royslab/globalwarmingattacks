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
	void initGame();
	void addNewBallAtPosition(cocos2d::Point p);
	bool onContactBegin(cocos2d::EventCustom* event, const cocos2d::PhysicsContact& contactRef);
	cocos2d::PhysicsWorld* m_world;

};
#endif // _ARCANOID_H_