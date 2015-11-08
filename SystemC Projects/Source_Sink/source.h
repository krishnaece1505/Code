//--------------------------------------------------------------------------------- 
// Module : SOURCE (SENDER) HEADER
//
// Description : Sends lower case alphabets
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------
#pragma once
#include "systemc.h"
#include "channel.h"

class source : public sc_module
{
public:
	//sc_port<w_if> out; // Uncomment this line to use the custom hierarchical channel write port instead of sc_fifo_out
	sc_fifo_out<char> out; 
	SC_HAS_PROCESS(source);

	source(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(source_p);
	}

	 void source_p();
};