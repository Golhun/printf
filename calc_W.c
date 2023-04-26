#include "main.h"

/**
 * parseWidth - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @list: list of arguments.
 *
 * Return: width.
 */
int parseWidth(const char *format, int *i, va_list list)
{
	int current;
	int width = 0;
	/*Loop through characters in format string, start from the index.*/
	for (current = *i + 1; format[current] != '\0'; current++)
	{
		/*If current character is digit, then update width accordingly.*/
		if (determineNumeric(format[current]))
		{
			width *= 10;
			width += format[current] - '0';
		}
		/* If current character is '*', get width from va_list and exit */
		else if (format[current] == '*')
		{
			current++;
			width = va_arg(list, int);
			break;
		}
		/* If current character is not a digit or '*' then exit the loop. */
		else
			break;
	}
	/* Update the index pointer to the last character processed. */
	*i = current - 1;

	return (width);
}
