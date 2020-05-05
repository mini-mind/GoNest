#include "CommonClass.h"
#include "Player.h"
#include "BulletManager.h"
#include "cmath"
#include "LessonX.h"

Player::Player(const char* szName,const char* playerName):CSprite(playerName)
{
    this->CloneSprite(szName);
    Dir=0;
    SpeedX=0.f;
    SpeedY=0.f;
    OnFireTime=0.f;
    ColWall=false;
    //state
    State.BulletType=0;
    State.BulletNum=0;
    State.shutTime=0;
    State.freezeTime=0;
    State.speedUpTime=0;
    changeSpeed=10;
    shootSound=new CSound("fire",false,1);
}

void Player::Init(float PositionX,float PositionY,int Dir)
{
    setDir(Dir);
    setSpeedX(0);
    setSpeedY(0);
    SetSpriteRotation(45*Dir);
    SetSpritePosition(PositionX,PositionY);
    SetSpriteWorldLimitMode(WORLD_LIMIT_STICKY);
    //setDestroyed(false);
}

void Player::flushMove()
{
	if(g_GameMain.GetGameState()==3)
	{
        SetSpriteLinearVelocity(0,0);
        return;
	}
    if(this->getShutTime()>fDeltaTime)
    {
        //cout<<"玩家："<<this->GetName()<<"被定身，flushMove直接退出"<<endl;
        //cout<<"玩家："<<this->GetName()<<"定身解除时间："<<this->getShutTime()<<"当前时间："<<fDeltaTime<<endl;
        SetSpriteLinearVelocity(0,0);
        return;
    }
    //cout<<"玩家："<<this->GetName()<<"定身状态解除，flushMove进入执行"<<endl;
    if(this->getFreezeTime()<=fDeltaTime)
    {
        if(this->getFreezeTime()!=0)
        {
            changeSpeed*=4;
            SpeedX*=4;
            SpeedY*=4;
            this->setFreezeTime(0.f);
        }
    }
    if(this->getSpeedUpTime()<=fDeltaTime)
    {
        //cout<<"Ending SpeedUp Time:"<<this->getSpeedUpTime()<<" Current Time:"<<fDeltaTime<<endl;
        if(this->getSpeedUpTime()!=0)
        {
            changeSpeed/=2;
            SpeedX/=2;
            SpeedY/=2;
            this->setSpeedUpTime(0.f);
        }
    }
	int r=getDir();
    if(getSpeedX()==0&&getSpeedY()<0)
        r=0;
    else if(getSpeedX()>0&&getSpeedY()<0)
        r=1;
    else if(getSpeedX()>0&&getSpeedY()==0)
        r=2;
    else if(getSpeedX()>0&&getSpeedY()>0)
        r=3;
    else if(getSpeedX()==0&&getSpeedY()>0)
        r=4;
    else if(getSpeedX()<0&&getSpeedY()>0)
        r=5;
    else if(getSpeedX()<0&&getSpeedY()==0)
        r=6;
    else if(getSpeedX()<0&&getSpeedY()<0)
        r=7;
    setDir(r);
    SetSpriteLinearVelocity(SpeedX,SpeedY);
    SetSpriteRotation(45*getDir());
    setShutTime(0.f);
}

float Player::getDigPointX()
{
    float distance=this->GetSpriteHeight()/2+0.25;
    if(this->Dir==0||this->Dir==4)
        return this->GetSpritePositionX();
    else if(this->Dir==1||this->Dir==3)
        return this->GetSpritePositionX()+distance/sqrt(2);
    else if(this->Dir==2)
        return this->GetSpritePositionX()+distance;
    else if(this->Dir==5||this->Dir==7)
        return this->GetSpritePositionX()-distance/sqrt(2);
    else if(this->Dir==6)
        return this->GetSpritePositionX()-distance;
}

float Player::getDigPointY()
{
    float distance=this->GetSpriteHeight()/2+0.25;
    if(this->Dir==2||this->Dir==6)
        return this->GetSpritePositionY();
    else if(this->Dir==3||this->Dir==5)
        return this->GetSpritePositionY()+distance/sqrt(2);
    else if(this->Dir==4)
        return this->GetSpritePositionY()+distance;
    else if(this->Dir==1||this->Dir==7)
        return this->GetSpritePositionY()-distance/sqrt(2);
    else if(this->Dir==0)
        return this->GetSpritePositionY()-distance;
}

