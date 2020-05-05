#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H
#include <vector>
using namespace std;
#include "Bullet.h"
using namespace std;
class BulletManager
{
    public:
        BulletManager();
        void setDir(int Dir)
        {
            this->Dir=Dir;
        }
        int getDir()
        {
            return this->Dir;
        }
        //void BulletDestroy(const char*,bool=false,int=0);
		void clearAll();
		void createOneBullet(float x,float y,Player* player);
		void OnSpriteColSprite(const char *szSrcName, const char *szTarName);
		Bullet* getBulletByName(const char* SrcName);
		void destroyBullet(const char*);
        virtual ~BulletManager();
		vector<Bullet*> bulletPool;
    protected:
    private:
        int Dir;
		int bulTemp;
};
extern BulletManager g_BulletManager;
#endif // BULLETMANAGER_H
