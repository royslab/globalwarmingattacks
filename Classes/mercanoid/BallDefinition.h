#ifndef  _MERCANOID_BALL_DEFINITION_H_
#define  _MERCANOID_BALL_DEFINITION_H_

class BallDefinition
{
	public:	
		virtual int getId() = 0;
		virtual char* getAssetFile() = 0;
		virtual int getRadius() = 0;
};

#endif // _MERCANOID_BALL_DEFINITION_H_