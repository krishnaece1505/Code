--------------------------------------------------------------------------------- 
-- Module : Testbench for Clock controller
--
-- Author : Krishnaswamy Kannan
---------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

entity test is end test;

architecture TB_clock of test is
component clock_controller is
  port(G_UP     : in std_logic;
       M_RESET : in std_logic;
       CLK    : in std_logic;
       SW : in std_logic;
       count_0 : out std_logic_vector(6 downto 0);
       count_1 : out std_logic_vector(6 downto 0));
end component;

signal SW : std_logic := '1';
signal UP : std_logic := '1';
signal RST : std_logic := '0';
signal clock : std_logic := '1';

signal digit0,digit1 : std_logic_vector(6 downto 0):=(others=>'0');

begin
  contr : clock_controller port map(UP,RST,clock,SW,digit0,digit1);
  SW <= '1' after 5 ns;
  RST <= '1' after 5 ns;
  UP <= '0' after 2000 ns;
  clock <= not(clock) after 15 ns;
end TB_clock;
