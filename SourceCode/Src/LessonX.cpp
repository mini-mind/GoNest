/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include "PlayerManager.h"
#include "MapManager.h"
#include "BulletManager.h"
#include "GameSetter.h"
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;
PlayerManager   g_PlayerManager;
MapManager      mapManager;
BulletManager   g_BulletManager;
GameSetter gameSetter;
TreasureManager TM;
//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
    m_iGameState			=	0;
    panduan=0;
    jl=0;
    jl2=0;
    guangbiao_sound =new CSound("BlIP",false,1);
    beijing_sound=new CSound("beijing",true,1);
	helpButton=new CSprite("helpButton");
}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
    switch( GetGameState() )
    {
    // 初始化游戏，清空上一局相关数据
    case 1:
    {
        GameInit();
        SetGameState(2); // 初始化之后，将游戏状态设置为进行中
    }
    break;

    // 游戏进行中，处理各种游戏逻辑
    case 2:
    case 3:
    {
        // TODO 修改此处游戏循环条件，完成正确游戏逻辑
        if( true )
        {
            GameRun( fDeltaTime );
        }
        else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
        {
            SetGameState(0);
            GameEnd();
        }
    }
    break;

    // 游戏结束/等待按空格键开始
    case 0:
    {
        jiemian();//游戏初始化界面
        gameSetter.closeSetterMenu();
    }
    break;
    default:
        break;
    };
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
	Time=0;
	Time2=0;
	Time3=0;
	jl=0;
    jl2=0;
    mapManager.createMap();
    g_PlayerManager.createPlayer();
    TM.creat_shouhu();
    TM.creat_dingshen();
    TM.creat_zidanA();
    TM.creat_zidanB();
    TM.creat_jiasu();
    TM.Creat_nest();
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    if(m_iGameState==2||m_iGameState==3)
    {
        g_PlayerManager.flushMove();
        if(m_iGameState==2)
        {
            g_PlayerManager.UpDatePlayerTime(fDeltaTime);
            g_PlayerManager.setPM_fDelaTime(g_PlayerManager.getPM_fDelaTime()+fDeltaTime);
            count_time(fDeltaTime);
            count2_time(fDeltaTime);
        }
    }
}
//=============================================================================
//
// 本局游戏结束
void CGameMain::GameEnd()
{
    DeleteAllSprite();
    panduan=0;
    m_iGameState			=	0;
    TM.daodu_count=0;

}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
    if(m_iGameState==3)
    {
        if(gameSetter.endBeClick(fMouseX,fMouseY))
        {
            gameSetter.endCurrentGame();
            return;
        }else if(gameSetter.backBarBeClick(fMouseX,fMouseY))
        {
        	gameSetter.changeBackSound(fMouseX);
        }else if(gameSetter.effectBarBeClick(fMouseX,fMouseY))
        {
        	gameSetter.changeEffectSound(fMouseX);
        }
    }
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void CGameMain::OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	if(m_iGameState==5)
	{
		if(iKey==KEY_H)
		{
			gameSetter.returnMainMenu();
			m_iGameState=0;
			return;
		}
	}
	if(m_iGameState==4)
	{
		if(iKey==KEY_H)
		{
			gameSetter.closeHowToPlay();
			m_iGameState=0;
		}
		return;
	}
	if(m_iGameState==0&&iKey==KEY_H)
	{
		gameSetter.showHowToPlay();
		m_iGameState=4;
		return;
	}
    if(iKey==KEY_P)
    {
        if(m_iGameState==2)
        {
            gameSetter.showSetterMenu();
            SetGameState(3);
        }
        else if(m_iGameState==3)
        {
            gameSetter.closeSetterMenu();
            SetGameState(2);
        }
    }
    if(GetGameState()==0)
    {
        float x=guangbiao->GetSpritePositionX();
        float y=guangbiao->GetSpritePositionY();
        if(iKey==KEY_W)
        {
            guangbiao_sound->PlaySound();
            if(x==Map0->GetSpritePositionX()&&y==Map0->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map5->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map5->GetSpritePositionY());
            }
            else if(x==Map1->GetSpritePositionX()&&y==Map1->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map0->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map0->GetSpritePositionY());
            }
            else if(x==Map2->GetSpritePositionX()&&y==Map2->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map1->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map1->GetSpritePositionY());
            }
            else if(x==Map3->GetSpritePositionX()&&y==Map3->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map2->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map2->GetSpritePositionY());
            }
            else if(x==Map4->GetSpritePositionX()&&y==Map4->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map3->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map3->GetSpritePositionY());
            }
            else if(x==Map5->GetSpritePositionX()&&y==Map5->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map4->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map4->GetSpritePositionY());
            }
        }
        else if(iKey==KEY_S)
        {
            guangbiao_sound->PlaySound();
            if(x==Map0->GetSpritePositionX()&&y==Map0->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map1->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map1->GetSpritePositionY());
            }
            else if(x==Map1->GetSpritePositionX()&&y==Map1->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map2->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map2->GetSpritePositionY());
            }
            else if(x==Map2->GetSpritePositionX()&&y==Map2->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map3->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map3->GetSpritePositionY());
            }
            else if(x==Map3->GetSpritePositionX()&&y==Map3->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map4->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map4->GetSpritePositionY());
            }
            else if(x==Map4->GetSpritePositionX()&&y==Map4->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map5->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map5->GetSpritePositionY());
            }
            else if(x==Map5->GetSpritePositionX()&&y==Map5->GetSpritePositionY())
            {
                guangbiao->SetSpritePositionX(Map0->GetSpritePositionX());
                guangbiao->SetSpritePositionY(Map0->GetSpritePositionY());
            }
        }
        else if(iKey==KEY_J)
        {
        	helpButton->SetSpriteVisible(false);
            beijing->SetSpriteVisible(false);
            Map0->SetSpriteVisible(false);
            Map1->SetSpriteVisible(false);
            Map2->SetSpriteVisible(false);
            Map3->SetSpriteVisible(false);
            Map4->SetSpriteVisible(false);
            Map5->SetSpriteVisible(false);
            guangbiao->SetSpriteVisible(false);
            if(x==Map0->GetSpritePositionX()&&y==Map0->GetSpritePositionY())
            {
                mapManager.setRandMap(5);
            }
            else
            if(x==Map1->GetSpritePositionX()&&y==Map1->GetSpritePositionY())
            {
                mapManager.setRandMap(0);
            }
            else if(x==Map2->GetSpritePositionX()&&y==Map2->GetSpritePositionY())
            {
                //加载地图2
                mapManager.setRandMap(1);
            }
            else if(x==Map3->GetSpritePositionX()&&y==Map3->GetSpritePositionY())
            {
                //加载地图3
                mapManager.setRandMap(2);
            }
            else if(x==Map4->GetSpritePositionX()&&y==Map4->GetSpritePositionY())
            {
                //加载地图4
                mapManager.setRandMap(3);
            }
            else if(x==Map5->GetSpritePositionX()&&y==Map5->GetSpritePositionY())
            {
                //加载地图5
                mapManager.setRandMap(4);
            }
            SetGameState(1);
        }
    }
    else if(GetGameState()==2||m_iGameState==3)
    {
        //cout<<"检测到GameMain OnKeyDown"<<endl;
        g_PlayerManager.OnKeyDown(iKey);
    }
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void CGameMain::OnKeyUp( const int iKey )
{
    if(m_iGameState==2||m_iGameState==3)
    {
        g_PlayerManager.OnKeyUp(iKey);
    }
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    if(strstr(szSrcName,"bul"))
    {
        Bullet* bul=g_BulletManager.getBulletByName(szSrcName);
        if(bul!=NULL)
        {
            if(strstr(szTarName,"WALL"))
            {
                float x,y,dmg=1;
                x=bul->GetSpritePositionX();
                y=bul->GetSpritePositionY();
                dmg=bul->getHeart();
                mapManager.damageArea(x,y,dmg);
                g_BulletManager.destroyBullet(szSrcName);
            }
            if(strstr(szTarName,"rightPlayer"))
            {
                if(bul->getBulltType()==2)//若为减速子弹
                {
                    g_PlayerManager.UpDateFreezeTime(g_PlayerManager.getRightPlayer());/*更新减速子弹的减速效果结束时间*/
                    g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getRightPlayer());
                    g_BulletManager.destroyBullet(szSrcName);
                }
            }
            if(strstr(szTarName,"leftPlayer"))
            {
                if(bul->getBulltType()==2)//若为减速子弹
                {
                	//g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getLeftPlayer());
                    g_PlayerManager.UpDateFreezeTime(g_PlayerManager.getLeftPlayer());/*更新减速子弹的减速效果结束时间*/
                    g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getLeftPlayer());
                    g_BulletManager.destroyBullet(szSrcName);
                }
            }
            /*检测普通子弹碰撞*/
        }
    }
    if(strstr(szTarName,"daoju"))
    {
        Treasure* treSprite = FindTreasureByName(szTarName);
        if(treSprite!=NULL)
        {
            if((strcmp(szSrcName,"leftPlayer")==0)||(strcmp(szSrcName,"rightPlayer")==0))
            {
				mapManager.PlayEatSound();
                g_PlayerManager.OnSpriteColSprite(treSprite,szSrcName,Time);//调用角色A碰撞方法
                TM.DeleteByName(szTarName);
                TM.daodu_count--;
                cout<<TM.daodu_count<<endl;
            }
        }
    }
    if(strcmp(szSrcName,"leftPlayer")==0)
    {
        //cout<<"11"<<endl;
       if(strstr(szTarName,"nest1"))
       {
           gameSetter.leftWin();
           //cout<<"1"<<endl;
       }
    }
     if(strcmp(szSrcName,"rightPlayer")==0)
    {
        //cout<<"12"<<endl;
       if(strstr(szTarName,"nest2"))
       {
           gameSetter.rightWin();
           //cout<<"2"<<endl;
       }
    }
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}

