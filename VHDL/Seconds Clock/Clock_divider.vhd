--------------------------------------------------------------------------------- 
-- Module : Clock Divider that converts 50 Mhz to 1 Hz (1 second)
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_signed.all;
entity clock_divider is
    Port (
        clk_in : in  STD_LOGIC;
        reset  : in  STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end clock_divider;

architecture Behavioral of clock_divider is
    signal temp: STD_LOGIC;
    signal counter : integer range 0 to 50000000:= 0; -- Specify the clock frequency to be divided
begin
    frequency_divider: process (reset, clk_in) begin
        if (reset = '0') then
            temp <= '0';
            counter <= 0;
        elsif rising_edge(clk_in) then
            if (counter = 50000000/2) then  -- Clock_frequency/2
                temp <= NOT(temp);
                counter <= 0;
            else
                counter <= counter + 1;
            end if;
        end if;
    end process;
    
    clk_out <= temp;
end Behavioral;
