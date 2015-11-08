//--------------------------------------------------------------------------------- 
// Module : SINK (RECEIVER)
//
// Description : Sends lower case alphabets
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------

#pragma once
#include "systemc.h"
#include "channel.h"

class sink : public sc_module
{
public:
	//sc_port<r_if> in; // Uncomment this line to use the custom hierarchical channel read port instead of sc_fifo_in
	sc_fifo_in<char> in;
	SC_HAS_PROCESS(sink);

	sink(sc_module_name name) : sc_module(name)
	{
		SC_THREAD(sink_p);
	}
	 void sink_p();
};