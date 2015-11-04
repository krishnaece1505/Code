//--------------------------------------------------------------------------------- 
// Module : HIERARCHICAL CHANNEL HEADER
//
// Description : Custom channel for communication between source and sink
//
// Author : Krishnaswamy Kannan
//---------------------------------------------------------------------------------

#pragma once
#include "systemc.h"
class w_if : virtual public sc_interface
{
public:
	virtual void write(char) = 0;
	virtual void reset() = 0;
};

class r_if : virtual public sc_interface
{
public:
	virtual void read(char &) = 0;
	virtual int num_available() = 0;
};