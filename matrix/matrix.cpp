#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( double** pTabD, double** pTab, int nDim );


//***********************************************************************************
int CreateMatrix( double*** pTab, int nDim )
{
	*pTab = ( double** )malloc( nDim * sizeof( double* ) );														 // alokacja tablicy wskŸników na wierszye
	if( !*pTab )
	{
		return 0;
	}

	memset( *pTab, 0, nDim * sizeof( double* ) );

	double **Temp = *pTab;																														 // wskaŸnik do poszczególnych elementów macierz

	for( int i = 0; i < nDim; i++, Temp++ )																					   // alokacja pamiêci poszczególnych wierszy 
	{
		*Temp = ( double* )malloc( nDim * sizeof( double ));
		if( !*Temp )
		{
			return 0;
		}
		memset( *Temp, 0, nDim * sizeof( double) );
	}

	return 1; 

}
//***********************************************************************************
void DeleteMatrix( double*** pTab, int nDim )
{
	double **Temp = *pTab;																														  // wskaŸnik do poszczególnych elementów macierzy 

	for( int i = 0; i < nDim; i++ )																											// usuwa poszczególne wiersze
	{
		free( *Temp++ );
	}
	free( *pTab );																																			// usuwa tablicê wskaŸników na wiersze

	*pTab = NULL;

}
//***********************************************************************************
void TransMatrix( double** pTab, int nDim )																						 //transponowanie macierzy (na razie bez wskaŸników)
{
	double** temp1 = pTab;																															 
	for( int i = 0; i < nDim - 1; i++, temp1++ )
	{
		double* temp2 = *temp1 + i + 1;
		for( int j = i + 1 ; j < nDim ; j++, temp2++ )
		{
			double temp3 = *temp2;
			*temp2 = pTab[ j ][ i ];
			pTab[ j ][ i ] = temp3;
			/*if( i == j )	 continue;
			double temp = pTab[ i ][ j ];
			pTab[ i ][ j ] = pTab[ j ][ i ];
			pTab[ j ][ i ] = temp;*/
		}
		//i--;
	
	}
}
//***********************************************************************************
void InverseMatrix( double** pInv, double** pTab, int nDim, double det )							 // macierz odwrotna, na wejœciu obliczony wczesniej w main() wyznacznik(det)
{																																											 // A^-1 = ((A^D)^T)/det(A)
	ComplMatrix( pInv, pTab, nDim );																										 // obliczamy macierz dope³enieñ
	TransMatrix( pInv, nDim );																													 // transponujemy macierz dope³nieñ
	for( int i = 0; i < nDim; i++, pInv++ )
	{
		double* temp = *pInv;																															 //	wskaŸnik do tablicy wierszy 
		for( int j = 0; j < nDim; j++, temp++ )
		{
			*temp /= det;																																		 // dzielimy poszczególne elementy macierzy przez wyznacznik
		}
	}
}
//***********************************************************************************
double Det( double** pTab, int nDim )																									 // wyznacznik rekurencyjnie 
{
	if( nDim == 1 ) return **pTab;
	if( nDim == 2 ) return **pTab * pTab[ 1 ][ 1 ] - pTab[ 0 ][ 1 ] * pTab[ 1 ][ 0 ];
	
	double** TempMatrix = NULL;																												 // korzystamy z rozwniniêcia Laplace'a wiêc potrzebujemy macierzy do obliczeni minorów
	if( !CreateMatrix( &TempMatrix, nDim - 1 ) )																			 // rozmiar tej maciezy mniejszy o 1, bo wycianmy 1 wierszi  1 kolumne
	{
		perror( "Det allocation error\n" );
		return 0;
	}

	double det = 0;
	double x = 1;																																			 // zmienna przyjmuje wartoœæ 1 lub -1 w zale¿noœci któr¹ kolumne i wiersz wycinamy
	double* y = *pTab;																																 
	for( int i = 0; i < nDim; i++ )
	{
		Complement( TempMatrix, pTab, 0, i, nDim );																			 // wycianmy wiersz 0 oraz kolumne i(nastêpnie bêdzie z tego liczony minor(wyznacznik))
		det += x * Det( TempMatrix, nDim - 1) * *y++;													 
		x = -x;
	}
	DeleteMatrix( &TempMatrix, nDim - 1 );
	return det;
}
//***********************************************************************************
void LayoutEqu( double** pInv, double* pVec, double* pRes, int nDim )									 // rozwi¹zuje uk³ad równañ
{																																											 // wektor wynikowy jest równy macierzy odwrotnej pomno¿onej przez wczytany wektor
	for( int i = 0; i < nDim; i++, pRes++ )
	{
		double* temp = *pInv++;																														 // wskaŸnik na tablice wierszy
		double* temp2 = pVec;																															 // wskaŸnik na wektor
		for( int j = 0; j < nDim; j++, temp++, temp2++ )
		{
			*pRes +=  *temp * *temp2;																												// X=A^-1*B sumuje elementy macierzy odwrtonej pomno¿one przez wektor
		}
	}
}
//***********************************************************************************
void PrintMatrix( double** pTab, int nDim )																						 // drukuje macierz 
{
	for( int i = 0; i < nDim; i++, pTab++ )
	{
		double *Temp = *pTab;																														 // wskaŸnik do tablicy wierszy
		for( int j = 0; j < nDim; j++ )
		{
			printf( "%.1lf ", *Temp++ );																										// wypisuje wiersz macierzy
		}
		printf( "\n" );																																		 // koniec wiersz - drukuje now¹ linie
	}
}
//***********************************************************************************
void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )				 // wycina wiersz i kolumne z tablicy wejœciowej pTabI i reszte kopiuje do tablicy wyjsciowej pTabO 
{
	for( int i = 0; i < nDim; i++, pTabI++ )
	{
		if( i == nRow )		continue;																												 // pomijamy wiersz i (wiersz który jest wycinany)
		double* temp = *pTabI;				 																										 // wskaŸnik do elementów tablicy we
		double* temp2 = *pTabO++;																													 // wskaŸnik do elementów tablicy wy
		for( int l = 0; l < nDim; l++, temp++ )
		{
			if( l == nCol )		continue;																											 // pomijamy kolumne l (kolumna która jest wycinana)
			*temp2++ = *temp;																																 // do nowej tablicy zapisujemy elementy tablicy we bez wiersza i oraz kolumny l																												 
		}
	}
}
//***********************************************************************************
// oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
void ComplMatrix( double** pTabD, double** pTab, int nDim )														 
{
	double** ComplementMatrix = NULL;											
	if( !CreateMatrix( &ComplementMatrix, nDim - 1 ) )																	 // tworzymy macierz dope³nieñ o rozmiarz mniejszym o 1 od macierzy wejœciowej
	{
		perror( "Matrix alloaction error" );
		return;
	}
	for( int i = 0; i < nDim; i++, pTabD++ )
	{
		int x = ( i % 2 ) ? -1 : 1; 
		double* temp = *pTabD;
		for( int j = 0; j < nDim; j++, temp++ )
		{
			Complement( ComplementMatrix, pTab, i, j, nDim );																 // wycina macierz
			*temp = x * Det( ComplementMatrix, nDim - 1 );
			x = -x;
		}
	}
	

	DeleteMatrix( &ComplementMatrix, nDim - 1 );
}
//***********************************************************************************