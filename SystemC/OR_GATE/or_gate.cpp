#define _CRT_SECURE_NO_WARNINGS
#include "systemc.h"

SC_MODULE(or_gate)
{
	// Ports of OR gate
	sc_in<sc_logic> a, b;
	sc_out<sc_logic> c;
	sc_event print1, print2;
	SC_CTOR(or_gate)
	{
		
		SC_METHOD(or_dataflow);
		sensitive << a << b;
		// Used to tell scheduler not to include the method in runnable set during initialization phase
		dont_initialize();
		SC_THREAD(printa);
		SC_THREAD(printb);
		
	}
	void or_dataflow()
	{
		c = a | b;
		cout << "\n@" <<sc_time_stamp()<<endl;
		cout << a << b << endl;
		// Used to make a non-blocking call with a certain delay i.e. dynamic sensitivity for SC_METHOD
		next_trigger(3,SC_NS);
	}

	void printa()
	{
		cout << "\n@" << sc_simulation_time();
		wait(print1);
		
		cout << "\n HELLLLOOOOOO 1" << endl;
		print2.notify();
	}
	void printb()
	{
		//wait(print2);
		cout << "\n@" << sc_simulation_time();
		cout << "\n HELLLLOOOOOO 2" << endl;
		print1.notify();
		cout << "\n HELLLLOOOOOO 2" << endl;
	}
};