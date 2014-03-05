#ifndef  _MERCANOID_BALLS_FACTORY_H_
#define  _MERCANOID_BALLS_FACTORY_H_

#include "cocos2d.h"
#include "Ball.h"
#include "BallDefinition.h"

class BallsFactory
{
	public:
		static const int TIER1 = 1;
		static const int TIER2 = 2;

		Ball* getBall(int tier);
		BallDefinition* getDefinition(int tier);
};

#endif // _MERCANOID_BALLS_FACTORY_H_