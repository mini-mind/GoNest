#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include"Player.h"
#include"MapManager.h"
#include"CommonClass.h"
class PlayerManager
{
    public:
        PlayerManager();
        void setPM_fDelaTime(float fDelaTime)
        {
            this->PM_fDelaTime=fDelaTime;
        }
        float getPM_fDelaTime()
        {
            return PM_fDelaTime;
        }
        Player* getLeftPlayer()
        {
            return leftPlayer;
        }
        Player* getRightPlayer()
        {
            return rightPlayer;
        }
        void OnKeyDown(const int iKey);
		void OnKeyUp(const int iKey);
		void UpDatePlayerTime(float fDelaTime);
		void UpDateFreezeTime(Player* player);
		void UpDateSpeedUpTime(Player* player);
		void UpDateShutTime(const char* szSrcName);
		void UpDateFreezeSpeed(Player* player);
		void createPlayer();
		//void destroyLeft();
		//void destroyRight();
		void flushMove();
		void OnPlayerColWall(const char* szSrcName,const char* szTarName);
		void OnSpriteColSprite(Treasure* treSprite,const char *szSrcName,float Time);
		void clearAll();
        virtual ~PlayerManager();
        void createDigger(char*,CSprite* &);
		void deleteDigger(CSprite* &);
    protected:
    private:
		Player *leftPlayer;
		Player *rightPlayer;
		CSprite* digger1;
        CSprite* digger2;
        float PM_fDelaTime;
};
extern PlayerManager g_PlayerManager;
#endif // PLAYERMANAGER_H
