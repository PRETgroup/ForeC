library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all; 
use work.arm_defs.all;

library lpm;
use lpm.lpm_components.all;


-------------------------------------------------------------------------------
-- V4 Changes:
-- * Added instruction for 8-bit unsigned integer division with coprocessor 9
-- * Added instruction for getting the SPSR with coprocessor 12
-- * Added instructions for getting and setting the CPSR with coprocessor 12
-- * Delay an exception-on-expire until the current multicycle instruction 
--   finishes executing
-- V3 Changes:
-- * Added a bus interface to connect to IO
-- * Added a Mux to mux the data going into IO line or memory line
-- * Removed condition checker component and integrated it into the controller
-- V2 Changes:
-- * Removed the bypass wire and clocked the registers and SPM on the
--   negative clock edge
-- * Changed the circuitry of register and SPM to be clock synchronous and
--   removed the tri-state in attempt to infer bram
-- * Removed the generics since they are defined in arm_defs.
-- * Hooked up Mux for instruction address between BootROM and sram
-------------------------------------------------------------------------------

entity arm_iu_datapath is
	port (
		clk   : in std_ulogic;
		reset : in std_ulogic; --active low signal
		addrbus : out datawire;
		doutbus : out datawire;
		dinbus : in datawire;
		mem_read : out std_logic;
		mem_write : out std_logic;
		mem_tid : out std_logic_vector(THREADBITS-1 downto 0)
	);
end arm_iu_datapath;

