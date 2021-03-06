library ieee;
use ieee.std_logic_1164.all;

package arm_defs is
-------------------------------------------------------------------------------
-- CONSTANTS
-------------------------------------------------------------------------------
constant DATAWIDTH : integer := 32;
constant ADDRWIDTH : integer := 32;
constant REGADDRWIDTH : integer := 4;
constant THREADBITS : integer := 2;
constant SPMPOWERSIZE : integer := 15;
constant BOOTROMADDRWIDTH : integer := 10;

constant BOOTROM_MASK : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFF0000";
constant BOOTROM_RES : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0000";
constant THREAD0_RESET_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0000";
constant THREAD1_RESET_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0000";
constant THREAD2_RESET_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0000";
constant THREAD3_RESET_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0000";
-- TODO: currently just resets
constant THREAD0_EE_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0020";
constant THREAD1_EE_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0020";
constant THREAD2_EE_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0020";
constant THREAD3_EE_ADDR : std_logic_vector(ADDRWIDTH-1 downto 0) := X"FFFE0020";

subtype datawire is std_logic_vector(DATAWIDTH-1 downto 0);
subtype spm_addrwire is std_logic_vector(SPMPOWERSIZE+THREADBITS-1 downto 0);
subtype reg_addrwire is std_logic_vector(REGADDRWIDTH+THREADBITS-1 downto 0);

-------------------------------------------------------------------------------
-- PSR (Program Status Register)
-------------------------------------------------------------------------------
type cond_code is record	-- condition codes
  n : std_logic;      -- negative
  c : std_logic;      -- carry
  z : std_logic;      -- zero
  v : std_logic;      -- overflow
end record;

type irq_codes is record	-- Interrupt disable bits
  a : std_logic;		-- imprecise data aborts
  i : std_logic;		-- disable IRQ
  f : std_logic;		-- disable FIQ
end record;

type PSR is record                      -- program status register
  cc   : cond_code;                     -- condition code
  q    : std_logic;                     -- overflow or saturation
  ge   : std_logic_vector(3 downto 0);  -- greater than or equal
  e    : std_logic;                     -- endian
  idb  : irq_codes;                     -- interrupt disable bits
  mode : std_logic_vector(4 downto 0);  -- mode bits
  tid  : std_logic_vector(THREADBITS-1 downto 0);  -- added the thread bits as part of the PSR
end record;

-------------------------------------------------------------------------------
-- Instruction field 
-------------------------------------------------------------------------------
type instFields is record
	cond : std_logic_vector(3 downto 0);
	mainop : std_logic_vector(2 downto 0);
	opcode : std_logic_vector(3 downto 0);
	rn : std_logic_vector(3 downto 0);
	rd : std_logic_vector(3 downto 0);
	rm : std_logic_vector(3 downto 0);
	rs : std_logic_vector(3 downto 0);
	shift_amount : std_logic_vector(4 downto 0);
	shift : std_logic_vector(1 downto 0);
	imm8 : std_logic_vector(7 downto 0);
	imm12 : std_logic_vector(11 downto 0);
	offset24 : std_logic_vector (23 downto 0);
	s  : std_ulogic;
	opcode1 : std_logic_vector(3 downto 0);
	opcode2 : std_logic_vector(2 downto 0);
	shift_bit : std_logic_vector(0 downto 0);
	reglist : std_logic_vector(15 downto 0);
	LS_p : std_logic;
	LS_u : std_logic;
	LS_b : std_logic;
	LS_w : std_logic;
	LS_l : std_logic;
	B_l : std_logic;
end record;

-------------------------------------------------------------------------------
-- Instruction bits 
-------------------------------------------------------------------------------
constant INST_ROTATE_U : integer := 11;			-- imm rotate amount
constant INST_ROTATE_D : integer := 8;   
constant INST_IMMEDIATE_U    : integer := 7;		-- imm const
constant INST_IMMEDIATE_D    : integer := 0;   
constant INST_SHIFTAMOUNT_U   : integer := 11;	-- shift immediate amount
constant INST_SHIFTAMOUNT_D   : integer := 7;

-------------------------------------------------------------------------------
--  Condition Codes
-------------------------------------------------------------------------------
constant ARM_COND_EQ : std_logic_vector(3 downto 0) := "0000";
constant ARM_COND_NE : std_logic_vector(3 downto 0) := "0001";
constant ARM_COND_CS : std_logic_vector(3 downto 0) := "0010";
constant ARM_COND_CC : std_logic_vector(3 downto 0) := "0011";
constant ARM_COND_MI : std_logic_vector(3 downto 0) := "0100";
constant ARM_COND_PL : std_logic_vector(3 downto 0) := "0101";
constant ARM_COND_VS : std_logic_vector(3 downto 0) := "0110";
constant ARM_COND_VC : std_logic_vector(3 downto 0) := "0111";
constant ARM_COND_HI : std_logic_vector(3 downto 0) := "1000";
constant ARM_COND_LS : std_logic_vector(3 downto 0) := "1001";
constant ARM_COND_GE : std_logic_vector(3 downto 0) := "1010";
constant ARM_COND_LT : std_logic_vector(3 downto 0) := "1011";
constant ARM_COND_GT : std_logic_vector(3 downto 0) := "1100";
constant ARM_COND_LE : std_logic_vector(3 downto 0) := "1101";
constant ARM_COND_AL : std_logic_vector(3 downto 0) := "1110";
constant ARM_COND_NV : std_logic_vector(3 downto 0) := "1111";

