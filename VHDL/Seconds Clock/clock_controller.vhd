--------------------------------------------------------------------------------- 
-- Module : Clock controller for Clock that displays seconds
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity clock_controller is
  port(G_UP     : in std_logic;
       M_RESET : in std_logic;
       CLK    : in std_logic;
       SW      : in std_logic;
       count_0 : out std_logic_vector(6 downto 0);
       count_1 : out std_logic_vector(6 downto 0));
end clock_controller;

architecture behavioural of clock_controller is
component updowncounter1 
  port(UP   : in std_logic;
       CLK    : in std_logic;
       EN     : in std_logic;
       RST    : in std_logic;
       rst1   : in std_logic_vector(1 downto 0);
       OUT1   : out std_logic;
       OUT2   : out std_logic_vector(3 downto 0));
end component;

component clock_divider is
    Port (
        clk_in : in  STD_LOGIC;
        reset  : in  STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end component;

component segment is 
port(switch : in std_logic;
binary_in : in std_logic_vector(3 downto 0);
hex_code : out std_logic_vector(6 downto 0));
end component;
 
signal COUNT0,COUNT1 : std_logic_vector(3 downto 0):=(others=>'0');
signal reset0,reset1 : std_logic := '1';
signal rst1_0,rst1_1 : std_logic_vector(1 downto 0) := (others=>'1')  ;--:= 'Z';
signal enable0,enable1 : std_logic := '0';
signal C_clock : std_logic;
signal OUT1,OUT2 : std_logic;


begin
  CLK_GEN : clock_divider port map(CLK,M_RESET,C_clock);
  COUNTER0 : updowncounter1 port map(G_UP,C_clock,enable0,reset0,rst1_0,OUT1,COUNT0); -- Counter for digit 0
  COUNTER1 : updowncounter1 port map(G_UP,C_clock,enable1,reset1,rst1_1,OUT2,COUNT1); -- COunter for digit 1
  DISPLAY0 : segment port map(SW,COUNT0,count_0);
  DISPLAY1 : segment port map(SW,COUNT1,count_1);
  process(C_clock)
    begin
    if (M_RESET = '0') then
        reset0 <= '0';
        reset1 <= '0';
     elsif rising_edge(C_clock) then
        reset0 <= '1';
        reset1 <= '1';
        rst1_0 <= "11";
            rst1_1 <= "11";
        enable1 <= '1';
        -- Clock that displays seconds
		-- Counts from 0 to 59 and resets while UP counter is enabled
		-- Counts from 59 down to 0 while DOWN counter is enabled
        if (COUNT1 = "1000"and G_UP = '1')  then
          enable0 <= '1';
          reset1  <= '0'; 
           elsif (COUNT0 = "0000" and COUNT1 = "0001" and G_UP = '0') or (COUNT0 = "0000" and COUNT1 = "0000" and G_UP = '0') then
            enable1 <= '1';
            rst1_0 <= "00";
            rst1_1 <= "01";
         elsif (COUNT1 = "0001" and G_UP = '0') then
           enable0 <= '1';
           enable1 <= '1';
           rst1_1 <= "01";
            
            
          else
          enable0 <= '0';
          reset1  <= '1';
          
         end if;
    
        if(COUNT0 = "0101") and (COUNT1 = "1001") and G_UP ='1' then
          reset0  <= '0';
        else 
          reset0  <= '1';
       end if;
       
       
      
   end if;
 
    end process;

end behavioural;