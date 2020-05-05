#include <iostream>
#include "PlayerManager.h"
using namespace std;
PlayerManager::PlayerManager()
{
    //ctor
    PM_fDelaTime=5.f;
    digger1=NULL;
    digger2=NULL;
}

void PlayerManager::createPlayer()
{
	leftPlayer=new Player("Player1","leftPlayer");
	leftPlayer->Init(-45,-35,4);
	//cout<<"leftPlayer has been created!"<<endl;
    rightPlayer=new Player("Player2","rightPlayer");
    rightPlayer->Init(45,35,0);
    //cout<<"rightPlayer has been created!"<<endl;
}

void PlayerManager::createDigger(char *s,CSprite* &digger)
{
	char *str=CSystem::MakeSpriteName(s,0);
	digger=new CSprite(str);
    digger->CloneSprite("digEffect");
    digger->SpriteMountToSprite(s,0,-1);
}

void PlayerManager::deleteDigger(CSprite* &digger)
{
	if(digger!=NULL)
	{
		digger->DeleteSprite();
		delete digger;
		digger=NULL;
	}
}

void PlayerManager::UpDatePlayerTime(float fDelaTime)//更新玩家开火时间
{
    leftPlayer->setOnFireTime(leftPlayer->getOnFireTime()+fDelaTime);
    rightPlayer->setOnFireTime(rightPlayer->getOnFireTime()+fDelaTime);
    leftPlayer->setfDeltaTime(PM_fDelaTime);
    rightPlayer->setfDeltaTime(PM_fDelaTime);
}

void PlayerManager::UpDateFreezeTime(Player* player)//设定玩家受到减速效果结束计时
{
    player->setFreezeTime(5.0+PM_fDelaTime);
    //player->setFreezeTime(player->getFreezeTime()+PM_fDelaTime);
}

void PlayerManager::UpDateSpeedUpTime(Player* player)//设定玩家受到加速效果结束计时
{
    player->setSpeedUpTime(5.0+PM_fDelaTime);
    //player->setSpeedUpTime(player->getSpeedUpTime()+PM_fDelaTime);
}

void PlayerManager::UpDateFreezeSpeed(Player* player)//受到减速攻击时减慢移动速度
{
	if(player->getFreezeTime()!=0)
	{
		player->setChangeSpeed(player->getChangeSpeed()/4);
		player->setSpeedX(player->getSpeedX()/4);
		player->setSpeedY(player->getSpeedY()/4);
	}
}

/*void PlayerManager::UpDateShutTime(const char* szSrcName)//设定玩家定身效果结束时间
{
    if(strcmp(szSrcName,"leftPlayer"))
        rightPlayer->setShutTime(5.0+PM_fDelaTime);
    else if(strcmp(szSrcName,"rightPlayer"))
        leftPlayer->setShutTime(5.0+PM_fDelaTime);
}*/

void PlayerManager::flushMove()
{
    leftPlayer->flushMove();
    rightPlayer->flushMove();
}

void PlayerManager::OnKeyDown(const int iKey)
{
	float x,y;
    //cout<<"已进入PlayerManager OnKeyDown"<<endl;
    switch(iKey)
    {
    case KEY_W:

        leftPlayer->OnMove(0,iKey);
        //cout<<"w down#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_D:

        leftPlayer->OnMove(2,iKey);
        //cout<<"d down#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_S:

        leftPlayer->OnMove(4,iKey);
        //cout<<"s down#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_A:

        leftPlayer->OnMove(6,iKey);
        //cout<<"a down#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_J:
        mapManager.damageBlock(leftPlayer->getDigPointX(),leftPlayer->getDigPointY(),1);
        createDigger("leftPlayer",digger1);
        break;
    case KEY_K:
        //if(leftPlayer->getBulletNum()>0)
        //{
            //leftPlayer->setBulletNum(leftPlayer->getBulletNum()-1);
            //cout<<"leftPlayer KEY_K has been down"<<endl;
            leftPlayer->OnFire();
            //cout<<"leftPlayer has fire"<<endl;
        //}
        break;
    case KEY_UP:
        rightPlayer->OnMove(0,iKey);
        break;
    case KEY_DOWN:
        rightPlayer->OnMove(4,iKey);
        break;
    case KEY_LEFT:
        rightPlayer->OnMove(6,iKey);
        break;
    case KEY_RIGHT:
        rightPlayer->OnMove(2,iKey);
        break;
    case KEY_NUMPAD2:
        mapManager.damageBlock(rightPlayer->getDigPointX(),rightPlayer->getDigPointY(),1);
        createDigger("rightPlayer",digger2);
        break;
    case KEY_NUMPAD3:
        //if(rightPlayer->getBulletNum()>0)
        //{
            //rightPlayer->setBulletNum(rightPlayer->getBulletNum()-1);
            //cout<<"rightPlayer KEY_UMPAD3 has been down"<<endl;
            rightPlayer->OnFire();
            //cout<<"rightPlayer has fire"<<endl;
        //}
        break;
    }
}

