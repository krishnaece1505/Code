//--------------------------------------------------------------------------------- 
// Module : SOURCE (SENDER)
//
// Description : Sends lower case alphabets
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <systemc.h>
#include "source.h"
#include "channel.cpp"

	void source :: source_p()
	{
		const char *alphabet =
			"abcdefghijklmnopqrstuvwxyz\n";
		
		while (*alphabet)
		{
			
			cout <<*alphabet <<endl;
			out->write(*alphabet++);
		}
	}
