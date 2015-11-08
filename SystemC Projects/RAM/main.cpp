#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include "systemc.h"
#include "ram.h"
#include "TB_RAM.h"
#include "TB_noise.h"

int sc_main(int argc, char* argv[])
{
	sc_signal<sc_logic> CE, WE;// , listing_flag;
	sc_signal<sc_lv<8> > data;
	sc_signal<int> address,mem_addr_flag;
	
	sc_signal<sc_logic> CE_A, WE_A;// , listing_flag;
	sc_signal<sc_lv<8> > data_A;
	sc_signal<int> address_A, mem_addr_flag_A;

	sc_signal<sc_logic> CE_B, WE_B;// , listing_flag;
	sc_signal<sc_lv<8> > data_B;
	sc_signal<int> address_B, mem_addr_flag_B;

	cout << "              RAM MODEL\n" << "----------------------------------------\n\n";
	//RAM ram1("ram1", 2048,"C:\\Kannan\\T1.txt");  // 1024
	//TB_RAM test1("TB_RAM");
/*
	ram1.data(data);
	ram1.address(address);
	ram1.CE(CE);
	ram1.WE(WE);
	ram1.mem_addr_flag(mem_addr_flag);

	test1.data(data);
	test1.address(address);
	test1.CE(CE);
	test1.WE(WE);
	test1.mem_addr_flag(mem_addr_flag);
	*/
	
	
	RAM ramA("ramA", 1024, "C:\\Kannan\\T3.txt"); // Listing_A
	TB_noise test2("TB_NOISE");
	
	RAM ramB("ramB", 1024, "C:\\Kannan\\T3.txt",1);// Listing_B
	TB_noise test3("TB_NOISE",1); 


	ramA.data(data_A);
	ramA.address(address_A);
	ramA.CE(CE_A);
	ramA.WE(WE_A);
	ramA.mem_addr_flag(mem_addr_flag_A);
	
	ramB.data(data_B);
	ramB.address(address_B);
	ramB.CE(CE_B);
	ramB.WE(WE_B);
	ramB.mem_addr_flag(mem_addr_flag_B);
	


	test2.data(data_A);
	test2.address(address_A);
	test2.CE(CE_A);
	test2.WE(WE_A);
	test2.mem_addr_flag(mem_addr_flag_A);

	test3.data(data_B);
	test3.address(address_B);
	test3.CE(CE_B);
	test3.WE(WE_B);
	test3.mem_addr_flag(mem_addr_flag_B);

	
	sc_start();
	
	
	return(0);
}