void PlayerManager::OnKeyUp(const int iKey)
{
    //cout<<"已进入PlayerManager OnKeyUp"<<endl;
    switch(iKey)
    {
    case KEY_W:

        leftPlayer->OnMove(4,iKey);
        //cout<<"w up#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_D:

        leftPlayer->OnMove(6,iKey);
        //cout<<"d up#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_S:

        leftPlayer->OnMove(0,iKey);
        //cout<<"s up#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_A:

        leftPlayer->OnMove(2,iKey);
        //cout<<"a up#SpeedX:"<<leftPlayer->getSpeedX()<<" SpeedY:"<<leftPlayer->getSpeedY()<<endl;
        break;
    case KEY_J:
    	deleteDigger(digger1);
        break;
    case KEY_UP:
        rightPlayer->OnMove(4,iKey);
        break;
    case KEY_DOWN:
        rightPlayer->OnMove(0,iKey);
        break;
    case KEY_LEFT:
        rightPlayer->OnMove(2,iKey);
        break;
    case KEY_RIGHT:
        rightPlayer->OnMove(6,iKey);
        break;
    case KEY_NUMPAD2:
    	deleteDigger(digger2);
        break;
    }
}

/*void PlayerManager::destroyLeft()
{
	leftPlayer->destroy();
}

void PlayerManager::destroyRight()
{
	rightPlayer->destroy();
}*/

void PlayerManager::clearAll()
{
	leftPlayer->DeleteSprite();
	delete leftPlayer;
    rightPlayer->DeleteSprite();
    delete rightPlayer;
}

PlayerManager::~PlayerManager()
{
    //dtor
}

void PlayerManager::OnPlayerColWall(const char* szSrcName,const char* szTarName)
{
    if(strstr(szSrcName,"leftPlayer")&&strstr(szTarName,"WALL"))
        leftPlayer->setColWall(true);
    else if(strstr(szSrcName,"rightPlayer")&&strstr(szTarName,"WALL"))
        rightPlayer->setColWall(true);
}

void PlayerManager::OnSpriteColSprite(Treasure* treSprite,const char *szSrcName,float Time)
{
	if(!strcmp(szSrcName,"leftPlayer"))
	{
	    if(!strncmp(treSprite->GetName(),"daoju_dingshen",14))
        {
            //rightPlayer->setSpeedX(0);
            //rightPlayer->setSpeedX(0);
            rightPlayer->OnSpriteColSprite(treSprite,PM_fDelaTime);
            //rightPlayer->setChangeSpeed(rightPlayer->getChangeSpeed()/4);
            //rightPlayer->setSpeedX(rightPlayer->getSpeedX()/4);
            //rightPlayer->setSpeedY(rightPlayer->getSpeedY()/4);
        }
        else
            leftPlayer->OnSpriteColSprite(treSprite,PM_fDelaTime);
	}else
	if(!strcmp(szSrcName,"rightPlayer"))
	{
	    if(!strncmp(treSprite->GetName(),"daoju_dingshen",14))
        {
            //leftPlayer->setSpeedX(0);
            //leftPlayer->setSpeedX(0);
            leftPlayer->OnSpriteColSprite(treSprite,PM_fDelaTime);
            //leftPlayer->setChangeSpeed(leftPlayer->getChangeSpeed()/4);
            //leftPlayer->setSpeedX(leftPlayer->getSpeedX()/4);
            //leftPlayer->setSpeedY(leftPlayer->getSpeedY()/4);
        }
        else
            rightPlayer->OnSpriteColSprite(treSprite,PM_fDelaTime);
	}
}
