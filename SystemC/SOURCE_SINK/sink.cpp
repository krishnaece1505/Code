//--------------------------------------------------------------------------------- 
// Module : SINK (RECEIVER)
//
// Description : Converts the received lower case alphabets to upper case
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include <systemc.h>
#include <cctype>
#include "channel.cpp"
#include "sink.h"
#ifndef SINK  // or use #pragma once as guards
#define SINK

	void sink::sink_p()
	{
		char c;
		cout << endl << endl;
		cout << "UPPER CASE LETTERS AT SINK" << endl;
		while (true) {
			in->read(c);
			c = (char)toupper(c);
			cout<< c << "\n" << flush;
			
		}
	}


#endif // SINK