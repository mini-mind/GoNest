#ifndef CROWMAP_H_INCLUDED
#define CROWMAP_H_INCLUDED
#include<cstring>
#include"dungoen.h"
int row,col;
int dir[8]= {-1,0,0,1,1,0,0,-1};
void test_maze(void *);//测试
void iterate_maze(void *curMap);//栅栏
void dig_maze(void *curMap);//星空
void bin_maze(void *curMap);//迷阵
void room_maze(void *curMap);//方块
void break_maze(void *curMap);//废墟
//void active_maze:动态迷宫

bool legal(int x,int y)
{
    if(x<0||x>=row||y<0||y>=col)
    {
        return false;
    }
    return true;
}

void randMap(void *curMap,int r,int c,int mapType)//
{
    row=r;
    col=c;
    int i,j;
    memset(curMap,0,sizeof(int)*r*c);
    switch(mapType%6)
    {
    case 0:
        dig_maze(curMap);
        break;
    case 1:
        bin_maze(curMap);
        break;
    case 2:
        break_maze(curMap);
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                *((int*)curMap+col*i+j)=!*((int*)curMap+col*i+j);
            }
        }
        dig_maze(curMap);
        //dig_maze(curMap);
        break;
    case 3:
        room_maze(curMap);
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                *((int*)curMap+col*i+j)-=1;
            }
        }
        bin_maze(curMap);
        break;
    case 4:
        iterate_maze(curMap);
        break;
    case 5:
        test_maze(curMap);
        break;
    }
    for(i=0; i<12; i++)
    {
        for(j=0; j<12; j++)
        {
            *((int*)curMap+c*i+j)=*((int*)curMap+c*(row-i-1)+col-j-1)=0;
        }
    }
}
////////////////////////////////////////////
void iterate_maze(void *curMap)
{
    int i,j,cnt;
    int mp[row][col];
    int buf[row][col];
    //随机点
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            mp[i][j]=rand()%2;
        }
    }
    //迭代生成通道
    int T=2;
    int x,y;
    while(T--)
    {
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                cnt=0;
                for(x=i-1; x<i+2; x++)
                {
                    for(y=j-1; y<j+2; y++)
                    {
                        if(legal(x,y)&&mp[x][y])
                            cnt++;
                    }
                }
                if(mp[i][j])
                    cnt--;
                if(mp[i][j])
                {
                    if(cnt>=4)
                    {
                        buf[i][j]=0;
                    }
                    else
                    {
                        buf[i][j]=1;
                    }
                }
                else
                {
                    if(cnt>=5||!T&&cnt<2)
                    {
                        buf[i][j]=0;
                    }
                    else
                    {
                        buf[i][j]=1;
                    }
                }
            }
        }
        memcpy(mp,buf,sizeof(mp));
    }
    //保留端点
    int w=4;
    for(i=0; i<w; i++)
    {
        for(j=0; j<w; j++)
        {
            mp[row-i-1][col-j-1]=0;
            mp[i][j]=0;
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j])
                *((int*)curMap+col*i+j)=1;
        }
    }
}
///////////////////////////////////////////
bool dig_legal(void *mp,int x,int y)
{
    int w=1,i,j;
    if(x<w||x>=row-w||y<w||y>=col-w)
    {
        return false;
    }
    w=1;
    int cnt=0;
    for(i=-w; i<=w; i++)
    {
        for(j=-w; j<=w; j++)
        {
            if(*((int *)mp+(x+i)*col+y+j)==0)
            {
                cnt++;
            }
            if(!legal(x+i,y+j))
                return false;
        }
    }
    if(cnt==9)
    {
        return false;
    }
    return true;
}
void dig(void *mp,int x,int y)
{
    int i,j;
    if(dig_legal(mp,x,y))
    {
        int w=1;
        for(i=-w; i<=w; i++)
        {
            for(j=-w; j<=w; j++)
            {
                *((int *)mp+(x+i)*col+y+j)=0;
            }
        }
        int a[4]= {0,1,2,3};
        for(i=3; i; i--)
        {
            int t=rand()%i;
            swap(a[i],a[t]);
        }
        for(i=0; i<4; i++)
        {
            int xx=dir[a[i]*2]*2+x;
            int yy=dir[a[i]*2+1]*2+y;
            //cout<<"dir:"<<x<<' '<<y<<' '<<xx<<' '<<yy<<endl;
            if(a[i]%2)
            {
                if(legal(xx-2,yy)&&!*((int *)mp+(xx-2)*col+yy))
                {
                    //cout<<1<<endl;
                    continue;
                }
                if(legal(xx+2,yy)&&!*((int *)mp+(xx+2)*col+yy))
                {
                    //cout<<2<<endl;
                    continue;
                }
            }
            else
            {
                if(legal(xx,yy-2)&&!*((int *)mp+(xx)*col+yy-2))
                {
                    //cout<<3<<endl;
                    continue;
                }
                if(legal(xx,yy+2)&&!*((int *)mp+(xx)*col+yy+2))
                {
                    //cout<<4<<endl;
                    continue;
                }
            }
            //cout<<"OK"<<endl;
            //cout<<"dig:"<<x<<' '<<y<<" to "<<x+dir[a[i]*2]<<' '<<y+dir[a[i]*2+1]<<endl;
            dig(mp,x+dir[a[i]*2],y+dir[a[i]*2+1]);
        }
    }
    //else cout<<"ilegal"<<endl;
}
void dig_maze(void *curMap)
{
    int i,j,t1,t2,x,y;
    int mp[row][col];
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            mp[i][j]=1;
        }
    }
    dig(mp,1,1);
    dig(mp,row-3,col-4);
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            mp[i][j]=mp[row-i-1][col-j-1]=0;
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j])
                *((int*)curMap+col*i+j)=1;
        }
    }
}
////////////////////////////////////////////
void openAdoor(void *mp, int x1, int y1, int x2, int y2)
{
    int pos;
    if (x1 == x2)
    {
        pos = y1 + rand()%((y2 - y1 )/2+ 1)*2;//在奇数位置开门
        *((int*)mp+x1*col+pos) = false;
    }
    else if (y1 == y2)
    {
        pos = x1 + rand()%((x2 - x1 )/2+ 1)*2;
        *((int*)mp+col*pos+y1) = false;
    }
    else
    {
        cout<<"wrong";
    }
}

