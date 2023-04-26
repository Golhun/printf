#include "main.h"

/**
 * print_Mem_Location - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_Mem_Location(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char matrix = 0, padd = ' ';
	int i = SIZE_OF_BUFFER - 2, length = 2, padd_start = 1; /* len=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED_ENTITY(width);
	UNUSED_ENTITY(size);
	UNUSED_ENTITY(precision);
	/* Handle NULL pointer argument */
	if (addrs == NULL)
		return (write(1, "(nil)", 5));
	/* Initialize the buffer */
	buffer[SIZE_OF_BUFFER - 1] = '\0';
	UNUSED_ENTITY(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[i--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++; /* Increase the length of the buffer as digits are added */
	}
	/* Handle special formatting flags */
	if ((flags & F_ZERO_PAD) && !(flags & F_LEFT_JUST))
		padd = '0';
	if (flags & F_POS_INDICATOR)
		matrix = '+', length++;
	else if (flags & F_PADDING_BLANK)
		matrix = ' ', length++;

	i++;

	/*return (write(1, &buffer[i], SIZE_OF_BUFFER - i - 1));*/
	return (printPointer_Value(buffer, i, length,
		width, flags, padd, matrix, padd_start));
}

/**
 * print_Esc_Chars - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_Esc_Chars(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(precision);
	UNUSED_ENTITY(size);
	/* If null, print "(null)" and return the number of characters printed */
	if (str == NULL)
		return (write(1, "(null)", 6));
	/* Loop through each character in the string */
	while (str[j] != '\0')
	{
		/* If character is printable, add it to the buffer */
		if (determinePrintable(str[j]))
			buffer[j + offset] = str[j];
		/* If not printable, append hex code to the buffer and update */
		else
			offset += addHex_Code(str[j], buffer, j + offset);

		j++;
	}

	buffer[j + offset] = '\0';

	return (write(1, buffer, j + offset));
}

/**
 * printString_Backwards - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int printString_Backwards(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int j, count = 0;

	UNUSED_ENTITY(buffer);
	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(size);
	/* get a char pointer argument from the va_list */
	str = va_arg(types, char *);
	/* check if the char pointer is NULL */
	if (str == NULL)
	{
		UNUSED_ENTITY(precision);

		str = ")Null(";
	}
	for (j = 0; str[j]; j++)
		;
	/* iterate backwards through the char pointer */
	for (j = j - 1; j >= 0; j--)
	{
		char c = str[j]; /* get the current character */

		write(1, &c, 1); /* write the character to stdout */
		count++;
	}
	return (count);
}
/**
 * printEncoded_String - Print a string in rot13.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int printEncoded_String(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char k, *str;
	unsigned int n, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	/* retrieve the string argument */
	str = va_arg(types, char *);
	UNUSED_ENTITY(buffer);
	UNUSED_ENTITY(flags);
	UNUSED_ENTITY(width);
	UNUSED_ENTITY(precision);
	UNUSED_ENTITY(size);

	if (str == NULL)
		str = "(AHYY)";
	/* loop through the input string */
	for (n = 0; str[n]; n++)
	{
		/* loop through lookup arrays */
		for (j = 0; in[j]; j++)
		{
			/* if the current input character is found in the lookup array */
			if (in[j] == str[n])
			{
				k = out[j]; /* get the corresponding rotated character */
				write(1, &k, 1); /* print the rotated character */
				count++;
				break;
			}
		} /* if input character is not found in lookup array */
		if (!in[j])
		{
			k = str[n]; /* use original char */
			write(1, &k, 1); /* print original char */
			count++;
		}
	}
	return (count);
}
