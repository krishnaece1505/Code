#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "ram.h"
#include <iostream>
#include<fstream>
#include "systemc.h"

#include "Listing_A.h"
using namespace std;

void Listing_A::noiseA()
{

	for (int i = 0; i < mem_addr_flag; i++)
	{
		int temp;
		char *a = (char *)ram[i].c_str();
		temp = strtol(a, NULL, 16);
		if (temp == 112) // 0x70
			temp = temp | 115;  // BITWISE OR 0x73
		else if (temp == 103) // 0x67
			temp = temp | 99; // BITWISE OR 0x63
		ram[i] = to_string(temp);


	}
}