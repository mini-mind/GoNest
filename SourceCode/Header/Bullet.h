#ifndef BULLET_H
#define BULLET_H
#include"CommonClass.h"
#include"Player.h"
class Bullet:public CSprite
{
    public:
        Bullet(const char* szName,const char*);
        //set
        void setHeart(int heart)
        {
            m_iHeart=heart;
        }
        void setOwnerPlayer(Player* ownlayer)
        {
            this->ownerPlayer=ownerPlayer;
        }
        void setDir(int dir)
        {
            m_iDir = dir;
        }
        void setBulltType(int bulletType)
        {
            this->bulletType=bulletType;
        }
        void setSpeedX(float speedX)
        {
            m_fSpeedX = speedX;
        }
        void setSpeedY(float speedY)
        {
            m_fSpeedY = speedY;
        }
        //get
        int getHeart()
        {
            return m_iHeart;
        }
        Player* getOwnerPlayer()
        {
            return ownerPlayer;
        }
        int getDir()
        {
            return m_iDir;
        }
        int getBulltType()
        {
            return bulletType;
        }
        float getSpeedX()
        {
            return m_fSpeedX;
        }
        float getSpeedY()
        {
            return m_fSpeedY;
        }
        void Init(int heart,int BulletType,int Dir);
        //void OnMove(int Dir);
        void changeState();
        //virtual void OnColBullet(const char* TargetName);
        void OnFire();
        void OnMove(int );
        //virtual ~Bullet();
    private:
        Player* ownerPlayer;
        int m_iHeart;
        int bulletType;
        int m_iDir;
        int m_iOwner;
        float m_fSpeedX;
        float m_fSpeedY;
};

#endif // BULLET_H
