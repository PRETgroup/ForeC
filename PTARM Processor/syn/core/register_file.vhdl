library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

-- 3 read ports and 1 write port
-- Top 2 bits are used to separate the different thread's register space
entity register_file IS
  generic (	
    DATAWIDTH: integer := 32;
    ADDRWIDTH  : integer := 4;
    THREADBITS : integer := 2);
  port (
    clk: IN std_logic;
    dina: IN std_logic_VECTOR(DATAWIDTH-1 downto 0);
    addra: IN std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
    wea: IN std_logic;
    addrc: IN std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
    doutc: OUT std_logic_VECTOR(DATAWIDTH-1 downto 0);
    addrd: IN std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
    doutd: OUT std_logic_VECTOR(DATAWIDTH-1 downto 0);
    addre: IN std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
    doute: OUT std_logic_VECTOR(DATAWIDTH-1 downto 0));
end register_file;

ARCHITECTURE sim OF register_file IS
  type register_file_type is array (0 to (2**(ADDRWIDTH+THREADBITS))-1) of std_logic_vector(DATAWIDTH-1 downto 0);
  signal REGFILE : register_file_type := (others => (others => '0'));
begin
    
  -- purpose: Synchronously read/write to the register
  -- type   : sequential
  -- inputs : clk, reset, addrc, addrd, addre, dina, dinb, addra, addrb, wea, web
  -- outputs: 
  register_read_write: process (clk)
  begin  -- process register_write
    if clk'event and clk = '1' then  -- rising clock edge
      doutc <= REGFILE(conv_integer(addrc));
      doutd <= REGFILE(conv_integer(addrd));
      doute <= REGFILE(conv_integer(addre));

      if (wea = '1') then
        REGFILE(conv_integer((addra))) <= dina;
      end if;
    end if;
  end process register_read_write;
end sim;

