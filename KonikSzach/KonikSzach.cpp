#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>

#define CHESSBOARD_SIZE 6										// rozmiar szachownicy
#define HORSE_MOVES 8												// mo¿liwe offsety ruchów

// zdefiniowac typ wyliczeniowy: od FIRST to EIGHT

enum Number {	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT } Move;

// zdefiniowac typ strukt Point (sk³adowe x i y)

typedef struct Point
{
	int x;
	int y;
}	Point;

int** createChessboard( int nDim );							// druga metoda tworzenia tablicy 2D kreuje i zeruje tablice 
void freeChessboard( int*** pChessBoard );					// zwalnia pamiêæ
void printChessBoard( int** pChessBoard, int nDim );						// wypisuje szachownice
int move( int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves );
int root( int** pChessBoard, int nDim, int x, int y, Point* pHorseMoves );

int main( int argc, char* argv[] )
{
	//odczytac ustawienie poczatkowe x0, y0 konika szachowego z parametrow main()

	if ( argc != 3 )
	{
		printf( "Usage %s <start_point_x> <start_point_y>\n", argv[ 0 ] );
		return -1;
	}

	int x = atoi( argv[ 1 ] );
	int y = atoi( argv[ 2 ] );
	

	// sprawdzenie czy poprawne

	if( x < 0 || y < 0 || x >= CHESSBOARD_SIZE || y >= CHESSBOARD_SIZE )
	{
		printf( "Startup coordinates are out of chessboard\n" );
		return -2;
	}

	//Wykreowac dynamicznie tablice kwadratow¹ o rozmiarze CHESSBOARD_SIZE

	int** pChessBoard = createChessboard( CHESSBOARD_SIZE );
	/*if( !&pChessBoard )
	{
		perror( "ERROR: pChessBoard allocation error" );
		return -3;
	}*/
	

	// zdefiniowac tablica do pamietania mozliwych offestow ruchow

	Point HorseMove[ HORSE_MOVES ] = { { -2,1 }, { -2,-1 }, { -1,2 }, { -1,-2 }, { 1,2 }, { 1,-2 }, { 2,1 }, { 2,-1 } };

	// Jezeli nie znaleziono drogi od (x0,y0) - wypisac
	// "** Nie ma mozliwosci odwiedzic jednokrotnie ka¿dego pola!!\n\n";
	

	if( !root( pChessBoard, CHESSBOARD_SIZE, x, y, HorseMove ) )											// je¿eli root zwróci 0 ( !root ) to nie mo¿na znaleŸæ drogi
	{
		printf( "** Nie ma mozliwosci odwiedzic jednokrotnie kazdego pola!!\n\n" );
		return -3;
	}

	// jesli ok to wypisac szachownice z numerami kolejnych krokow

	else	printChessBoard( pChessBoard, CHESSBOARD_SIZE );



	// zwolnic pamiec!!

	freeChessboard( &pChessBoard );
	
	return 0;
}
//**************************************************************************************************************
int** createChessboard( int nDim )
{
	int** pChessBoard = ( int** )malloc( sizeof( int* ) * nDim );						// tablica adresów do wierszy
	if( !pChessBoard )
	{
		//perror( "ERROR: allocation error" );
		return NULL;																													// zwraca NULL lub 
	}
	memset( pChessBoard, 0, sizeof( int* ) * nDim );												// ka¿dy wiersz macierzy musi byæ wyzerowany – memset()
	*pChessBoard = (int*)malloc(sizeof(int) * nDim * nDim);	// tablica o rozmiarze nDim^2
	if( !*pChessBoard )
	{
		return NULL;																													// zwraca NULL lub 
	}
	memset(*pChessBoard, 0, sizeof(int) * nDim * nDim);									// ka¿dy wiersz macierzy musi byæ wyzerowany – memset()
	int** p = pChessBoard + 1;
	int*  v = *pChessBoard + nDim;

	for( int i = 1; i < nDim; i++, v += nDim )
	{
		*p++ = v;
	}

	return pChessBoard;																											// lub adres zaalokowanej pamiêci
}
//**************************************************************************************************************
void freeChessboard( int*** pChessBoard )
{
	free( **pChessBoard );
	free( *pChessBoard );
	*pChessBoard = NULL;
}
//**************************************************************************************************************
void printChessBoard( int** pChessBoard, int nDim )
{
	for( int i = 0; i < nDim; i++ )
	{
		int* temp = *pChessBoard++;
		printf( "\n" );														// nowy wiersz - nowa linia
		for( int j = 0; j < nDim; j++ )
		{
			printf( "%d ", *temp++ );								// wypisuje poszczególne elementy
		}
	}
	printf( "\n" );
}
//**************************************************************************************************************
/* pChessBoard - szachownica (kwadratowa) - pamieta ruchy
	 nDim - rozmiar szachownicy
	 move - numer mozliwego ruchu konia szachowego (indeks pHorseMoves)
	 x, y - indeksy w tablicy skad wykonujemy kolejny ruch
	 px, py - nowe wspolrzedne (params output)
	 pHorseMoves - offsety (x i y) dla obliczenia kolejnej mozliwosci skoku konia z zadanego punktu
*/
int move( int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves )
{
	// x  y - wsporzedne skad robimy nowy ruch   obliczyc nowa pozycje skoczka
	
	*px = x + pHorseMoves[ move ].x;
	*py = y + pHorseMoves[ move ].y;

	if( *px < 0 || *py < 0 || *px >= nDim || *py >= nDim ) return 0;			// sprawdza czy nowe wspó³rzêdne nie znjaduj¹ siê poza tablic¹
	if( pChessBoard[ *px ][ *py ] > 0 )							 return 0;			// sprawdza czy konik nie by³ ju¿ na tych wspó³rzêdnych
	return 1;

}
//**************************************************************************************************************
/* pChessBoard - szachownica (kwadratowa) o romiarze nDim
	 moveNo - numer ruchu (do sprawdzenia czy juz wszystkie pola odwiedzone)
	 x, y - wspol skad robimy kolejny ruch
	 pHorseMoves - offsety (x i y) wszystkich mozliwych skokow konia z ZADANEJ pozycji
*/
int root( int** pChessBoard, int nDim, int x, int y, Point* pHorseMoves )
{
	// tabl pChessBoard pamieta droge - 0 pole nie odwiedzone  
		//                                  1..nDim^2 numer kolejnego ruchu

	// wstawic kolejny numer ruchu

	static int moveNo = 1;
	pChessBoard[ x ][ y ] = moveNo;
	//printf( "move no = %d\n", moveNo );
	if( moveNo++ == nDim * nDim )		return 1;				 // jesli koniec to zwracamy 1

		// zdefiniowac nowe pozycje x i y
		int px = x;
		int py = y;
		// sprwadzic wszystkie mozliwosci ruchu (petla od FIRST do EIGHT)
		for( int j = ONE; j <= EIGHT; j++ )																									// j - numer mo¿liwego ruchu( z offsetów HorseMove )
		{
			if ( move( pChessBoard, nDim, j, x, y, &px, &py, pHorseMoves  ) )						// jesli ruch do nowej poycji mozliwy
				if ( root( pChessBoard, nDim, px, py, pHorseMoves ) )										// to rekurencyjnie wykonac ruch moveNo+1 
					return 1;																																		  // jesli zwrocono 1 z rekurencji to zwrocic   1;
		}
		// jezeli wracamy to ustawiamy w pChessBoard[x][y] na 0 bo ten ruch byl zly
		pChessBoard[ x ][ y ] = 0;
		moveNo--;
		return 0;
}
//**************************************************************************************************************

// dla 5
// ( 0 1 ) ( 0 3 )  ( 1 0 )  ( 1 2 )
 
// dla 6
// ( 4 0 )
//
