#ifndef  _MERCANOID_BALL_H_
#define  _MERCANOID_BALL_H_

#include "cocos2d.h"

class Ball : public cocos2d::Object
{
	public:
		static Ball* create(const std::string& skin);
		
		bool init(const std::string& skin);

		void setLife(int amount);
		void addLife(int amount);
		int getLife();

		void setPosition(cocos2d::Point position);
		void addImpulse(cocos2d::Point impulse);
		
		
		cocos2d::Sprite* getView();
		void collide(int damage);
		~Ball();
	protected:
		int life = 0;
		cocos2d::Sprite *view;
		cocos2d::LabelBMFont *lifeLabel;
		
		void initView(const std::string& skin);
		void initLife();
		void updateLifeLabel();
};

#endif // _MERCANOID_BALL_H_