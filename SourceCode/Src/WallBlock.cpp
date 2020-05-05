#include "WallBlock.h"
#include<iostream>
using namespace std;
WallBlock::WallBlock()
{
	//ctor
	sprite=NULL;
	HP=0;
	digable=false;
}

void WallBlock::init()
{
	sprite=NULL;
	HP=0;
}

void WallBlock::setWallBlock(float x,float y,int tp)
{
	char *name=NULL;
	char *newName=NULL;
	if(tp==-1)
	{
		HP=-1;
		name="grass";
		digable=false;
		newName=CSystem::MakeSpriteName("GRASS",x*100+y);
	}else{
		HP=tp;
		name="wall";
		digable=true;
		newName=CSystem::MakeSpriteName("WALL",x*100+y);
	}
    sprite=new CSprite(newName);
    sprite->CloneSprite(name);
    sprite->SetSpritePosition(x,y);
    if(tp!=-1)
	{
		setColor(HP);
	}
}

void WallBlock::damage(float dmg)
{
	if(sprite==NULL||HP<0)
		return;
	if(HP>0)
	{
		HP-=dmg;
		setColor(HP);
	}
	if(HP<=0)
	{
		destroySelf();
	}
}

void WallBlock::destroySelf()
{
	if(sprite)
    {
		sprite->DeleteSprite();
        delete sprite;
    }
	HP=0;
	sprite=NULL;
}

void WallBlock::setColor(float HP)
{
	int tp=int(HP+0.5)%9;
	if(tp>7)
	{
		tp=7;
	}
	sprite->SetSpriteColorRed(color[tp]>>16&0x0000ff);
	sprite->SetSpriteColorGreen(color[tp]>>8&0x0000ff);
	sprite->SetSpriteColorBlue(color[tp]&0x0000ff);
}
