--------------------------------------------------------------------------------- 
-- Module : Seven segment display Hex code
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity segment is 
port(switch : in std_logic;
binary_in : in std_logic_vector(3 downto 0);
hex_code : out std_logic_vector(6 downto 0));
end segment;

architecture behavioural of segment is
begin
 
  process(switch,binary_in)
    begin
      
  if switch = '0' then
    hex_code <= "1111111"; -- To display nothing
  else
    case binary_in is
      when "0000" => hex_code <= "1000000"; -- To display 0
      when "0001" => hex_code <= "1111001"; -- To display 1
      when "0010" => hex_code <= "0100100"; -- To display 2
      when "0011" => hex_code <= "0110000"; -- To display 3
      when "0100" => hex_code <= "0011001"; -- To display 4
      when "0101" => hex_code <= "0010010"; -- To display 5
      when "0110" => hex_code <= "0000010"; -- To display 6
      when "0111" => hex_code <= "1111000"; -- To display 7
      when "1000" => hex_code <= "0000000"; -- To display 8
      when "1001" => hex_code <= "0011000"; -- To display 9
      when others => hex_code <= "1111111"; -- To display nothing
    end case;
  end if;
  end process;
end behavioural;