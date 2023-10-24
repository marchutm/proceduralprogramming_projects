#pragma once

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int  ReadData( Player*** pAllPlayers, const char* sfileName );
int  AllocAddMem( Player*** pTab, int nCurrSize );
int AllocAddMemBets( int*** pTab, int maxBets );
void FreeMem( Player*** pTab, int nPlayersNo );
int  SetSex( Player* p, char c );
int  SetDate( Player* p, int d, int m, int y );
int  SetHour( Player* p, int hh, int mm );