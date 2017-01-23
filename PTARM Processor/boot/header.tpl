library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity BootROM is 
  generic (
    DATAWIDTH : integer := 32;
    ADDRWIDTH : integer := 5);
  port (
    CLK : in std_logic;
    EN_A : in std_logic;
    EN_B : in std_logic;
    WEN_A : in std_logic;
    ADDR_A : in std_logic_vector(ADDRWIDTH-1 downto 0);
    DI_A : in std_logic_vector(DATAWIDTH-1 downto 0);
    DO_A : out std_logic_vector(DATAWIDTH-1 downto 0);
    ADDR_B : in std_logic_vector(ADDRWIDTH-1 downto 0);
    DO_B : out std_logic_vector(DATAWIDTH-1 downto 0));
  
    -- NOTE! Make sure to hook addr signal to bits (4 downto 2),
    -- not starting from 0!! We assume its word aligned access only!!
end entity BootROM;
architecture behavioral of BootROM is
  type mem is array (((2**ADDRWIDTH) - 1) downto 0) of std_logic_vector(DATAWIDTH-1 downto 0);

  signal my_Rom : mem := (
