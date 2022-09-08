#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N (10)

int error = 0;
int top = -1;
int c = 0;
int line = 1;

int readnum(int first)
{
	char num[20];
	char curr[4];
	sprintf(num, "%d", first - 48);
	char ch = getchar();

	while (isdigit(ch))
	{
		sprintf(curr, "%d", ch - 48);
		strcat(num, curr);
		ch = getchar();
	}

	return atoi(num);
}

/**
 * @brief Check if given integer represents a binary operator
 *
 * @param i integer to validate as operator
 * @return 	int 1 if valid operator, 0 otherwise.
 */
int isop(int i)
{
	return i == '+' || i == '-' || i == '*' || i == '/';
}

/**
 * @brief Performs given binary op c on the stack
 *
 * @param stack 	stack of number to perform operation on
 * @param top		index for stack's top
 * @param operator	binary operator to be handled
 * @return 			int 1 if success, 0 on error (div/0)
 */
int handle_op(int *stack, int top, int operator)
{
	if (operator== '+')
		stack[top - 1] += stack[top];

	else if (operator== '-')
		stack[top - 1] -= stack[top];

	else if (operator== '*')
		stack[top - 1] *= stack[top];

	else // Division
	{
		if (stack[top] != 0)
			stack[top - 1] /= stack[top];

		else // Division by zero
			return 0;
	}
	return 1;
}

/**
 * @brief Report error and toggle error flag
 *
 */
void err()
{
	printf("line %d: error at %c\n", line, c);
	error = 1;
}

/**
 * @brief Get the next non-space character from stdin
 *
 * @return int ascii representation of next non-space character
 */
int get_nonspace()
{
	int ns;
	while ((ns = getchar()) == ' ')
		continue;
	return ns;
}

int main(void)
{
	int *stack = calloc(N, sizeof(int));

	while (c != -1)
	{
		// assign c, skip to next linebreak if error occured:
		while ((c = get_nonspace()) != '\n' && error)
			continue;

		if (isdigit(c))
		{
			if (top++ < N - 1) // subtract one to adjust for top starting at 0
				stack[top] = readnum(c);

			// Too many numbers on the stack
			else
				err();
		}
		else if (isop(c))
		{
			if (top > 0 && handle_op(stack, top, c))
				top--;

			else // 0 division or not enough numbers
				err();
		}
		else if (c == '\n')
		{
			if (!error)
			{
				// Newline when zero or more than one numbers in stack
				if (top)
					printf("line %d: error at \\n\n", line);

				// Successfully calculated line
				else
					printf("line %d: %d\n", line, stack[0]);
			}
			// Reset for next line
			line++;
			top = -1;
			error = 0;
		}
		// invalid character (-1 = EOF)
		else if (c != -1)
			err();
	}
	free(stack);
	return 0;
}
