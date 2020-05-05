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
// ��ʱ֧�ֵ����ĵ�ͼ�����
#define MAX_TILES_NUM  10000

// ����Ĵ�С
#define MAX_ROOM_WIDTH  8
#define MAX_ROOM_HEIGHT 8
#define MIN_ROOM_WIDTH  4
#define MIN_ROOM_HEIGHT 4

// ��������ȵĺϼ�������
#define DEFAULT_FEATURE_NUM 1000

// �������ɷ�������ȵĲ��Դ�������������
#define MAX_TRY_TIMES  1000

// Ĭ�ϴ�������ĸ��ʣ�100-��ֵ��Ϊ�������ȵĸ��ʣ�
#define DEFAULT_CREATE_ROOM_CHANCE  70

// ���ȳ���
#define MIN_CORRIDOR_LEN   3
#define MAX_CORRIDOR_LEN   20
//-------------------------------------------------------------------------------
// ���ӿ�
enum Tile
{
  Unused, // û�õĸ��ӣ����飩
  DirtWall,  // ǽ��
  DirtFloor,  // ����ذ�
  Corridor,  // ����
  Door,  // ����
  UpStairs,  // ���
  DownStairs // ����
};
//-------------------------------------------------------------------------------
// ����
enum Direction
{
  North,  // ��
  South,  // ��
  East,  // ��
  West,  // ��
};
//-------------------------------------------------------------------------------
class Map
{
public:
	int roomNum=0;
  Map():
    xSize(0), ySize(0),
    data() { }

  // ���캯����ȫ������
  Map(int x, int y, Tile value = Unused):
    xSize(x), ySize(y),
    data(x * y, value) { }

  // ���ĳ������
  void SetCell(int x, int y, Tile celltype)
  {
    assert(IsXInBounds(x));
    assert(IsYInBounds(y));

    data[x + xSize * y] = celltype;
  }

  // ��ȡĳ������
  Tile GetCell(int x, int y) const
  {
    assert(IsXInBounds(x));
    assert(IsYInBounds(y));

    return data[x + xSize * y];
  }

  // ����һ������Ϊָ�����Ϳ�
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

  // �ж�һ���Ƿ�����Ч��Χ��
  bool IsXInBounds(int x) const
  {
    return x >= 0 && x < xSize;
  }

  // �ж�һ���Ƿ�����Ч��Χ��
  bool IsYInBounds(int y) const
  {
    return y >= 0 && y < ySize;
  }

  // �ж�һ�������Ƿ��ѱ�ʹ�ù�
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

  // �ж�һ����ͼ����Χ�Ƿ��ٽ�ĳ�ֵ�ͼ��
  bool IsAdjacent(int x, int y, Tile tile)
  {
    assert(IsXInBounds(x - 1) && IsXInBounds(x + 1));
    assert(IsYInBounds(y - 1) && IsYInBounds(y + 1));

    return (GetCell(x - 1, y) == tile || GetCell(x + 1, y) == tile ||
      GetCell(x, y - 1) == tile || GetCell(x, y + 1) == tile);
  }

  // �����ͼ
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
  // ��ͼ�ܿ��
  int xSize, ySize;
  // ȫ����ͼ������
  std::vector<Tile> data;
};
//-------------------------------------------------------------------------------
class DungeonGenerator
{
public:
  int m_nSeed;   // ���������
  int m_nXSize, m_nYSize; // ��ͼ�����
  int m_nMaxFeatures; // ��������ȵ�������
  int m_nChanceRoom;  // ��������ĸ��ʡ�0,100��
  int m_nChanceCorridor;  // �������ȵĸ��ʡ�0,100�� �ø���+��������ĸ���Ӧ�� = 100

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
    // step1: ����ͼ����
    Map map = Map(m_nXSize, m_nYSize, Unused);

    MakeDungeon(map);

    return map;
  }

