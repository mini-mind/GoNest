#include "MapManager.h"
#include "Position.h"
#include"crowmap.h"
#include<cmath>
#include"PlayerManager.h"
MapManager::MapManager()
{
    //ctor
    row=75;
    col=100;
    srand(time(NULL));
    loading=new CSprite("loading");
    explosion=new CEffect("explosion","explosion",1);
    explosionSound=new CSound("explosionSound", false, 1);
    digSound=new CSound("hit",false,1);
    eatSound=new CSound("eatSound",false,1);
    mapIndex=0;
}

void MapManager::init()
{
    showLoading(false);
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            mapBlock[i][j].init();
        }
    }
}

float MapManager::ColToX(int c)
{
    return c-col/2+0.5;
}
int MapManager::XToCol(float x)
{
    return int(x+col/2);
}
float MapManager::RowToY(int r)
{
    return r-1.0*row/2+0.5;
}
int MapManager::YToRow(float y)
{
    return int(y+1.0*row/2);
}

void MapManager::showLoading(bool show)
{
    loading->SetSpriteVisible(show);
}

void MapManager::createMapBlock(int r,int c,int tp)
{
    mapBlock[r][c].setWallBlock(ColToX(c),RowToY(r),tp);
}

void MapManager::setRandMap(int index)
{
    mapIndex=index;
}

void MapManager::createMap()
{
    showLoading(true);
    init();
    int mp[row][col];
    int i,j,t1,t2;
    int x,y;
    memset(mp,0,sizeof(mp));
    for(i=0; i<row; i+=t1)
    {
        for(j=0; j<col; j+=t2)
        {
            t1=rand()%(row/10)+1;//段宽度
            t2=rand()%(col/10)+1;//段高度
            int tp=rand()%8+1;//类别
            for(x=0; x<t1; x++)
            {
                for(y=0; y<t2; y++)
                {
                    if(x+i>=0&&x+i<row&&y+j>=0&&y+j<col)
                        mp[x+i][y+j]=tp;
                }
            }
        }
    }
    randMap(curMap,row,col,mapIndex);
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(curMap[i][j])
            {
                createMapBlock(i,j,mp[i][j]);
            }
        }
    }
    insertGrass();
    //cout<<"逻辑地图生成完毕"<<endl;
    showLoading(false);
}

void MapManager::insertGrass()
{
    int i,x,y;
    int T=80;
    int walls;
    int st,ed;
    bool vis[row][col];
    memset(vis,0,sizeof(vis));
    while(T--)
    {
        st=ed=walls=0;
        x=rand()%row;
        y=rand()%col;
        position cur(x,y);
        if(!legal(x,y)||vis[x][y]||curMap[x][y]||x<8||y<8||x>=row-8||y>=col-8)
            continue;
        vis[x][y]=true;
        que[ed++]=cur;
        int d[4]= {0,1,2,3};
        while(st<ed&&walls<row*col/20)
        {
            for(i=3; i; i--)
            {
                int t=rand()%i;
                swap(d[i],d[t]);
            }
            for(i=0; i<4; i++)
            {
                x=que[st].x+dir[d[i]*2];
                y=que[st].y+dir[d[i]*2+1];
                if(legal(x,y)&&!vis[x][y]&&curMap[x][y]==0&&!(x<8&&y<8||x>=row-8&&y>=col-8)&&rand()%2)
                {
                    vis[x][y]=true;
                    que[ed++]= {x,y};
                }
                else
                {
                    walls++;
                }
            }
            st++;
        }
        for(i=0; i<ed; i++)
        {
            createMapBlock(que[i].x,que[i].y,-1);
        }
    }
}

void MapManager::damageBlock(float xx,float yy,float dmg)
{
    int i,j;
    int sy=YToRow(yy);
    int sx=XToCol(xx);
    if(legal(sy,sx)&&mapBlock[sy][sx].sprite!=NULL&&mapBlock[sy][sx].digable==true)
    {
        digSound->PlaySound();
        mapBlock[sy][sx].damage(dmg);
        return;
    }
    int mr=-1,mc=-1,r,c;
    double dis,min_dis=100;
    float x,y;
    for(i=-1; i<2; i++)
    {
        for(j=-1; j<2; j++)
        {
            r=sy+i;
            c=sx+j;
            if(legal(r,c)&&mapBlock[r][c].sprite!=NULL&&mapBlock[sy][sx].digable==true)
            {
                dis=sqrt((yy-RowToY(r))*(yy-RowToY(r))+(xx-ColToX(c))*(xx-ColToX(c)));
                if(min_dis>dis)
                {
                    min_dis=dis;
                    mr=r;
                    mc=c;
                }
            }
        }
    }
    if(legal(mr,mc))
    {
        digSound->PlaySound();
        mapBlock[mr][mc].damage(dmg);
    }
}

void MapManager::damageArea(float xx,float yy,float dmg)
{
    int i,j;
    int r=YToRow(yy);
    int c=XToCol(xx);
    explosionSound->PlaySound();
    explosion->PlayEffect(xx,yy,rand()%360);
    int x,y;
    for(i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            x=r+i-4;
            y=c+j-4;
            if(legal(x,y))
            {
                mapBlock[x][y].damage(dmg);
            }
        }
    }
}

bool MapManager::getNewTreasurePosition(float &x,float &y)
{
    /*
    int i;
    int ed=0,st=0;
    int xx,yy;
    int r=YToRow(y);
    int c=XToCol(x);
    que[ed++]={r,c};
    while(st<ed)
    {
    	for(i=0;i<4;i++)
    	{
    		xx=r+dir[i*2];
    		yy=c+dir[i*2+1];
    		if(legal(xx,yy))
    		{
    			if(mapBlock[xx][yy].sprite==NULL)
    			{
    				x=ColToX(xx);
    				y=RowToY(yy);
    				return true;
    			}
    			que[ed++]={xx,yy};
    		}
    		if(st>=ed)
    		{
    			return false;
    		}
    	}
    	st++;
    }
    return false;*/
}

void MapManager::clearAll()
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            mapBlock[i][j].destroySelf();
            curMap[i][j]=0;
        }
    }
    mapManager.showLoading(true);
}

void MapManager::PlayEatSound()
{
    eatSound->PlaySound();
}