-------------------------------------------------------------------------------
-- ALU OPCODES
-------------------------------------------------------------------------------
constant ALU_OP_AND : std_logic_vector(3 downto 0) := "0000";
constant ALU_OP_EOR : std_logic_vector(3 downto 0) := "0001";
constant ALU_OP_SUB : std_logic_vector(3 downto 0) := "0010";
constant ALU_OP_RSB : std_logic_vector(3 downto 0) := "0011";
constant ALU_OP_ADD : std_logic_vector(3 downto 0) := "0100";
constant ALU_OP_ADC : std_logic_vector(3 downto 0) := "0101";
constant ALU_OP_SBC : std_logic_vector(3 downto 0) := "0110";
constant ALU_OP_RSC : std_logic_vector(3 downto 0) := "0111";
constant ALU_OP_TST : std_logic_vector(3 downto 0) := "1000";
constant ALU_OP_TEQ : std_logic_vector(3 downto 0) := "1001";
constant ALU_OP_CMP : std_logic_vector(3 downto 0) := "1010";
constant ALU_OP_CMN : std_logic_vector(3 downto 0) := "1011";
constant ALU_OP_ORR : std_logic_vector(3 downto 0) := "1100";
constant ALU_OP_MOV : std_logic_vector(3 downto 0) := "1101";
constant ALU_OP_BIC : std_logic_vector(3 downto 0) := "1110";
constant ALU_OP_MVN : std_logic_vector(3 downto 0) := "1111";

-------------------------------------------------------------------------------
-- PIPELINE CONTROL SIGNALS
-------------------------------------------------------------------------------
type DEtoRegFile is record
  addr1 : std_logic_vector(REGADDRWIDTH-1 downto 0);
  addr2 : std_logic_vector(REGADDRWIDTH-1 downto 0);
  addr3 : std_logic_vector(REGADDRWIDTH-1 downto 0);
  addr1ValMux : std_logic;              -- used to select if rn value is loaded from register or the currentAddr field for load/store multiple
end record;

type ExOp1MuxSrc is (                   -- ALU op1 mux
  ExOp1PC, 
  ExOp1Reg
);

type ExOp2MuxSrc is (                   -- ALU op2 mux
  ExOp2Shifter, 
  ExOp2SIMM24,
  ExOp2IMM12,
  ExOP2PC,
  ExOp2TIMER,
  ExOp2InstCount,
  ExOp2VAL4
);

type shifter_type is (
  styp_none,  -- no shift
  styp_immrot,-- DAPRAM: OP2 immediate rotated
  styp_simm,  -- DAPRAM: OP2 shift with imm, LDSTAM: addr v1 reg (adm_LDSTAM_reg) 
  styp_sreg   -- DAPRAM: OP2 shift with reg  
);       

type shifter_op is (
  sOp_snone,    -- no shieft
  sOp_slsl,     -- LSL #: logical shift left 
  sOp_slsr,     -- LSR #: logical shift righ
  sOp_sasr,     -- ASR #: arithmetic shift left
  sOp_sror,     -- ROR #: rotate 
  sOp_srrx      -- RRX #: rotate 1 with carry
);

-- in delay until, alu needs borrow bit from timer_adder.
type alu_cc_src is (
	alu_cc_normal,			-- normal operation
	alu_cc_timer_adder	-- use carry from timer_adder
);


-- get time is multi-cycle
type ns_word_src is (
  ns_h_src,
  ns_l_src
);

type ExCtrlSig is record
	sh_op : shifter_op;								-- opcode for shifter
	sh_type : shifter_type;							-- address type for shifter
	op1_sel : ExOp1MuxSrc;							-- mux select for op1
	op2_sel : ExOp2MuxSrc;							-- mux select for op2
	alu_op : std_logic_vector(3 downto 0);		-- alu opcode
	alu_cc_sel : alu_cc_src;						-- mux for cc in to alu (allow for borrow from timer_adder)
	ns_word_sel : ns_word_src;						-- ns_word is passed to wb stage
	deadline_enable : std_logic;					-- enable/disable exception_on_expire
	deadline_disable : std_logic;					-- enable/disable exception_on_expire
	test_and_set : std_logic;						-- get mutex
	test_and_clear : std_logic;					-- release mutex
	reset_count : std_logic;						-- reset instruction and cycle counters
	cpsr_set : std_logic;							-- set cpsr from register
end record;                    

type MePCMuxSrc is (						-- PC mux src
	MeALUresult,
	MeRdVal,
	MePC4
);

