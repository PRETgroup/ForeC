library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

entity pc_adder is
generic (
  DATAWIDTH : integer := 32);
port (
  pc : in std_logic_vector(DATAWIDTH-1 downto 0); 
  INC4, INC8 : out std_logic_vector(DATAWIDTH-1 downto 0));
end pc_adder;

architecture rtl of pc_adder is
begin  -- rtl
INC4 <= std_logic_vector(unsigned(pc) + X"00000004");
INC8 <= std_logic_vector(unsigned(pc) + X"00000008");
end rtl;


