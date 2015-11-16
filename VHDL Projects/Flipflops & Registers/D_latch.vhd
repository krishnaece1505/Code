--------------------------------------------------------------------------------- 
-- Module : D Latch
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

ENTITY D_latch IS
PORT(
d: IN std_logic;
clk: IN std_logic;
q: OUT std_logic);
END D_latch;

ARCHITECTURE behavioural OF D_latch IS
BEGIN
PROCESS(clk,d)
BEGIN
IF (clk='1' o) THEN -- Level sensitive
q<=d;
END IF;
END PROCESS;
END behavioural;
