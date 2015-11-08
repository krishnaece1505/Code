--------------------------------------------------------------------------------- 
-- Module : Testbench for D Latch
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;


ENTITY test IS END test;

ARCHITECTURE testDbit OF test IS
COMPONENT D_latch
PORT (
d:IN std_logic;
clk:IN std_logic;
q:OUT std_logic);
END COMPONENT;

COMPONENT D_FF
PORT (
d:IN std_logic;
clk:IN std_logic;
q:OUT std_logic);
END COMPONENT;

SIGNAL test,clk,qLatch,qFlop:std_logic:='0';
BEGIN
U1:D_latch PORT MAP(test, clk,qLatch);
U2:D_FF PORT MAP(test, clk,qFlop);
clk <= not(clk) after 20 ns;
test<= '0',
'1' AFTER 20 ns,
'0' AFTER 40 ns,
'1' AFTER 70 ns,
'0' AFTER 75 ns,
'1' AFTER 125 ns;



END testDbit;