architecture rtl of arm_iu_datapath is 
	-- purpose: reset the PSR (Program status register, see arm_defs)
	procedure resetPSR (
		tid : in std_logic_vector(THREADBITS-1 downto 0);
		CPSR : out PSR
	) is 
	variable outPSR : PSR;
	begin  -- resetPSR
		outPSR.cc.n := '0';
		outPSR.cc.c := '0';
		outPSR.cc.z := '0';
		outPSR.cc.v := '0';

		outPSR.idb.a := '0';
		outPSR.idb.i := '0';
		outPSR.idb.f := '0';

		outPSR.e := '0';
		outPSR.q := '0';
		outPSR.tid := tid;
		outPSR.mode := "00000";
		outPSR.ge := "0000";

		CPSR := outPSR;
	end resetPSR;

	procedure resetCoreState (
		CPUstate : out processor_state 
	) is 
	variable vCPUstate : processor_state;
	begin 
		vCPUstate(0).npc := THREAD0_RESET_ADDR;
		vCPUstate(1).npc := THREAD1_RESET_ADDR;
		vCPUstate(2).npc := THREAD2_RESET_ADDR;
		vCPUstate(3).npc := THREAD3_RESET_ADDR;
		resetPSR("00", vCPUstate(0).cpsr);
		resetPSR("01", vCPUstate(1).cpsr);
		resetPSR("10", vCPUstate(2).cpsr);
		resetPSR("11", vCPUstate(3).cpsr);
		vCPUstate(0).lsMult.valid := '0';
		vCPUstate(1).lsMult.valid := '0';
		vCPUstate(2).lsMult.valid := '0';
		vCPUstate(3).lsMult.valid := '0';
		vCPUstate(0).lsMult.hold_pc := '0';
		vCPUstate(1).lsMult.hold_pc := '0';
		vCPUstate(2).lsMult.hold_pc := '0';
		vCPUstate(3).lsMult.hold_pc := '0';
		vCPUstate(0).bForward := '0';
		vCPUstate(1).bForward := '0';
		vCPUstate(2).bForward := '0';
		vCPUstate(3).bForward := '0';   
		vCPUstate(0).state := "00";
		vCPUstate(1).state := "00";
		vCPUstate(2).state := "00";
		vCPUstate(3).state := "00";   
		vCPUstate(0).deadline_enabled := '0';
		vCPUstate(1).deadline_enabled := '0';
		vCPUstate(2).deadline_enabled := '0';
		vCPUstate(3).deadline_enabled := '0';  
		CPUstate := vCPUstate;
	end resetCoreState;
  
	component BootROM is 
		generic (
			DATAWIDTH : integer;
			ADDRWIDTH : integer
		);
		
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
	end component;
  
	component SPM is
		generic(
			POWERSIZE : integer;
			DATAWIDTH : integer;
			THREADBITS : integer
		);
		
		port (
			CLK : in std_logic;
			EN_A : in std_logic;                       -- Output enable A
			EN_B : in std_logic;                       -- Output enable B
			ADDR_A : in std_logic_vector(SPMPOWERSIZE+THREADBITS-1 downto 0);  -- Address
			DO_A : out std_logic_vector(DATAWIDTH-1 downto 0);    -- Data out
			ADDR_B : in std_logic_vector(SPMPOWERSIZE+THREADBITS-1 downto 0);  -- Address
			DI_B : in std_logic_vector(DATAWIDTH-1 downto 0);    -- Data in
			DO_B : out std_logic_vector(DATAWIDTH-1 downto 0);    -- Data out
			WEN_B : in std_logic;                       -- Write enable for B
			CTRL : in std_logic  -- Used to control B store type
		); 
	end component;

	component timer_64bit_ns		
		port (
			clk   : in  std_logic;
			reset : in  std_logic;
			nanoseconds : out std_logic_vector(63 downto 0)
		);
	end component;
    
	component timer_32
		port (
			clk   : in  std_logic;
			reset : in  std_logic;
			en : in std_logic;
			value : out std_logic_vector(31 downto 0)
		);
	end component;
    
	component iu_controller 
		generic (
			DATAWIDTH: integer := 32;
			ADDRWIDTH: integer := 32;
			REGADDRWIDTH  : integer := 4;
			THREADBITS: integer := 2;
			SPMPOWERSIZE : integer := 14
		);
		
		port (
			ctrl_i : in iu_controller_in;
			ctrl_o : out iu_controller_out
		);
	end component;

	component pc_adder
		generic (
			DATAWIDTH : integer := 32
		);
		
		port (
			pc : in std_logic_vector(DATAWIDTH-1 downto 0); 
			INC4, INC8 : out std_logic_vector(DATAWIDTH-1 downto 0)
		);
	end component;

	component addsub
		generic (
			DATAWIDTH : integer := 32
		);
		
		port (
			a : in std_logic_vector(DATAWIDTH-1 downto 0);
			b : in std_logic_vector(DATAWIDTH-1 downto 0);
			add : in std_logic;
			result : out std_logic_vector(DATAWIDTH-1 downto 0);
			cout : out std_logic
		);
	end component;
  
	component comparator 
		generic (
			n : integer := 32
		);
		
		port(
			a : in std_logic_vector(n-1 downto 0);
			b : in std_logic_vector(n-1 downto 0);
			lt: out std_logic;
			eq: out std_logic
		);
	end component;
  
	component register_file 
		generic (	
			DATAWIDTH: integer := 32;
			ADDRWIDTH  : integer := 4;
			THREADBITS : integer := 2
		);
		
		port (
			clk: in std_logic;
			dina: in std_logic_VECTOR(DATAWIDTH-1 downto 0);
			addra: in std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
			wea: in std_logic;
			addrc: in std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
			doutc: out std_logic_VECTOR(DATAWIDTH-1 downto 0);
			addrd: in std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
			doutd: out std_logic_VECTOR(DATAWIDTH-1 downto 0);
			addre: in std_logic_VECTOR(ADDRWIDTH+THREADBITS-1 downto 0);
			doute: out std_logic_VECTOR(DATAWIDTH-1 downto 0)
		);
	end component;

	component shifter
		port (
			inst  : in std_logic_vector(INST_ROTATE_U downto INST_IMMEDIATE_D);
			shiftOp   : in shifter_op;
			shiftType   : in shifter_type;
			data1 : in std_logic_vector(31 downto 0);
			data2 : in std_logic_vector(31 downto 0);
			carry : in std_logic;
			shiftout      : out std_logic_vector(31 downto 0);
			shiftcarryout : out std_logic);
	end component;

	component alu 
		generic (
			DATAWIDTH : integer := 32
		);
		
		port (
			opcode : in std_logic_vector(3 downto 0);
			op1, op2 : in std_logic_vector(DATAWIDTH-1 downto 0); 
			cc_in : in cond_code;
			cc_out : out cond_code;
			shiftcarry : in std_logic;
			results : out std_logic_vector(DATAWIDTH-1 downto 0)
		);
	end component;

	-- mul
	component multiplier
		port (
			a : in std_logic_vector(31 downto 0);
			b : in std_logic_vector(31 downto 0);
			p : out std_logic_vector(31 downto 0)
		);
	end component;

	-- div
	component LPM_DIVIDE
		generic (
			LPM_WIDTHN : natural;    -- MUST be greater than 0
			LPM_WIDTHD : natural;    -- MUST be greater than 0
			LPM_NREPRESENTATION : string := "UNSIGNED";
			LPM_DREPRESENTATION : string := "UNSIGNED";
			LPM_PIPELINE : natural := 0;
			LPM_TYPE : string := L_DIVIDE;
			LPM_HINT : string := "UNUSED"
		);
		
		port (
			NUMER : in std_logic_vector(LPM_WIDTHN-1 downto 0);
			DENOM : in std_logic_vector(LPM_WIDTHD-1 downto 0);
			ACLR : in std_logic := '0';
			CLOCK : in std_logic := '0';
			CLKEN : in std_logic := '1';
			QUOTIENT : out std_logic_vector(LPM_WIDTHN-1 downto 0);
			REMAIN : out std_logic_vector(LPM_WIDTHD-1 downto 0)
		);
	end component LPM_DIVIDE;


  -- Pipeline state signals
  signal nclk : std_logic;
  signal sthreadCounter : std_logic_vector(THREADBITS-1 downto 0);
  signal sCPUstate : processor_state;
  signal sIFtoDE_i, sIFtoDE_o : IFtoDEreg;
  signal sDEtoEX_i, sDEtoEX_o : DEtoEXreg;
  signal sEXtoME_i, sEXtoME_o : EXtoMEreg;
  signal sMEtoWB_i, sMEtoWB_o : MEtoWBreg;

  -- Intermediate wires
  --Fetch Stage
  signal IF_pc : datawire;
  signal IF_spm_addr_In : spm_addrwire;
  signal IF_spm_dout, IF_br_dout : datawire;
  signal IF_br_en, IF_br_nen : std_logic;
  -- Decode Stage
  signal DE_ctrl_i : iu_controller_in;
  signal DE_ctrl_o : iu_controller_out;
  signal DE_reg_In : DEtoRegFile;
  signal DE_reg_addr1_In, DE_reg_addr2_In, DE_reg_addr3_In : reg_addrwire;
  signal DE_addrc_val : datawire;          -- Used for input to mux load/store base address
  -- Execute Stage
  signal EX_alu_result : datawire;
  signal EX_shifter_to_ALU : datawire;
  signal EX_shifter_cout : std_logic;
  signal EX_alu_op1_Mux, EX_alu_op2_Mux : datawire;
  signal EX_simm24, EX_imm12 : datawire;
  signal nanoseconds : std_logic_vector(63 downto 0); -- from 64-bit timer
  signal deadline : std_logic_vector(63 downto 0); -- deadline for exception
  -- Memory Stage
  signal ME_spm_AddrB_Mux : datawire;
  signal ME_spm_AddrB_In : spm_addrwire;
  signal ME_rom_AddrB_In : std_logic_vector(BOOTROMADDRWIDTH-1 downto 0);
  signal ME_spm_wen, ME_spm_ren, ME_spm_enable : std_logic;  
  signal ME_pc_wb_Mux : datawire;
  signal ME_io_en: std_logic;
  signal ME_rom_en : std_logic;
  signal ME_spm_dout : datawire;
  signal ME_rom_dout : datawire;
  signal ME_memdata : datawire;
  signal ME_memdata_tmp : datawire;
  -- Writeback Stage
  signal WB_reg_we : std_logic;
  signal WB_reg_we_mux : std_logic;
  signal WB_reg_addr_In: reg_addrwire;
  signal WB_reg_din_Mux : datawire;
  
  -- Result of deadline comparison to current time
  signal deadline_eq : std_logic;
  signal deadline_lt : std_logic;
  signal deadline_exception : std_logic; -- if deadline exception should occur
  signal timer_adder_result : datawire;
  signal inst_count : datawire;
  signal cycle_count : datawire;
  signal en_cycle : std_logic;
  signal en_inst : std_logic;
  signal alu_cc_in : cond_code;
  signal alu_cc_out : cond_code;
  
  -- multiplier
  signal multiplier_result : std_logic_vector(31 downto 0);
  signal multiplier_cc_out : cond_code;

  -- divider
  signal divider_result : std_logic_vector(31 downto 0);

  -- mutex
  signal lock : std_logic_vector(2**THREADBITS - 1 downto 0);
  
  -- cpsr and spsr as datawires
  signal cpsr_reg, spsr_reg : datawire;
