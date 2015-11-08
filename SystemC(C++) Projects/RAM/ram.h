#pragma once


#include "systemc.h"
#include <string>

using namespace std;

class RAM : public sc_module
{
public:
	sc_inout<sc_lv<8> > data; //sc_uint<16>
	sc_in<int> address;
	sc_in<sc_logic> CE; // Chip Enable
	sc_in<sc_logic> WE; // Write Enable
	//sc_in<sc_logic> listing_flag;
	sc_inout<int> mem_addr_flag; // To store the last address
	int RAM_SIZE;
	int listing_flag;
	string *ram = new string[RAM_SIZE]; // Create a dynamic array for RAM storage
	string init_file;

	// ------------ Since default constructor SC_CTOR is not used ------------
	SC_HAS_PROCESS(RAM);

	// ------------ Constructor for Listing_A ------------
	RAM(sc_module_name name, int size, string file) : sc_module(name),RAM_SIZE(size),init_file(file)
	{
		SC_METHOD(ram_init);
		SC_THREAD(listing_A);
		SC_METHOD(ram_operation);
		sensitive << WE << CE << address << data;
	}
	
	// ------------ Constructor for Listing_B ------------
	RAM(sc_module_name name, int size, string file, int listing_flag) : sc_module(name), RAM_SIZE(size), init_file(file), listing_flag(listing_flag)
	{
		SC_METHOD(ram_init);
		SC_THREAD(listing_B);
		SC_METHOD(ram_operation);
		sensitive << WE << CE << address << data;
	}
	void ram_init();
	void listing_A();
	void listing_B();
	void ram_operation();
	

};