type MeCtrlSig is record 
	-- memory control
	addr_src : std_logic;				-- pre-index or post-index address source
	we : std_logic;						-- write enable
	en : std_logic;						-- read enable
	ctrl : std_logic;						-- byte or word mode control

	-- Pipeline propagation control
	wb_cpsr : std_logic;					-- update the CPSR
	wb_pc_sel : MePCMuxSrc;				-- select what to update the PC with
	hold_pc : std_logic;					-- hold the PC for multi-cycle instructions
	bForward : std_logic;				-- bit for forwarding the loaded results into the pc
	cTime : std_logic;					-- check timer sub results on whether to forward the pc or not
end record;

type WbMuxSrc is (						-- writeback stage Mux sources
	WbALUresult,
	WbMemData,
	WbThreadID,
	WbTimer,
	WbMul,
	WbDiv,
	WbExceptionPC,
	WbPC4,
	WbCPSR,
	WbSPSR
);

type WbCtrlSig is record 
	wb_we : std_logic;												-- write enable
	wb_addr : std_logic_vector(REGADDRWIDTH-1 downto 0);	-- writeback address
	wb_sel : WbMuxSrc;												-- select which data to write back
end record;


-------------------------------------------------------------------------------
-- PIPELINE REGISTERS
-------------------------------------------------------------------------------
type lsMultState is record							-- the state stored when doing load store multiple
  RegList : std_logic_vector(15 downto 0);	-- register list. Bit position = register number
  valid   : std_logic;
  hold_pc : std_logic;								-- stall the pc until the multi-cycle load/store has finished.
  currentAddr : datawire;							-- the current register address
end record;

type pipeCtrl is record
  tid : std_logic_vector(THREADBITS-1 downto 0);  -- thread id
  cpsr : PSR;                           -- processor state register
  flush : std_logic;                    -- flush this instruction
  state : std_logic_vector(1 downto 0);
  pc4      : datawire;
  pc8      : datawire;
  exception : std_logic;
end record;

type thread_state is record
	npc : std_logic_vector(ADDRWIDTH-1 downto 0);				-- next program counter
	exception_pc : std_logic_vector(ADDRWIDTH-1 downto 0);	-- the pc on exception
	bForward : std_logic;												-- forwarding bit if previous instruction is load to pc
	cpsr : PSR;																-- current PSR
	spsr : PSR;																-- saved PSR on exception

	lsMult : lsMultState;												-- state information for load/store multiple
	state : std_logic_vector(1 downto 0);
	deadline : std_logic_vector(63 downto 0);						-- deadline in ns
	deadline_enabled : std_logic;										-- exception_on_expire enabled or not
end record;

type IFtoDEreg is record
	pc   : datawire;
	inst : datawire;
	ctrlPipe : pipeCtrl;
	lsMult : lsMultState;
end record;

type DEtoEXreg is record 
  inst     : datawire;
  regc_val : datawire;
  regd_val : datawire;
  rege_val : datawire;
  lsMult   : lsMultState;
  ctrlEx   : ExCtrlSig;
  ctrlMe   : MeCtrlSig;
  ctrlWb   : WbCtrlSig;
  ctrlPipe : pipeCtrl;
end record;

type EXtoMEreg is record 
	inst      : datawire;
	ALUresult : datawire;
	rn        : datawire;
	rd        : datawire;
	newCC     : cond_code;
	lsMult    : lsMultState;
	ns_word   : datawire;		-- either ns_h or ns_l
	timer_adder_z : std_logic;	-- if lower 32 bit sub of delay_until and time is zero
	ctrlMe    : MeCtrlSig;
	ctrlWb    : WbCtrlSig;
	ctrlPipe  : pipeCtrl;
end record;

type MEtoWBreg is record
	inst      : datawire;
	ALUresult : datawire;
	ns_word   : datawire; -- either ns_h or ns_l
	MemData   : datawire;
	newCC     : cond_code;
	ctrlWb    : WbCtrlSig;
	ctrlPipe  : pipeCtrl;
end record;

-------------------------------------------------------------------------------
-- INTERFACES
-------------------------------------------------------------------------------
-- IU_CONTROLLER
type iu_controller_in is record	-- input to iu_controller
  inst    : datawire;
  cc      : cond_code;  
  lsMult  : lsMultState;
  thread_state : std_logic_vector(1 downto 0);
end record;

type iu_controller_out is record	-- output of iu_controller
  DEtoReg : DEtoRegFile;
  ctrlEx  : ExCtrlSig;
  ctrlMe  : MeCtrlSig;
  ctrlWb  : WbCtrlSig;
  lsMult  : lsMultState;
  next_state : std_logic_vector(1 downto 0);	-- will be set if the instruction requires multiple cycles
end record;

-- State of the processor, which includes the state of each thread
type processor_state is array (2**THREADBITS-1 downto 0) of thread_state;  

type iu_probe_signals is record          -- data structure to pass up the probe values
	thread_states : processor_state;
	ex2me : EXtoMEreg;
	hold_pc_mux : std_logic;
	me_pipestate_mux : std_logic_vector(1 downto 0);
end record;
  
end arm_defs;
