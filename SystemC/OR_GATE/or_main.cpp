#define _CRT_SECURE_NO_WARNINGS
// Uncomment the below macro to generate a waveform for the OR gate inputs and outputs
//#define WAVE
#include "or_gate.cpp"
#include "TB_or_gate.cpp"


int sc_main(int argc, char* argv[])
{
	// Turn off warnings due to deprecated features
	sc_core::sc_report_handler::set_actions("/IEEE_Std_1666/deprecated",
		sc_core::SC_DO_NOTHING);

	// Declare the channel to communicate between or_gate and its TB
	sc_buffer<sc_logic> A, B, C;

	// MODULE INST USING POINTERS
	or_gate *OR;
	OR = new or_gate("OR");
	OR->a(A);// NAME BINDING
	OR->b(B);
	OR->c(C);

	TB_or_gate TB_OR("TB_OR"); 
	TB_OR.a(A); // NAME BINDING
	TB_OR.b(B);
	TB_OR.c(C);
	//TB_OR(A, B, C); // POSITIONAL BINDING

#ifdef WAVE
	// Generate waveform
	sc_trace_file *wf = sc_create_vcd_trace_file("OR_GATE");
	sc_trace(wf, OR->a, "a");
	sc_trace(wf, OR->b, "b");
	sc_trace(wf, OR->c, "c");
#endif
	sc_start(20, SC_NS);

	//sc_close_vcd_trace_file(wf);

	return(0);
}
