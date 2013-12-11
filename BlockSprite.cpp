//
//  BlockSprite.cpp
//  samegame
//
//  Created by Murayama Kunshiro on 2013/12/03.
//
//

#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
}

BlockSprite::~BlockSprite()
{
}

BlockSprite* BlockSprite::createWithBlockType(kBlock blockType)
{
    BlockSprite* pRet = new BlockSprite();
    if(pRet && pRet->initWithBlockType(blockType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BlockSprite::initWithBlockType(kBlock blockType)
{
    if(!CCSprite::initWithFile(getBlockImageFileName(blockType)))
    {
        return false;
    }
    
    m_blockType = blockType;
    
    return true;
}

const char* BlockSprite::getBlockImageFileName(kBlock blockType)
{
    switch (blockType) {
        case kBlockRed:
            return "red.png";
            break;
        case kBlockBlue:
            return "blue.png";
            break;
        case kBlockYellow:
            return "yellow.png";
            break;
        case kBlockGreen:
            return "green.png";
            break;
        case kBlockGray:
            return "gray.png";
            break;
        default:
            CCAssert(false, "invalid blockType");
            return "";
    }
}