void genMaze(void *mp,int x,int y,int height,int width)
{
    int xPos, yPos;
    if (height <= 2 || width <= 2)
        return;
    //横着画线，在偶数位置画线
    xPos=x+rand()%(height/2)*2+1;
    for (int i = y; i < y + width; i++)
    {
        *((int *)mp+xPos*col+i) = 1;
    }

    //竖着画一条线，在偶数位置画线
    yPos=y+rand()%(width/2)*2+1;
    for (int i = x; i < x + height; i++)
    {
        *((int *)mp+i*col+yPos) = 1;
    }

    //随机开三扇门，左侧墙壁为1，逆时针旋转
    int isClosed = rand()%(4) + 1;
    switch (isClosed)
    {
    case 1:
        openAdoor(mp, xPos + 1, yPos, x + height - 1, yPos);// 2
        openAdoor(mp, xPos, yPos + 1, xPos, y + width - 1);// 3
        openAdoor(mp, x, yPos, xPos - 1, yPos);// 4
        break;
    case 2:
        openAdoor(mp, xPos, yPos + 1, xPos, y + width - 1);// 3
        openAdoor(mp, x, yPos, xPos - 1, yPos);// 4
        openAdoor(mp, xPos, y, xPos, yPos - 1);// 1
        break;
    case 3:
        openAdoor(mp, x, yPos, xPos - 1, yPos);// 4
        openAdoor(mp, xPos, y, xPos, yPos - 1);// 1
        openAdoor(mp, xPos + 1, yPos, x + height - 1, yPos);// 2
        break;
    case 4:
        openAdoor(mp, xPos, y, xPos, yPos - 1);// 1
        openAdoor(mp, xPos + 1, yPos, x + height - 1, yPos);// 2
        openAdoor(mp, xPos, yPos + 1, xPos, y + width - 1);// 3
        break;
    default:
        break;
    }

    // 左上角
    genMaze(mp, x, y, xPos - x, yPos - y);
    // 右上角
    genMaze(mp, x, yPos + 1, xPos - x, width - yPos + y - 1);
    // 左下角
    genMaze(mp, xPos + 1, y, height - xPos + x - 1, yPos - y);
    // 右下角
    genMaze(mp, xPos + 1, yPos + 1, height - xPos + x - 1, width - yPos + y - 1);

}
void bin_maze(void *curMap)
{
    int i,j;
    int mp[row][col];
    int bf[row][col];
    int _row=(row+1)/2+1;
    int _col=(col+1)/2+1;
    int buf[_row][_col];
    memset(buf,0,sizeof(buf));
    memset(mp,0,sizeof(mp));
    swap(row,_row);
    swap(col,_col);
    genMaze(buf,0,0,row,col);
    swap(row,_row);
    swap(col,_col);
    for(i=-2; i<row; i+=2)
    {
        for(j=0; j<col; j+=2)
        {
            mp[i+2][j]=buf[(i+1)/2][(j+1)/2];
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if((legal(i-1,j)&&mp[i-1][j])&&(legal(i+1,j)&&mp[i+1][j])||(legal(i,j+1)&&mp[i][j+1])&&(legal(i,j-1)&&mp[i][j-1])||mp[i][j])
            {
                bf[i][j]=1;
            }
            else
            {
                bf[i][j]=0;
            }
        }
    }
    for(i=0; i<row; i++)
    {
        bf[i][0]=bf[i][col-1]=0;
    }
    for(i=0; i<col; i++)
    {
        bf[0][i]=bf[row-1][i]=0;
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(bf[i][j])
                *((int*)curMap+col*i+j)=1;
        }
    }
}
///////////////////////////////////////////////////////////////////////
void break_maze(void *curMap)
{
    int mp[row][col];
    int buf[row][col];
    memset(buf,0,sizeof(buf));
    memset(mp,0,sizeof(mp));
    int t=0;
    do
    {
        DungeonGenerator* pGenerator = new DungeonGenerator(col,row);
        Map mp = pGenerator->Generate();
        t=mp.roomNum;
        if(t>row*col/50)
            mp.Print(curMap,row,col);
    }
    while(t<=row*col/50);
    int i,j;
    for(i=0; i<(row+1)/2; i++)
    {
        for(j=0; j<(col+1)/2; j++)
        {
            mp[i*2][j*2]=*((int*)curMap+col*(i+row/4)+j+(col/4));
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if((!legal(i-1,j-1)||mp[i-1][j-1])&&(!legal(i+1,j-1)||mp[i+1][j-1])&&(!legal(i-1,j+1)||mp[i-1][j+1])&&(!legal(i+1,j+1)||mp[i+1][j+1]))
            {
                buf[i][j]=1;
            }
        }
    }
    memcpy(mp,buf,sizeof(mp));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            t=0;
            if(!legal(i-1,j)||mp[i-1][j])
                t++;
            if(!legal(i+1,j)||mp[i+1][j])
                t++;
            if(!legal(i,j+1)||mp[i][j+1])
                t++;
            if(!legal(i,j-1)||mp[i][j-1])
                t++;
            if(t>=rand()%3+1||mp[i][j])
            {
                buf[i][j]=1;
            }
            else
            {
                buf[i][j]=0;
            }
        }
    }
    memcpy(mp,buf,sizeof(buf));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            t=0;
            if((!legal(i-1,j)||mp[i-1][j])&&(!legal(i+1,j)||mp[i+1][j]))
                t=1;
            if((!legal(i,j+1)||mp[i][j+1])&&(!legal(i,j-1)||mp[i][j-1]))
                t=1;
            if(t||mp[i][j])
            {
                buf[i][j]=1;
            }
            else
            {
                buf[i][j]=0;
            }
        }
    }
    memcpy(mp,buf,sizeof(mp));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            t=0;
            if(!legal(i-1,j)||mp[i-1][j])
                t++;
            if(!legal(i+1,j)||mp[i+1][j])
                t++;
            if(!legal(i,j+1)||mp[i][j+1])
                t++;
            if(!legal(i,j-1)||mp[i][j-1])
                t++;
            if(t>=rand()%3+1||mp[i][j])
            {
                buf[i][j]=1;
            }
            else
            {
                buf[i][j]=0;
            }
        }
    }
    memcpy(mp,buf,sizeof(mp));
    //保留端点
    int w=4;
    for(i=0; i<w; i++)
    {
        for(j=0; j<w; j++)
        {
            mp[row-i-1][col-j-1]=0;
            mp[i][j]=0;
        }
    }
    //////////////
    /*//保证连通
    bool vis[row][col];
    position que[row*col];
    position wall_que[row*col];
    position father[row][col];
    int wlen;
    int st=0,ed=0;
    while(!vis[row-1][col-1])
    {
        //查找空地
        int a=-1,b=-1;
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                if(!mp[i][j])
                {
                    a=i,b=j;
                    break;
                }
            }
            if(a>=0&&b>=0)
                break;
        }
        memset(vis,0,sizeof(vis));
        st=ed=wlen=0;
        que[ed++]= {a,b};
        vis[a][b]=true;
        //访问空白区
        while(st<ed)
        {
            for(i=0; i<4; i++)
            {
                int x=dir[i*2]+que[st].x;
                int y=dir[i*2+1]+que[st].y;
                if(!legal(x,y))
                    continue;
                if(!vis[x][y])
                {
                    if(mp[x][y])
                    {
                        wall_que[wlen++]= {x,y};
                    }
                    else
                    {
                        que[ed++]= {x,y};
                    }
                    vis[x][y]=true;
                }
            }
            st++;
        }
        st=ed=0;
        //初始化父节点
        for(i=0; i<row; i++)
        {
            for(j=0; j<col; j++)
            {
                father[i][j]= {i,j};
            }
        }
        //寻找未访问空白区
        position noBlock[row*col];
        int block_len=0;
        while(st<wlen)
        {
            for(i=0; i<4; i++)
            {
                int x=dir[i*2]+wall_que[st].x;
                int y=dir[i*2+1]+wall_que[st].y;
                if(!legal(x,y))
                    continue;
                if(!vis[x][y])
                {
                    {
                        wall_que[wlen++]= {x,y};
                    }
                    father[x][y]= {wall_que[st].x,wall_que[st].y};
                    vis[x][y]=true;
                }
            }
            st++;
        }
        //连接区域
        w=1;
        position cur=noBlock[rand()%block_len];
        while(father[cur.x][cur.y]!=cur)
        {
            for(i=-w; i<=w; i++)
            {
                for(j=-w; j<=w; j++)
                {
                    mp[cur.x+i][cur.y+j]=0;
                }
            }
            cur=father[cur.x][cur.y];
        }
        for(i=-w; i<=w; i++)
        {
            for(j=-w; j<=w; j++)
            {

                mp[cur.x+i][cur.y+j]=0;
            }
        }
    }
    //扩宽最短通路
    memset(vis,0,sizeof(vis));
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            father[i][j]= {i,j};
        }
    }
    //寻找路径
    st=ed=0;
    que[ed++]= {0,0};
    vis[0][0]=true;
    int a[4]= {0,1,2,3};
    while(st<ed)
    {
        for(i=3; i; i--)
        {
            int t=rand()%i;
            swap(a[i],a[t]);
        }
        for(i=0; i<4; i++)
        {
            int x=dir[a[i]*2]+que[st].x;
            int y=dir[a[i]*2+1]+que[st].y;
            if(legal(x,y)&&!vis[x][y])
            {
                vis[x][y]=true;
                father[x][y]= {que[st].x,que[st].y};
                que[ed++]= {x,y};
            }
        }
        if(vis[row-1][col-1])
        {
            break;
        }
        st++;
    }
    //打开通路
    w=1;
    int x,y;
    position cur(row-1,col-1);
    while(father[cur.x][cur.y]!=cur)
    {
        int t=w;
        for(i=-t; i<=t; i++)
        {
            for(j=-t; j<=t; j++)
            {
                x=i+cur.x;
                y=j+cur.y;
                if(!legal(x,y))
                {
                    if(t==w)
                    {
                        t++;
                        i=-t;
                    }
                    continue;
                }
                mp[x][y]=0;
            }
        }
        cur=father[cur.x][cur.y];
    }*/
    /////////////
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j]==0)
                *((int*)curMap+col*i+j)=1;
        }
    }
}
////////////////////////////////////////////////////
void room_maze(void *curMap)
{
    int mp[row][col];
    int buf[row][col];
    memset(buf,0,sizeof(buf));
    memset(mp,0,sizeof(mp));
    int t=0;
    do
    {
        DungeonGenerator* pGenerator = new DungeonGenerator(col,row);
        Map mp = pGenerator->Generate();
        t=mp.roomNum;
        if(t>row*col/80)
            mp.Print(curMap,row,col);
    }
    while(t<=row*col/80);
    int i,j;
    for(i=0; i<(row+1)/2; i++)
    {
        for(j=0; j<(col+1)/2; j++)
        {
            mp[i*2][j*2]=*((int*)curMap+col*(i+row/4)+j+(col/4));
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j]||(!legal(i,j+1)||mp[i][j+1])&&(!legal(i,j-1)||mp[i][j-1])||(!legal(i-1,j)||mp[i-1][j])&&(!legal(i+1,j)||mp[i+1][j])||(!legal(i-1,j-1)||mp[i-1][j-1])&&(!legal(i+1,j-1)||mp[i+1][j-1])&&(!legal(i-1,j+1)||mp[i-1][j+1])&&(!legal(i+1,j+1)||mp[i+1][j+1]))
            {
                buf[i][j]=1;
            }
        }
    }
    memcpy(mp,buf,sizeof(buf));//保留端点
    int w=4;
    for(i=0; i<w; i++)
    {
        for(j=0; j<w; j++)
        {
            mp[row-i-1][col-j-1]=0;
            mp[i][j]=0;
        }
    }
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j]==0)
                *((int*)curMap+col*i+j)=1;
        }
    }
}
/////////////////////////////////////////////////
void test_maze(void *curMap)
{
    int i,j;
    int mp[row][col];
    memset(mp,0,sizeof(mp));
    memset(curMap,0,sizeof(mp));

    for(row=0; row<75; row++)
    {
        for(col=0; col<100; col++)
        {
            if((row==5||row==70)&&(col>=15&&col<=30||col>=40&&col<=60||col>=70&&col<=85))
                mp[row][col]=1;
            if(row>5&&row<=20&&(col==15||col==30||col==40||col==60||col==70||col==85))
                mp[row][col]=1;
            if((row==30||row==45)&&(col>=5&&col<=30||col>=40&&col<=60||col>=70&&col<=95))
                mp[row][col]=1;
            if(row>30&&row<45&&(col==5||col==40||col==60||col==95))
                mp[row][col]=1;
            if(row>=55&&row<70&&(col==15||col==30||col==40||col==60||col==70||col==85))
                mp[row][col]=1;
        }
    }

/*
	int cnt=0;
    for(i=0;i<=row/2;i++)
	{
		for(j=0;j<=col/2;j++)
		{
			if(rand()%100==0)
			{
				if(cnt>80)
				{
					break;
				}
				if(rand()%2)
				{
					int xx=rand()%(col/3*2);
					for(int t=j;t<=xx;t++)
					{
						mp[i][t]=1;
						cnt++;
						if(cnt>80)
						{
							break;
						}
					}
				}else
				{
					int yy=rand()%(row/3*2);
					for(int t=i;t<=yy;t++)
					{
						mp[t][j]=1;
					}
				}
			}
			mp[row-i-1][col-j-1]=mp[row-i-1][j]=mp[i][col-j-1]=mp[i][j];
		}
	}
*/

    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(mp[i][j])
                *((int*)curMap+col*i+j)=1;
        }
    }
}
#endif // CROWMAP_H_INCLUDED
