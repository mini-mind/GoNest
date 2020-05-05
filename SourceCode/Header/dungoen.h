#ifndef DUNGOEN_H_INCLUDED
#define DUNGOEN_H_INCLUDED

// Author: FreeKnight 2014-09-02
//#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <ctime>
//-------------------------------------------------------------------------------
// 暂时支持的最大的地图块个数
#define MAX_TILES_NUM  10000

// 房间的大小
#define MAX_ROOM_WIDTH  8
#define MAX_ROOM_HEIGHT 8
#define MIN_ROOM_WIDTH  4
#define MIN_ROOM_HEIGHT 4

// 房间和走廊的合计最大个数
#define DEFAULT_FEATURE_NUM 1000

// 尝试生成房间和走廊的测试次数（即步长）
#define MAX_TRY_TIMES  1000

// 默认创建房间的概率（100-该值则为创建走廊的概率）
#define DEFAULT_CREATE_ROOM_CHANCE  70

// 走廊长度
#define MIN_CORRIDOR_LEN   3
#define MAX_CORRIDOR_LEN   20
//-------------------------------------------------------------------------------
// 格子块
enum Tile
{
  Unused, // 没用的格子（土块）
  DirtWall,  // 墙壁
  DirtFloor,  // 房间地板
  Corridor,  // 走廊
  Door,  // 房门
  UpStairs,  // 入口
  DownStairs // 出口
};
//-------------------------------------------------------------------------------
// 朝向
enum Direction
{
  North,  // 北
  South,  // 南
  East,  // 东
  West,  // 西
};
//-------------------------------------------------------------------------------
class Map
{
public:
	int roomNum=0;
  Map():
    xSize(0), ySize(0),
    data() { }

  // 构造函数，全屏填土
  Map(int x, int y, Tile value = Unused):
    xSize(x), ySize(y),
    data(x * y, value) { }

  // 填充某块类型
  void SetCell(int x, int y, Tile celltype)
  {
    assert(IsXInBounds(x));
    assert(IsYInBounds(y));

    data[x + xSize * y] = celltype;
  }

  // 获取某块类型
  Tile GetCell(int x, int y) const
  {
    assert(IsXInBounds(x));
    assert(IsYInBounds(y));

    return data[x + xSize * y];
  }

  // 设置一块区域为指定类型块
  void SetCells(int xStart, int yStart, int xEnd, int yEnd, Tile cellType)
  {
    assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
    assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

    assert(xStart <= xEnd);
    assert(yStart <= yEnd);

    for (int y = yStart; y != yEnd + 1; ++y)
    {
      for (int x = xStart; x != xEnd + 1; ++x)
      {
        SetCell(x, y, cellType);
      }
    }
  }

  // 判断一块是否在有效范围内
  bool IsXInBounds(int x) const
  {
    return x >= 0 && x < xSize;
  }

  // 判断一块是否在有效范围内
  bool IsYInBounds(int y) const
  {
    return y >= 0 && y < ySize;
  }

  // 判断一个区域是否已被使用过
  bool IsAreaUnused(int xStart, int yStart, int xEnd, int yEnd)
  {
    assert(IsXInBounds(xStart) && IsXInBounds(xEnd));
    assert(IsYInBounds(yStart) && IsYInBounds(yEnd));

    assert(xStart <= xEnd);
    assert(yStart <= yEnd);

    for (int y = yStart; y != yEnd + 1; ++y)
    {
      for (int x = xStart; x != xEnd + 1; ++x)
      {
        if (GetCell(x, y) != Unused)
        {
          return false;
        }
      }
    }

    return true;
  }

  // 判断一个地图块周围是否临接某种地图块
  bool IsAdjacent(int x, int y, Tile tile)
  {
    assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
    assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));

    return (GetCell(x - 1, y) == tile || GetCell(x + 1, y) == tile ||
      GetCell(x, y - 1) == tile || GetCell(x, y + 1) == tile);
  }

  // 输出地图
  void Print(void *mp,int row,int col) const
  {
    for (int y = 0; y != ySize; y++)
    {
      for (int x = 0; x != xSize; x++)
      {
        switch(GetCell(x, y))
        {
        case Unused:
          *((int*)mp+col*y+x)=1;
          break;
        case DirtWall:
          *((int*)mp+col*y+x)=1;
          break;
        case DirtFloor:
          *((int*)mp+col*y+x)=0;
          break;
        case Corridor:
          *((int*)mp+col*y+x)=0;
          break;
        case Door:
          *((int*)mp+col*y+x)=0;
          break;
        case UpStairs:
          *((int*)mp+col*y+x)=0;
          break;
        case DownStairs:
          *((int*)mp+col*y+x)=0;
          break;
        };
      }

      //std::cout << std::endl;
    }

    //std::cout << std::endl;
  }

