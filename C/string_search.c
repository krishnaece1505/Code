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
	 
	int str_count = 0, substr_count = 0, i, j, str_found_flag;

	while (op == 'Y' || op == 'y')
	{
	printf("\n ----------------- WORD (or) SUBSTRING SEARCH -----------------");
	printf("\n\n  Enter a string: ");
	scanf(" %[^\n]s", &str); // Escape sequence [^\n]s to support spaces in scanf

	printf("\n  Enter the word (or) substring to search: ");
	scanf(" %s", &search);

	while (str[str_count] != '\0')
		str_count++;

	while (search[substr_count] != '\0')
		substr_count++;

	for (i = 0; i <= (str_count-substr_count); i++)
	{
		for (j = i; j< (i + substr_count); j++)
		{
			str_found_flag = 1;
			if (str[j] != search[j - i])
			{
				str_found_flag = 0;
				break;
			}
		}
		if (str_found_flag == 1)
			break;
	}
	if (str_found_flag == 1)
		printf("\n  SEARCH SUCCESSFUL!");
	else
		printf("\n  SEARCH UNSUCCESSFUL!");
	printf("\n\n  Do you want to continue(Type Y or N)? : ");
	scanf(" %c", &op);

	system("@cls||clear");
	}
	
}