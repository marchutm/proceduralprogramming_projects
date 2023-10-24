#include "Data.h"
#include <stdio.h> 
#include <time.h> 
#include <malloc.h> 
#include <memory.h> 
//*************************************************************************************************************
int ReadData( Player*** pAllPlayers, const char* sfileName )
{
  
  FILE* fin = fopen( sfileName, "r" );        // otwieramy plik do czytania
  if ( !fin ) 
  {
    printf( "Error: nie udalo sie otworzyc pliku!!\n" );
    return 0;
  }
  int nData = 0;            // liczba wczytanych danych
  int maxTab = 0;            // aktualny maxym rozmiar tablicy pAllPalyers     
  Player** pDraws = *pAllPlayers;   //kopie  parametru* pAllPalyers

  char c;

  while( !feof( fin ) && (  fgetc( fin ) == '*' ) )
  {
    // jesli trzeba to realokowac
    if( nData == maxTab )
    {
      maxTab += AllocAddMem( &pDraws, nData );                // dodac do zmiennej maxym rozmiar wynik funkcji realokujacej (3- ilosc o ktora realokujemy)
      if( nData == maxTab )               // if( (ilosc wczytanych danych == maxym rozmiar)  to koniec (przerw petli)
        break;
    }

    char sex;     // plec
    int hour = 0;     // godzina
    int minute = 0;     // minuta
    int day = 0;      // dzien
    int month = 0;      // miesiac
    int year = 0;       // rok

    Player* newPlayer = pDraws[ nData ] = ( Player* )calloc( 1, sizeof( Player ) );
    if ( !newPlayer )
    {
      perror( "Error creating: no memory!" );
      break;
    }


    SWIFT* sw = &( newPlayer->AccountData.Swift );
    IBAN* ib = &( newPlayer->AccountData.IBAN );

    // wczytywac jedna instrukcja fscanf wszystkie dane opisujace gracza
    fscanf( fin, "%s %s %c %4c %2c %2c %3c %2c %2c %8c %16c %d:%d %d/%d/%d %11c", newPlayer->sSName, newPlayer->sFName, &sex,
      sw->InstitutionCode, sw->CountryCode, sw->LocalizationCode, sw->BranchCode, ib->CountryCode,
      ib->bban.ControlIban, ib->bban.BankCode, ib->AccountNumber, &hour, &minute, &day, &month, &year, newPlayer->Pesel );

    // niepowodzenie wczytania plci daty lub godziny
    if( !SetSex(newPlayer, sex ) || !SetDate( newPlayer, day, month, year ) || !SetHour( newPlayer, hour, minute ) )
    {
      perror( "Error: SetSex or SetDate or SetHour!" );
      break;
    }

    int nDraws = 0;            // wczytane zak³ady
    //int mBets = 0;             // max ilosc zaalokowanych zakladow
    fscanf(fin, "\n");
    char flag = 0;
   
    //czytanie zakladow
    while( 1 )
    {
      if( newPlayer->BetsMax == nDraws )                 // tak samo jak przy graczu
      {
        newPlayer->BetsMax += AllocAddMemBets( &(newPlayer->pBets ), nDraws );
        if( newPlayer->BetsMax == nDraws )
        {
          break;
        }
      }
      //ungetc( c, fin );

      int* temp = newPlayer->pBets[ nDraws ] = ( int* )calloc( MAXBETS, sizeof( int ) );
      if ( !temp )
      {
        printf( "Error: nie udalo sie zaalokowac pamieci dla zakladow\n" );
        break;
      }

      for( int i = 0; i < MAXBETS; i++ ) 
      {
        fscanf( fin, "%d", temp++ );
      }
      nDraws++;
      //newPlayer->BetsMax = nDraws;
      fscanf( fin, "\n" );
      if( ( c = fgetc( fin ) ) == '*' )
      {
        ungetc( c, fin ); flag = 1;
        break;
      }
      else if( feof( fin ) )
      {
        flag = 1;
        break;
      }
      else ungetc(c, fin);
    }
    ///ungetc( c, fin );
    if( !flag  )  break;
    nData++; //gracz dodany
   
  }
  *pAllPlayers = pDraws;      // przywrocic wskaznik *pAllPalyers;
  fclose( fin );            //zamknac plik 
  return nData;
}
//*************************************************************************************************************
int AllocAddMem( Player*** pTab, int nCurrSize ) 
{
  int nSize = ALLOCPLAYER + nCurrSize;      // ilosc nowo zaalokowanej pamieci na gracza
  Player** temp = ( Player** )realloc( *pTab, nSize * sizeof( Player* ) );
  if ( !temp )
  {
    printf( "Error: Brak pamieci przy realokacji gracza!\n" );
    return 0;
  }
  memset( temp + nCurrSize, 0, ALLOCPLAYER * sizeof( Player* ) );
  *pTab = temp;
  return ALLOCPLAYER;
}
//*************************************************************************************************************
int AllocAddMemBets( int*** pTab, int maxBets ) 
{
  int nSize = ALLOCBET + maxBets;     // ilosc nowo zaalokowanej pamieci na zaklad
  int** pTemp = ( int** )realloc( *pTab, nSize * sizeof( int* ) );
  if( !pTemp )
  {
    printf( "Error: Brak pamieci przy realokacji zakladu!\n" );
    return 0;
  }
  memset( pTemp + maxBets, 0, ALLOCBET * sizeof( int* ) );
  *pTab = pTemp;
  
  return ALLOCBET;
}
//*************************************************************************************************************
void FreeMem( Player*** pTab, int nPlayersNo )  
{
  Player** p = *pTab;
  for( int i = 0; i < nPlayersNo; i++, p++ )   // petla po graczach
  {
    Player* t = *p;
    int** tBets =  t->pBets;
    for( int j = 0; j < t->BetsMax; j++ )       // petla po zakladach
    {
      free( *tBets++ );     // zwalnainaie pamieci wierszy    // !!!!
    }
    free( t->pBets );     // zwalnianie pamieci pierwszego elem zakladu
    free( t );        // zwalnianie pamieci Player
  }
  free( *pTab );       // zwalnianie pamieci wskaznika na Player
  *pTab = NULL;
  }
