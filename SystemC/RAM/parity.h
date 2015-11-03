#pragma once
#include <string>
#include "HextoBin.h"
using namespace std;


// ------------------- Check RAM data for odd parity -------------------
int check_odd_parity(string data)
{

	int bin1_count = 0;
	for (int i = 2; i < data.length(); i++)
	{
		if (data.at(i) == '1')
			bin1_count++;
	}

	// Check for odd number of 1's
	if (bin1_count % 2 != 0)
		return (1);
	else
		return (0);
}

// ------------------- Correct RAM data with odd parity -------------------
string correct_odd_parity(string data, char *file_data)
{

	for (int i = data.length() - 1; i > 2; i--)
	{
		if (data.at(i) == '1')
		{
			data.at(i) = '0';

			if ("0b0" + HexToBin(file_data) == data)
			{
				break;
			}
			else
			{
				data.at(i) = '1';
			}
		}
		else
		{
			data.at(i) = '1';

			if ("0b0" + HexToBin(file_data) == data)
			{
				break;
			}
			else
			{
				data.at(i) = '0';
			}
		}

	}

	return data;
}
