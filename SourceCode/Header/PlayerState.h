#ifndef PLAYERSTATE_H_INCLUDED
#define PLAYERSTATE_H_INCLUDED
struct PlayerState
{
    int BulletType;//持有子弹类型
    int BulletNum;//持有子弹数量
    int BulletHeart;//持有子弹伤害
    float shutTime;//道具定身时间
    float freezeTime;//子弹减速时间
    float speedUpTime;//加速持续时间
};


#endif // PLAYERSTATE_H_INCLUDED
