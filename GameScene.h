//
//  GameScene.h
//  samegame
//
//  Created by Murayama Kunshiro on 2013/12/03.
//
//

#ifndef __samegame__GameScene__
#define __samegame__GameScene__

#include "cocos2d.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8
#define REMOVING_TIME 0.1f
#define MOVING_TIME 0.2f

#define PNG_BACKGROUND "background.png"
#define MP3_REMOVE_BLOCK "se_remove.mp3"

class GameScene : public cocos2d::CCLayer
{
protected:
    enum kTag
    {
        kTagBackground = 1,
        kTagBaseBlock = 10000,
    };
    
    enum kZOrder
    {
        kZOrderBackground,
        kZOrderBlock,
    };
    
    struct PositionIndex
    {
        PositionIndex(int x1, int y1)
        {
            x = x1;
            y = y1;
        }
        
        int x;
        int y;
    };
    
    // 2-2-3
    cocos2d::CCSprite* m_background;
    void showBackground();
    
    // 2-2-4
    float m_blockSize;
    std::map<kBlock, std::list<int> > m_blockTags;
    void initForVariables();
    void showBlock();
    cocos2d::CCPoint getPosition(int posIndexX, int posIndexY);
    int getTag(int posIndexX, int posIndexY);
    
    // 2-2-5
    void getTouchBlockTag(cocos2d::CCPoint touchPoint, int &tag, kBlock &blockType);
    std::list<int> getSameColorBlockTags(int baseTag, kBlock blockType);
    void removeBlock(std::list<int> blockTags, kBlock blockType);
    bool hasSameColorBlock(std::list<int> blockTagList, int searchBlockTag);
    
    // 2-3-1
    void removingBlock(cocos2d::CCNode* block);
    
    // 2-3-2
    std::vector<kBlock> blockTypes;
    PositionIndex getPositionIndex(int tag);
    void setNewPosition1(int tag, PositionIndex posIndex);
    void searchNewPosition1(std::list<int> blocks);
    void moveBlock();
    void movingBlockAnimation1(std::list<int> blocks);
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif /* defined(__samegame__GameScene__) */
