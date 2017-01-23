-- 5-stage PTARM core for development of timing instructions
-- (get_time, delay_until, exception_on_expire, deactivate_exception)
-- and DRAM controller with DMA. 
-- authors: Isaac Liu, Michael Zimmer

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;


-------------------------------------------------------------------------------
-- IO Addresses (Only 0xFFFF xxxx addresses are considered by ME_io_en)
-- 0xFFFF 0000 ~ 0xFFFF 000C - UART
-- 0xFFFF F000 - Switches and Keys
-- 0xFFFF FF00 - Green LEDs
-- 0xFFFF FF09 - Red LEDs
-- 0xFFFF FF20 ~ 0xFFFF FF58 - 7 Segments
-- 0xFFFF FF60 - LCD
-------------------------------------------------------------------------------

-- PTARM core including IO peripheral controllers
-- (currently just UART and LEDs, no DRAM or DVI)
entity ptarm is
	port (
		CLOCK_50: in std_logic;
		KEY : in std_logic_vector(3 downto 0);
		SW: in std_logic_vector(17 downto 0);
		UART_RXD : in std_ulogic;
		UART_TXD : out std_ulogic;
		LEDG : out std_logic_vector(8 downto 0);
		LEDR : out std_logic_vector(17 downto 0);
		HEX0 : out std_logic_vector(6 downto 0);
		HEX1 : out std_logic_vector(6 downto 0);
		HEX2 : out std_logic_vector(6 downto 0);
		HEX3 : out std_logic_vector(6 downto 0);
		HEX4 : out std_logic_vector(6 downto 0);
		HEX5 : out std_logic_vector(6 downto 0);
		HEX6 : out std_logic_vector(6 downto 0);
		HEX7 : out std_logic_vector(6 downto 0);
		LCD_DATA : out std_logic_vector(7 downto 0);
		LCD_EN : out std_logic;
		LCD_RS : out std_logic;
		LCD_RW : out std_logic;
		LCD_ON : out std_logic
	);
end ptarm;

architecture rtl of ptarm is 
	component arm_iu_datapath is
		port (
			clk   : in std_ulogic;
			reset : in std_ulogic; --active low signal
			
			-- IO bus to IO peripheral controllers 
			-- (currently just UART and LEDs, no DRAM or DVI)  
			addrbus : out datawire; 
			doutbus : out datawire;
			dinbus  : in datawire;
			
			-- Control signals used by DRAM controller 
			-- (Not currently used)
			mem_read : out std_logic;
			mem_write : out std_logic;
			mem_tid : out std_logic_vector(THREADBITS-1 downto 0)
		);
	end component;

	-- UART peripheral
	component UART is
		generic (
			ClockFreq : integer;
			Baud : integer;
			Width : integer;
			Parity : integer;
			StopBits : integer
		);
		
		port (
			Clock : in std_logic;
			Reset : in std_logic;
			DataIn : in std_logic_vector(Width-1 downto 0);
			DataInValid : in std_logic;
			DataInReady : out std_logic;
			DataOut : out std_logic_vector(Width-1 downto 0);
			DataOutValid : out std_logic;
			DataOutReady : in std_logic;
			SIn : in std_logic;
			SOut : out std_logic
		);
	end component;

	component Gateway is
		generic (
			CWidth : integer;
			WWidth : integer
		);
		
		port (
			Clock : in std_logic;
			Reset : in std_logic;
			DataIn : in std_logic_vector(CWidth-1 downto 0);
			DataInValid : in std_logic;
			DataInReady : out std_logic;
			DataOut : out std_logic_vector(CWidth-1 downto 0);
			DataOutValid : out std_logic;
			DataOutReady : in std_logic;
			ProcessorDataIn : out std_logic_vector(WWidth-1 downto 0);
			ProcessorDataOut : in std_logic_vector(WWidth-1 downto 0);
			ProcessorAddress : in std_logic_vector(WWidth-1 downto 0);
			ProcessorMemRead : in std_logic;
			ProcessorMemWrite : in std_logic
		);
	end component;

	signal clk, nclk, reset_clk : std_logic;
	signal locked: std_logic;
	signal dinbus, doutbus, addrbus : datawire;
	signal proc_read, proc_write : std_logic;
	signal uartinbus, uartoutbus : std_logic_vector(7 downto 0);
	signal DinValid, DinReady, DoutValid, DoutReady : std_logic;
	signal ProcessorDataIn : datawire;
	signal reset : std_logic;
