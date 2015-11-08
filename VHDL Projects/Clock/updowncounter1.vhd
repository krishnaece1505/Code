--------------------------------------------------------------------------------- 
-- Module : Up/Down Counter
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_signed.all; -- For arithmetic operations
use ieee.std_logic_arith.all; -- Conversion functions from int to vector & vice versa

entity updowncounter1 is
  port(UP     : in std_logic;
       CLK    : in std_logic;
       EN     : in std_logic;
       RST    : in std_logic;
       rst1   : in std_logic_vector(1 downto 0);
       OUT1   : out std_logic;
       OUT2   : out std_logic_vector(3 downto 0));
end updowncounter1;

architecture behavioural1 of updowncounter1 is
signal count : std_logic_vector(3 downto 0); 
signal count1 : integer:=0;
begin
process(clk,rst)
  begin
    if rst = '0' and rising_edge(clk) then -- Active Low
      count <= (others => '0');
 elsif rst1 = "00" and rising_edge(clk) then
  count <= "0101"; -- Reset 1st counter to '5' while Down counter is enabled
  elsif rst1 = "01" and rising_edge(clk) then
  count <= "1001"; -- Reset 2nd counter to '9' while Down counter is enabled
   elsif EN = '1' and rising_edge(clk) then
      case UP is
        when '1'    => count <= count + 1; 
        when others => count <= count - 1;
      end case; 
    end if;
	 
	  
	  end process;
  
  OUT1 <= '1' when (UP = '1' and count = 15) or (UP = '0' and count = 0) -- Used to signal if counter reaches its maximum
              else '0';
         
  OUT2 <= count;
end behavioural1;