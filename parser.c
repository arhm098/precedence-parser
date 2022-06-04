//group members
//first Member : 
// Name : Muhammad Arham     Roll : 2314-53689
//Second Member :
// Name : Muhammad Tayyab	 Roll : 2214-40255

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// stack start
//////////////////////
int MAXSIZE = 32;
char stack[32];
int top = -1;
int isempty()
{
	if (top == -1)
		return 1;
	else
		return 0;
}
int isfull()
{
	if (top == MAXSIZE)
		return 1;
	else
		return 0;
}

int peek()
{
	return stack[top];
}
int pop()
{
	int data;
	if (!isempty())
	{
		data = stack[top];
		top--;
		return data;
	}
	else
	{
		return -1;
	}
}
int push(char data)
{
	if (!isfull())
	{
		top++;
		stack[top] = data;
	}
	else
	{
		return -1;
	}
}
//////////////////////////
// stack end

void shift(char alphabet)
{
	push(alphabet);
}
int reduce()
{
	printf("\nintiated reduce functon");
	char lexeme[3] = {stack[top-2],stack[top-1],stack[top]};
	if (lexeme[0] == 'E' && lexeme[1] == '+' && lexeme[2] == 'T')
	{
		pop();
		pop();
		pop();
		push('E');
	}
	else if (lexeme[0] == 'T' && lexeme[1] == '*' && lexeme[2] == 'F')
	{
		pop();
		pop();
		pop();
		push('T');
	}
	else if (lexeme[0] == '(' && lexeme[1] == 'E' && lexeme[2] == ')')
	{
		pop();
		pop();
		pop();
		push('F');
	}
	char* lexemeSingle = malloc(1);
	lexemeSingle[0] = peek();

	if (*lexemeSingle == 'T')
	{
		pop();
		push('E');
	}
	else if (*lexemeSingle == 'F')
	{
		pop();
		push('T');
	}
	else if (*lexemeSingle == 'i')
	{
		pop();
		push('F');
	}
	else
	{
		printf("\nnone of reduce actions are applicable\n");
		return -1;
	}
	return 0;
}

int main()
{
	push('$'); int check = 0;
	char string[12] = {'(','i','+','i','+','(','i','+','i',')',')','$'}; //(id+id +(id*id))
	int pointer = 0;
	while (pointer < 12)
	{
		printf("pointer state %d\n", pointer);
		for ( int i = 0;i<top+1;i++)
		{
			printf(" %c ",stack[i]);
		}
		// base conditions for ending and accepting
		if (peek() == '$')
		{
			push(string[pointer]);
			pointer++;
		}
		else if ((top == 1) && (peek() == 'E') && (string[pointer] == '$'))
		{
			printf("accepted");
			return 0;
		}
		else if (string[pointer] == '$')
		{
			reduce();
		}

		// cases of plus
		else if ((peek() == '+') && ((string[pointer] == '+') || (string[pointer] == ')')))
		{
			reduce();
		}
		else if ((peek() == '+') && ((string[pointer] == '*') || (string[pointer] == '(') || (string[pointer] == 'i')))
		{
			push(string[pointer]);
			pointer++;
		}
		// cases of mul
		else if ((peek() == '*') && ((string[pointer] == '+') || (string[pointer] == '*') || (string[pointer] == ')')))
		{
			reduce();
		}
		else if ((peek() == '*') && ((string[pointer] == '(') || (string[pointer] == 'i')))
		{
			push(string[pointer]);
			pointer++;
		}
		// cases of (
		else if ((peek() == '(') && (string[pointer] == ')'))
		{
			printf("rejected");
			return 0;
		}
		else if (peek() == '(')
		{
			push(string[pointer]);
			pointer++;
		}
		// cases of )
		else if ((peek() == ')') && ((string[pointer] == '(') || (string[pointer] == 'i')))
		{
			printf("rejected");
			return 0;
		}
		else if (peek() == ')')
		{
			reduce();
		}
		// cases of id
		else if ((peek() == 'i') && ((string[pointer] == '(') || (string[pointer] == 'i')))
		{
			printf("rejected");
			return 0;
		}
		else if (peek() == 'i')
		{
			reduce();
		}
		else if ((peek() == 'F') || (peek() == 'T') || (peek() == 'E'))
		{
			if (peek() == 'E')
			{
				push(string[pointer]);
				pointer++;
			}
			reduce();
		}
		else
		{
			printf("case did not run %d", pointer);
			printf("\n stack top %c ", peek());
		}
	}
}
