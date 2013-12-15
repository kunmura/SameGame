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
    initNextPos();
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

// 移動先の初期化
void BlockSprite::initNextPos()
{
    m_nextPosX = -1;
    m_nextPosY = -1;
}

// 移動先インデックスをセット
void BlockSprite::setNextPos(int nextPosX, int nextPosY)
{
    m_nextPosX = nextPosX;
    m_nextPosY = nextPosY;
}