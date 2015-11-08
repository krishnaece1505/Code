//--------------------------------------------------------------------------------- 
// Module : MAIN MODULE 
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS
#include <systemc.h>
#include <cctype>
#include "channel.cpp"
#include "source.h"
#include "sink.h"

int sc_main(int, char *[]) {
	
	// hier_channel hier_channel_inst("hier_channel1"); // Uncomment to use custom channel instead of sc_fifo
	sc_fifo<char> fifo("FF");
	source source_inst("src");
	sink sink_inst("sink");
	
	source_inst.out(fifo);	
	sink_inst.in(fifo);
	
	sc_start();
	return 0;
}