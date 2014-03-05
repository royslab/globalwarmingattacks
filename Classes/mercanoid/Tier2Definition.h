#ifndef  _MERCANOID_TIER2_DEFINITION_H_
#define  _MERCANOID_TIER2_DEFINITION_H_

#include "BallDefinition.h"

class Tier2Definition : public BallDefinition {
public:
	virtual int getId() { return 2; };
	virtual char* getAssetFile(){ return "mercanoid/ball2.png"; };
	virtual int getRadius() { return 13; };
};

#endif // _MERCANOID_TIER1_DEFINITION_H_