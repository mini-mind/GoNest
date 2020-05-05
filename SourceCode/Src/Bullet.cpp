#include "Bullet.h"
#include"Player.h"
Bullet::Bullet(const char* szName,const char* bulletName):CSprite(bulletName) //对构造函数进行实现
{
    this->CloneSprite(szName);
    //cout<<"name:"<<bulletName<<endl;
    m_iHeart=1;
    m_iOwner=0;
    m_iDir=0;
    m_fSpeedX=0.f;
    m_fSpeedY=0.f;
}

void Bullet::Init(int heart,int bulletType,int Dir)
{
    setHeart(heart);
    setBulltType(bulletType);
    setDir(Dir);
    setSpeedX(0);
    setSpeedY(0);
    SetSpriteRotation(45*Dir);
    SetSpriteWorldLimitMode(WORLD_LIMIT_KILL);
}

void Bullet::OnMove(int iDir)
{
    setDir(iDir);
    switch(getDir())
    {
    case 0:
        setSpeedX(0);
        setSpeedY(-20);
        break;
    case 1:
        setSpeedX(20);
        setSpeedY(-20);
        break;
    case 2:
        setSpeedX(20);
        setSpeedY(0);
        break;
    case 3:
        setSpeedX(20);
        setSpeedY(20);
        break;
    case 4:
        setSpeedX(0);
        setSpeedY(20);
        break;
    case 5:
        setSpeedX(-20);
        setSpeedY(20);
        break;
    case 6:
        setSpeedX(-20);
        setSpeedY(0);
        break;
    case 7:
        setSpeedX(-20);
        setSpeedY(-20);
        break;
    }
    SetSpriteRotation(45*getDir());
    SetSpriteLinearVelocity(getSpeedX(),getSpeedY());
}

void Bullet::changeState()
{

}
