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
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
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
// ��������
CGameMain::~CGameMain()
{
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
    switch( GetGameState() )
    {
    // ��ʼ����Ϸ�������һ���������
    case 1:
    {
        GameInit();
        SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
    }
    break;

    // ��Ϸ�����У����������Ϸ�߼�
    case 2:
    case 3:
    {
        // TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
        if( true )
        {
            GameRun( fDeltaTime );
        }
        else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
        {
            SetGameState(0);
            GameEnd();
        }
    }
    break;

    // ��Ϸ����/�ȴ����ո����ʼ
    case 0:
    {
        jiemian();//��Ϸ��ʼ������
        gameSetter.closeSetterMenu();
    }
    break;
    default:
        break;
    };
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
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
// ÿ����Ϸ������
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
// ������Ϸ����
void CGameMain::GameEnd()
{
    DeleteAllSprite();
    panduan=0;
    m_iGameState			=	0;
    TM.daodu_count=0;

}
//==========================================================================
//
// ����ƶ�
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseMove( const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// �����
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
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
// ��굯��
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
void CGameMain::OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{

}
//==========================================================================
//
// ���̰���
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
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
                //���ص�ͼ2
                mapManager.setRandMap(1);
            }
            else if(x==Map3->GetSpritePositionX()&&y==Map3->GetSpritePositionY())
            {
                //���ص�ͼ3
                mapManager.setRandMap(2);
            }
            else if(x==Map4->GetSpritePositionX()&&y==Map4->GetSpritePositionY())
            {
                //���ص�ͼ4
                mapManager.setRandMap(3);
            }
            else if(x==Map5->GetSpritePositionX()&&y==Map5->GetSpritePositionY())
            {
                //���ص�ͼ5
                mapManager.setRandMap(4);
            }
            SetGameState(1);
        }
    }
    else if(GetGameState()==2||m_iGameState==3)
    {
        //cout<<"��⵽GameMain OnKeyDown"<<endl;
        g_PlayerManager.OnKeyDown(iKey);
    }
}
//==========================================================================
//
// ���̵���
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
void CGameMain::OnKeyUp( const int iKey )
{
    if(m_iGameState==2||m_iGameState==3)
    {
        g_PlayerManager.OnKeyUp(iKey);
    }
}
//===========================================================================
//
// �����뾫����ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
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
                if(bul->getBulltType()==2)//��Ϊ�����ӵ�
                {
                    g_PlayerManager.UpDateFreezeTime(g_PlayerManager.getRightPlayer());/*���¼����ӵ��ļ���Ч������ʱ��*/
                    g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getRightPlayer());
                    g_BulletManager.destroyBullet(szSrcName);
                }
            }
            if(strstr(szTarName,"leftPlayer"))
            {
                if(bul->getBulltType()==2)//��Ϊ�����ӵ�
                {
                	//g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getLeftPlayer());
                    g_PlayerManager.UpDateFreezeTime(g_PlayerManager.getLeftPlayer());/*���¼����ӵ��ļ���Ч������ʱ��*/
                    g_PlayerManager.UpDateFreezeSpeed(g_PlayerManager.getLeftPlayer());
                    g_BulletManager.destroyBullet(szSrcName);
                }
            }
            /*�����ͨ�ӵ���ײ*/
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
                g_PlayerManager.OnSpriteColSprite(treSprite,szSrcName,Time);//���ý�ɫA��ײ����
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
// ����������߽���ײ
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{

}

Treasure* CGameMain::FindTreasureByName(const char* szName)//�������ֲ��ҵ�����
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
