#include <iostream>
#include <stdio.h>
#include <stdarg.h>
using namespace std;

int Printf( const char *sFormat , ... );
int PrintfV( const char *sFormat, va_list /*va_arg/arg_list*/ );

void OutDec( int );         // znakowo wypisuje liczbe calkowita
void OutChar( char );       // wypisuje znak ( putchar() )
void OutStr( char* );       // wypisuje znakowo string
void OutDouble( double );   // wypisuje znakowo liczbe double   0.
void OutNum( int );         // wypisuje znakowo liczbe int > 0    ( rekurencyjnie!! )

int main( int argc, char* argv[] )
{
    //Funkcja ma realizowac formaty %d, %s, %f %c
    //Wypisywanie tylko znakowo
    int n = -0;
    char c = '$';
    double x = 12000000.34050000012;
    double y = -.12;
    double z = -0.5;
    char* str = ( char* )"StRing";
    

    Printf("%s\n%f%c  n=%d \\ % /\ny=%f ` ` z=%%f\n\n %0", str, x, c, n, y, z );
    return 0;
}
//*******************************************************
int Printf( const char *sFormat, ... )
{
  va_list arg;
  va_start ( arg, sFormat);
  int val = PrintfV( sFormat, arg );
  va_end( arg );
  return val;
}
//*******************************************************
int PrintfV( const char *sFormat, va_list arg_list )
{
  char c;
  while( c = *sFormat++ )
  {
    switch( c )
    {
      case '%':
      
        switch( c = *sFormat++ )
        {
          case 'd': OutDec( va_arg( arg_list, int ) );        break;
          case 'f': OutDouble( va_arg( arg_list, double) );   break;
          case 'c': OutChar( va_arg( arg_list, char ) );      break;
          case 's': OutStr( va_arg( arg_list, char* ) );      break;
          default: OutChar( '%' );
            if( !c ) return 1;
            if( c == '%' ) sFormat--;                                 
            else OutChar(c); 
          break;
        }
        break;
      case '`' :  c = '\'';
       
        //sFormat++;
        default : OutChar(c);
        break;
    }
  }
  return 0;
}
//*******************************************************
void OutDec( int x )
{
  if( !x )                                  // x dodatnie - zwyk³e wywo³anie funkcji OutNum
  {
    OutChar('0');
    return;
  }
  if( x < 0 )                            // x ujemne dopisz '-' przed znakiem
  { 
    x = -x;                                   // -x, bo OutNum wypisuje tylko liczby dodatnie
    OutChar( '-' );
  }
  OutNum(x);
}

//*******************************************************
void OutChar( char c )
{
  putchar( c );
}
//*******************************************************
void OutStr( char* str )
{
  while( *str  )
  {
    OutChar( *str++ );
  }
}
//*******************************************************
#define MAXDIG 8
void OutDouble( double x )
{
  if( x>-1 && x < 0 )
  { 
    OutChar( '-' );
  }
  OutDec( ( int ) x );                      // OutDec() by w przypadku .15 przed kropk¹ wypisaæ 0
  if( x < 0 ) x = -x; 
  OutChar( '.' );
  x = x - (int) x;
  for( int i = 0; i < MAXDIG && x>1.e-5; i++ )
  {
      OutChar( (int) ( x*=10 ) + '0' );
      x = x - ( int )x;
  }
}

//*******************************************************
void OutNum( int x )
{
  if ( x > 0 )                    
  {
    OutNum( x / 10 );
    char c = ( x % 10 ) + '0';
    OutChar( c );
  }
}