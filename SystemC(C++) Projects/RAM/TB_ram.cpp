#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
#include "systemc.h"
#include<fstream>
#include <string>
#include "ram.h"
#include "TB_RAM.h"
using namespace std;

	void TB_RAM::copy_to_ram()
	{
		ifstream datafile;
		int faddr; char fdata[10];
		datafile.open(input_file_name);
		cout << "\n Copying data from T2.txt to RAM..............";
		while (!datafile.eof())
		{
			datafile >> faddr >> fdata;
			address.write(faddr);
			wait(2, SC_NS);
			data.write(strtol(fdata, NULL, 16));
			wait(2, SC_NS);
		}
	}
	void TB_RAM::check_mem()
	{
		int faddr;
		int i = 0;
		int mem_check_flag = 0;
		char fdata[10];
		ifstream datafile;
		ofstream errfile;
	
		// -------------- RAM check mode ------------
		//wait(check_event);
		datafile.open(input_file_name);
		cout << "\n Checking RAM for errors..............";
		string file_addr[1045] = { "" };

		wait(2, SC_NS);
		
		// ------------ Store file data into an array ------------
		while (!datafile.eof()) {
			datafile >> faddr >> fdata;
	
			if (faddr >= mem_addr_flag.read()+1) // To restrict array size to RAM_SIZE
				break;
			file_addr[faddr] = fdata;
			
		}
		
		// ------------ Check for errors (Missing addresses) ------------
		errfile.open(output_file_name); // Open log file to store errors
		while (i <= mem_addr_flag.read())
		{
			// ------------ Read from RAM ------------
			CE = SC_LOGIC_1;
			WE = SC_LOGIC_0;
			address.write(i);
			wait(2, SC_NS);
			char *a = (char *)file_addr[i].c_str();

			if (data.read() != strtol(a, NULL, 16)) // Check for errors
			{
				errfile << "ADDR : " << i << "\t RAM : " << data.read().to_string(SC_HEX, true) << "\t DATA :" << "0" << endl; // Address   Memory_Data   File_Data
				mem_check_flag = 1;
			}
			i++;
		}
		if (mem_check_flag == 1)
		{
			cout << "\n RAM has errors. See "<< output_file_name<<" for the error log!";
		}
		cout << "\n RAM Initialization check complete!";
		check_complete.notify();

		datafile.close();
		errfile.close();
	}

	void TB_RAM::test()
	{
	// ---------------------------- TASK 3.1 ----------------------------
		
	// ------------ Test case 1 (Initialization check of T1 data) ------------

		cout << "\n -------- Test 1 : Checking RAM data after intialization from T1.txt --------";
		input_file_name = "C:\\Kannan\\T1.txt";
		output_file_name = "C:\\Kannan\\RAM_init_errors.txt";
		wait(check_complete);


		// ------------ Test case 2 (Copy T2 data to RAM) ------------
		cout << "\n ------------ Test 2 : Copy data from T2.txt to RAM ------------";
		CE = SC_LOGIC_1;
		WE = SC_LOGIC_1;
		input_file_name = "C:\\Kannan\\T2.txt";
		output_file_name = "C:\\Kannan\\RAM_T2_errors.txt";
		copy_to_ram();
		cout << "\n Copied Data. Now checking..............";
		check_mem();
		
	// ------------ Test case 3 (Write OP when CE = '0') ------------
		cout << "\n ------------ Test 3 : Write OP when CE = '0' ------------";
		read_address = 1000;
		CE = SC_LOGIC_0;
		WE = SC_LOGIC_1;
		address.write(read_address);
		wait(5, SC_NS);
		data.write("00100100");
		//cout << "\n RAM[" << read_address << "] : " << data.read().to_string(SC_HEX, true);

	// ------------ Test case 4 (Read OP when CE = '0') ------------
		cout << "\n ------------Test 4 : Read OP when CE = '0' ------------";
		read_address = 1034;
		CE = SC_LOGIC_0;
		WE = SC_LOGIC_0;
		address.write(read_address);
		wait(2, SC_NS);
		cout << "\n RAM[" << read_address << "] : " << data.read().to_string(SC_HEX, true);
	
	// ------------ Test case 5 (Out of range address) ------------
		cout << "\n ------------ Test 5 : Out of range address ------------";
		read_address = 1020;
		CE = SC_LOGIC_1;
		WE = SC_LOGIC_0;
		address.write(read_address);
		wait(5, SC_NS);
		cout << "\n RAM[" << read_address << "] : " << data.read().to_string(SC_HEX, true);
		//check_event.notify();

		

		sc_stop();

	}



