--------------------------------------------------------------------------------- 
-- Module : Testbench for N-bit register
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity test is 
 generic (size : integer :=4); -- Specify the register size here
end test;

architecture TB_Reg of test is
component Reg
 generic (size : integer:=test.size);
  port(D : in std_logic_vector(size-1 downto 0);
       clk : in std_logic;
       q : out std_logic_vector(size-1 downto 0));
end component;
signal test_vector, output : std_logic_vector(size-1 downto 0);
signal clk : std_logic;
begin
Reg1 : Reg port map(test_vector,clk,output);

test_vector <= "0001",
"0010" AFTER 10 ns,
"1000" AFTER 20 ns,
"1100" AFTER 30 ns;

clk <= '0',
'1' AFTER 10 ns,
'0' AFTER 20 ns,
'1' AFTER 30 ns;


end TB_Reg;