//*************************************************************************************************************
int SetSex( Player* p, char c )           // funkcja ustawiajaca plec gracza
{

  switch( c )
  {
    case 'f':
    case 'F':    p->Sex  = FEMALE;  return 1;
    case 'm':
    case 'M':    p->Sex  = MALE;    return 1;
  }
  return 0;
}
//*************************************************************************************************************
int SetDate( Player* p, int d, int m, int y )           // funkcja ustawiajaca date zakladu
{
  if( d < 1 || d > 31 )
  {
    printf( "Bledna data - numer dnia!" );
    return 0;
  }
  if( m < 1 || m > 12 )
  {
    printf( "Bledna data - numer miesiaca!" );
    return 0;
  }
  if( y < 1990 || y > 2023 )
  {
    printf( "Bledna data - numer roku!" );
    return 0;
  }

  p->BetsDate.nDay = d;       // ustawienie dnia
	p->BetsDate.nYear = y;      // ustawienie roku

  switch( m )       // ustawienie miesiaca
  {
    case 1:  p->BetsDate.Month = Jan; break;
    case 2:  p->BetsDate.Month = Feb; break;
    case 3:  p->BetsDate.Month = Mar; break;
    case 4:  p->BetsDate.Month = Apr; break;
    case 5:  p->BetsDate.Month = May; break;
    case 6:  p->BetsDate.Month = Jun; break;
    case 7:  p->BetsDate.Month = Jul; break;
    case 8:  p->BetsDate.Month = Aug; break;
    case 9:  p->BetsDate.Month = Jan; break;
    case 10: p->BetsDate.Month = Sep; break;
    case 11: p->BetsDate.Month = Nov; break;
    case 12: p->BetsDate.Month = Dec; break;
  }

  struct tm Time;
  memset( &Time, 0, sizeof( Time ) );

  Time.tm_year = y - 1900;
  Time.tm_mday = d;
  Time.tm_mon = m - 1;
  mktime( &Time );        // funkcja obliczaj¹ca dzien tygodnia

  switch( Time.tm_wday )        // ustawienie dnia tygodnia
  {
    case 0: p->BetsDate.weekDay = Sun; break;
    case 1: p->BetsDate.weekDay = Mon; break;
    case 2: p->BetsDate.weekDay = Tue; break;
    case 3: p->BetsDate.weekDay = Wed; break;
    case 4: p->BetsDate.weekDay = Thu; break;
    case 5: p->BetsDate.weekDay = Fri; break;
    case 6: p->BetsDate.weekDay = Sat; break;
  }
  return 1;
}
//*************************************************************************************************************
int SetHour( Player* p, int hh, int mm )        // funkcja ustawiajaca godzine zakladu
{
  if( hh < 0 || hh > 23 )
  {
    printf( "Bledna godzina - godzina!" );
    return 0;
  }
  if( mm < 0 || mm > 59 )
  {
    printf( "Bledna godzina - minuta!");
    return 0;
  }
  p->BetsHour.nHour = hh;
  p->BetsHour.nMin = mm;

  return 1;
}
//*************************************************************************************************************