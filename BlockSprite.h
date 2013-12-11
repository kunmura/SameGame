//
//  BlockSprite.h
//  samegame
//
//  Created by Murayama Kunshiro on 2013/12/03.
//
//

#ifndef __samegame__BlockSprite__
#define __samegame__BlockSprite__

#include "cocos2d.h"
#include "Config.h"

class BlockSprite : public cocos2d::CCSprite
{
protected:
    const char* getBlockImageFileName(kBlock blockType);
    
public:
    CC_SYNTHESIZE_READONLY(kBlock, m_blockType, BlockType);
    
    BlockSprite();
    virtual ~BlockSprite();
    virtual bool initWithBlockType(kBlock blockType);
    static BlockSprite* createWithBlockType(kBlock blockType);
};

#endif /* defined(__samegame__BlockSprite__) */
