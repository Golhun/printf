#include "main.h"

/**
 * printUsgndInt - Prints an unsigned number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int printUsgndInt(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = SIZE_OF_BUFFER - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);
	/* Convert the argument to the appropriate size */
	num1 = convertTo_UnsignedInt(num1, size);
	/* If the argument is 0, add '0' to the buffer */
	if (num1 == 0)
		buffer[j--] = '0';
	/* Add a null terminator to the end of the buffer */
	buffer[SIZE_OF_BUFFER - 1] = '\0';
	/* Loop through digits, and add to the buffer */
	while (num1 > 0)
	{
		buffer[j--] = (num1 % 10) + '0';
		num1 /= 10;
	}

	j++;

	return (printUnsgnd_Int(0, j, buffer, flags, width, precision, size));
}

/**
 * printOctal_Int - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printOctal_Int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = SIZE_OF_BUFFER - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);
	unsigned long int init_num = num1;

	UNUSED_ENTITY(width);
	/* Convert the number to the specified size */
	num1 = convertTo_UnsignedInt(num1, size);
	/* If the number is 0, add '0' to the buffer */
	if (num1 == 0)
		buffer[j--] = '0';

	buffer[SIZE_OF_BUFFER - 1] = '\0';
	/* Convert the number to octal and store the digits in the buffer */
	while (num1 > 0)
	{
		buffer[j--] = (num1 % 8) + '0';
		num1 /= 8;
	}

	if (flags & F_ADD_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (printUnsgnd_Int(0, j, buffer, flags, width, precision, size));
}

/**
 * printHex_Dec - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printHex_Dec(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex_Lower(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * printHex_Upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printHex_Upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (printHex_Lower(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * printHex_Lower - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int printHex_Lower(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int j = SIZE_OF_BUFFER - 2;
	unsigned long int num1 = va_arg(types, unsigned long int);
	unsigned long int init_num = num1;

	UNUSED_ENTITY(width);
	/* Convert the argument to the specified size */
	num1 = convertTo_UnsignedInt(num1, size);

	if (num1 == 0)
		buffer[j--] = '0';

	buffer[SIZE_OF_BUFFER - 1] = '\0';
	/* Convert the argument to hexadecimal and store it in the buffer */
	while (num1 > 0)
	{
		buffer[j--] = map_to[num1 % 16];
		num1 /= 16;
	}
	/* Add the "0x" prefix if the '#' flag is set and the argument is non-zero */
	if (flags & F_ADD_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (printUnsgnd_Int(0, j, buffer, flags, width, precision, size));
}
