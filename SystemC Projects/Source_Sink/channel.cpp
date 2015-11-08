//--------------------------------------------------------------------------------- 
// Module : HIERARCHICAL CHANNEL
//
// Description : Custom channel for communication between source and sink
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <systemc.h>
#include "channel.h"
#ifndef CHANNEL  // or use #pragma once as guards
#define CHANNEL

class hier_channel : public sc_channel, public w_if, public r_if
{
public:
	hier_channel(sc_module_name name) : sc_channel(name), num_elements(0), first(0) {}

	void write(char c) {
		
		data[num_elements] = c;
		
		++num_elements;
		
	
	}

	void read(char &c) {
		
		if (num_elements < 0)
		{
			wait(write_event); // Equivalent to sc_stop() as this event will never occur
		}
				
		c = data[first];
		first++;
		--num_elements;
		
	}

	void reset() {
		num_elements = first = 0;
	}

	int num_available() { return num_elements; }

private:
	
	char data[40];
	int num_elements, first;
	sc_event write_event, read_event;
};

#endif // CHANNEL