void Player::OnMove(int Dir,int iKey)
{
    //cout<<"已进入PlayerManager OnKeyDown中Player的OnMove"<<endl;
    Dir/=2;
    if((Dir)%2)
    {
        SpeedX+=(2-Dir)*changeSpeed;
        //SetSpriteLinearVelocityX(SpeedX);
    }else
    {
        SpeedY+=(Dir-1)*changeSpeed;
        //SetSpriteLinearVelocityY(SpeedY);
    }
    //cout<<"After SpeedUp:Direction->"<<this->getDir()<<" SpeedX:"<<this->getSpeedX()<<" SpeedY:"<<this->getSpeedY()<<endl;
}

void Player::OnFire()
{
    //cout<<"Go Into PlayerManager's OnKeyDown ->Player OnFire()"<<endl;
    if(OnFireTime>0.2f&&this->getBulletNum()>0)
    {
    	shootSound->PlaySound();
        g_BulletManager.createOneBullet(this->GetSpritePositionX(),this->GetSpritePositionY(),this);
        this->setBulletNum(this->getBulletNum()-1);
        //cout<<"In Function OnFire size:"<<g_BulletManager.bulletPool.size()<<endl;
        OnFireTime=0;
    }
}

void Player::destroy()
{
	DeleteSprite();
	//destroyed=true;
	//cout<<GetName()<<"had been destroyed"<<endl;
}

Player::~Player()
{
    //dtor
}

void Player::OnSpriteColSprite(Treasure* treSprite,float Time/*游戏已运行时间*/)
{
    if(treSprite->gettype()==2)
    {
        //暂停五秒钟
        setShutTime(5.0+fDeltaTime);
    }

    else if(treSprite->gettype()==1)
{
        if(strcmp(this->GetName(),"rightPlayer"))
    {
        if( g_GameMain.jl2==0)
        {
        char* szName = CSystem::MakeSpriteName("shouhub",shouhub_Count);
		TM.shouhub = new Treasure(szName);
		TM.shouhub->CloneSprite("shouhub");
		shouhub_Count++;
        float nest2_x=TM.nest2->GetSpritePositionX();
        float nest2_y=TM.nest2->GetSpritePositionY();
		TM.shouhub->SetSpritePosition(nest2_x,nest2_y);
		TM.shouhub->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		TM.treasurePool.push_back(TM.shouhub);
		 g_GameMain.jl2=1;
        }

        else if( g_GameMain.jl2==1)
        {
        g_GameMain.Time3=0;
        }
    }
    else if(strcmp(this->GetName(),"leftPlayer"))
    {
        if( g_GameMain.jl==0)
        {
        char* szName = CSystem::MakeSpriteName("shouhua",shouhua_Count);
		TM.shouhua = new Treasure(szName);
		TM.shouhua->CloneSprite("shouhua");
		shouhua_Count++;
        float nest1_x=TM.nest1->GetSpritePositionX();
        float nest1_y=TM.nest1->GetSpritePositionY();
		TM.shouhua->SetSpritePosition(nest1_x,nest1_y);
		TM.shouhua->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		TM.treasurePool.push_back(TM.shouhua);
		 g_GameMain.jl=1;
        }

        else if( g_GameMain.jl==1)
        {
        g_GameMain.Time2=0;
        }
    }
    }
    else if(treSprite->gettype()==3)
    {
        //装载子弹A
        //cout<<this->GetName()<<" get BulletType:1--normal"<<endl;
        setBulletHeart(4);//设定子弹伤害为4
        setBulletNum(1);//设定子弹数目为1
        setBulltType(1);//设定普通子弹类型
    }
    else if(treSprite->gettype()==4)
    {
        //装载子弹B
        //cout<<this->GetName()<<" get BulletType:2--Freeze"<<endl;
        setBulletHeart(2);//设定子弹伤害为2
        setBulletNum(1);//设定子弹数目为1
        setBulltType(2);//设定Freeze子弹类型
    }
    else if(treSprite->gettype()==5)
    {
        //加速道具
        //cout<<"before SpeedUp:Direction->"<<this->getDir()<<" SpeedX:"<<this->getSpeedX()<<" SpeedY:"<<this->getSpeedY()<<endl;
        if(getSpeedUpTime()==0)
		{
			changeSpeed*=2;
			SpeedX*=2;
            SpeedY*=2;
        }
        setSpeedUpTime(5.0+fDeltaTime);
    }
}
