#pragma once
#include<iostream>
#include <string>
#include "systemc.h"
using namespace std;


SC_MODULE(TB_RAM)
{
	sc_inout<sc_lv<8> > data;
	sc_out<int> address;
	sc_inout<int> mem_addr_flag;
	sc_out<sc_logic> CE; // Chip Enable
	sc_out<sc_logic> WE; // Write Enable
						 //sc_out<sc_logic> listing_flag;
	sc_event check_complete, check_event;
	int read_address;
	string input_file_name, output_file_name;

	SC_CTOR(TB_RAM)
	{

		SC_THREAD(test);
		SC_THREAD(check_mem);

	}

	void test();
	void check_mem();
	void copy_to_ram();

};