begin                                   -- rtl
  nclk <= not clk;
  
  -----------------------------------------------------------------------------
  -- Fetch stage connections
  -----------------------------------------------------------------------------
  -- Forwarding connection for load instructions straight to pc
  IF_pc <= sCPUstate(conv_integer(sthreadCounter)).npc when sCPUstate(conv_integer(sthreadCounter)).bForward = '0'
           else sMEtoWB_o.MemData;
  IF_spm_addr_In <= IF_pc(THREADBITS+SPMPOWERSIZE-1 downto 0);
  
  sIFtoDE_i.pc <= IF_pc;
  sIFtoDE_i.ctrlPipe.tid <= sthreadCounter;
  sIFtoDE_i.ctrlPipe.cpsr <= sCPUstate(conv_integer(sthreadCounter)).cpsr;
  sIFtoDE_i.ctrlPipe.state <= sCPUstate(conv_integer(sthreadCounter)).state;
  sIFtoDE_i.lsMult <= sCPUstate(conv_integer(sthreadCounter)).lsMult;
  sIFtoDE_i.ctrlPipe.flush <= '0';
  sIFtoDE_i.ctrlPipe.exception <= '0';
    
  IF_br_en <= '1' when (IF_pc and BOOTROM_MASK) = BOOTROM_RES else '0';
  IF_br_nen <= not IF_br_en;
  
  -- Mux to determine if data is coming in from BootROM or SPM
  sIFtoDE_i.inst <= IF_spm_dout when IF_br_en = '0' else IF_br_dout;

	boot : BootROM 
	generic map (
		DATAWIDTH => DATAWIDTH,
		ADDRWIDTH => BOOTROMADDRWIDTH
	) port map (
		CLK => nclk,
		EN_A => ME_rom_en,
		EN_B => IF_br_en,
		WEN_A => '0',
		ADDR_A => ME_rom_AddrB_in,
		DI_A => X"00000000",
		DO_A => ME_rom_dout,
		ADDR_B => IF_pc(BOOTROMADDRWIDTH+1 downto 2),
		DO_B => IF_br_dout
	);
  
	spms : spm
	generic map(
		POWERSIZE => SPMPOWERSIZE,
		DATAWIDTH => DATAWIDTH,
		THREADBITS => THREADBITS
	) port map (
		CLK => nclk,
		EN_A => IF_br_nen,
		EN_B => ME_spm_ren, 
		ADDR_A => IF_spm_addr_In,
		DO_A => IF_spm_dout,
		ADDR_B => ME_spm_AddrB_In,
		DI_B => sEXtoME_o.rd,
		DO_B => ME_spm_dout,
		WEN_B => ME_spm_wen,
		CTRL => sEXtoME_o.ctrlMe.ctrl
	); 

  -----------------------------------------------------------------------------
  -- Decode stage connections
  -----------------------------------------------------------------------------
  sDEtoEX_i.inst <= sIFtoDE_o.inst;
  sDEtoEX_i.ctrlPipe.tid <= sIFtoDE_o.ctrlPipe.tid;
  sDEtoEX_i.ctrlPipe.cpsr <= sIFtoDE_o.ctrlPipe.cpsr;
  sDEtoEX_i.ctrlPipe.flush <= sIFtoDE_o.ctrlPipe.flush;  
  sDEtoEX_i.ctrlPipe.exception <= sIFtoDE_o.ctrlPipe.exception; 
  
  -- Setting the controller input 
  DE_ctrl_i.inst <= sIFtoDE_o.inst;
  DE_ctrl_i.cc <= sIFtoDE_o.ctrlPipe.cpsr.cc;
  DE_ctrl_i.lsMult <= sIFtoDE_o.lsMult;
  DE_ctrl_i.thread_state <= sIFtoDE_o.ctrlPipe.state;
  
	brains: iu_controller 
	generic map (
		DATAWIDTH => DATAWIDTH,
		ADDRWIDTH => ADDRWIDTH,
		REGADDRWIDTH => REGADDRWIDTH,
		THREADBITS => THREADBITS,
		SPMPOWERSIZE => SPMPOWERSIZE
	) port map (
		ctrl_i => DE_ctrl_i,
		ctrl_o => DE_ctrl_o
	);

  -- Distributing the controller output
  DE_reg_in <= DE_ctrl_o.DEtoReg;
  sDEtoEX_i.ctrlEx <= DE_ctrl_o.ctrlEx;
  sDEtoEX_i.ctrlMe <= DE_ctrl_o.ctrlMe;
  sDEtoEX_i.ctrlWb <= DE_ctrl_o.ctrlWb;
  sDEtoEX_i.lsMult <= DE_ctrl_o.lsMult;
  sDEtoEX_i.ctrlPipe.state <= DE_ctrl_o.next_state;

  -- mux used to load in the rn value
  -- 0 : value is loaded from register (normal operations)
  -- 1 : value is loaded from currentAddr field (for load/store multiple or
  -- pre/post index addressing)
  sDEtoEX_i.regc_val <= DE_addrc_val when DE_reg_in.addr1ValMux = '0' else sDEtoEX_i.lsMult.currentAddr;
  
  DE_reg_addr1_In <= sIFtoDE_o.ctrlPipe.tid & DE_reg_In.addr1;
  DE_reg_addr2_In <= sIFtoDE_o.ctrlPipe.tid & DE_reg_In.addr2;
  DE_reg_addr3_In <= sIFtoDE_o.ctrlPipe.tid & DE_reg_In.addr3;

	addPC: pc_adder
	generic map (
		DATAWIDTH => DATAWIDTH
	) port map (
		pc => sIFtoDE_o.pc,
		INC4 => sDEtoEX_i.ctrlPipe.pc4,
		INC8 => sDEtoEX_i.ctrlPipe.pc8
	);

	-- 64 bit timer (time available in the execute stage)
	clock: timer_64bit_ns
	port map (
		clk => clk,
		reset => reset,
		nanoseconds => nanoseconds
	);
 
	reg: register_file 
	generic map (	
		DATAWIDTH => DATAWIDTH,
		ADDRWIDTH => REGADDRWIDTH,
		THREADBITS => THREADBITS
	) port map (
		clk => nclk,
		dina => WB_reg_din_Mux,
		addra => WB_reg_addr_In,
		wea => WB_reg_we,
		addrc => DE_reg_addr1_In,
		doutc => DE_addrc_val,
		addrd => DE_reg_addr2_In,
		doutd => sDEtoEX_i.regd_val,
		addre => DE_reg_addr3_In,
		doute => sDEtoEX_i.rege_val
	);
  
  -----------------------------------------------------------------------------
  -- Execute stage connections
  -----------------------------------------------------------------------------
  sEXtoME_i.inst <= sDEtoEX_o.inst;
  sEXtoME_i.ctrlPipe.tid <= sDEtoEX_o.ctrlPipe.tid;
  sEXtoME_i.ctrlPipe.cpsr <= sDEtoEX_o.ctrlPipe.cpsr;
  sEXtoME_i.ctrlPipe.state <= sDEtoEX_o.ctrlPipe.state;
  sEXtoME_i.ctrlPipe.pc4 <= sDEtoEX_o.ctrlPipe.pc4;
  sEXtoME_i.ctrlPipe.pc8 <= sDEtoEX_o.ctrlPipe.pc8;
  
  -- flush and exception need deadline exception results
  sEXtoME_i.ctrlMe <= sDEtoEX_o.ctrlMe;
  sEXtoME_i.ctrlWb <= sDEtoEX_o.ctrlWb;
  sEXtoME_i.rn <= sDEtoEX_o.regc_val;
  
  -- ns_word will contain ns_l in the 1st thread cycle of get_time, and ns_h
  -- in the 2nd (stored in lsMult to save registers...).
  sEXtoME_i.ns_word <= cycle_count when sDEtoEX_o.ctrlEx.op2_sel = ExOP2InstCount
                       else nanoseconds(31 downto 0)  when sDEtoEX_o.ctrlEx.ns_word_sel = ns_l_src
                       else sDEtoEX_o.lsMult.currentAddr;
        
  sEXtoME_i.rd <= sDEtoEX_o.rege_val(7 downto 0) & sDEtoEX_o.rege_val(7 downto 0) & sDEtoEX_o.rege_val(7 downto 0) & sDEtoEX_o.rege_val(7 downto 0) when sDEtoEX_o.ctrlMe.ctrl = '1'
                  else sDEtoEX_o.rege_val;

	shift: shifter
	port map (
		inst => sDEtoEX_o.inst(INST_ROTATE_U downto INST_IMMEDIATE_D),
		shiftOp => sDEtoEX_o.ctrlEx.sh_op,
		shiftType => sDEtoEX_o.ctrlEx.sh_type,
		data1 => sDEtoEX_o.regd_val,
		data2 => sDEtoEX_o.rege_val,
		carry => sDEtoEX_o.ctrlPipe.cpsr.cc.c,
		shiftout => EX_shifter_to_ALU,
		shiftcarryout => EX_shifter_cout
	);

	-- delay_until(31:0) - nanoseconds(31:0)
	timer_adder : addsub
	generic map (
		DATAWIDTH => DATAWIDTH
	) port map (
		a => sDEtoEX_o.regd_val,
		b => nanoseconds(31 downto 0),
		add => '0', -- subtract
		result => timer_adder_result
	);
	
  -- check if sub result is zero
  sEXtoME_i.timer_adder_z <= '1' when (timer_adder_result = X"00000000") else '0';
      
  EX_simm24 <= std_logic_vector(resize(signed(sDEtoEX_o.inst(23 downto 0)), 30)) & "00";
  EX_imm12 <= std_logic_vector(resize(unsigned(sDEtoEX_o.inst(11 downto 0)), 32));
  EX_alu_op1_Mux <= sDEtoEX_o.ctrlPipe.pc8 when sDEtoEX_o.ctrlEx.op1_sel = ExOp1PC 
						  else sDEtoEX_o.regc_val;
  EX_alu_op2_Mux <= EX_shifter_to_ALU when sDEtoEX_o.ctrlEx.op2_sel = ExOp2Shifter 
						  else EX_simm24 when sDEtoEX_o.ctrlEx.op2_sel = ExOp2SIMM24  
						  else EX_imm12 when sDEtoEX_o.ctrlEx.op2_sel = ExOp2IMM12 
						  else sDEtoEX_o.ctrlPipe.pc8 when sDEtoEX_o.ctrlEx.op2_sel = ExOp2PC 
						  else nanoseconds(63 downto 32) when sDEtoEX_o.ctrlEx.op2_sel = ExOp2TIMER 
						  else inst_count when sDEtoEX_o.ctrlEx.op2_sel = ExOp2InstCount 
						  else X"00000004";

  -- if subtraction result of lower 32-bits is negative, then need to borrow
  -- from upper 32 bit subtraction (looks like carry in to alu sbc)
  alu_cc_in.c <= not(timer_adder_result(31)) when sDEtoEX_o.ctrlEx.alu_cc_sel = alu_cc_timer_adder 
                 else sDEtoEX_o.ctrlPipe.cpsr.cc.c; 
  alu_cc_in.n <= sDEtoEX_o.ctrlPipe.cpsr.cc.n;
  alu_cc_in.z <= sDEtoEX_o.ctrlPipe.cpsr.cc.z;
  alu_cc_in.v <= sDEtoEX_o.ctrlPipe.cpsr.cc.v;

	al_unit : alu 
	generic map (
		DATAWIDTH => DATAWIDTH
	) port map (
		opcode => sDEtoEX_o.ctrlEx.alu_op,
		op1 => EX_alu_op1_Mux,
		op2 => EX_alu_op2_Mux,
		cc_in => alu_cc_in,
		cc_out => alu_cc_out,
		shiftcarry => EX_shifter_cout,
		results => EX_alu_result
	);

  -- move to later stage?
  multiplier_cc_out.c <= '0';
  multiplier_cc_out.n <= '1' when multiplier_result(31) = '1' else '0';
  multiplier_cc_out.z <= '1' when multiplier_result = X"00000000" else '0';
  multiplier_cc_out.v <= '0';

  -- need to change control signal from ctrlWb to ctrlEX
  sEXtoME_i.ALUresult <= multiplier_result when sDEtoEX_o.ctrlWb.wb_sel = WbMul 
								 else divider_result when sDEtoEX_o.ctrlWb.wb_sel = WbDiv 
								 else EX_alu_result;
  sEXtoME_i.newCC <= multiplier_cc_out when sDEtoEX_o.ctrlWb.wb_sel = WbMul else alu_cc_out;
  sEXtoME_i.lsMult.currentAddr <= EX_alu_result;
  sEXtoME_i.lsMult.valid <= sDEtoEX_o.lsMult.valid;
  sEXtoME_i.lsMult.hold_pc <= sDEtoEX_o.lsMult.hold_pc;
  sEXtoME_i.lsMult.RegList <= sDEtoEX_o.lsMult.RegList;

  -- get stored exception deadline
  deadline <= sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline;
  
  -- compare current time to deadline if exception_on_expire is enabled and a multi-cycle 
  -- instruction has finished.
  -- exception if: not a deactivate_exception instruction and deadline <= current time
  -- or deactivate_exception instruction and deadline < current time
  deadline_exception <= sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline_enabled
								and not (sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).lsMult.hold_pc or sDEtoEX_o.lsMult.hold_pc)
								and (
										(not sDEtoEX_o.ctrlEx.deadline_disable and (deadline_lt or deadline_eq)) 
										 or (sDEtoEX_o.ctrlEx.deadline_disable and deadline_lt)
									 );
    
  -- set exception and flush the instruction if a deadline exception occurs.
  sEXtoME_i.ctrlPipe.exception <= sDEtoEX_o.ctrlPipe.exception or deadline_exception;
  sEXtoME_i.ctrlPipe.flush <= sDEtoEX_o.ctrlPipe.flush or deadline_exception;
  
	-- compare exception deadline to current time
	deadline_compare : comparator
	generic map ( 
		n => 64
	) port map (
		a => deadline,
		b => nanoseconds,
		lt => deadline_lt,
		eq => deadline_eq
	);
  
	-- mul hardware multiplier uses execute and memory stage
	mul32 : multiplier
	port map (
		a => sDEtoEX_o.regd_val,
		b => sDEtoEX_o.rege_val,
		p => multiplier_result
	);
  
	div32: LPM_DIVIDE
	generic map(
		LPM_WIDTHN => 32,
		LPM_WIDTHD => 32,
		LPM_NREPRESENTATION => "UNSIGNED",
		LPM_DREPRESENTATION => "UNSIGNED",
		LPM_PIPELINE => 8,
		LPM_TYPE => L_DIVIDE,
		LPM_HINT => "LPM_REMAINDERPOSITIVE = TRUE, MAXIMIZE_SPEED = 9"
	) port map (
		NUMER => sDEtoEX_o.regc_val,
		DENOM => sDEtoEX_o.regd_val,
		CLOCK => clk,
		QUOTIENT => divider_result,
		REMAIN => open
	);
	  
  -- instruction and thread cycle counters are only enabled when thread 0 goes through the decode stage
  en_cycle <= '1' when sDEtoEX_o.ctrlPipe.tid = "00" else '0';
  en_inst <= '1' when en_cycle = '1' and sDEtoEX_o.ctrlPipe.state = "00" else '0';
  
	inst_counter : timer_32
	port map (
		clk => clk,
		reset => sDEtoEX_o.ctrlEx.reset_count,
		en => en_inst,
		value => inst_count
	);

	cycle_counter : timer_32
	port map (
		clk => clk,
		reset => sDEtoEX_o.ctrlEx.reset_count,
		en => en_cycle,
		value => cycle_count
	);
  
  -----------------------------------------------------------------------------
  -- Memory stage connections
  -- TODO : remove newCC from propagating? Do memory access instructions
  --        change CC?
  -- TODO : Does DeMuxing the addr and data signals save power?
  -----------------------------------------------------------------------------
  sMEtoWB_i.inst <= sEXtoME_o.inst;
  sMEtoWB_i.ctrlWb <= sEXtoME_o.ctrlWb;
  sMEtoWB_i.ctrlPipe <= sEXtoME_o.ctrlPipe;
  sMEtoWB_i.ns_word <= sEXtoME_o.ns_word;
  sMEtoWB_i.newCC <= sEXtoME_o.newCC;

  ME_spm_AddrB_Mux <= sEXtoME_o.ALUresult when sEXtoME_o.ctrlMe.addr_src = '0'
                      else sEXtoME_o.rn;
  ME_spm_AddrB_In <= ME_spm_AddrB_Mux(THREADBITS+SPMPOWERSIZE-1 downto 0);
  ME_rom_AddrB_in <= ME_spm_AddrB_Mux(BOOTROMADDRWIDTH+1 downto 2);

  -- memory mapped IO (in the FFFF XXXX memory range)
  ME_io_en <= '1' when ME_spm_AddrB_Mux(DATAWIDTH-1 downto 16) = X"FFFF" --or ME_spm_AddrB_Mux(DATAWIDTH-1 downto 28) = X"4" 
				  else '0';
  -- rom
  ME_rom_en <= '1' when (ME_spm_AddrB_Mux and BOOTROM_MASK) = BOOTROM_RES else '0';
  
  --FIX ME: limit the addressing of SPM to the size of spm
  ME_spm_enable <= '1' when conv_integer(ME_spm_AddrB_Mux(DATAWIDTH-1 downto THREADBITS+SPMPOWERSIZE)) = 0 else '0';
  ME_spm_wen <= sEXtoME_o.ctrlMe.we and (not sEXtoME_o.ctrlPipe.flush) and (not ME_io_en) and (not ME_rom_en) and ME_spm_enable;
  ME_spm_ren <= sEXtoME_o.ctrlMe.en and (not sEXtoME_o.ctrlPipe.flush) and (not ME_io_en) and (not ME_rom_en) and ME_spm_enable;
  
  -- IO bus connections
  addrbus <= ME_spm_AddrB_Mux;
  doutbus <= sEXtoME_o.rd;
  mem_read <= ME_io_en and sEXtoME_o.ctrlMe.en and (not sEXtoME_o.ctrlPipe.flush);
  mem_write <= ME_io_en and sEXtoME_o.ctrlME.we and (not sEXtoME_o.ctrlPipe.flush); 
  mem_tid <= sEXtoME_o.ctrlPipe.tid;

  ME_memdata <= dinbus when ME_io_en = '1'
                else ME_rom_dout when ME_rom_en = '1'
                else ME_spm_dout when ME_spm_enable = '1' --fix to limit spm read
				    else (others => '0'); --get 0 if there are no memory enabled

  -- load in byte mode if needed
  ME_memdata_tmp <= ME_memdata when sEXtoME_o.ctrlMe.ctrl = '0'
                    else X"000000" & ME_memdata(7 downto 0) when ME_spm_AddrB_In(1 downto 0) = "00"
                    else X"000000" & ME_memdata(15 downto 8) when ME_spm_AddrB_In(1 downto 0) = "01"
                    else X"000000" & ME_memdata(23 downto 16) when ME_spm_AddrB_In(1 downto 0) = "10"
                    else X"000000" & ME_memdata(31 downto 24) when ME_spm_AddrB_In(1 downto 0) = "11"
                    else X"00000000";
	
  -- do a RFU abort jump if needed
  sMEtoWB_i.MemData <= ME_memdata_tmp;

  -- the ALUresult could be a result from ALU or it could be a previous
  -- address calculation that is being stored back to the base register
  sMEtoWB_i.ALUresult <= ME_spm_AddrB_Mux when sEXtoME_o.ctrlME.bForward = '0' else sEXtoME_o.ALUresult;
    
  -- select what to write back to PC
  ME_pc_wb_Mux <= sEXtoME_o.ALUresult when sEXtoME_o.ctrlME.wb_pc_sel = MeALUresult
                  else sEXtoME_o.rd when sEXtoME_o.ctrlME.wb_pc_sel = MeRdVal
                  else sEXtoME_o.ctrlPipe.pc4;

  -----------------------------------------------------------------------------
  -- Writeback stage connections
  -----------------------------------------------------------------------------
  WB_reg_we_mux <= sMEtoWB_o.ctrlWb.wb_we or sMEtoWB_o.newCC.n when sMEtoWB_o.ctrlWB.wb_sel = WBTimer 
						 else sMEtoWB_o.ctrlWB.wb_we;
						 
  cpsr_reg <= X"000"
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.cc.n	-- cond_code
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.cc.c
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.cc.z
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.cc.v
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.q		-- q
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.ge		-- ge
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.e		-- e
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.idb.a	-- irq_codes
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.idb.i
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.idb.f
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.mode	-- mode
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).cpsr.tid;	-- thread id
				  
  spsr_reg <= X"000"
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.cc.n	-- cond_code
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.cc.c
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.cc.z
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.cc.v
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.q		-- q
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.ge		-- ge
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.e		-- e
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.idb.a	-- irq_codes
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.idb.i
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.idb.f
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.mode	-- mode
				  & sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).spsr.tid;	-- thread id
  
  WB_reg_din_Mux <= sMEtoWB_o.MemData when sMEtoWB_o.ctrlWb.wb_sel = WbMemData
                    else X"0000000" & B"00" & sMEtoWB_o.ctrlPipe.tid when sMEtoWB_o.ctrlWb.wb_sel = WbThreadID
						  else sCPUstate(conv_integer(sMEtoWB_o.ctrlPipe.tid)).exception_pc when sMEtoWB_o.ctrlWb.wb_sel = WbExceptionPC
						  else cpsr_reg when sMEtoWB_o.ctrlWb.wb_sel = WbCPSR
						  else spsr_reg when sMEtoWB_o.ctrlWb.wb_sel = WbSPSR
                    else sMEtoWB_o.ctrlPipe.pc4 when sMEtoWB_o.ctrlWb.wb_sel = WbPC4
                    else sMEtoWB_o.ns_word  when sMEtoWB_o.ctrlWb.wb_sel = WbTimer
                    else sMEtoWB_o.ns_word  when sMEtoWB_o.ctrlWb.wb_sel = WbTimer
                    else sMEtoWB_o.ALUresult;

  WB_reg_we <= WB_reg_we_mux and (not sMEtoWB_o.ctrlPipe.flush);
  WB_reg_addr_In <= sMEtoWB_o.ctrlPipe.tid & sMEtoWB_o.ctrlWb.wb_addr;

	--	purpose: The synchronous update of the pipeline registers
	-- type   : sequential
	-- inputs : clk, reset
	-- outputs: 
	datapath: process (clk)
		variable vCPUstate : processor_state;
	begin  -- process datapath
		if clk'event and clk = '1' then		-- rising clock edge
			if reset = '1' then					-- synchronous reset
				---------------------------------------------------------------------------
				-- Reset state and pipeline signals
				---------------------------------------------------------------------------
				-- reset thread counter
				sthreadCounter <= "00";
				
				-- reset thread states
				resetCoreState(vCPUstate);
				sCPUstate <= vCPUstate;
				
				-- flush the pipeline
				sIFtoDE_o.ctrlPipe.flush <= '1';
				sDEtoEX_o.ctrlPipe.flush <= '1';
				sEXtoME_o.ctrlPipe.flush <= '1';
				sMEtoWB_o.ctrlPipe.flush <= '1';
				
				-- reset lock
				lock <= (others=>'0');
			else
				---------------------------------------------------------------------------
				-- Propagate pipeline registers
				---------------------------------------------------------------------------
				sthreadCounter <= sthreadCounter + 1;  -- increment thread counter

				sIFtoDE_o <= sIFtoDE_i;
				sDEtoEX_o <= sDEtoEX_i;
				sEXtoME_o <= sEXtoME_i;
				sMEtoWB_o <= sMEtoWB_i;

				---------------------------------------
				-- Thread update in execute stage
				---------------------------------------
				if sDEtoEX_o.ctrlEx.deadline_enable = '1' then
					-- store deadline with exception_on_expire instruction
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline_enabled <= '1';
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline(63 downto 32) <= sDEtoEX_o.regc_val; 
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline(31 downto 0) <= sDEtoEX_o.regd_val;
				elsif sDEtoEX_o.ctrlEx.deadline_disable = '1' then
					-- deactivate with deactivate_exception instruction
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).deadline_enabled <= '0';
				end if;
		  
				if sDEtoEX_o.ctrlEx.test_and_set = '1' then
					if (conv_integer(lock) = 0) then
						-- no thread has the lock
						lock(conv_integer(sDEtoEX_o.ctrlPipe.tid)) <= '1';	-- give lock to the thread
					else
						-- a thread has the lock
						if (lock(conv_integer(sDEtoEX_o.ctrlPipe.tid)) = '0') then
							-- stall because that thread is not me
							sEXtoME_o.ctrlMe.hold_pc  <= '1';					-- thread will be in the ME stage in the next clock cycle
						end if;
					end if;
				elsif sDEtoEX_o.ctrlEx.test_and_clear = '1' then
					-- release the lock
					lock(conv_integer(sDEtoEX_o.ctrlPipe.tid)) <= '0';
				end if;
				
				if sDEtoEX_o.ctrlEx.cpsr_set = '1' then			
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.cc.n <= sDEtoEX_o.regd_val(19);			-- cond_code
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.cc.c <= sDEtoEX_o.regd_val(18);
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.cc.z <= sDEtoEX_o.regd_val(17);
					sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.cc.v <= sDEtoEX_o.regd_val(16);
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.q <= sDEtoEX_o.regd_val(15);				-- q
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.ge <= sDEtoEX_o.regd_val(14 downto 11);	-- ge
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.e <= sDEtoEX_o.regd_val(10);				-- e
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.idb.a <= sDEtoEX_o.regd_val(9);			-- irq_codes
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.idb.i <= sDEtoEX_o.regd_val(8);
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.idb.f <= sDEtoEX_o.regd_val(7);
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.mode <= sDEtoEX_o.regd_val(6 downto 2);	-- mode
				--	sCPUstate(conv_integer(sDEtoEX_o.ctrlPipe.tid)).cpsr.tid <= sDEtoEX_o.regd_val(1 downto 0);	-- thread id
				end if;
		  
				-----------------------------------------------------------------------
				-- THREAD UPDATE UNIT in the memory stage
				-----------------------------------------------------------------------
				if sEXtoME_o.ctrlPipe.flush = '0' then 
					if sEXtoME_o.ctrlMe.hold_pc = '0' then 
						-- delay-until instruction check
						if not (sEXtoME_o.ctrlMe.cTime = '1' and sEXtoME_o.newCC.n = '0' and (sEXtoME_o.newCC.z = '0' or sEXtoME_o.timer_adder_z = '0')) then
							sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).npc <= ME_pc_wb_Mux;
						end if;
					end if;
					
					if sEXtoME_o.ctrlMe.wb_cpsr = '1' then
						sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).cpsr.cc <= sEXtoME_o.newCC;
					end if;
					
					sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).lsMult <= sEXtoME_o.lsMult;				-- update lsMult state	
					sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).bForward <= sEXtoME_o.ctrlMe.bForward;	-- bit to forward the load result to pc
					sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).state <= sEXtoME_o.ctrlPipe.state;		-- state bit for multi-cycle instructions
				end if;
				
				-- handle deadline exception
				-- on deadline, sEXtoME is flushed so store that PC to restore executions (current instruction will finish executing)
				if sEXtoME_o.ctrlPipe.exception = '1' then
					case sEXtoME_o.ctrlPipe.tid is
						when "00" => sCPUstate(0).exception_pc <= sCPUstate(0).npc; 
										 sCPUstate(0).npc <= THREAD0_EE_ADDR; 
										 sCPUstate(0).deadline_enabled <= '0';
						when "01" => sCPUstate(1).exception_pc <= sCPUstate(1).npc; 
										 sCPUstate(1).npc <= THREAD1_EE_ADDR; 
										 sCPUstate(1).deadline_enabled <= '0';
						when "10" => sCPUstate(2).exception_pc <= sCPUstate(2).npc; 
										 sCPUstate(2).npc <= THREAD2_EE_ADDR; 
										 sCPUstate(2).deadline_enabled <= '0';
						when "11" => sCPUstate(3).exception_pc <= sCPUstate(3).npc; 
										 sCPUstate(3).npc <= THREAD3_EE_ADDR; 
										 sCPUstate(3).deadline_enabled <= '0';
						when others => null;
					end case;
					
					-- Save the Processor Status Register.
					sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).spsr <= sCPUstate(conv_integer(sEXtoME_o.ctrlPipe.tid)).cpsr;
				end if;
			end if;
		end if;
	end process datapath;

end architecture rtl;
