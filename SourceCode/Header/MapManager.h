#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include"CommonClass.h"
#include"WallBlock.h"
#include<cstdlib>
#include<ctime>
#include "Position.h"

class MapManager
{
	public:
		MapManager();
		void init();
		//void setMap(int);
		void setRandMap(int);
		void insertGrass();
		void damageArea(float,float,float damage);
		void damageBlock(float,float,float damage);
		void showLoading(bool);
		bool getNewTreasurePosition(float&,float&);//新建宝物位置
		void createMap();
		void clearAll();
		void PlayEatSound();
	protected:
	private:
		CSprite *loading;
		void createMapBlock(int ,int ,int);
		float ColToX(int);
		float RowToY(int);
		int XToCol(float);
		int YToRow(float);
		int row;
		int col;
		int mapIndex;
		position que[7500];
		int curMap[75][100];
		WallBlock mapBlock[75][100];
		CEffect *explosion;
		CSound *explosionSound;
		CSound *digSound;
		CSound *eatSound;
};

extern MapManager mapManager;
#endif // MAPMANAGER_H
