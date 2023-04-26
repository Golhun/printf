#include "main.h"

/**
 * parseSize - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int parseSize(const char *format, int *i)
{
	int curr = *i + 1;
	int size = 0;

	if (format[curr] == 'l')
		size = DATA_LENGTH_LONG;
	else if (format[curr] == 'h')
		size = DATA_LENGTH_SHORT;

	if (size == 0)
		*i = curr - 1;
	else
		*i = curr;

	return (size);
}
