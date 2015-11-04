//--------------------------------------------------------------------------------- 
// Module : WORD (OR) SUBSTRING SEARCH FROM A STRING
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS // To disable scanf error/warning in Visual studio
#include<stdio.h>
#include<conio.h>
#include <stdlib.h> // For use of system() to clear the screen

void main()
{
	char str[500], search[30];
	char op = 'Y';
	system("@cls||clear"); // Clear the console
	 
	int count1 = 0, count2 = 0, i, j, flag;

	while (op == 'Y' || op == 'y')
	{
	printf("\n ----------------- WORD (or) SUBSTRING SEARCH -----------------");
	printf("\n\n  Enter a string: ");
	scanf(" %[^\n]s", &str); // Escape sequence [^\n]s to support spaces in scanf

	printf("\n  Enter the word (or) substring to search: ");
	scanf(" %s", &search);

	while (str[count1] != '\0')
		count1++;

	while (search[count2] != '\0')
		count2++;

	for (i = 0; i <= count1 - count2; i++)
	{
		for (j = i; j<i + count2; j++)
		{
			flag = 1;
			if (str[j] != search[j - i])
			{
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
		printf("\n  SEARCH SUCCESSFUL!");
	else
		printf("\n  SEARCH UNSUCCESSFUL!");
	printf("\n\n  Do you want to continue(Type Y or N)? : ");
	scanf(" %c", &op);

	system("@cls||clear");
	}
	
}