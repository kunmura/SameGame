//
//  GameScene.cpp
//  samegame
//
//  Created by Murayama Kunshiro on 2013/12/03.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// initiarize
bool GameScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    // 変数初期化
    initForVariables();
    
    // 背景表示
    showBackground();
    
    // コマ表示
    showBlock();
    
    return true;
}

// タッチ開始イベント
bool GameScene::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
    return true;
}

// タッチ終了イベント
void GameScene::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    CCLog("ccTouchEnded");
}

// 変数初期化
void GameScene::initForVariables()
{
    // 乱数初期化
    srand((unsigned)time(NULL));
    
    // コマの一辺の長さを取得
    BlockSprite* pBlock = BlockSprite::createWithBlockType(kBlockRed);
    m_blockSize = pBlock->getContentSize().height;
}

// show background
void GameScene::showBackground()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // create background
    m_background = CCSprite::create("background.png");
    m_background->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(m_background, kZOrderBackground, kTagBackground);
}

// 位置取得
CCPoint GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width * 0.168;
    float offsetY = m_background->getContentSize().height * 0.029;
    return CCPoint((posIndexX + 0.5) * m_blockSize + offsetX, (posIndexY + 0.5) * m_blockSize + offsetY);
}

// タグ取得
int GameScene::getTag(int posIndexX, int posIndexY)
{
    return kTagBaseBlock + posIndexX * 100 + posIndexY;
}

// コマ表示
void GameScene::showBlock()
{
    // 8x8のコマを作成する
    for (int x = 0; x < MAX_BLOCK_X; x++)
    {
        for (int y = 0; y < MAX_BLOCK_Y; y++)
        {
            // ランダムでコマを作成
            kBlock blockType = (kBlock)(rand() % kBlockCount);
            
            // 対応するコマ配列によるタグを追加
            int tag = getTag(x, y);
            m_blockTags[blockType].push_back(tag);
            
            // コマを作成
            BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
            pBlock->setPosition(getPosition(x, y));
            m_background->addChild(pBlock, kZOrderBlock, tag);
        }
    }
}

// タップされたコマのタグを取得
void GameScene::getTouchBlockTag(CCPoint touchPoint, int &tag, kBlock &blockType)
{
    for (int x=0; x < MAX_BLOCK_X; x++)
    {
        for (int y=0; y < MAX_BLOCK_Y; y++)
        {
            int currentTag = getTag(x, y);
            CCNode* node = m_background->getChildByTag(currentTag);
            if (node && node->boundingBox().containsPoint(touchPoint))
            {
                tag = currentTag;
                blockType = ((BlockSprite*)node)->getBlockType();
                
                return;
            }
        }
    }
}

// コマ配列にあるか検索
bool GameScene::hassSameColorBlock(list<int> blockTagList, int searchBlockTag)
{
    list<int>::iterator it;
    for (it = blockTagList.begin(); it != blockTagList.end(); ++it)
    {
        if (*it == searchBlockTag)
        {
            return true;
        }
    }
    
    return false;
}

// タップされたコマと同色でかつ接しているコマの配列を返す
list<int> GameScene::getSameColorBlockTags(int baseTag, kBlock blockType)
{
    // 同色のコマを格納する配列の初期化
    list<int> sameColorBlockTags;
    sameColorBlockTags.push_back(baseTag);
    
    list<int>::iterator it = sameColorBlockTags.begin();
    while (it != sameColorBlockTags.end())
    {
        int tags[] = {
            *it + 100,  // right block tag
            *it - 100,  // left block tag
            *it + 1,    // up block tag
            *it - 1,    // down block tag
        };
        
        for (int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++)
        {
            // すでにリストにあるか検索
            if (!hassSameColorBlock(sameColorBlockTags, tags[i]))
            {
                sameColorBlockTags.push_back(tags[i]);
            }
        }
        
        it++;
    }
    
    return sameColorBlockTags;
}