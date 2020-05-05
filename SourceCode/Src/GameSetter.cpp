#include "GameSetter.h"
#include"LessonX.h"

GameSetter::GameSetter()
{
	//ctor
	background=new CSprite("setter");
	endButtun=new CSprite("endButtun");
	backSoundBar=new CSprite("backSoundBar");
	effectSoundBar=new CSprite("effectSoundBar");
	helpMenu=new CSprite("howToPlay");
	leftWinMenu=new CSprite("leftWin");
	rightWinMenu=new CSprite("rightWin");
}
void GameSetter::showSetterMenu()
{
	CSystem::ShowCursor(true);
	background->SetSpriteVisible(true);
	background->SetSpritePosition(0,0);
	endButtun->SetSpritePosition(0,15);
	backSoundBar->SetSpritePositionY(-5);
	effectSoundBar->SetSpritePositionY(5);
	endButtun->SetSpriteVisible(true);
	backSoundBar->SetSpriteVisible(true);
	effectSoundBar->SetSpriteVisible(true);
}
void GameSetter::closeSetterMenu()
{
	CSystem::ShowCursor(false);
	background->SetSpriteVisible(false);
	background->SetSpritePosition(0,70);
	endButtun->SetSpritePosition(0,85);
	backSoundBar->SetSpritePositionY(65);
	effectSoundBar->SetSpritePositionY(75);
	endButtun->SetSpriteVisible(false);
	backSoundBar->SetSpriteVisible(false);
	effectSoundBar->SetSpriteVisible(false);
}
void GameSetter::changeBackSound(float x)
{
	if(x<-4.5){
		x=-4.5;
	}else if(x>25)
	{
		x=25;
	}
	backSoundBar->SetSpritePositionX(x);
}
void GameSetter::changeEffectSound(float x)
{
	if(x<-4.5){
		x=-4.5;
	}else if(x>25)
	{
		x=25;
	}
	effectSoundBar->SetSpritePositionX(x);
}
void GameSetter::endCurrentGame()
{
	closeSetterMenu();
	g_GameMain.SetGameState(0);
	g_GameMain.GameEnd();
	g_GameMain.time2=0;
}
bool GameSetter::endBeClick(float x,float y)
{
	return endButtun->IsPointInSprite(x,y);
}
bool GameSetter::backBarBeClick(float x,float y)
{
	return x>=-4.5&&x<=25&&y>=-7&&y<=-4;
}
bool GameSetter::effectBarBeClick(float x,float y)
{
	return x>=-4.5&&x<=25&&y>=3&&y<=6;
}

void GameSetter::showHowToPlay()
{
	helpMenu->SetSpritePosition(0,0);
}
void GameSetter::closeHowToPlay()
{
	helpMenu->SetSpritePosition(0,-125);
}
void GameSetter::leftWin()
{
	g_GameMain.GameEnd();
	leftWinMenu->SetSpritePosition(0,0);
	g_GameMain.SetGameState(5);
}
void GameSetter::rightWin()
{
	g_GameMain.GameEnd();
	rightWinMenu->SetSpritePosition(0,0);
	g_GameMain.SetGameState(5);
}
void GameSetter::returnMainMenu()
{
	leftWinMenu->SetSpritePosition(0,-125);
	rightWinMenu->SetSpritePosition(0,-125);
}
