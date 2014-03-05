#ifndef  _MERCANOID_TIER1_DEFINITION_H_
#define  _MERCANOID_TIER1_DEFINITION_H_

#include "BallDefinition.h"

class Tier1Definition : public BallDefinition
{
	public:
		virtual int getId() { return 1; };
		virtual char* getAssetFile(){ return "mercanoid/ball.png"; };
		virtual int getRadius() { return 26; };
};

#endif // _MERCANOID_TIER1_DEFINITION_H_