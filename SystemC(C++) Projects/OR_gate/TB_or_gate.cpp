#define _CRT_SECURE_NO_WARNINGS
#include "systemc.h"

SC_MODULE(TB_or_gate)
{
	// Testbench module ports
	sc_out<sc_logic> a, b;
	sc_in<sc_logic> c;

	SC_CTOR(TB_or_gate)
	{
		SC_METHOD(print);
		sensitive << c;
		SC_THREAD(drive_a);
		//sensitive << a;
		SC_THREAD(drive_b);
		//sensitive << b;
	}

	void drive_a()
	{
		cout << "OR GATE" << endl;// << "See the waveform generated for results" << endl;
		
		// Case 00
		a = SC_LOGIC_0;
		
		wait(2, SC_NS);

		// Case 01
		a = SC_LOGIC_0;
		
		wait(2, SC_NS);

		// Case 10
		a = SC_LOGIC_1;
		
		wait(2, SC_NS);

		// Case 1
		a = SC_LOGIC_1;
		
		wait(2, SC_NS);

		// Stop the simulation
		//sc_stop();
	}
	void drive_b()
	{
		
		// Case 00
		
		b = SC_LOGIC_0;
		wait(2, SC_NS);

		// Case 01
		
		b = SC_LOGIC_1;
		wait(2, SC_NS);

		// Case 10
		
		b = SC_LOGIC_0;
		wait(2, SC_NS);

		// Case 1
		
		b = SC_LOGIC_1;
		wait(2, SC_NS);

		// Stop the simulation
		//sc_stop();
	}
	void print()
	{
		cout <<"\nc Value : " << c<<endl;
	}
};