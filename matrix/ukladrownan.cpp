#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

#define _DEBUG_
#define DET 1e-100

void ReadData( FILE* fin, double** pMatrix, double* pVector, int nDim );
int CreateVector( double** pVec, int nDim );
void PrintVector( double* pVec, int nDim );
void DeleteVector( double** pVec );

int main( int argc, char* argv[] )
{
	// sprwdzic argumenty main
	if( argc != 2 )
	{
		printf( "Usage: %s <input_file>\n", argv[ 0 ] );
		return 1;
	}

	// odtworzyc plik do odczytu (tekstowy)

	FILE* fin = NULL;																														// wskaźnik na strukturę FILE

	if( ( fin = fopen( argv[1], "rt" ) ) == NULL )															// r - otwiera pplik do czytania, t - otwiera plik w trybie tekstowym
	{																																						// fopen zwraca NULL gdy nie może otworzyć pliku, a w przypadku poprawnego otwarcia zwraca wskaznik(fin)
		perror( "ERROR: cannot open input file\n" );
		return -1;
	}

	// odczytac rozmiar nDim

	int nDim = 0;

	
	fscanf( fin, "%d", &nDim );																									// 1argument - wskaźnik do pliku, 2argument- format, 3argument - ustawnienia regionalne do użycia(adres nDim)	
#ifdef _DEBUG_
	printf( "Wymiar macierzy wynosi: %d\n\n", nDim );
#endif

	// wykreowac macierz ukladu nDim x nDim


	double **Matrix = NULL;

	if( !CreateMatrix( &Matrix, nDim ) )
	{
		perror( "ERROR: matrix allocation error\n" );
		return -2;
	}

	// wykreowac wektor wyrazow wolnych 

	double *Vector = NULL;

	if( !CreateVector( &Vector, nDim ) )
	{
		perror( "ERROR: vector allocation error\n" );
		return -3;
	}

	// wczytac dane ( ReadData() )

	ReadData( fin, Matrix, Vector, nDim );

	//wydruk kontrolny macierzy i wektora

	#ifdef _DEBUG_
	printf( "Wczytana macierz\n\n" );
	PrintMatrix( Matrix, nDim );
	printf( "\nWczytany wektor\n\n" );
	PrintVector( Vector, nDim );
	#endif

	// obliczyć wyznacznik

	double det = Det( Matrix, nDim );
	#ifdef _DEBUG_
	printf( "\nWyznacznik: %.1f\n\n", det );
	#endif


	// sprawdzić czy wyznacznik równy 0																										
	if( fabs( det ) < DET )													// wyzbacznik może być ujemny dlatego trzeba obliczyć jego wartość bezwzględna
	{
		printf( "ERROR: Wyznacznik wczytanej macierzy wynosi 0" );
		return -4;
	}

	/*TransMatrix( Matrix, nDim );
#ifdef _DEBUG_
	printf( "\nTransponowana macierz\n\n");
	PrintMatrix( Matrix, nDim );
#endif*/

	// obrocic macierz

	double** InvMatrix = NULL;
	if( !CreateMatrix( &InvMatrix, nDim ) )
	{
		perror( "ERROR: inverse matrix allocation error\n" );
		return -5;
	}

	InverseMatrix( InvMatrix, Matrix, nDim, det );
	//wydruk kontrolny

	#ifdef _DEBUG_
	printf( "Macierz odwrotna \n\n" );
	PrintMatrix( InvMatrix, nDim );
	#endif

	// wykreowac wektor wynikowy

	double* ResVector = NULL;

	if( !CreateVector( &ResVector, nDim ) )
	{
		perror( "ERROR: result vector allocation error\n" );
		return -6;
	}

	// rozwiazac ukl

	LayoutEqu( InvMatrix, Vector, ResVector, nDim );

	// wyniki


	printf( "\nWektor wynikowy\n\n" );
	PrintVector( ResVector, nDim );

	// zwolnić pamięć

	DeleteMatrix( &Matrix, nDim );
	DeleteMatrix( &InvMatrix, nDim );
	DeleteVector( &Vector );
	DeleteVector( &ResVector );

	return 0;

}
//**********************************************************************************
void ReadData( FILE* fin, double** pMatrix, double* pVector, int nDim )								// czyta dane
{
	for( int i = 0; i < nDim; i++, pMatrix++ )
	{
		double* temp = *pMatrix;																													// wskaznik do elementów macierzy
		for( int j = 0; j < nDim; j++ )
		{
			fscanf( fin, "%lf", temp++ );																										// lf - double, zczytuje wartości macierzy
		}
		fscanf( fin, "%lf", pVector++ );																									// zczytuje wartosci wektora
	}
}
//***********************************************************************************
int CreateVector( double** pVec, int nDim ) 																					 // tworzy wektor
{
	*pVec = ( double* )malloc( nDim * sizeof( double ) );
	if( !*pVec )
	{
		return 0;
	}
	memset( *pVec, 0, nDim * sizeof( double ) );

	return 1;
}
//***********************************************************************************
void PrintVector( double* pVec, int nDim )																						// drukuje wektor
{
	for( int i =0; i < nDim; i++ )
	{
	 printf( "%.1lf\n", *pVec++ );
	}
}
//***********************************************************************************
void DeleteVector( double** pVec )																										  // usuwa wektor!!!
{
	free( *pVec );
	*pVec = NULL;
}
//***********************************************************************************