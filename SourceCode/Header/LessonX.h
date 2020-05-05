/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
#include "Player.h"
#include <Windows.h>
#include "Treasure.h"
#include "TreasureManager.h"
#include "PlayerManager.h"
#include "Player.h"
/////////////////////////////////////////////////////////////////////////////////

// ��Ϸ�ܹ��ࡣ��������Ϸ��ѭ������Ϸ��ʼ���������ȹ���
class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������
public:
	CGameMain();            //���캯��
	~CGameMain();           //��������

	// Get����
	int				GetGameState()											{ return m_iGameState; }

	// Set����
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }

	// ��Ϸ��ѭ����
	void			GameMainLoop( float	fDeltaTime );
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );

	float           count_time(float);
	float           count2_time(float);
	void DeleteAllSprite();
	Treasure*       FindTreasureByName(const char* szName);
	void jiemian();

	//TreasureManager* TM;
	CSprite* Map0;
	CSprite* Map1;
	CSprite* Map2;
	CSprite* Map3;
	CSprite* Map4;
	CSprite* Map5;
	CSprite* guangbiao;
	CSprite* beijing;
	int time2;
	CSound* beijing_sound;
	CSound* guangbiao_sound;

	float			Time;	//��Ϸʱ��
	float Time2;
	float Time3;
	float jl;
	float jl2;

	int panduan;
	CSprite *helpButton;
};

/////////////////////////////////////////////////////////////////////////////////
//
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_
