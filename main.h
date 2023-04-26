#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED_ENTITY(x) (void)(x)
#define SIZE_OF_BUFFER 1024

/*----------Flags--------*/
#define F_LEFT_JUST 1
#define F_POS_INDICATOR 2
#define F_ZERO_PAD 4
#define F_ADD_HASH 8
#define F_PADDING_BLANK 16

/*---------Sizes--------- */
#define DATA_LENGTH_LONG 2
#define DATA_LENGTH_SHORT 1

/**
 * struct fmt_specifier - Struct op
 *
 * @fmt_specifier: The format.
 * @fn: The function associated.
 */
struct fmt_specifier
{
	char fmt_specifier;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt_specifier fmt_specifier_t - Struct op
 *
 * @fmt_specifier: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt_specifier fmt_specifier_t;

int _printf(const char *format, ...);
int processFmtSpecifier(const char *fmt_specifier, int *i,
		va_list list, char buffer[], int flags, int width, int precision, int size);
/*---------Function Dclarations--------*/
/*Declarations to print strings, %s and chars*/
int printCharacter(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printStr(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printPercentage(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/*Declarations to print out numbers*/
int printSgndInt(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printBin(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printUsgndInt(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printOctal_Int(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printHex_Dec(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int printHex_Upper(va_list types, char buffer[],
		int flags, int width, int precision, int size);

int printHex_Lower(va_list types, char map_to[],
		char buffer[], int flags, char flag_ch, int width, int precision, int size);

/*Print non-printable characters */
int print_Esc_Chars(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/*Print memory address */
int print_Mem_Location(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/*Handle other specifiers */
int parseFlags(const char *format, int *i);
int parseWidth(const char *format, int *i, va_list list);
int parsePrecision_Value(const char *format, int *i, va_list list);
int parseSize(const char *format, int *i);

/*Function to print string in reverse*/
int printString_Backwards(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int printEncoded_String(va_list types, char buffer[],
		int flags, int width, int precision, int size);

/* width handler */
int printSingle_Char(char c, char buffer[],
		int flags, int width, int precision, int size);
int printNumeric_Value(int is_positive, int ind, char buffer[],
		int flags, int width, int precision, int size);
int GenerateNumeric_Str(int ind, char bff[], int flags, int width, int precision,
		int length, char padd, char extra_c);
int printPointer_Value(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start);

int printUnsgnd_Int(int is_negative, int ind,
		char buffer[],
		int flags, int width, int precision, int size);

/*---------Utils-----------*/
int determinePrintable(char);
int addHex_Code(char, char[], int);
int determineNumeric(char);

long int convertTo_SignedInt(long int num, int size);
long int convertTo_UnsignedInt(unsigned long int num, int size);

#endif 
