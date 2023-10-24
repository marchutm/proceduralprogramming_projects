#include "Data.h"
#include "defs.h"
#include "Print.h"
#include <string.h> 
#include <malloc.h> 
#include <cstdlib>
#include <string>


void CalcStat( int* pNumsAll, Player** pPlayers, int nPlayersNo );
void Sort( Player** pPlayers, int nPlayersNo );                       // sortuje po nazwisko + imie (jesli nazwisko ident)
int CmpStr( char* s1, char* s2 );                                     // porownanie stringow
void HeapCheck();

//*************************************************************************************************************
int main( int argc, char* argv[] )      // Parametrem progrmu jest plik tekstowy z zakladami
{
  if ( argc != 2)
  {
    printf( "Bledna liczba argumentow\n" );
    return 2;
  }

  // definicja dynamicznej tablicy typu Player** (tabl wsk do graczy)

  Player** pPlayers = NULL;                           

  // zdefiniowac zmienna dla pamiatania ilosci wczytanych danych (ilosci gracczy)
  int nPlayers = ReadData( &pPlayers, argv[ 1 ] );
  if ( !nPlayers )
  {
    printf( "Error: No Data Loaded!\n" );
    return 2;
  }

  // sprawdzenie stosu

  HeapCheck();

  // definicja tablicy dla pamiatania statystyk dla wyboru 6 z 49                 (tak jak w Lotto)

  int pStatistics[ 49 ] = { 0 };

  // przetwarzanie danych
  // obliczenie statystyk 

  CalcStat( pStatistics, pPlayers, nPlayers );

  // posortowac ze wzgledu na nazwisko i imie(przestawiac wskazniki w tablicy)

  Sort( pPlayers, nPlayers );

  // wydrukowac dane do pliku - wyniki.txt

  PrintResults( pStatistics, pPlayers, nPlayers );

  //zwolnic pamiec

  FreeMem( &pPlayers, nPlayers );


  // sprawdzenie stosu

  HeapCheck();

  return 0;
}
//*************************************************************************************************************
void CalcStat( int* pNumsAll, Player** pPlayers, int nPlayersNo ) 
{
  Player** p = pPlayers;
  for( int i = 0; i < nPlayersNo; i++ )               // gracze
  {
    Player* p1 = *pPlayers++;
    int** temp = p1->pBets;
    for( int j = 0; j < p1->BetsMax; j++, temp++ )   // zak³ady gracza
    {
      int* tmp = *temp;
      if( !tmp )  break;
      for( int k = 0; k < MAXBETS; k++, tmp++ )     // pojedynczy zak³ad
      {
        pNumsAll[ *tmp - 1 ]++;                     // liczba ktora obliczamy - 1(indeksy tablicy od 0)
      }
    }
  }
}
//*************************************************************************************************************
void Sort( Player** pPlayers, int nPlayersNo )                  // proste wybierania
{
  for( int i = 0; i < nPlayersNo - 1; i++ )
  {
    Player* min = pPlayers[ i ];
    int x = i;

    for ( int j = i + 1; j < nPlayersNo; j++ )
    {// jesli nazwisko takie same to sprawdza imie
      if ( ( CmpStr( pPlayers[ j ]->sSName, min->sSName ) ) < 0
        || ( CmpStr( pPlayers[ j ]->sSName, min->sSName ) == 0 && ( ( CmpStr( pPlayers[ j ]->sFName, min->sFName ) ) < 0 ) ) )
      {
        min = pPlayers[ j ];
        x = j;
      }
    }
    pPlayers[ x ] = pPlayers[ i ];
    pPlayers[ i ] = min;
  }
}
//*************************************************************************************************************
int CmpStr( char* s1, char* s2 )
{  
  char* str1 = ( char* )calloc( strlen( s1 ) + 1, sizeof( char ) );
  char* str2 = ( char* )calloc( strlen( s2 ) + 1, sizeof( char ) );
  strcpy( str1, s1 );
  strcpy( str2, s2 );
  _strlwr( str1 );  // na DUZE ROBI _strupr()
  _strlwr( str2 );

  int res = strcmp( str1, str2 );

  free( str1 );
  free( str2 );

  return res;
}
//*************************************************************************************************************
void HeapCheck()
{
  int heapstatus = _heapchk();
  switch( heapstatus )
  {
  case _HEAPOK:
    printf( " OK - heap is fine\n\n" );
    break;
  case _HEAPEMPTY:
    printf( " OK - heap is empty\n\n" );
    break;
  case _HEAPBADBEGIN:
    printf( "ERROR - bad start of heap\n\n" );
    break;
  case _HEAPBADNODE:
    printf( "ERROR - bad node in heap\n\n" );
    break;
  }
}