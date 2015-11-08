#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include "systemc.h"
#include<fstream>
#include <string>
#include "TB_noise.h"
#include "ram.h"
#include "HextoBin.h"
#include "parity.h"

using namespace std;

// ------------------- Check RAM for errors -------------------
void TB_noise::check_mem()
{

	int faddr = 0;
	int i = 0, odd_parity = 0;
	int mem_check_flag = 0;
	char fdata[10];
	string file_addr[1045] = { "" };
	ifstream datafile;
	ofstream errfile;
	datafile.open(input_file_name);
	if (ram_A_flag == 1)
	{
		wait(2, SC_NS); // Wait till mem_addr_flag value is written to the port
		cout << "\n\n --------------- RAM A ---------------";
	}
	if (ram_B_flag == 1)
	{
		wait(50000, SC_NS); // Wait till RAM_A operations are complete
		cout << "\n\n --------------- RAM B ---------------";
	}
	cout << "\n Checking RAM for errors..............";

	// ------------ Open log file to store errors ------------
	errfile.open(output_file_name);

	// ------------ Store file values into an array to break after reaching RAM_SIZE ------------
	while (!datafile.eof())
	{
		datafile >> faddr >> fdata;
		if (faddr > mem_addr_flag.read())
			break;
		file_addr[faddr] = fdata;
	}
	//cout << "\n OUTSIDE LOOP ";

	while (i <= mem_addr_flag.read())
	{

		// ------------ Enable Read mode in RAM ------------
		CE = SC_LOGIC_1;
		WE = SC_LOGIC_0;
		address.write(i);
		wait(2, SC_NS);
		char *a = (char *)file_addr[i].c_str();

		// ------------ Check for mismatch of RAM data with T3.txt
		if (data.read() != strtol(a, NULL, 16))
		{
			string ram_data = data.read().to_string(SC_BIN, true);
			// ------------ Obtain the parity of RAM data ------------
			odd_parity = check_odd_parity(ram_data);

			if (i == 25)
			{
				cout << "\nDATA : " << ram_data << "\t" << strtol(a, NULL, 16);

			}
			// ------------ Correct the erroneous data in the RAM ------------
		string correct_data = correct_odd_parity(ram_data, a);
			err_correction_flag = 1;

			//wait(2, SC_NS);
			// ------------ Log the data if it is eroneous even after correction ------------
			if (correct_data != "0b0" + HexToBin(file_addr[i]))
			{ 
				errfile << "ADDR : " << i << "\t DATA :" << strtol(a, NULL, 16) << "\t RAM : " << data.read().to_string(SC_HEX, true) << "\t ODD_PARITY : " << odd_parity << endl; // Address   Memory_Data   File_Data
				mem_check_flag = 1;
			}

			// ------------ Write the correct data to memory ------------
			else
			{
				// ------------ Enter RAM write mode ------------
				CE = SC_LOGIC_1;
				WE = SC_LOGIC_1;
				address.write(i);
				//wait(10, SC_NS);
				data.write(strtoul(file_addr[i].substr(0, 2).c_str(), NULL, 16));
				wait(2, SC_NS);
			}
		} // End if of mismatch check
		i++;
	} // End of while loop

	if (mem_check_flag == 1)
	{
		cout << "\n Errors found in some addresses in RAM. See " << output_file_name << " for the error log!..............";
	}
	if (err_correction_flag)
	{
		cout << "\n Errors were found in some addresses in RAM. They were corrected successfully..............";
	}

	cout << "\n RAM check complete!..............";
	check_complete.notify();

	datafile.close();
	errfile.close();
}

// ------------------- Test Bench for the RAM affected by noise -------------------
void TB_noise::test()
{
	// File to be verified for init errors
	input_file_name = "C:\\Kannan\\T3.txt";
	wait(check_complete);
	/*
	// ------------ Test Write Operation ------------
	CE = SC_LOGIC_1;
	WE = SC_LOGIC_1;
	address.write(1000);
	data.write("10001001");

	*/

	// ------------ Test RAM data after correction ------------
	cout << "\n Testing RAM data after error correction..............\n";
	
	// ------------ Test case 1 for parity correction ------------
		read_address = 1;
		wait(5, SC_NS);
		CE = SC_LOGIC_1;
		WE = SC_LOGIC_0;
		address.write(read_address);
		wait(5, SC_NS);
		cout << "\n RAM[" << read_address << "] : " << data.read();
		wait(5, SC_NS);

	// ------------ Test case 2 for parity correction ------------
		read_address = 25;
		wait(5, SC_NS);
		CE = SC_LOGIC_1;
		WE = SC_LOGIC_0;
		address.write(read_address);
		wait(5, SC_NS);
		cout << "\n RAM[" << read_address << "] : " << data.read() << endl;
		wait(5, SC_NS);
		//sc_stop();
	
}



/*
if (i == 25)
{
cout << "\nADDR WRITTEN : " <<i ;

}

if (i == 25)
{
cout << "\nRAM[" << i << "] : " << data.read();

}
//cout << "\nRAM["<<i<<"] : " << data.read() <<"\t" << strtol(a, NULL, 16);

if (i == 1)
{
cout << " \nDATA FOR CORRECTION : " << ram_data << "\t i : " << i;

cout << "\n DATA AFTER CORRECTION : " << correct_data <<"\t"<< "0b0"+HexToBin(file_addr[i]);

cout << "\n ATOI : " << atoi(a);
if (i == 1)
{
cout << "\nDATA TO RAM :" << atoi(a);
if (i == 1)
{
cout << "\nDATA TO RAM :" << file_addr[i].substr(0, 2).c_str() <<"\t"<<strtoul(file_addr[i].substr(0, 2).c_str(), NULL, 16);
}
}
if (i == 25)
cout << "\n INSIDE LOOP : "; if (i == 25)
cout << "\n DATA WRITE : " << strtoul(file_addr[i].substr(0, 2).c_str(), NULL, 16);
*/