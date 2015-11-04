//--------------------------------------------------------------------------------- 
// Module : STACK
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS // To disable scanf error/warning in Visual studio
#include <stdio.h>
#include <stdlib.h> // For use of system() to clear the screen
#define STACKSIZE 5 //define the size of the stack here

/* Structure definition for stack */
struct stack 
{
	int stk[STACKSIZE];
	int top;
	
};

typedef struct stack STACK;
STACK s;

void push(void);
int pop(void);
void display(void);

void main()
{
	int choice;
	char op = 'Y';
	system("@cls||clear"); // Clear the console
	s.top = -1;
	printf(" ---------------- STACK MODEL ----------------\n");
	while (op == 'Y' || op == 'y')
	{
		printf("\n STACK OPERATIONS\n");
		printf("------------------------------------------\n");
		printf(" 1 --> PUSH \n");
		printf(" 2 --> POP \n");
		printf(" 3 --> DISPLAY \n");
		printf(" 4 --> EXIT \n");
		printf("------------------------------------------\n");
		
		printf("Enter your choice\n");
		scanf(" %d", &choice);

		switch (choice)
		{
		case 1: push();
			break;
		case 2: pop();
			break;
		case 3: display();
			break;
		case 4: return;
		default: printf("Select from the options above\n");
			break;
		}
		
		fflush(stdin);
		printf("Do you want to continue(Type Y or N)? : ");
		scanf(" %c", &op);
	
		system("@cls||clear");
	}
}

/*Function to add an element to the stack*/
void push()
{
	int num;
	if (s.top == (STACKSIZE - 1))
	{
		printf("Stack is Full\n");
		return;
	}
	else
	{
		printf("Enter the element to be pushed\n");
		scanf(" %d", &num);
		s.top = s.top + 1;
		s.stk[s.top] = num;
	}
	return;
}

/*Function to delete an element from the stack*/
int pop()
{
	int num;
	if (s.top == -1)
	{
		printf("Stack is Empty\n");
		return (s.top);
	}
	else
	{
		num = s.stk[s.top];
		printf("The element %d is popped out of the stack\n", s.stk[s.top]);
		s.top = s.top - 1;
	}
	return(num);
}

/*Function to display the status of the stack*/
void display()
{
	int i;
	if (s.top == -1)
	{
		printf("Stack is empty\n");
		return;
	}
	else
	{
		printf("\n ------ STACK ------ \n\n");
		for (i = s.top; i >= 0; i--)
		{
			//printf("-------\n");
			printf("  %d", s.stk[i]);
			printf("\n-------\n");
		}
	}
	printf("\n");
}