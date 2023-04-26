#include "main.h"

/**
 * printCharacter - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printCharacter(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	/* extract the character argument from the va_list */
	char args = va_arg(types, int);
	/* call printSingle_Char() to write the character to the buffer */
	return (printSingle_Char(args, buffer, flags, width, precision, size));
}
/**
 * printStr - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printStr(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0, i;
	char *str = va_arg(types, char *);

	UNUSED_ENTITY(buffer);
	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(precision);
	UNUSED_ENTITY(size);
	/* if the string is null, set it to "(null)" */
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	} /* get the length of the string */
	while (str[len] != '\0')
		len++;
	/* if precision is specified, limit the length of the string */
	if (precision >= 0 && precision < len)
		len = precision;
	/* if the width is greater than the length of the string, add padding */
	if (width > len)
	{/* if minus flag set, left-align string */
		if (flags & F_LEFT_JUST)
		{ /* write the string */
			write(1, &str[0], len);
			for (i = width - len; i > 0; i--)
				write(1, " ", 1);
			return (width);
		} /* right-align string */
		else
		{
			for (i = width - len; i > 0; i--)
				write(1, " ", 1); /* add paddin-left */
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}
/**
 * printPercentage - Prints a percent(%) sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printPercentage(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	/* UNUSED_ENTITY() macro suppresses warnings about UNUSED_ENTITY parameters */
	UNUSED_ENTITY(types);
	UNUSED_ENTITY(buffer);
	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(precision);
	UNUSED_ENTITY(size);
	return (write(1, "%%", 1));
}

/*-----Print Int------*/
/**
 * printSgndInt - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printSgndInt(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = SIZE_OF_BUFFER - 2;
	int is_neg = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;
	/* Convert the input number to the appropriate size */
	n = convertTo_SignedInt(n, size);
	/* If the number is zero, add a '0' character to the buffer. */
	if (n == 0)
		buffer[i--] = '0';
	/* Set the last character of the buffer to a null terminator. */
	buffer[SIZE_OF_BUFFER - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_neg = 1;
	}
	/* Add the digits of the number to the buffer in reverse order. */
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (printNumeric_Value(is_neg, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * printBin - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int printBin(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, add;
	unsigned int a[32];
	int count;

	UNUSED_ENTITY(buffer);
	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(precision);
	UNUSED_ENTITY(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, add = 0, count = 0; i < 32; i++)
	{
		add += a[i];
		if (add || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
