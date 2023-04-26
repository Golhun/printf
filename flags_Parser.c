#include "main.h"

/**
 * parseFlags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int parseFlags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_LEFT_JUST, F_POS_INDICATOR, F_ZERO_PAD, F_ADD_HASH, F_PADDING_BLANK, 0};
	/* Loop through the format string, starting from *i+1 */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* Loop through the flag characters */
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			/* If current character match flag character, set corresponding flag bit */
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j]; /* Set flag bit using bitwise OR */
				break;
			}
		}
		/* If current character does not match any flag character, break loop */
		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = curr_i - 1; /* Set the updated index value */
	return (flags);
}
