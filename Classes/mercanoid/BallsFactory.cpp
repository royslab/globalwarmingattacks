#include "BallsFactory.h"
#include "Tier1Definition.h"
#include "Tier2Definition.h"

Ball* BallsFactory::getBall(int tier) {
	
	return Ball::create(this->getDefinition(tier));
}

BallDefinition* BallsFactory::getDefinition(int tier) {
	BallDefinition* def;
	if (tier == TIER1) {
		def = new Tier1Definition();
	}
	else if (tier == TIER2) {
		def = new Tier2Definition();
	}
	return def;
}