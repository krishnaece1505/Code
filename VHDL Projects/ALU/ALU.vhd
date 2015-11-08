--------------------------------------------------------------------------------- 
-- Module : Arithmetic Logic Unit
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

entity alu is
  generic (size : integer:=4);
  port(a    : in bit_vector(size-1 downto 0);
       b    : in bit_vector(size-1 downto 0);
       ctrl  : in bit_vector(1 downto 0);
       output : out bit_vector(size-1 downto 0);
       cout   : out bit);
end alu;

architecture behavioural_alu of alu is

component add_sub
  generic (size : integer:=alu.size);
   port(a    : in bit_vector(size-1 downto 0);
       b    : in bit_vector(size-1 downto 0);
       cin  : in bit;
       out_sum : out bit_vector(size-1 downto 0);
       cout   : out bit);
end component;
signal ca_in,alu_cout : bit;
signal alu_out : bit_vector(size-1 downto 0);

begin
  addsub_unit : add_sub port map(a,b,ca_in,alu_out,alu_cout);
  process(ctrl,alu_out)
begin
    case ctrl is
    when "00" => -- ADD
      ca_in <= '0';
      output <= alu_out;
      cout <= alu_cout;
    when "01" => -- SUB
      ca_in <= '1';
      output <= alu_out;
      cout <= alu_cout;
    when "10" => -- NAND
      output <= a nand b;
      cout <= '0';
    when "11" => -- NOR
      output <= a nor b;
      cout <= '0';
    end case;
end process;  

end behavioural_alu;
