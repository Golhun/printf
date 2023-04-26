#include "main.h"
/**
 * processFmtSpecifier - Prints an argument based on its type
 * @fmt_specifier: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: ind.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int processFmtSpecifier(const char *fmt_specifier, int *ind, va_list list, char buffer[],
	int flags, int width, int precision, int size)

{
	int j, unknow_len = 0, printed_chars = -1;
	/* Define an array of formats and their respective functions */
	fmt_specifier_t fmt_specifier_types[] = {
		{'c', printCharacter}, {'s', printStr}, {'%', printPercentage},
		{'i', printSgndInt}, {'d', printSgndInt}, {'b', printBin},
		{'u', printUsgndInt}, {'o', printOctal_Int}, {'x', printHex_Dec},
		{'X', printHex_Upper}, {'p', print_Mem_Location}, {'S', print_Esc_Chars},
		{'r', printString_Backwards}, {'R', printEncoded_String}, {'\0', NULL}
	};
	/* Loop through each type to find a matching one */
	for (j = 0; fmt_specifier_types[j].fmt_specifier != '\0'; j++)
		if (fmt_specifier[*ind] == fmt_specifier_types[j].fmt_specifier)
			/* If found, call corresponding print function and return its result */
			return (fmt_specifier_types[j].fn(list, buffer, flags, width, precision, size));
	/* If no matching type, handle unknown formats */
	if (fmt_specifier_types[j].fmt_specifier == '\0')
	{
		if (fmt_specifier[*ind] == '\0')
			return (-1);
		/* Print '%%' if the current character is not a valid format specifier */
		unknow_len += write(1, "%%", 1);
		if (fmt_specifier[*ind - 1] == ' ') /* If previous character was a space, print */
			unknow_len += write(1, " ", 1);
		else if (width) /* If width skip to start of the current format specifier */
		{
			--(*ind);
			while (fmt_specifier[*ind] != ' ' && fmt_specifier[*ind] != '%')
				--(*ind);
			if (fmt_specifier[*ind] == ' ')
				--(*ind);
			return (1);
		} /* Otherwise, print the current character as is */
		unknow_len += write(1, &fmt_specifier[*ind], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