begin
	iu : arm_iu_datapath 
	port map (
		clk => clk,
		reset => reset,
		addrbus => addrbus,
		doutbus => doutbus,
		dinbus => dinbus,
		mem_read => proc_read,
		mem_write => proc_write
	);

	uart_controller : Gateway
	generic map (
		CWidth => 8,
		WWidth => 32
	) port map (
		Clock => nclk,
		Reset => reset,
		DataIn => uartinbus,
		DataInValid => DinValid,
		DataInReady => DinReady,
		DataOut => uartoutbus,
		DataOutValid => DoutValid,
		DataOutReady => DoutReady,
		ProcessorDataIn => ProcessorDataIn,
		ProcessorDataOut => doutbus,
		ProcessorAddress => addrbus,
		ProcessorMemRead => proc_read,
		ProcessorMemWrite => proc_write
	);
  
	uart0 : UART 
	generic map (
		ClockFreq => 50000000,
		Baud => 115200,
		Width => 8,
		Parity => 0,
		StopBits => 1
	) port map (
		Clock => nclk,
		Reset => reset,
		DataIn => uartoutbus,
		DataInValid => DoutValid,
		DataInReady => DoutReady,
		DataOut => uartinbus,
		DataOutValid => DinValid,
		DataOutReady => DinReady,
		SIn => UART_RXD,
		SOut => UART_TXD
	);

	-- purpose: memory mapped io controller
	-- type   : sequential
	-- inputs : nclk, reset
	-- outputs: 
	mmio_controller: process (nclk, reset)
	begin  -- process led_controller
		if reset = '1' then                
			LEDG <= "110101010";
			LEDR <= "101010101010101010";
			HEX0 <= "0110110";
			HEX1 <= "1001001";
			HEX2 <= "0110110";
			HEX3 <= "1001001";
			HEX4 <= "0110110";
			HEX5 <= "1001001";
			HEX6 <= "0110110";
			HEX7 <= "1001001";
		elsif nclk'event and nclk = '1' then  -- rising clock edge
			if proc_write = '1' then
				case addrbus is
					when X"FFFFFF00" =>	LEDG <= doutbus(8 downto 0);
					when X"FFFFFF09" =>	LEDR <= doutbus(17 downto 0);
					when X"FFFFFF20" =>	HEX0 <= doutbus(6 downto 0);
					when X"FFFFFF28" =>	HEX1 <= doutbus(6 downto 0);
					when X"FFFFFF30" =>	HEX2 <= doutbus(6 downto 0);
					when X"FFFFFF38" =>	HEX3 <= doutbus(6 downto 0);
					when X"FFFFFF40" =>	HEX4 <= doutbus(6 downto 0);
					when X"FFFFFF48" =>	HEX5 <= doutbus(6 downto 0);
					when X"FFFFFF50" =>	HEX6 <= doutbus(6 downto 0);
					when X"FFFFFF58" =>	HEX7 <= doutbus(6 downto 0);
					when X"FFFFFF60" =>	LCD_EN <= doutbus(11);
												LCD_RS <= doutbus(10);
												LCD_RW <= doutbus(9);
												LCD_ON <= doutbus(8);
												LCD_DATA <= doutbus(7 downto 0);
					when others => null;
				end case;
			end if;
			
			if proc_read = '1' then
				case addrbus is 
					when X"FFFFF000" =>	dinbus <= "0000000000" & SW & KEY;
					when others		  =>	dinbus <= ProcessorDataIn;
				end case;
			end if;
		end if;
	end process mmio_controller;

	clk <= CLOCK_50;
	nclk <= not clk;
	reset <= not(KEY(0));
end architecture rtl;
