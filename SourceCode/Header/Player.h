#ifndef PLAYER_H
#define PLAYER_H
#include"CommonClass.h"
#include"PlayerState.h"
#include"TREASURE.H"
class Player:public CSprite
{
    public:
        Player(const char* szName,const char*);
        //set
        void setDir(int Dir)
        {
            this->Dir=Dir;
        }
        void setSpeedX(float x)
        {
            SpeedX=x;
        }
        void setSpeedY(float y)
        {
            SpeedY=y;
        }
        void setOnFireTime(float fDelaTime)
        {
            OnFireTime=fDelaTime;
        }
        void setBulltType(int BulletType)
        {
            State.BulletType=BulletType;
        }
        void setBulletNum(int BulletNum)
        {
            State.BulletNum=BulletNum;
        }
        void setBulletHeart(int heart)
        {
            State.BulletHeart=heart;
        }
        void setShutTime(float shutTime)
        {
            State.shutTime=shutTime;
        }
        void setFreezeTime(float freezeTime)
        {
            State.freezeTime=freezeTime;
        }
        void setSpeedUpTime(float speedUpTime)
        {
            State.speedUpTime=speedUpTime;
        }
        void setfDeltaTime(float fDeltaTime)
        {
            this->fDeltaTime=fDeltaTime;
        }
        void setChangeSpeed(float changeSpeed)
        {
            this->changeSpeed=changeSpeed;
        }
        void setColWall(bool ColWall)
        {
            this->ColWall=ColWall;
        }
        //get
        int getDir()
        {
            return Dir;
        }
        float getSpeedX()
        {
            return SpeedX;
        }
        float getSpeedY()
        {
            return SpeedY;
        }
        float getOnFireTime()
        {
            return OnFireTime;
        }
        int getBulltType()
        {
            return State.BulletType;
        }
        int getBulletNum()
        {
            return State.BulletNum;
        }
        int getBulletHeart()
        {
            return State.BulletHeart;
        }
        float getShutTime()
        {
            return State.shutTime;
        }
        float getFreezeTime()
        {
            return State.freezeTime;
        }
        float getSpeedUpTime()
        {
            return State.speedUpTime;
        }
        float getfDeltaTime()
        {
            return fDeltaTime;
        }
        float getChangeSpeed()
        {
            return changeSpeed;
        }
        bool getColWall()
        {
            return ColWall;
        }
        void Init(float x,float y,int dir);
        void OnMove(int Dir,int iKey);
        void changeMove(int iKey);
        void OnFire();
        //void setState();
        //void checkState();
		//void bulletReturn();
		void destroy();
		//bool isDestroyed();
		void flushMove();
		void OnKeyDown(const int iKey);
		void OnKeyUp(const int iKey);
		float getDigPointX();
		float getDigPointY();
        void UpDateShutTime(float PM_fDeltaTime);
		void OnSpriteColSprite(Treasure* treSprite,float Time/*游戏已运行时间*/);
		virtual ~Player();
    private:
        int Dir;
        float SpeedX;
        float SpeedY;
        float changeSpeed;
        float OnFireTime;
        float fDeltaTime;
        bool ColWall;
        PlayerState State;
       int  shouhub_Count;
       int shouhua_Count;
       CSound *shootSound;
};

#endif // PLAYER_H
