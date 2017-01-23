library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

-- Increments time by 20ns, i.e., assumes a clock frequency of 50MHz
entity timer_64bit_ns is
  port (
    clk   : in  std_logic;
    reset : in  std_logic;
    nanoseconds : out std_logic_vector(63 downto 0));
end timer_64bit_ns;

architecture rtl of timer_64bit_ns is 
  signal ns_u_60 : std_logic_vector(58 downto 0) := (others => '0');
  signal ns_l_4 : std_logic_vector(4 downto 0) := (others => '0');
  signal carry : std_logic;
  signal count : std_logic_vector(4 downto 0) := (others => '0');

-- 64 bit ns counter is done in two stages. A 4-bit counter is incremented
-- in the 1st stage by 10ns and any overflow triggers a 60-bit accumulator 
-- in the 2nd stage. As long as at least 4 bits are used for the counter,
-- any distribution of 64 bits will work. Synthesized accumulators are cheaper
-- than counters. Two stages is acceptable because timer value isn't needed
-- until the execute stage.
-- TODO: parameterize
begin  -- rtl

-- 4-bit timer with overflow
counter: process (clk) is
  variable sum : std_logic_vector(5 downto 0);
begin
  if rising_edge(clk) then
    if reset = '1' then
      carry <= '0';
      count <= (others => '0');
    else
      sum := std_logic_vector(('0' & unsigned(count)) + 20);
      carry <= sum(5);
      count <= sum(4 downto 0);
    end if;
	 ns_l_4 <= count; -- delay count a cycle
  end if;
end process counter;

-- 60-bit accumulator
accumulator: process (clk)
begin
  if rising_edge(clk) then
    if reset = '1' then
      ns_u_60 <= (others => '0');
    elsif carry = '1' then
      ns_u_60 <= std_logic_vector(unsigned(ns_u_60) + 1);
    else
      ns_u_60 <= ns_u_60;
    end if;
  end if;
end process accumulator;

-- output timer
nanoseconds <= ns_u_60 & ns_l_4;


end rtl;
