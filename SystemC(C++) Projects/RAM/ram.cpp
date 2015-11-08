#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include "systemc.h"
#include<fstream>
#include <bitset>
#include "ram.h"
using namespace std;

// ------------------- Initialize RAM with values from file -------------------
void  RAM::ram_init()
{
	cout << "\n\n Intializing RAM with values from text file..............";
	int faddr;
	string fdata;
	ifstream datafile;
	// ------------ Open the text file to load values into RAM ------------
	datafile.open(init_file);

	while (!datafile.eof()) {

		datafile >> faddr >> fdata;
		// ------------ Restrict RAM size to the size required ------------
		if (faddr >= RAM_SIZE)
			break;
		//ram[faddr] = fdata;
		// ------------ Data is stored in integer format in RAM ------------
		ram[faddr] = to_string(strtoul(fdata.c_str(), NULL, 16));
		
	}
	mem_addr_flag.write(faddr - 1);
	cout << "\n RAM data intialized..............";
	datafile.close();

}

// ------------------- Distortion for Memory A -------------------
void RAM::listing_A()
{

	wait(2, SC_NS);
	cout << "\n\n Corrupting RAM - LISTING_A..............";
	for (int i = 0; i <= mem_addr_flag; i++)
	{
		int temp;
		char *a = (char *)ram[i].c_str();
		temp = atoi(a);  // strtol(a, NULL, 16);
		temp = temp | 4;  // BITWISE OR 0x04
		// ------------ Data stored as Integers in RAM ------------
		ram[i] = to_string(temp);
	}
	
}

// ------------------- Distortion for Memory B -------------------
void RAM::listing_B()
{
	wait(50000, SC_NS);
	cout << "\n\n Corrupting RAM - LISTING_B..............";
	for (int i = 0; i <= mem_addr_flag; i++)
	{
		int temp;
		char *a = (char *)ram[i].c_str();
		temp = atoi(a);
		if (temp == 112) // 0x70
		{
			temp = temp & 115;  // BITWISE OR 0x73
		}
		else if (temp == 103) // 0x67
		{
			temp = temp & 99; // BITWISE OR 0x63
		}

		// ------------ Data stored as Integers in RAM ------------
		ram[i] = to_string(temp);

	}
	
}

// ------------------- RAM operations for READ & WRITE -------------------
void  RAM::ram_operation()
{
	// ------------ WRITE Mode ------------
	if (WE.read() == SC_LOGIC_1)
	{
		if (CE.read() == SC_LOGIC_0)
		{
			cout << "\n Write operation discarded as Chip Enable is \"LOW\".............." ;
		}
		else
		{
			if (address.read() > mem_addr_flag.read())
			{
				SC_REPORT_ERROR("", "\n Out of Range Address..............");
			}
			string buf;
			buf = data.read().to_string(SC_HEX, true);
			// ------------ Data stored as Integers in RAM ------------
			ram[address.read()] = to_string(strtoul(buf.substr(3, 5).c_str(), NULL, 16)); // Convert hex to Int

		}
	}
	// ------------ READ Mode ------------
	else
	{
		if (CE.read() == SC_LOGIC_0)
		{
			cout << "\n Chip Enable is \"LOW\".............. ";
			data.write("11111111");
		}
		else
		{
			if (address.read() > mem_addr_flag.read())
			{
				SC_REPORT_ERROR("", "\n Out of Range Address..............");
			}
			char *a = (char *)ram[address.read()].c_str();
			data.write(atoi(a));  // Convert string to Int using atoi
			
		}

	} // outer else

}


/*
cout << "\n TEMP : " << i;
if (address.read() == 112)
{
cout << " \nDATA READ : " <<a <<"\t" << atoi(a);// data.read().to_string(SC_HEX, true);
}

if (address.read() == 112)
{
cout << " \nDATA WRITE ON PORT DONE";// : " << a;// data.read().to_string(SC_HEX, true);
}
if (address.read() == 1)
{
cout << "\nIN RAM : " << ram[address.read()];// << "\t" << strtoul(buf.substr(3, 5).c_str(), NULL, 16);// data.read().to_string(SC_HEX, true);
}
if (address.read() == 1)
{
cout << "\nIN RAM READ: " << ram[address.read()] <<"\t" << atoi(a);
}
if (address.read() == 25)
cout << "\nIN RAM READ: " << atoi(a);
//cout << "\nDATA IN RAM : " << ram[address.read()] <<"\t"<<strtol(a,NULL,16) << endl;
*/