#include <iostream>
#include <memory.h>
#include <stdlib.h>
#include "sortowania.h"

void update( int* pTab, int l, int p );
void quickSort2( int* pTab, int l, int p );

//*************************************************************************
void simpleInsertion( int* pTab, int nSize )		 // proste wstawianie
{
	for ( int i = 1; i < nSize; i++ )
	{
		int temp = pTab[ i ];
		int j = i - 1;
		while ( ( j >= 0 ) && ( pTab[ j ] > temp ) ) pTab[ j + 1 ] = pTab[ j-- ];
		pTab[ j + 1 ] = temp;
		
	}
}
//*************************************************************************
void simpleSelectionSort( int* pTab, int nSize )		// proste wybieranie
{
	for ( int i = 0; i < nSize - 1; i++ )
	{
		int x = i;
		int min = pTab[ i ];													  // minimalna wartoœæ
		for ( int j = i + 1; j < nSize; j++ )
		{
			if ( pTab[ j ] < min )
			{
				min = pTab[ j ];
				x = j;
			}
		}
		pTab[ x ] = pTab[ i ];
		pTab[ i ] = min;
	}
}
//*************************************************************************
void bubbleSort( int* pTab, int nSize )						 // b¹belkowe
{
	for ( int i = 0; i < nSize; i++ )
	{
		for ( int j = nSize - 1; j > i; j-- )					 // zaczynamy od ostatniego elementu i idzie on w gore ( babelki )
		{
			if ( pTab[ j ] < pTab[ j - 1 ] )
			{
				int temp = pTab[ j - 1 ];
				pTab[ j - 1 ] = pTab[ j ];
				pTab[ j ] = temp;
			}
		}
	}
}
//*************************************************************************
void mixedBubbleSort( int* pTab, int nSize )		   // mieszane (babelkowe)
{
	int k = nSize - 1;														   // pamiêtanie	pozycji ostaniej zmiany 
	int l = 0;																		   //	pocz¹tek zakresu
	int p = nSize - 1;															 // koniec zakresu
	do
	{
		for ( int j = p; j >= l; j-- )								 // przegl¹danie w lew¹ stronê
		{
			if ( pTab[ j - 1 ] > pTab[ j ] )
			{
				int temp = pTab[ j ];
				pTab[ j ] = pTab[ j - 1 ];
				pTab[ j - 1 ] = temp;
				k = j;
			}
		}
		l = k + 1;
		for ( int j = l; j <= p; j++ )								 // przegl¹danie w praw¹ stronê 
		{
			if ( pTab[ j - 1 ] > pTab[ j ] )
			{
				int temp = pTab[ j ];
				pTab[ j ] = pTab[ j - 1 ];
				pTab[ j - 1 ] = temp;
				k = j;
			}
		}
		p = k - 1;
	} while ( l <= p );
}
//*************************************************************************
void halfSort( int* pTab, int nSize )						 // po³ówkowe (modyfikacja wstawiania o wyszukiwanie polowkowe)  !!!!!!!!!!
{
	for ( int i = 1; i < nSize - 1; i++ )
	{
		int temp = pTab[ i ];
		int l = 0;																	 // indeks pierwszego elementu ( lewa strona )
		int p = i - 1;
		while ( l <= p )
		{
			int m = ( l + p ) / 2;										 // dzielenie przedzia³u na pó³
			if ( temp < pTab[ m ] )
			{
				p = m - 1;
			}
			else
			{
				l = m + 1;
			}
		}
		for ( int j = i - 1; j >= l; j-- )
		{
			pTab[ j + 1 ] = pTab[ j ];
		}
		pTab[ l ] = temp;
	}
}
//*************************************************************************
void heapSort( int* pTab, int nSize )							       // sortowanie stogowe ( NIE REKURENCYJNIE!!! )						
{
	
	for ( int l = ( nSize / 2 ); l >= 0; l--) update( pTab, l, nSize - 1 );
	for ( int p = nSize - 1; p > 0; p-- )
	{
		int x = pTab[ 0 ];
		pTab[ 0 ] = pTab[ p ];
		pTab[ p ] = x;
		update( pTab, 0, p - 1 );
	}
}
//*************************************************************************
void update( int* pTab, int l, int p )									// przywracanie warunku stogu, p - rozmiar tablicy
{
	if ( l >= p ) return;
	int i = l;																						// i, j para indeksów wskazuj¹cych na elementy które mog¹ byæ zamienione podczas przesiewania
	int j = 2 * i + 1;
	int x = pTab[ i ];
	while ( j <= p )
	{
		if ( j < p )
		{
			if ( pTab[ j ] < pTab[ j + 1 ] ) j++;

		}
		if ( x >= pTab[ j ] ) break;
		pTab[ i ] = pTab[ j ];
		i = j;
		j = 2 * i + 1;
	}
	pTab[ i ] = x;
}
//*************************************************************************
void quickSort( int* pTab, int nSize )							 // sortowanie szybkie ( REKURENCYJNIE )
{
	quickSort2( pTab, 0, nSize - 1 );
}
//*************************************************************************
void quickSort2( int* pTab, int l, int p )
{
	int a = l;																				 // pocz¹tek tablicy 
	int b = p;																			   // koniec tablicy
	int temp = pTab[ ( l + p ) / 2 ];
	do
	{
		while ( pTab[ a ] < temp ) a++;
		while ( temp < pTab[ b ] ) b--;
		if ( a <= b )
		{
			int temp2 = pTab[ a ];
			pTab[ a ] = pTab[ b ];
			pTab[ b ] = temp2;
			a++;
			b--; 
		}
	} while ( b > a );

	if ( l < b ) quickSort2( pTab, l, b );
	if ( a < p ) quickSort2( pTab, a, p );
}
//*************************************************************************