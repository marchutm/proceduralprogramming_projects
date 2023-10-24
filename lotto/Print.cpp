#include "Print.h"
#include <stdio.h> 

// funkcja wyswietlajaca rezultaty
void PrintResults( int* pNums49, Player** pPlayers, int nPlayersNo )
{
  FILE* fout = fopen( "wyniki.txt", "w" );                        // otwieramy plik do zapisu
  if( !fout )  
  {
    printf( "Error opening file\n" );                 // b³ad otwarcia
    return;
  }
  // wyswietlam graczy po kolei
  for( int i = 0; i < nPlayersNo; i++, pPlayers++  )
  {
    Player* pPlayer = *pPlayers; 
    fprintf( fout, " %s %s         ", pPlayer->sSName, pPlayer->sFName );             // wypisuje imie i nazwisko
    PrintSex( fout, pPlayer );    // wyisuje p³eæ
    PrintHour( fout, pPlayer );   // wypisuje godzine
    PrintDate( fout, pPlayer );   // wypisuje date
    fprintf( fout, "  " );
      fprintf( fout, "%.11s", pPlayer->Pesel );   // wypisuje pesel
    fprintf( fout, "\n" );

    SWIFT* sw = &( pPlayer->AccountData.Swift );
    IBAN* ib = &( pPlayer->AccountData.IBAN );

    fprintf( fout, " %.4s %.2s %.2s %.3s     %.2s %.2s %.10s %.16s\n", sw->InstitutionCode, sw->CountryCode,
    sw->LocalizationCode, sw->BranchCode, ib->CountryCode, ib->bban.ControlIban, ib->bban.BankCode, ib->AccountNumber );
    //fprintf( fout, "\n" );
    fprintf( fout, "--------------------------------------------------------\n" );

    // wypisuje zak³ady
    PrintBets( fout, pPlayer );
  }

  fprintf( fout, "===========================================================\n                        "
    "STATYSTYKI\n===========================================================\n" );

  // wypisuje statystki
  for( int i = 0; i < 49; i++ )
  {
    fprintf( fout, "%2d:%2d ", i + 1, *pNums49++ );
    if( !( ( i + 1 ) % 10 ) )   fprintf( fout, "\n" );            // nowa lini co 10
  }
  fclose( fout );
}
//*************************************************************************************************************
void PrintSex( FILE* fout, Player* p )          // funkcja wyswietlajaca plec gracza
{
  switch( p->Sex )
  {
    case MALE:    fprintf( fout, "*Facet* " );    break;
    case FEMALE:  fprintf( fout, "*Panienka* " ); break;
  }
}
//*************************************************************************************************************
void PrintDate( FILE* fout, Player* p )         // funkcja wyswietlajaca date dla danego gracza
{
  switch( p->BetsDate.weekDay )     // wypisuje dzieñ tygodnia
  {
    case Mon: fprintf( fout, "Mon, " ); break;
    case Tue: fprintf( fout, "Tue, " ); break;
    case Wed: fprintf( fout, "Wed, " ); break;
    case Thu: fprintf( fout, "Thu, " ); break;
    case Fri: fprintf( fout, "Fri, " ); break;
    case Sat: fprintf( fout, "Sat, " ); break;
    case Sun: fprintf( fout, "Sun, " ); break;
  }

  fprintf( fout, "%d/", p->BetsDate.nDay );       // wypisuje dzieñ 

  switch( p->BetsDate.Month )          // wypisuje miesiac
  {
    case Jan: fprintf( fout, "Jan/" ); break;
    case Feb: fprintf( fout, "Feb/" ); break;
    case Mar: fprintf( fout, "Mar/" ); break;
    case Apr: fprintf( fout, "Apr/" ); break;
    case May: fprintf( fout, "May/" ); break;
    case Jun: fprintf( fout, "Jun/" ); break;
    case Jul: fprintf( fout, "Jul/" ); break;
    case Aug: fprintf( fout, "Aug/" ); break;
    case Sep: fprintf( fout, "Sep/" ); break;
    case Oct: fprintf( fout, "Oct/" ); break;
    case Nov: fprintf( fout, "Nov/" ); break;
    case Dec: fprintf( fout, "Dec/" ); break;
  }

  fprintf( fout, "%d", p->BetsDate.nYear );       // wypisuje rok
}
//*************************************************************************************************************
void PrintHour( FILE* fout, Player* p )           // funkcja wyswietlajaca godzine dla danego gracza     
{
  fprintf( fout, "%d:", p->BetsHour.nHour );
  if ( p->BetsHour.nMin < 10 )  fprintf( fout, "0" );         // jesli liczba jest jednocyfrowa to wyswietla przed ni¹ 0
  fprintf( fout, "%d ", p->BetsHour.nMin );
}
//*************************************************************************************************************
void PrintBets( FILE* fout, Player* p )                
{
  int**  v = p->pBets;
  for( int i = 0; i < p->BetsMax; i++, v++ )     // petla - tablica wksaznikow
  {
    int* temp = *v; 
    if( !temp ) break;
    for( int j = 0; j < MAXBETS; j++, temp++ )
    {
      fprintf( fout, " %2d", *temp );         // wypisuje kolejne lementy jednego zak³adu
    }
    fprintf( fout, "\n" );        // nowa linia po jednym zak³adzie
  }
  fprintf( fout, "\n" );        // nowa linia przed kolejsnym graczem
}
//*************************************************************************************************************