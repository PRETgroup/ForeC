library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

entity timer_32 is
  
  port (
    clk   : in  std_logic;
    reset : in  std_logic;
    en : in std_logic;
    value : out std_logic_vector(31 downto 0));
end timer_32;

architecture rtl of timer_32 is 
signal c : std_logic_vector(31 downto 0) := (others => '0');

begin  -- rtl

  
-- purpose: The actual timer
-- type   : sequential
-- inputs : clk, reset, re, sel
-- outputs: value
clock: process (clk, reset)
begin  -- process clock
  if clk'event and clk = '1' then    -- rising clock edge
      if reset = '1' then                   -- synchronous reset
        c <= (others => '0');
      elsif en = '1' then
        c <= std_logic_vector(unsigned(c) + X"00000001");
      end if;
  end if;
end process clock;

value <= c;
end rtl;
