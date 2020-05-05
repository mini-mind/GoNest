#include "BulletManager.h"
#include<iterator>
BulletManager::BulletManager()
{
    //ctor
    //usedBulletNo=0;
    bulTemp=0;
}

BulletManager::~BulletManager(){}

void BulletManager::createOneBullet(float x,float y,Player* player)
{
    //cout<<"Player' OnFire  ->  BulletManager ->  createOneBullet "<<endl;
    Bullet* bul;
    char *str=CSystem::MakeSpriteName("bul",bulTemp);
    bulTemp++;
//    cout<<"createOneBullet中 准备new子弹精灵"<<endl;
//	cout<<player->GetName()<<"'sBulletType(out of if): "<<player->getBulltType()<<endl;
    if(!strcmp(player->GetName(),"leftPlayer"))
    {
//        cout<<player->GetName()<<"'s BulletType: "<<player->getBulltType()<<endl;
        if(player->getBulltType()==1)
            bul=new Bullet("leftBullet",str);
        else if(player->getBulltType()==2)
            bul=new Bullet("leftFreeze",str);
    }
    else if(!strcmp(player->GetName(),"rightPlayer"))
    {

        if(player->getBulltType()==1)
            bul=new Bullet("rightBullet",str);
        else if(player->getBulltType()==2)
            bul=new Bullet("rightFreeze",str);
    }

    /*if(player->getBulltType()==1)
        bul=new Bullet("Bullet",str);
    else if(player->getBulltType()==2)
        bul=new Bullet("Freeze",str);*/

    //cout<<"createOneBullet :new bullet complete."<<endl;
    int r=player->getDir();
    if(player->getSpeedX()==0&&player->getSpeedY()<0)
        r=0;
    else if(player->getSpeedX()>0&&player->getSpeedY()<0)
        r=1;
    else if(player->getSpeedX()>0&&player->getSpeedY()==0)
        r=2;
    else if(player->getSpeedX()>0&&player->getSpeedY()>0)
        r=3;
    else if(player->getSpeedX()==0&&player->getSpeedY()>0)
        r=4;
    else if(player->getSpeedX()<0&&player->getSpeedY()>0)
        r=5;
    else if(player->getSpeedX()<0&&player->getSpeedY()==0)
        r=6;
    else if(player->getSpeedX()<0&&player->getSpeedY()<0)
        r=7;
    setDir(r);
    bul->setOwnerPlayer(player);
    bul->Init(player->getBulletHeart(),player->getBulltType(),getDir());
    bul->SetSpritePosition(x,y);
    bul->OnMove(getDir());
	bul->SetSpriteWorldLimitMode(WORLD_LIMIT_KILL);
	bulletPool.push_back(bul);
	//cout<<"created size:"<<bulletPool.size()<<endl;
}

/*void BulletManager::BulletDestroy(const char *s)
{
	vector<Bullet*>::iterator it;
	for(it=bulletPool.begin();it!=bulletPool.end();it++)
	{
		if(!strcmp(s,(*it)->GetName()))
		{
			(*it)->DeleteSprite();
			break;
		}
	}
}*/

Bullet* BulletManager::getBulletByName(const char* SrcName)
{
    vector<Bullet*>::iterator it;
    //cout<<"srcName:"<<SrcName<<endl;
    //cout<<"size£º"<<bulletPool.size()<<endl;
    for(it=bulletPool.begin();it!=bulletPool.end();it++)
    {
        //cout<<'\t'<<(*it)->GetName()<<endl;
        if(!strcmp(SrcName,(*it)->GetName()))
        {
            return (*it);
        }
    }
    return NULL;
}

void BulletManager::clearAll()
{
	vector<Bullet*>::iterator it;
	for(it=bulletPool.begin();it!=bulletPool.end();it++)
	{
		(*it)->DeleteSprite();
		delete (*it);
	}
	bulletPool.clear();
}

void BulletManager::destroyBullet(const char *bulName)
{
    vector<Bullet*>::iterator it;
    for(it=bulletPool.begin();it!=bulletPool.end();it++)
    {
        if(!strcmp(bulName,(*it)->GetName()))
        {
            //cout<<(*it)->GetName()<<endl;
            (*it)->DeleteSprite();
            //bulletPool.erase(it);
            return;
        }
    }
}