Treasure* CGameMain::FindTreasureByName(const char* szName)//根据名字查找到对象
{
    for(int i=0; i<TM.treasurePool.size(); i++)
    {
        if(strcmp(szName,TM.treasurePool[i]->GetName()) == 0)
        {
            return TM.treasurePool[i];
        }
    }
}

float CGameMain::count_time(float time)
{
    Time+=time;
    if(Time>=5)
    {
        TM.random_treasure();
        Time=0;
        cout<<TM.daodu_count<<endl;
    }
}

void CGameMain::jiemian()
{
    if(panduan==0)
    {
        //cout<<"jiemian1"<<endl;
        Map0 =new CSprite("Map0");
        Map1 =new CSprite("Map1");
        Map2 =new CSprite("Map2");
        Map3 =new CSprite("Map3");
        Map4 =new CSprite("Map4");
        Map5 =new CSprite("Map5");
        guangbiao=new CSprite("guangbiao");
        beijing =new CSprite("beijing");

        beijing->SetSpriteVisible(true);
        Map0->SetSpriteVisible(true);
        Map1->SetSpriteVisible(true);
        Map2->SetSpriteVisible(true);
        Map3->SetSpriteVisible(true);
        Map4->SetSpriteVisible(true);
        Map5->SetSpriteVisible(true);
        guangbiao->SetSpriteVisible(true);
		helpButton->SetSpriteVisible(true);

        beijing_sound->PlaySound();
        //mapManager.createMap();
      guangbiao->SetSpritePositionX(Map0->GetSpritePositionX());
       guangbiao->SetSpritePositionY(Map0->GetSpritePositionY());
        panduan=1;
    }
}
void	CGameMain::DeleteAllSprite()
{
    g_PlayerManager.getLeftPlayer()->destroy();
    g_PlayerManager.getRightPlayer()->destroy();
    g_BulletManager.clearAll();
    mapManager.clearAll();

	while((TM.treasurePool.size())!=0)
    {
		vector<Treasure*>::iterator itr= TM.treasurePool.begin();
		Treasure* cw = *itr;
        TM.treasurePool.erase(itr);
		cw->DeleteSprite();
		delete cw;
	}
}

float CGameMain::count2_time(float time)
{
    if(jl2==1){
        Time3+=time;
        //cout<<"time3="<<Time3<<endl;
    }
    if(Time3>=5){
        if(TM.shouhub!=NULL)
        {
            TM.shouhub->DeleteSprite();
            jl2=0;
            Time3=0;
        }
    }

    if(jl==1){
        Time2+=time;
        //cout<<"time2="<<Time2<<endl;
    }
    if(Time2>=5){
        if(TM.shouhua!=NULL)
        {
            TM.shouhua->DeleteSprite();
            jl=0;
            Time2=0;
        }
    }
}
