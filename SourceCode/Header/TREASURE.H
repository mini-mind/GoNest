#ifndef TREASURE_H
#define TREASURE_H
#include "CommonClass.h"


class Treasure : public CSprite
{
    public:
        Treasure( const char *szName );
        virtual ~Treasure();
        void setkeepTime(float time){keepTime=time;}
        void settype(int t){type=t;}
        float getkeepTime(){return keepTime;}
        int gettype(){return type;}

        virtual  void OnColTreasure(Treasure* pSprite); //精灵与精灵碰撞时处理函数

    protected:
    	float keepTime;
    private:
    	int type;
    	//friend class Myplay;
};

#endif // TREASURE_H
