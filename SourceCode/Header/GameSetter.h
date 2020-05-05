#ifndef GAMESETTER_H
#define GAMESETTER_H
#include "CommonClass.h"

class GameSetter
{
	public:
		GameSetter();
		void showSetterMenu();
		void closeSetterMenu();
		void endCurrentGame();
		void changeBackSound(float x);
		void changeEffectSound(float x);
		bool endBeClick(float,float);
		bool backBarBeClick(float,float);
		bool effectBarBeClick(float,float);

		void showHowToPlay();
		void closeHowToPlay();

		void leftWin();
		void rightWin();
		void returnMainMenu();
	protected:
	private:
		CSprite *endButtun;
		CSprite *background;
		CSprite *backSoundBar;
		CSprite *effectSoundBar;

		CSprite *helpMenu;
		CSprite *leftWinMenu;
		CSprite *rightWinMenu;
};

extern GameSetter gameSetter;
#endif // GAMESETTER_H
