#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

struct position
{
    int x,y;
    bool operator!=(const position p)
    {
        return p.x!=x||p.y!=y;
    }
    position() {}
    position(int x,int y)
    {
        this->x=x;
        this->y=y;
    }
};

#endif // POSITION_H_INCLUDED
