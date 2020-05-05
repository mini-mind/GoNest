#ifndef FREEZEBULLET_H
#define FREEZEBULLET_H


class FreezeBullet//:public Bullet
{
    public:
        FreezeBullet(const char* szName,const char*);
        void OnColBullet();
        virtual ~FreezeBullet();
    protected:
    private:
};

#endif // FREEZEBULLET_H
