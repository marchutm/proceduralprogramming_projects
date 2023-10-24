#pragma once
typedef struct
{
  char* sName;  // wstawic string reprezentujacy liczbe int (itoa())
  int   nKey;
} FQInfo;

#define FQINFO FQInfo

void freeInfo( const void* );