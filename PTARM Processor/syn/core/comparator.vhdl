library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

entity comparator is
  generic (
    n : integer := 32
  );

  port(
    a : in std_logic_vector(n-1 downto 0);
    b : in std_logic_vector(n-1 downto 0);
    lt: out std_logic;
    eq: out std_logic
  );

end comparator;

architecture rtl of comparator is
begin
  process (a, b)
  begin
    if(a < b) then
      lt <= '1';
      eq <= '0';
    elsif(a = b) then
      lt <= '0';
      eq <= '1';
    else
      lt <= '0';
      eq <= '0';
    end if;
  end process;
end rtl;
