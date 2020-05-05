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
void TreasureManager::DeleteByName(const char* szName)//�������ְѾ����������ɾ��
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

        char* szName = CSystem::MakeSpriteName("daoju_shouhu",shouhu_Count);//�����ػ����ߣ���԰��һ��ʱ������ֹ�з�����
        Treasure* shouhu = new Treasure(szName);
		shouhu->CloneSprite("shouhu");
		shouhu->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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

        char* szName = CSystem::MakeSpriteName("daoju_dingshen",dingshen_Count);//�������ٵ��ߣ�5���ڶ��治���ƶ�
        Treasure* dingshen = new Treasure(szName);
		dingshen->CloneSprite("dingshen");
		dingshen->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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

        char* szName = CSystem::MakeSpriteName("daoju_zidanA",zidanA_Count);//�ӵ�A����*5������1����Χ2*1
        Treasure* zidanA = new Treasure(szName);
		zidanA->CloneSprite("zidanA");
		zidanA->SetSpritePosition(x,y);
		zidanA->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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

        char* szName = CSystem::MakeSpriteName("daoju_zidanB",zidanB_Count);//�ӵ�B����*5������2����Χ2*1�����ٵз�50%
        Treasure* zidanB = new Treasure(szName);
		zidanB->CloneSprite("zidanB");
		zidanB->SetSpritePosition(x,y);
		zidanB->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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

        char* szName = CSystem::MakeSpriteName("daoju_jiasu",jiasu_Count);//�ӵ�B����*5������2����Χ2*1�����ٵз�50%
        Treasure* jiasu = new Treasure(szName);
		jiasu->CloneSprite("jiasu");
		jiasu->SetSpritePosition(x,y);
		jiasu->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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
       char* szName = CSystem::MakeSpriteName("daoju_shouhu",shouhu_Count);//�����ػ����ߣ���԰��һ��ʱ������ֹ�з�����
        Treasure* shouhu = new Treasure(szName);
		shouhu->CloneSprite("shouhu");
		shouhu->SetSpritePosition(x,y);
		shouhu->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		shouhu->settype(1);
		shouhu_Count++;
		treasurePool.push_back(shouhu);
		daodu_count++;
		 //cout<<"11111TM.shouhu_Count="<<TM.shouhu_Count<<endl;
		//cout<<daodu_count<<endl;
    }
    else if(z==2||z==3)
    {
       char* szName = CSystem::MakeSpriteName("daoju_dingshen",dingshen_Count);//�������ٵ��ߣ�5���ڶ��治���ƶ�
		 Treasure*dingshen = new Treasure(szName);
		dingshen->CloneSprite("dingshen");
		dingshen->SetSpritePosition(x,y);
		dingshen->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		dingshen->settype(2);
		dingshen_Count++;
		treasurePool.push_back(dingshen);
		daodu_count++;
		//cout<<daodu_count<<endl;
    }
    else if(z==4||z==5||z==6)
    {
        char* szName = CSystem::MakeSpriteName("daoju_zidanA",zidanA_Count);//�ӵ�A����*5������1����Χ2*1
		 Treasure* zidanA = new Treasure(szName);
		zidanA->CloneSprite("zidanA");
		zidanA->SetSpritePosition(x,y);
		zidanA->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		zidanA->settype(3);
		zidanA_Count++;
		treasurePool.push_back(zidanA);
		daodu_count++;
		cout<<daodu_count<<endl;
   }
    else if(z==7||z==8||z==9)
  {
        char* szName = CSystem::MakeSpriteName("daoju_zidanB",zidanB_Count);//�ӵ�B����*5������2����Χ2*1�����ٵз�50%
		 Treasure* zidanB = new Treasure(szName);
		zidanB->CloneSprite("zidanB");
		zidanB->SetSpritePosition(x,y);
		zidanB->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		zidanB->settype(4);
		zidanB_Count++;
		treasurePool.push_back(zidanB);
		daodu_count++;
		cout<<daodu_count<<endl;

    }
  else
   {
        char* szName = CSystem::MakeSpriteName("daoju_jiasu",jiasu_Count);//�ӵ�B����*5������2����Χ2*1�����ٵз�50%
		Treasure* jiasu = new Treasure(szName);
		jiasu->CloneSprite("jiasu");
		jiasu->SetSpritePosition(x,y);
		jiasu->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
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
		nest1->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		nest1->SetSpriteWorldLimitMode(WORLD_LIMIT_STICKY);
		nest1->SetSpriteCollisionPhysicsReceive(false);
        nest1->SetSpriteCollisionPhysicsSend(false);

		nest2->SetSpritePosition(-48,-36);
		nest2->SetSpriteCollisionActive(1,1); //���ý��շ�����ײ
		nest2->SetSpriteWorldLimitMode(WORLD_LIMIT_STICKY);
		nest2->SetSpriteCollisionPhysicsReceive(false);
        nest2->SetSpriteCollisionPhysicsSend(false);
		treasurePool.push_back(nest1);
		treasurePool.push_back(nest2);

 }

/*1���ػ����� 2��������� 3����ͨ�ӵ� 4�������ӵ� 5�����ٵ���*/



