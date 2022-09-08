#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define N (10)

int readnum(int first)
{
	char num[20];
	char curr[2];
	sprintf(num, "%d", first - 48);
	char c = getchar();

	while (isdigit(c))
	{
		sprintf(curr, "%d", c - 48);
		strcat(num, curr);
		c = getchar();
	}

	return atoi(num);
}

int isop(int i)
{
	return i == '+' || i == '-' || i == '*' || i == '/';
}

/**
 * @brief Performs given binary op c on the stack
 *
 * @param stack
 * @param top
 * @param c
 * @return int 1 if success, 0 on error (div-0)
 */
int handle_op(int *stack, int top, int c)
{
	if (c == '+')
	{
		stack[top - 1] += stack[top];
	}
	else if (c == '-')
	{
		stack[top - 1] -= stack[top];
	}
	else if (c == '*')
	{
		stack[top - 1] *= stack[top];
	}
	else // Division
	{
		if (stack[top] != 0)
		{
			stack[top - 1] = stack[top - 1] / stack[top];
		}
		else
		{
			return 0;
		}
	}
	return 1;
}

int main(void)
{
	int line = 1;
	int *stack = calloc(N, sizeof(int));
	int top = -1;
	int c = 0;
	int error = 0;

	while (c != -1)
	{
		c = getchar();
		if (c != ' ')
		{
			printf("%d\n", c);
		}

		if (isdigit(c) && !error)
		{
			if (top < N - 1)
			{
				top++;
				stack[top] = readnum(c);
			}
			else
			{
				// Too many numbers on the stack
				printf("line %d: error at %c\n", line, c);
				error = 1;
				top = 0;
			}
		}
		else if (isop(c) && !error)
		{
			if (top > 0 && handle_op(stack, top, c))
				top--;
			else
			{
				printf("line %d: error at %c\n", line, c);
				error = 1;
				top = 0;
			}
		}
		else if (c == '\n')
		{
			if (top != 0)
			{
				printf("line %d: error at \\n\n", line);
			}
			else if (!error)
			{
				printf("line %d: %d\n", line, stack[0]);
			}
			line++;
			top = -1;
			error = 0;
		}
		else if ((c != ' ' && c != -1) && !error)
		{
			// invalid character
			printf("line %d: error at %c\n", line, c);
			error = 1;
			top = 0;
		}
	}
	free(stack);
	return 0;
}
