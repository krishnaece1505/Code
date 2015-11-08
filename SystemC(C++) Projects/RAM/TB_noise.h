#pragma once
#include<iostream>
#include <string>
#include "systemc.h"
using namespace std;
class TB_noise : public sc_module
{
public:
	sc_inout<sc_lv<8> > data;
	sc_out<int> address;
	sc_inout<int> mem_addr_flag;
	sc_out<sc_logic> CE; // Chip Enable
	sc_out<sc_logic> WE; // Write Enable
						 //sc_out<sc_logic> listing_flag;
	sc_event check_complete, check_event, ram_B_event;
	int mem_flag, err_correction_flag;
	int ram_A_flag, ram_B_flag = 0;
	int read_address;
	ofstream errfile;
	string input_file_name, output_file_name;

	SC_HAS_PROCESS(TB_noise);

	TB_noise(sc_module_name name) : sc_module(name)
	{
		output_file_name = "C:\\Kannan\\RAM_A_parity_errors.txt";
		ram_A_flag = 1;
		SC_THREAD(test);
		SC_THREAD(check_mem);
	}

	TB_noise(sc_module_name name, int mem_flag) : sc_module(name), mem_flag(mem_flag)
	{
		output_file_name = "C:\\Kannan\\RAM_B_parity_errors.txt";

		ram_B_flag = 1;
		SC_THREAD(test);
		SC_THREAD(check_mem);
	}

	void test();
	void check_mem();
};