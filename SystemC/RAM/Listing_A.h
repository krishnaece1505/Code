#pragma once

#include "ram.h"
#include "systemc.h"



class Listing_A : public RAM
{
public :
	void noiseA();
	Listing_A()
	{
		noiseA();
	}
};