#ifndef  _MERCANOID_BALL_H_
#define  _MERCANOID_BALL_H_

#include "cocos2d.h"

class Ball
{
	public:
		static Ball* create(const std::string& skin);

		bool init(const std::string& skin);
		void setLife(int amount);
		int getLife();
		cocos2d::Sprite* getView();
		void collide(int damage);
		~Ball();
	protected:
		int life = 0;
		cocos2d::Sprite *view;
};

#endif // _MERCANOID_BALL_H_