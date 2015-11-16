--------------------------------------------------------------------------------- 
-- Module : N-bit Register Behavioral Style
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity Reg is
  generic (size : integer);
  port(D : in std_logic_vector(size-1 downto 0);
       clk : in std_logic;
       q : out std_logic_vector(size-1 downto 0));
end Reg;       
architecture behavioural of Reg is 
begin
  Reg_D_FF : process(clk,D)
    begin
      if (rising_edge(clk)) then
      q <= D;
    end if;
    end process;
end behavioural;