private:
  // 地图总宽高
  int xSize, ySize;
  // 全部地图块数据
  std::vector<Tile> data;
};
//-------------------------------------------------------------------------------
class DungeonGenerator
{
public:
  int m_nSeed;   // 随机数种子
  int m_nXSize, m_nYSize; // 地图最大宽高
  int m_nMaxFeatures; // 房间和走廊的最大个数
  int m_nChanceRoom;  // 创建房间的概率【0,100】
  int m_nChanceCorridor;  // 创建走廊的概率【0,100】 该概率+创建房间的概率应当 = 100

  //typedef std::mt19937 RngT;
public:
  DungeonGenerator( int XSize, int YSize ):
    m_nSeed(time(NULL)),
    m_nXSize( XSize ), m_nYSize( YSize ),
    m_nMaxFeatures( DEFAULT_FEATURE_NUM ),
    m_nChanceRoom( DEFAULT_CREATE_ROOM_CHANCE )
  {
    m_nChanceCorridor = 100 - m_nChanceRoom;
  }

  Map Generate()
  {
    assert( m_nMaxFeatures > 0 && m_nMaxFeatures <= DEFAULT_FEATURE_NUM);
    assert( m_nXSize > 3 );
    assert( m_nYSize > 3 );

  	srand(time(NULL));
    // step1: 满地图填土
    Map map = Map(m_nXSize, m_nYSize, Unused);

    MakeDungeon(map);

    return map;
  }

private:
  // 获取随机int
  int GetRandomInt(int min, int max) const
  {
    return rand()%(max-min)+min;
  }

  // 获取随机方向
  Direction GetRandomDirection() const
  {
    return Direction(rand()%4);
  }

  // 创建走廊
  bool MakeCorridor(Map& map, int x, int y, int maxLength, Direction direction) const
  {
    assert(x >= 0 && x < m_nXSize);
    assert(y >= 0 && y < m_nYSize);

    assert(maxLength > 0 && maxLength <= std::max(m_nXSize, m_nYSize));

    // 设置走廊长度
    int length = GetRandomInt(MIN_CORRIDOR_LEN, maxLength);

    int xStart = x;
    int yStart = y;

    int xEnd = x;
    int yEnd = y;

    if (direction == North)
      yStart = y - length;
    else if (direction == East)
      xEnd = x + length;
    else if (direction == South)
      yEnd = y + length;
    else if (direction == West)
      xStart = x - length;

    // 检查整个走廊是否在地图内
    if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
      return false;

    // 检查走廊区域是否有被占用
    if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

    map.SetCells(xStart, yStart, xEnd, yEnd, Corridor);

    return true;
  }

  // 创造房间
  bool MakeRoom(Map& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction) const
  {
    assert( xMaxLength >= MIN_ROOM_WIDTH );
    assert( yMaxLength >= MIN_ROOM_HEIGHT );

    // 创建的房间最小是4 * 4，随机出房间大小
    int xLength = GetRandomInt(MIN_ROOM_WIDTH, xMaxLength);
    int yLength = GetRandomInt(MIN_ROOM_HEIGHT, yMaxLength);

    int xStart = x;
    int yStart = y;
    int xEnd = x;
    int yEnd = y;

    // 根据房间朝向随机出房间起始和终结位置
    if (direction == North)
    {
      yStart = y - yLength;
      xStart = x - xLength / 2;
      xEnd = x + (xLength + 1) / 2;
    }
    else if (direction == East)
    {
      yStart = y - yLength / 2;
      yEnd = y + (yLength + 1) / 2;
      xEnd = x + xLength;
    }
    else if (direction == South)
    {
      yEnd = y + yLength;
      xStart = x - xLength / 2;
      xEnd = x + (xLength + 1) / 2;
    }
    else if (direction == West)
    {
      yStart = y - yLength / 2;
      yEnd = y + (yLength + 1) / 2;
      xStart = x - xLength;
    }

    // 要保证生成的房间一定四个点都在地图中
    if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
      return false;

    // 要保证房间所占用土地未被其他地占用
    if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

    // 周围种墙
    map.SetCells(xStart, yStart, xEnd, yEnd, DirtWall);
    // 房间内铺地板
    map.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, DirtFloor);