private:
  // ��ȡ���int
  int GetRandomInt(int min, int max) const
  {
    return rand()%(max-min)+min;
  }

  // ��ȡ�������
  Direction GetRandomDirection() const
  {
    return Direction(rand()%4);
  }

  // ��������
  bool MakeCorridor(Map& map, int x, int y, int maxLength, Direction direction) const
  {
    assert(x >= 0 && x < m_nXSize);
    assert(y >= 0 && y < m_nYSize);

    assert(maxLength > 0 && maxLength <= std::max(m_nXSize, m_nYSize));

    // �������ȳ���
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

    // ������������Ƿ��ڵ�ͼ��
    if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
      return false;

    // ������������Ƿ��б�ռ��
    if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

    map.SetCells(xStart, yStart, xEnd, yEnd, Corridor);

    return true;
  }

  // ���췿��
  bool MakeRoom(Map& map, int x, int y, int xMaxLength, int yMaxLength, Direction direction) const
  {
    assert( xMaxLength >= MIN_ROOM_WIDTH );
    assert( yMaxLength >= MIN_ROOM_HEIGHT );

    // �����ķ�����С��4 * 4������������С
    int xLength = GetRandomInt(MIN_ROOM_WIDTH, xMaxLength);
    int yLength = GetRandomInt(MIN_ROOM_HEIGHT, yMaxLength);

    int xStart = x;
    int yStart = y;
    int xEnd = x;
    int yEnd = y;

    // ���ݷ��䳯�������������ʼ���ս�λ��
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

    // Ҫ��֤���ɵķ���һ���ĸ��㶼�ڵ�ͼ��
    if (!map.IsXInBounds(xStart) || !map.IsXInBounds(xEnd) || !map.IsYInBounds(yStart) || !map.IsYInBounds(yEnd))
      return false;

    // Ҫ��֤������ռ������δ��������ռ��
    if (!map.IsAreaUnused(xStart, yStart, xEnd, yEnd))
      return false;

    // ��Χ��ǽ
    map.SetCells(xStart, yStart, xEnd, yEnd, DirtWall);
    // �������̵ذ�
    map.SetCells(xStart + 1, yStart + 1, xEnd - 1, yEnd - 1, DirtFloor);

    return true;
  }


  // ����һ�������������
  bool MakeRoomOrCorridor(Map& map, int x, int y, int xmod, int ymod, Direction direction) const
  {
    // ���ѡ�񴴽����ͣ�����������ȣ�
    int chance = GetRandomInt(0, 100);

    if (chance <= m_nChanceRoom)
    {
      // ��������
      if (MakeRoom(map,x + xmod, y + ymod, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT, direction))
      {
        // ��ǰλ��������
        /*for(int i=-1;i<2;i++)
		{
			for(int j=-1;j<2;j++)
			{
				if(map.IsXInBounds(x+i)&&map.IsYInBounds(y+j))
					map.SetCell(x+i, y+j, Door);
			}
		}*/
		map.SetCell(x, y, Door);

        // ɾ�����Աߵ�ǽ�ڣ��Ľ�Ϊǽ��
        map.SetCell(x + xmod, y + ymod, DirtFloor);

        return true;
      }

      return false;
    }
    else
    {
      // ��������
      if (MakeCorridor(map, x + xmod, y + ymod, MAX_CORRIDOR_LEN, direction))
      {
        // ��ǰλ��������
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


  // ��ȫ��ͼ��������������ɷ��������
  bool MakeRandomFeature(Map& map) const
  {
    for( int tries = 0 ; tries != MAX_TRY_TIMES; ++tries)
    {
      // ��ȡһ��������ĵ��θ�
      int x = GetRandomInt( 1, m_nXSize - 2);
      int y = GetRandomInt( 1, m_nYSize - 2);

      // ��ȡһ�����ǽ�� ���� ����
      if (map.GetCell(x, y) != DirtWall && map.GetCell(x, y) != Corridor)
        continue;

      // ��֤��ǽ�ں����Ȳ��ٽ���
      if (map.IsAdjacent(x, y, Door))
        continue;

      // �Ҹ��ٽ�ǽ�ڻ������ȵĸ��� �����·����������
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

  // ������������
  bool MakeRandomStairs(Map& map, Tile tile) const
  {
    int tries = 0;
    int maxTries = MAX_TILES_NUM;

    for ( ; tries != maxTries; ++tries)
    {
      // �����ȡһ���Ǳ�Ե�ĵ�
      int x = GetRandomInt( 1, m_nXSize - 2);
      int y = GetRandomInt( 1, m_nYSize - 2);

      // �����Χû�еذ岢��û�����ȣ�ͨ·���Ļ���ֱ�ӷ���
      if (!map.IsAdjacent(x, y, DirtFloor) && !map.IsAdjacent(x, y, Corridor))
        continue;

      // ��Χ����������
      if (map.IsAdjacent(x, y, Door))
        continue;

      map.SetCell(x, y, tile);

      return true;
    }

    return false;
  }

  // ������ɵ���
  bool MakeDungeon(Map& map) const
  {
    // step2 : �����м䴴��һ������
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
