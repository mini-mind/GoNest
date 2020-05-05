#include <Stdio.h>
#include "CommonClass.h"
#include "Treasure.h"
Treasure::Treasure( const char *szName ):CSprite(szName)
{
}

Treasure::~Treasure()
{
}

void Treasure::OnColTreasure(Treasure* pSprite)
{
}
