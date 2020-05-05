#include<vector>
#include<Treasure.h>
using namespace std;
#ifndef TREASUREMANAGER_H
#define TREASUREMANAGER_H


class TreasureManager
{
    public:
        TreasureManager();
        virtual ~TreasureManager();
        Treasure* getTreasureByname(const char* szName);//�������ֲ��ҵ�����
        void DeleteByName(const char* szName);//�������ְѾ����������ɾ��
        void creat_shouhu();
        void creat_dingshen();
        void creat_zidanA();
        void creat_zidanB();
        void creat_jiasu();
        void random_treasure();
        void Creat_nest();
        friend class CGameMain;
        Treasure* nest1;
        Treasure* nest2;
        Treasure* shouhua;
       Treasure* shouhub;
        //int shouhua_P;
       // int shouhub_P;
       vector<Treasure*>	   treasurePool;//�����������

    protected:

    private:

        int shouhu_Count;
        int dingshen_Count;
        int zidanA_Count;
        int zidanB_Count;
        int jiasu_Count;
        int daodu_count;
        int nest1_Count;
        int nest2_Count;

};
extern TreasureManager TM;
#endif // TREASUREMANAGER_H
