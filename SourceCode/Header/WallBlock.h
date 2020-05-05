#ifndef WALLBLOCK_H
#define WALLBLOCK_H
#include"CommonClass.h"

static int color[8]=
{
    0xffd697,
    0xffb441,
    0xff9535,
    0xff7800,
    0xe76d00,
    0xc76700,
    0xa05000,
    0x663300
};
class WallBlock
{
public:
    WallBlock();
    void setWallBlock(float,float,int);
    void damage(float);
    void destroySelf();
    void init();
    CSprite *sprite=NULL;
    bool digable;
protected:
private:
    float HP;
    void setColor(float);
};

#endif // WALLBLOCK_H
