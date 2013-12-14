//
//  CCPlaySE.h
//  samegame
//
//  Created by Murayama Kunshiro on 2013/12/14.
//
//

#ifndef __samegame__CCPlaySE__
#define __samegame__CCPlaySE__

#include "cocos2d.h"

class CCPlaySE : public cocos2d::CCActionInstant
{
public:
    CCPlaySE(std::string sound);
    virtual ~CCPlaySE(){}
    
    virtual void update(float time);
    virtual CCFiniteTimeAction* reverse(void);
    virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
public:
    static CCPlaySE* create(std::String sound);
    
protected:
    std::string m_sound;
};

#endif /* defined(__samegame__CCPlaySE__) */
