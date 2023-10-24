#pragma once

#define MAXBETS       6					// ilosc zakladow
#define ALLOCPLAYER   3					// liczba realokowanych graczy za jednym razem ( realloc() )
#define ALLOCBET      2					// liczba realokowanych zakladow dla danego gracza
#define MAXNAME       31				// dlugosc nazwiska -30 znakow - string, Imie analogicznie
#define PESEL_DLUGOSC 11				// dlugosc peselu

#define SWIFT_INSTYTUCJA  4			// kod instytucji
#define SWIFT_KRAJ        2			// kod kraju
#define SWIFT_LOKALIZACJA 2			// kod lokalizacji lub miejscowoœci
#define SWIFT_ODDZIAL     3			// kod oddzia³u

#define BBAN_KONTROLNE   2			// kontrolne IBAN
#define BBAN_NUMER_BANKU 8			// numer rozliczeniowy banku

#define IBAN_KRAJ  2						// kod kraju
#define IBAN_KONTO 16						// account number

typedef enum { MALE, FEMALE } SexType;
typedef enum { Mon, Tue, Wed, Thu, Fri, Sat, Sun }    DayNames;
typedef enum { Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec }  MonthNames;


typedef struct
{
	char InstitutionCode[ SWIFT_INSTYTUCJA ];
	char CountryCode[ SWIFT_KRAJ ];
	char LocalizationCode[ SWIFT_LOKALIZACJA ];
	char BranchCode[ SWIFT_ODDZIAL ];
} SWIFT;

typedef struct
{
	char ControlIban[ BBAN_KONTROLNE ];
	char BankCode[ BBAN_NUMER_BANKU ];
}BBAN;

typedef struct
{
	char CountryCode[ IBAN_KRAJ ];
	BBAN bban;
	char AccountNumber[ IBAN_KONTO ];
} IBAN;


typedef struct
{
	SWIFT Swift;
	IBAN IBAN;
} Account;



typedef struct
{
	int nDay;									// numer dnia
	DayNames weekDay;					// dzien tygodnia
	MonthNames Month;					// miesiac
	int nYear;								// rok
} DateType;

typedef struct
{
	int nHour;								// godzina
	int nMin;									// minuta
} TimeType;

typedef struct
{
	char sSName[ MAXNAME ];							// nazwisko
	char sFName[ MAXNAME ];							// imie
	char Pesel[PESEL_DLUGOSC];					// pesel
	TimeType BetsHour;									// godzina zakladu
	DateType BetsDate;									// data zakladu
	SexType Sex;												// plec
	Account AccountData;								// dane konta
	int BetsMax;												// rozmiar tabl pBets      (obliczane podczas wczytywania) 
	int** pBets;												// tablica wskaznikow do zakladow (dynamicznie alokowana podczas wczytywania - realloc())
																			// Jesli na koncu nie ma zakladu to element tabl jest NULL
} Player;