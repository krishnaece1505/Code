--------------------------------------------------------------------------------- 
-- Module : Full Adder
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity FA is
  port(a    : in bit;
       b    : in bit;
       cin  : in bit;
       sum  : out bit;
       cout : out bit);
       
end FA;

architecture dataflow of FA is
begin
  sum   <= a xor b xor cin;
  cout  <= (a and b)or(a and cin)or(b and cin);
end dataflow;
