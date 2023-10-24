#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix( double** pTabD, double** pTab, int nDim );


//***********************************************************************************
int CreateMatrix( double*** pTab, int nDim )
{
	*pTab = ( double** )malloc( nDim * sizeof( double* ) );														 // alokacja tablicy wsk�nik�w na wierszye
	if( !*pTab )
	{
		return 0;
	}

	memset( *pTab, 0, nDim * sizeof( double* ) );

	double **Temp = *pTab;																														 // wska�nik do poszczeg�lnych element�w macierz

	for( int i = 0; i < nDim; i++, Temp++ )																					   // alokacja pami�ci poszczeg�lnych wierszy 
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
	double **Temp = *pTab;																														  // wska�nik do poszczeg�lnych element�w macierzy 

	for( int i = 0; i < nDim; i++ )																											// usuwa poszczeg�lne wiersze
	{
		free( *Temp++ );
	}
	free( *pTab );																																			// usuwa tablic� wska�nik�w na wiersze

	*pTab = NULL;

}
//***********************************************************************************
void TransMatrix( double** pTab, int nDim )																						 //transponowanie macierzy (na razie bez wska�nik�w)
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
void InverseMatrix( double** pInv, double** pTab, int nDim, double det )							 // macierz odwrotna, na wej�ciu obliczony wczesniej w main() wyznacznik(det)
{																																											 // A^-1 = ((A^D)^T)/det(A)
	ComplMatrix( pInv, pTab, nDim );																										 // obliczamy macierz dope�enie�
	TransMatrix( pInv, nDim );																													 // transponujemy macierz dope�nie�
	for( int i = 0; i < nDim; i++, pInv++ )
	{
		double* temp = *pInv;																															 //	wska�nik do tablicy wierszy 
		for( int j = 0; j < nDim; j++, temp++ )
		{
			*temp /= det;																																		 // dzielimy poszczeg�lne elementy macierzy przez wyznacznik
		}
	}
}
//***********************************************************************************
double Det( double** pTab, int nDim )																									 // wyznacznik rekurencyjnie 
{
	if( nDim == 1 ) return **pTab;
	if( nDim == 2 ) return **pTab * pTab[ 1 ][ 1 ] - pTab[ 0 ][ 1 ] * pTab[ 1 ][ 0 ];
	
	double** TempMatrix = NULL;																												 // korzystamy z rozwnini�cia Laplace'a wi�c potrzebujemy macierzy do obliczeni minor�w
	if( !CreateMatrix( &TempMatrix, nDim - 1 ) )																			 // rozmiar tej maciezy mniejszy o 1, bo wycianmy 1 wierszi  1 kolumne
	{
		perror( "Det allocation error\n" );
		return 0;
	}

	double det = 0;
	double x = 1;																																			 // zmienna przyjmuje warto�� 1 lub -1 w zale�no�ci kt�r� kolumne i wiersz wycinamy
	double* y = *pTab;																																 
	for( int i = 0; i < nDim; i++ )
	{
		Complement( TempMatrix, pTab, 0, i, nDim );																			 // wycianmy wiersz 0 oraz kolumne i(nast�pnie b�dzie z tego liczony minor(wyznacznik))
		det += x * Det( TempMatrix, nDim - 1) * *y++;													 
		x = -x;
	}
	DeleteMatrix( &TempMatrix, nDim - 1 );
	return det;
}
//***********************************************************************************
void LayoutEqu( double** pInv, double* pVec, double* pRes, int nDim )									 // rozwi�zuje uk�ad r�wna�
{																																											 // wektor wynikowy jest r�wny macierzy odwrotnej pomno�onej przez wczytany wektor
	for( int i = 0; i < nDim; i++, pRes++ )
	{
		double* temp = *pInv++;																														 // wska�nik na tablice wierszy
		double* temp2 = pVec;																															 // wska�nik na wektor
		for( int j = 0; j < nDim; j++, temp++, temp2++ )
		{
			*pRes +=  *temp * *temp2;																												// X=A^-1*B sumuje elementy macierzy odwrtonej pomno�one przez wektor
		}
	}
}
//***********************************************************************************
void PrintMatrix( double** pTab, int nDim )																						 // drukuje macierz 
{
	for( int i = 0; i < nDim; i++, pTab++ )
	{
		double *Temp = *pTab;																														 // wska�nik do tablicy wierszy
		for( int j = 0; j < nDim; j++ )
		{
			printf( "%.1lf ", *Temp++ );																										// wypisuje wiersz macierzy
		}
		printf( "\n" );																																		 // koniec wiersz - drukuje now� linie
	}
}
//***********************************************************************************
void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )				 // wycina wiersz i kolumne z tablicy wej�ciowej pTabI i reszte kopiuje do tablicy wyjsciowej pTabO 
{
	for( int i = 0; i < nDim; i++, pTabI++ )
	{
		if( i == nRow )		continue;																												 // pomijamy wiersz i (wiersz kt�ry jest wycinany)
		double* temp = *pTabI;				 																										 // wska�nik do element�w tablicy we
		double* temp2 = *pTabO++;																													 // wska�nik do element�w tablicy wy
		for( int l = 0; l < nDim; l++, temp++ )
		{
			if( l == nCol )		continue;																											 // pomijamy kolumne l (kolumna kt�ra jest wycinana)
			*temp2++ = *temp;																																 // do nowej tablicy zapisujemy elementy tablicy we bez wiersza i oraz kolumny l																												 
		}
	}
}
//***********************************************************************************
// oblicza macierz dopelnien pTabD na podstawie tablic wejsc pTab
void ComplMatrix( double** pTabD, double** pTab, int nDim )														 
{
	double** ComplementMatrix = NULL;											
	if( !CreateMatrix( &ComplementMatrix, nDim - 1 ) )																	 // tworzymy macierz dope�nie� o rozmiarz mniejszym o 1 od macierzy wej�ciowej
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