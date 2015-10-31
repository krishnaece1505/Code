--------------------------------------------------------------------------------- 
-- Module : Adder/Subtractor
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity add_sub is
  generic (size : integer);
  port(a    : in bit_vector(size-1 downto 0);
       b    : in bit_vector(size-1 downto 0);
       cin  : in bit;
       out_sum : out bit_vector(size-1 downto 0);
       cout   : out bit);
end add_sub;

architecture behavioural of add_sub is
component FA
   port(a    : in bit;
       b    : in bit;
       cin  : in bit;
       sum  : out bit;
       cout  : out bit);
end component;
signal c_int : bit_vector(size downto 0);
signal b_int : bit_vector(size-1 downto 0);
begin
  c_int(0) <= cin;
  forloop: for i in 0 to size-1 generate
    begin
      b_int(i) <= b(i) xor cin;
      FAi : FA port map(a(i),b_int(i),c_int(i),out_sum(i),c_int(i+1));
    end generate forloop;
    cout <= c_int(size);
end behavioural;
