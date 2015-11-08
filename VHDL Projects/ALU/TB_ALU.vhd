--------------------------------------------------------------------------------- 
-- Module : Testbench  for ALU
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity test is end test;
architecture test_alu of test is

component alu 
 generic (size : integer:=4);
  port(a    : in bit_vector(size-1 downto 0);
       b    : in bit_vector(size-1 downto 0);
       ctrl  : in bit_vector(1 downto 0);
       output : out bit_vector(size-1 downto 0);
       cout   : out bit);
end component;

signal test_vector1,test_vector2,sum : bit_vector(3 downto 0);
signal ctrl_in : bit_vector(1 downto 0);
signal co : bit;
begin
  comp1 : alu port map(test_vector1,test_vector2,ctrl_in,sum,co);
  test_vector1<="0001",
"0011" AFTER 10 ns,
"0001" AFTER 20 ns;
  test_vector2<="0001",
"0010" AFTER 10 ns,
"0000" AFTER 20 ns;
  ctrl_in<="10",
"00" AFTER 10 ns,
"01" AFTER 20 ns;
end test_alu;