    return true;
  }


  // 创建一个房间或者走廊
  bool MakeRoomOrCorridor(Map& map, int x, int y, int xmod, int ymod, Direction direction) const
  {
    // 随机选择创建类型（房间或者走廊）
    int chance = GetRandomInt(0, 100);

    if (chance <= m_nChanceRoom)
    {
      // 创建房间
      if (MakeRoom(map,x + xmod, y + ymod, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, direction))
      {
        // 当前位置设置门
        /*for(int i=-1;i<2;i++)
		{
			for(int j=-1;j<2;j++)
			{
				if(map.IsXInBounds(x+i)&&map.IsYInBounds(y+j))
					map.SetCell(x+i, y+j, Door);
			}
		}*/
		map.SetCell(x, y, Door);

        // 删除门旁边的墙壁，改建为墙壁
        map.SetCell(x + xmod, y + ymod, DirtFloor);

        return true;
      }

      return false;
    }
    else
    {
      // 创建走廊
      if (MakeCorridor(map, x + xmod, y + ymod, MAX_CORRIDOR_LEN, direction))
      {
        // 当前位置设置门
        /*for(int i=-1;i<2;i++)
		{
			for(int j=-1;j<2;j++)
			{
				if(map.IsXInBounds(x+i)&&map.IsYInBounds(y+j))
					map.SetCell(x+i, y+j, Door);
			}
		}*/
		map.SetCell(x, y, Door);

        return true;
      }

      return false;
    }
  }


  // 对全地图进行随机处理生成房间和走廊
  bool MakeRandomFeature(Map& map) const
  {
    for( int tries = 0 ; tries != MAX_TRY_TIMES; ++tries)
    {
      // 获取一个有意义的地形格
      int x = GetRandomInt( 1, m_nXSize - 2);
      int y = GetRandomInt( 1, m_nYSize - 2);

      // 获取一个随机墙壁 或者 走廊
      if (map.GetCell(x, y) != DirtWall && map.GetCell(x, y) != Corridor)
        continue;

      // 保证该墙壁和走廊不临接门
      if (map.IsAdjacent(x, y, Door))
        continue;

      // 找个临接墙壁或者走廊的格子 创建新房间或者走廊
      if (map.GetCell(x, y+1) == DirtFloor || map.GetCell(x, y+1) == Corridor)
      {
        if (MakeRoomOrCorridor(map, x, y, 0, -1, North))
          return true;
      }
      else if (map.GetCell(x-1, y) == DirtFloor || map.GetCell(x-1, y) == Corridor)
      {
        if (MakeRoomOrCorridor(map,  x, y, 1, 0, East))
          return true;
      }
      else if (map.GetCell(x, y-1) == DirtFloor || map.GetCell(x, y-1) == Corridor)
      {
        if (MakeRoomOrCorridor(map,  x, y, 0, 1, South))
          return true;
      }
      else if (map.GetCell(x+1, y) == DirtFloor || map.GetCell(x+1, y) == Corridor)
      {
        if (MakeRoomOrCorridor(map,  x, y, -1, 0, West))
          return true;
      }
    }

    return false;
  }

  // 随机制作出入口
  bool MakeRandomStairs(Map& map, Tile tile) const
  {
    int tries = 0;
    int maxTries = MAX_TILES_NUM;

    for ( ; tries != maxTries; ++tries)
    {
      // 随机获取一个非边缘的点
      int x = GetRandomInt( 1, m_nXSize - 2);
      int y = GetRandomInt( 1, m_nYSize - 2);

      // 如果周围没有地板并且没有走廊（通路）的话，直接放弃
      if (!map.IsAdjacent(x, y, DirtFloor) && !map.IsAdjacent(x, y, Corridor))
        continue;

      // 周围不允许有门
      if (map.IsAdjacent(x, y, Door))
        continue;

      map.SetCell(x, y, tile);

      return true;
    }

    return false;
  }

  // 随机生成地牢
  bool MakeDungeon(Map& map) const
  {
    // step2 : 在正中间创建一个房间
    MakeRoom(map,  m_nXSize / 2, m_nYSize / 2, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, GetRandomDirection());
    MakeRoom(map,  m_nXSize-1, m_nYSize-1, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, rand()%2?West:North);
    MakeRoom(map,  0, 0, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, rand()%2?East:South);

    for (int features = 1; features != m_nMaxFeatures; ++features)
    {
      if (!MakeRandomFeature(map))
      {
        map.roomNum=features;
        break;
      }
    }
    return true;
  }
};

#endif // DUNGOEN_H_INCLUDED
