library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

entity addsub is
  generic (
    DATAWIDTH : integer := 32
  );

  port(
    a : in std_logic_vector(DATAWIDTH-1 downto 0);
    b : in std_logic_vector(DATAWIDTH-1 downto 0);
    add : in std_logic;
    result : out std_logic_vector(DATAWIDTH-1 downto 0);
    cout : out std_logic
  );

end addsub;

architecture rtl of addsub is
begin
  process (a, b, add)
  variable sum : unsigned(DATAWIDTH downto 0);
  begin
    if(add = '1') then
      sum := ('0' & unsigned(a)) + ('0' & unsigned(b));
    else
      sum := ('0' & unsigned(a)) - ('0' & unsigned(b));
    end if;
    result <= std_logic_vector(sum(DATAWIDTH-1 downto 0));
    cout <= std_logic(sum(DATAWIDTH));
  end process;
end rtl;
