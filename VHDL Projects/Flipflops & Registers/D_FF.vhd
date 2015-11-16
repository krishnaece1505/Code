--------------------------------------------------------------------------------- 
-- Module : D Flip Flop
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY D_FF IS
PORT(
d: IN std_logic;
clk: IN std_logic;
q: OUT std_logic);
END D_FF;

ARCHITECTURE behavioural OF D_FF IS
BEGIN
PROCESS(clk,d)
BEGIN
IF (rising_edge(clk)) THEN 
q<=d;
END IF;
END PROCESS;

END behavioural;
