#include<vector>
#include<stdio.h>
#include "TreasureManager.h"
#include "LessonX.h"
#include<cstdlib>
#include<ctime>
#define random(a,b) (rand()%(b-a+1)+a)
#include "MapManager.h"

using namespace std;
MapManager      mapManager2;

TreasureManager::TreasureManager()
{
    jiasu_Count=0;
    shouhu_Count=0;
    dingshen_Count=0;
    zidanA_Count=0;
    zidanB_Count=0;
    daodu_count=0;
    nest1_Count=0;
    nest2_Count=0;
    //shouhua_P=0;
    //shouhub_P=0;

}

TreasureManager::~TreasureManager()
{

}
Treasure*  TreasureManager::getTreasureByname(const char* szName)
{
    int i;
    for( i=0; i<treasurePool.size(); i++)
	{
			if(strcmp(szName,treasurePool[i]->GetName()) == 0)
			{
				return treasurePool[i];
			}
	}
	return NULL;
}
void TreasureManager::DeleteByName(const char* szName)//根据名字把精灵从容器中删除
{
	for(vector<Treasure*>::iterator it=treasurePool.begin();it!=treasurePool.end();)
	{
		Treasure* cw =*it;
		if(strcmp(szName,cw->GetName()) == 0)
		{
			treasurePool.erase(it);
			cw->DeleteSprite();
			delete cw;
			break;
		}
		else
		{
			it++;
		}
	}
}

 void TreasureManager::creat_shouhu(){

    float x,y;
   //srand((unsigned)time(NULL));
    x=random(-38,38);
    y=random(-28,28);
    mapManager2.getNewTreasurePosition(x,y);

        char* szName = CSystem::MakeSpriteName("daoju_shouhu",shouhu_Count);//创建守护道具，家园在一定时间内阻止敌方进入
        Treasure* shouhu = new Treasure(szName);
		shouhu->CloneSprite("shouhu");
		shouhu->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		shouhu->SetSpritePosition(x,y);
		shouhu->settype(1);
		shouhu_Count++;
		daodu_count++;
		//cout<<daodu_count<<endl;
		//cout<<shouhu->GetSpritePositionX()<<" "<<shouhu->GetSpritePositionY()<<")"<<endl;
		treasurePool.push_back(shouhu);
}
 void TreasureManager::creat_dingshen(){
    float x,y;
    //srand((unsigned)time(NULL));
    x=random(-38,38);
    y=random(-28,28);
    mapManager2.getNewTreasurePosition(x,y);

        char* szName = CSystem::MakeSpriteName("daoju_dingshen",dingshen_Count);//创建减速道具，5秒内对面不能移动
        Treasure* dingshen = new Treasure(szName);
		dingshen->CloneSprite("dingshen");
		dingshen->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		dingshen->settype(2);
		dingshen->SetSpritePosition(x,y);
		dingshen_Count++;
		daodu_count++;
		//cout<<dingshen->GetSpritePositionX()<<" "<<dingshen->GetSpritePositionY()<<")"<<endl;
		//cout<<daodu_count<<endl;
		treasurePool.push_back(dingshen);
}
void TreasureManager::creat_zidanA(){
    float x,y;
    //srand((unsigned)time(NULL));
    x=random(-38,38);
    y=random(-28,28);
    mapManager2.getNewTreasurePosition(x,y);

        char* szName = CSystem::MakeSpriteName("daoju_zidanA",zidanA_Count);//子弹A道具*5，威力1，范围2*1
        Treasure* zidanA = new Treasure(szName);
		zidanA->CloneSprite("zidanA");
		zidanA->SetSpritePosition(x,y);
		zidanA->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		zidanA->settype(3);
		zidanA_Count++;
		daodu_count++;
		//cout<<zidanA->GetSpritePositionX()<<" "<<zidanA->GetSpritePositionY()<<")"<<endl;
		//cout<<daodu_count<<endl;
		treasurePool.push_back(zidanA);
}
void TreasureManager::creat_zidanB(){
    float x,y;
    //srand((unsigned)time(NULL));
    x=random(-38,38);
    y=random(-28,28);
    mapManager2.getNewTreasurePosition(x,y);

        char* szName = CSystem::MakeSpriteName("daoju_zidanB",zidanB_Count);//子弹B道具*5，威力2，范围2*1，减速敌方50%
        Treasure* zidanB = new Treasure(szName);
		zidanB->CloneSprite("zidanB");
		zidanB->SetSpritePosition(x,y);
		zidanB->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		zidanB->settype(4);
		zidanB_Count++;
		daodu_count++;
		//cout<<daodu_count<<endl;
		//cout<<zidanB->GetSpritePositionX()<<" "<<zidanB->GetSpritePositionY()<<")"<<endl;
		treasurePool.push_back(zidanB);
}
void TreasureManager::creat_jiasu(){

    float x,y;
    //srand((unsigned)time(NULL));
    x=random(-38,38);
    y=random(-28,28);
    mapManager2.getNewTreasurePosition(x,y);

        char* szName = CSystem::MakeSpriteName("daoju_jiasu",jiasu_Count);//子弹B道具*5，威力2，范围2*1，减速敌方50%
        Treasure* jiasu = new Treasure(szName);
		jiasu->CloneSprite("jiasu");
		jiasu->SetSpritePosition(x,y);
		jiasu->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		jiasu->settype(5);
		jiasu_Count++;
		daodu_count++;
		//cout<<daodu_count<<endl;
		//cout<<jiasu->GetSpritePositionX()<<" "<<jiasu->GetSpritePositionY()<<")"<<endl;
		treasurePool.push_back(jiasu);
}
void TreasureManager::random_treasure()
{
    float x,y,z;
    x=random(-45,45);
    y=random(-35,35);
    z=random(1,12);
    //cout<<x<<"  "<<y<<endl;
    mapManager2.getNewTreasurePosition(x,y);
    //cout<<x<<"  "<<y<<endl;
if(daodu_count<=5){
if(z==1)
    {
       char* szName = CSystem::MakeSpriteName("daoju_shouhu",shouhu_Count);//创建守护道具，家园在一定时间内阻止敌方进入
        Treasure* shouhu = new Treasure(szName);
		shouhu->CloneSprite("shouhu");
		shouhu->SetSpritePosition(x,y);
		shouhu->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		shouhu->settype(1);
		shouhu_Count++;
		treasurePool.push_back(shouhu);
		daodu_count++;
		 //cout<<"11111TM.shouhu_Count="<<TM.shouhu_Count<<endl;
		//cout<<daodu_count<<endl;
    }
    else if(z==2||z==3)
    {
       char* szName = CSystem::MakeSpriteName("daoju_dingshen",dingshen_Count);//创建减速道具，5秒内对面不能移动
		 Treasure*dingshen = new Treasure(szName);
		dingshen->CloneSprite("dingshen");
		dingshen->SetSpritePosition(x,y);
		dingshen->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		dingshen->settype(2);
		dingshen_Count++;
		treasurePool.push_back(dingshen);
		daodu_count++;
		//cout<<daodu_count<<endl;
    }
    else if(z==4||z==5||z==6)
    {
        char* szName = CSystem::MakeSpriteName("daoju_zidanA",zidanA_Count);//子弹A道具*5，威力1，范围2*1
		 Treasure* zidanA = new Treasure(szName);
		zidanA->CloneSprite("zidanA");
		zidanA->SetSpritePosition(x,y);
		zidanA->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		zidanA->settype(3);
		zidanA_Count++;
		treasurePool.push_back(zidanA);
		daodu_count++;
		cout<<daodu_count<<endl;
   }
    else if(z==7||z==8||z==9)
  {
        char* szName = CSystem::MakeSpriteName("daoju_zidanB",zidanB_Count);//子弹B道具*5，威力2，范围2*1，减速敌方50%
		 Treasure* zidanB = new Treasure(szName);
		zidanB->CloneSprite("zidanB");
		zidanB->SetSpritePosition(x,y);
		zidanB->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		zidanB->settype(4);
		zidanB_Count++;
		treasurePool.push_back(zidanB);
		daodu_count++;
		cout<<daodu_count<<endl;

    }
  else
   {
        char* szName = CSystem::MakeSpriteName("daoju_jiasu",jiasu_Count);//子弹B道具*5，威力2，范围2*1，减速敌方50%
		Treasure* jiasu = new Treasure(szName);
		jiasu->CloneSprite("jiasu");
		jiasu->SetSpritePosition(x,y);
		jiasu->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		jiasu->settype(5);
		jiasu_Count++;
		treasurePool.push_back(jiasu);
		daodu_count++;
		cout<<daodu_count<<endl;
  }
}

}

 void TreasureManager::Creat_nest()
 {
		char* szName = CSystem::MakeSpriteName("nest1",nest1_Count);
		nest1 = new Treasure(szName);
		nest1->CloneSprite("nest1");

		char* szName2 = CSystem::MakeSpriteName("nest2",nest2_Count);
		nest2 = new Treasure(szName2);
		nest2->CloneSprite("nest2");

		nest1->SetSpritePosition(48,36);
		nest1->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		nest1->SetSpriteWorldLimitMode(WORLD_LIMIT_STICKY);
		nest1->SetSpriteCollisionPhysicsReceive(false);
        nest1->SetSpriteCollisionPhysicsSend(false);

		nest2->SetSpritePosition(-48,-36);
		nest2->SetSpriteCollisionActive(1,1); //设置接收发送碰撞
		nest2->SetSpriteWorldLimitMode(WORLD_LIMIT_STICKY);
		nest2->SetSpriteCollisionPhysicsReceive(false);
        nest2->SetSpriteCollisionPhysicsSend(false);
		treasurePool.push_back(nest1);
		treasurePool.push_back(nest2);

 }

/*1：守护道具 2：定身道具 3：普通子弹 4：减速子弹 5：加速道具*/



