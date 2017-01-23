library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all; 
use work.arm_defs.all; 

entity iu_controller is
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
end iu_controller;


architecture rtl of iu_controller is 
	-- check_condition_code
	function check_condition_code (
		inst  : in std_logic_vector(3 downto 0);
		cc : in cond_code
	) return std_logic is 
	variable valid : std_logic;
	begin 
		valid := '0';
		case inst is
			when ARM_COND_EQ => valid := cc.z;
			when ARM_COND_NE => valid := not cc.z;
			when ARM_COND_CS => valid := cc.c;
			when ARM_COND_CC => valid := not cc.c;
			when ARM_COND_MI => valid := cc.n;
			when ARM_COND_PL => valid := not cc.n;
			when ARM_COND_VS => valid := cc.v;
			when ARM_COND_VC => valid := not cc.v;
			when ARM_COND_HI => valid := cc.c and (not cc.z);
			when ARM_COND_LS => valid := (not cc.c) or cc.z;
			when ARM_COND_GE => valid := not (cc.n xor cc.v);
			when ARM_COND_LT => valid := (cc.n xor cc.v);
			when ARM_COND_GT => valid := (not cc.z) and not (cc.n xor cc.v);
			when ARM_COND_LE => valid := cc.z or (cc.n xor cc.v);
			when ARM_COND_AL => valid := '1';
			when ARM_COND_NV => valid := '0';
			when others      => null;
		end case;
		
		return not valid;
	end check_condition_code;  


	-- purpose: Fill in a data structure from the instruction to allow easier decoding and control logic
	-- type   : combinational
	-- inputs : inst
	-- outputs: ifields 
	procedure fill_pipeline_fields (
		inst: in std_logic_vector(31 downto 0);
		ifields: out instFields
	) is
	begin 
		ifields.cond := inst(31 downto 28);
		ifields.mainop := inst(27 downto 25);
		ifields.opcode := inst(24 downto 21);
		ifields.rm := inst(3 downto 0);
		ifields.rd := inst(15 downto 12);
		ifields.rn := inst(19 downto 16); 
		ifields.rs := inst(11 downto 8); 
		ifields.shift_amount := inst(11 downto 7);
		ifields.shift := inst(6 downto 5); 
		ifields.imm8 := inst(7 downto 0);
		ifields.imm12 := inst(11 downto 0); 
		ifields.offset24 := inst(23 downto 0);
		ifields.s := inst(20); 
		ifields.opcode1 := inst(23 downto 20);
		ifields.opcode2 := inst(7 downto 5);
		ifields.shift_bit := inst(4 downto 4);
		ifields.reglist := inst(15 downto 0);
		ifields.LS_p := inst(24);
		ifields.LS_u := inst(23);
		ifields.LS_b := inst(22);
		ifields.LS_w := inst(21);    
		ifields.LS_l := inst(20);
		ifields.B_l := inst(24);
	end fill_pipeline_fields;


	-- purpose: Decode the PUBWL bits for load/store instructions. Separated it out to a procedure to avoid code duplication
	-- type   : combinational
	-- inputs : ifields, state
	-- outputs: vDEtoReg, vctrlEx, vctrlMe, vctrlWb 
	procedure decode_loadstore_bits (
		state : in std_logic_vector(1 downto 0);
		ifields : in instFields;
		vDEtoReg : inout DEtoRegFile;
		vctrlEx : inout ExCtrlSig;
		vctrlMe : inout MeCtrlSig;
		vctrlWb : inout WbCtrlSig;
		nextstate: inout std_logic_vector(1 downto 0)
	) is 
	variable writetopc : std_logic := '0';
	begin 
		-- Memory operations require a state machine because they might take more than one cycle to finish.
		writetopc := ifields.rd(3) and ifields.rd(2) and ifields.rd(1) and ifields.rd(0);
  
		if state /= "01" then 
			if ifields.LS_u = '1' then			-- Add or subtract offset
				vctrlEx.alu_op := ALU_OP_ADD;
			else
				vctrlEx.alu_op := ALU_OP_SUB;
			end if;
			
			vctrlMe.ctrl := ifields.LS_b;		-- byte mode
			vctrlMe.en := '1';
			vctrlMe.we := not ifields.LS_l;	-- write to memory if it's not a load (i.e. store)
			vctrlWb.wb_sel := WbMemData;
			vctrlWb.wb_we := ifields.LS_l and not (ifields.LS_p and not ifields.LS_w and writetopc);	-- Write to register on load (unless offset addressing to PC).
			vDEtoReg.addr3 := ifields.rd;		-- in case it's a store, we want to read rd
			
			-- FIXME: Store PC is currently not implemented
			
			-- Check for ldr pc instruction.
			-- PC not actually stored in register file, so all ld to PC will be single cycle instructions.
			if ifields.LS_l = '1' and writetopc = '1' then
				vctrlMe.bForward := '1';			-- Always write value to pc
				vctrlWb.wb_addr := ifields.rn;	-- If not offset addressing (pre/post index), write value to register.
				vctrlWb.wb_sel := WbALUresult;
			end if;

			-- TODO: Add in when W = 1 or W = 0 privileged mode
			if ((not ifields.LS_p) or ifields.LS_w) = '1' and state = "00" and writetopc = '0' then 
				nextstate := "01";
			else
				nextstate := state;
			end if;

			-- Need to execute next state if it's pre or post index addressing mode to update the base register
			vctrlMe.hold_pc := (not ifields.LS_p) or ifields.LS_w;  -- hold pc if need another state
			vctrlMe.addr_src := not ifields.LS_p;  -- if post index, then choose the post index address source
		else    
			-- the second state of the multi-cycle instruction
			-- Used to store back the updated address in the index register
			vDEtoReg.addr1ValMux := '1';	-- use the accumulated currentAddr as base
			vctrlMe.addr_src := '1';		-- select the accumulated currentAddr to store back
			vctrlWb.wb_we := '1';
			vctrlWb.wb_addr := ifields.rn;
			vctrlWb.wb_sel := WbALUresult;
			vDEtoReg.addr3 := X"F";			-- load the previously stored pc address from register file
		end if;
	end decode_loadstore_bits;

	-- purpose: Get the shifter opcode from the shift bits
	-- type   : combinational
	-- inputs : shift_amount, shift
	-- outputs: shifter_op
	function get_shift_op (
		shift_amount : in std_logic_vector(4 downto 0);
		shift : in  std_logic_vector(1 downto 0)
	) return shifter_op is 
		variable sop : shifter_op;
	begin
		case shift is
			when "00" => sop := sOp_slsl;
			when "01" => sop := sOp_slsr;
			when "10" => sop := sOp_sasr;
			when "11" => if shift_amount = "00000" then 
								 sop := sOp_srrx;
							 else
								 sop := sOp_sror;
							 end if;
			when others => sop := sOp_snone;
		end case;
		
		return sop;
	end get_shift_op;

	procedure BitFlip16 (
		input : in std_logic_vector(15 downto 0);
		output : out std_logic_vector(15 downto 0)) is 
	begin 
		output(15) := input(0);
		output(14) := input(1);
		output(13) := input(2);
		output(12) := input(3);
		output(11) := input(4);
		output(10) := input(5);
		output(9) := input(6);
		output(8) := input(7);
		output(7) := input(8);
		output(6) := input(9);
		output(5) := input(10);
		output(4) := input(11);
		output(3) := input(12);
		output(2) := input(13);
		output(1) := input(14);
		output(0) := input(15);        
	end BitFlip16;
 
	procedure get_reg_from_reglist (
		rl : in std_logic_vector(15 downto 0);		-- register list
		flip : in std_logic;								-- flag to determine if priority is inverted
		rd : out std_logic_vector(3 downto 0);		-- destination register
		nrl : out std_logic_vector(15 downto 0)	-- new register list
	) is
	variable vrd : std_logic_vector(3 downto 0);
	variable irl : std_logic_vector(15 downto 0);
	variable vnrl : std_logic_vector(15 downto 0);
	begin 
		if flip = '0' then 
			BitFlip16(rl, irl);
		else
			irl := rl;
		end if;
  
		-- priority encoder
		if (irl(0) or irl(1) or irl(2) or irl(3)) = '1' then
			if (irl(0) or irl(1)) = '1' then
				if irl(0) = '1' then
					vrd := X"0"; 
					vnrl := irl and X"FFFE";
				else
					vrd := X"1"; 
					vnrl := irl and X"FFFD";
				end if;
			else
				if irl(2) = '1' then
					vrd := X"2"; 
					vnrl := irl and X"FFFB";
				else
					vrd := X"3"; 
					vnrl := irl and X"FFF7";
				end if;
			end if;
		elsif (irl(4) or irl(5) or irl(6) or irl(7)) = '1' then 
			if (irl(4) or irl(5)) = '1' then
				if irl(4) = '1' then
					vrd := X"4"; 
					vnrl := irl and X"FFEF";
				else
					vrd := X"5"; 
					vnrl := irl and X"FFDF";
				end if;
			else
				if irl(6) = '1' then
					vrd := X"6"; 
					vnrl := irl and X"FFBF";
				else
					vrd := X"7"; 
					vnrl := irl and X"FF7F";
				end if;
			end if;
		elsif (irl(8) or irl(9) or irl(10) or irl(11)) = '1' then 
			if (irl(8) or irl(9)) = '1' then
				if irl(8) = '1' then
					vrd := X"8"; 
					vnrl := irl and X"FEFF";
				else
					vrd := X"9"; 
					vnrl := irl and X"FDFF";
				end if;
			else
				if irl(10) = '1' then
					vrd := X"A"; 
					vnrl := irl and X"FBfF";
				else
					vrd := X"B"; 
					vnrl := irl and X"F7FF";
				end if;
			end if;
		elsif (irl(12) or irl(13) or irl(14) or irl(15)) = '1' then 
			if (irl(12) or irl(13)) = '1' then
				if irl(12) = '1' then
					vrd := X"C"; 
					vnrl := irl and X"EFFF";
				else
					vrd := X"D"; 
					vnrl := irl and X"DFFF";
				end if;
			else
				if irl(14) = '1' then
					vrd := X"E"; 
					vnrl := irl and X"BFFF";
				else
					vrd := X"F"; 
					vnrl := irl and X"7FFF";
				end if;
			end if;
		end if;

		if flip = '0' then
			BitFlip16(vnrl, nrl);               -- if reglist was flipped, flip it back
			rd := not vrd;                      -- if reglist was flipped, then the destination register also was flipped, so flip it back
		else
			nrl := vnrl;
			rd := vrd;
		end if;
	end get_reg_from_reglist;
begin
	-- purpose: The controller of the iu
	-- type   : combinational
	-- inputs : ctrl_i
	-- outputs: ctrl_o.DEtoReg, ctrlEx, ctrlMe, ctrlWb
	controller: process (ctrl_i)
		variable ifields : instFields;
		variable vlsMult : lsMultState;
		variable vDEtoReg : DEtoRegFile;
		variable vctrlEx : ExCtrlSig;
		variable vctrlMe : MeCtrlSig;
		variable vctrlWb : WbCtrlSig;
		variable bypass : std_logic;
		variable nextstate : std_logic_vector(1 downto 0);
		variable vlsMultexec : std_logic := '0';  -- used for load/store multiple decoding
		variable vlsMultdone : std_logic := '0';  -- used for load/store multiple decoding
	begin
		fill_pipeline_fields(ctrl_i.inst, ifields);

		-----------------------------------------------------------------------------
		-- Initialize output control signals
		-----------------------------------------------------------------------------
		vDEtoReg.addr1 := ifields.rn;
		vDEtoReg.addr2 := ifields.rm;
		vDEtoReg.addr3 := ifields.rs;
		vDEtoReg.addr1ValMux := '0';		-- default select reg val
	
		if ifields.rn = X"F" then			-- r15 is PC
			vctrlEx.op1_sel := ExOp1PC;
		else
			vctrlEx.op1_sel := ExOp1Reg;
		end if;
		
		vctrlEx.sh_op := get_shift_op(ifields.shift_amount, ifields.shift);
		vctrlEx.sh_type := styp_none;
		vctrlEx.op2_sel := ExOp2Shifter;
		vctrlEx.alu_op := ifields.opcode;
		vctrlEx.alu_cc_sel := alu_cc_normal;
		vctrlEx.ns_word_sel := ns_l_src;
		vctrlEx.deadline_enable := '0';
		vctrlEx.deadline_disable := '0';
		vctrlEx.test_and_set := '0';
		vctrlEx.test_and_clear := '0';
		vctrlEx.reset_count := '0';
		vctrlEx.cpsr_set := '0';
  
		vctrlMe.addr_src := '0'; 
		vctrlMe.we := '0';
		vctrlMe.en := '0';
		vctrlMe.ctrl := '0';
		vctrlMe.wb_cpsr := '0';
		vctrlMe.wb_pc_sel := MePC4;		-- default select pc+4
		vctrlMe.hold_pc := '0';				-- default don't hold the pc
		vctrlMe.bForward := '0';			-- default don't forward the load results
      vctrlMe.cTime := '0';				-- default don't check timer on whether to hold pc or not
  
		vctrlWb.wb_we := '0';
		vctrlWb.wb_addr := ifields.rd;	-- default write back to rd
		vctrlWb.wb_sel := WbALUresult;	-- default write back from ALU result

		vlsMult.valid := '0';
		vlsMult.hold_pc := '0';
		vlsMult.currentAddr := ctrl_i.lsMult.currentAddr;  
		vlsMult.RegList := ifields.reglist;
		vlsMultexec := '0';
		vlsMultdone := '0';
  
		bypass := check_condition_code(ifields.cond, ctrl_i.cc);
		nextstate := "00";

		if bypass = '0' then
			-----------------------------------------------------------------------------
			-- Decode Logic
			-----------------------------------------------------------------------------
			case ifields.mainop is
				when "000"  =>
					if ctrl_i.inst(4) = '1' then 
						if ctrl_i.inst(7) = '1' then
							----------------------------------------------------------------------
							-- MULTIPLY, EXTRA LOAD STORE
							----------------------------------------------------------------------
							-- mul:
							-- ops will come from regd/rm and rege/rs
							-- use result from multiplier instead of alu when result is available in the mem stage
							vctrlWb.wb_sel := WbMul;        -- default write back from ALU result
							vctrlWb.wb_we := '1';
							vctrlWb.wb_addr := ifields.rn;
							vctrlMe.wb_cpsr := ifields.s;
						else 
							if ifields.opcode(3 downto 2) = "10" and ifields.s = '0' then
								---------------------------------------------------------------------
								-- MISCELLANEOUS INSTRUCTIONS
								---------------------------------------------------------------------
								-- BX special case --
								vctrlEx.op2_sel := ExOp2Shifter;
								vctrlEx.alu_op := ALU_OP_MOV;
								vctrlMe.wb_pc_sel := MeALUresult;          
							else
								----------------------------------------------------------------------
								-- DATA PROCESSING REG SHIFT
								----------------------------------------------------------------------
								if ifields.rm = X"F" then					-- r15 is PC
									vctrlEx.op2_sel := ExOp2PC;
								end if;
								
								vctrlEx.sh_type := styp_sreg;
								vctrlMe.wb_cpsr := ifields.s;
								
								if ifields.rd = X"F" then
									vctrlMe.wb_pc_sel := MeALUresult;	-- branch
								else
									-- write back to reg as long as it's not TST, TEQ, CMP, CMN          
									vctrlWb.wb_we := not (ifields.opcode(3) and not ifields.opcode(2));
								end if;
							end if;
						end if;
					else
						----------------------------------------------------------------------
						-- DATA PROCESSING IMM SHIFT
						----------------------------------------------------------------------
						if ifields.rm = X"F" then							-- r15 is PC
							vctrlEx.op2_sel := ExOp2PC;
						end if;

						vctrlEx.sh_type := styp_simm;
						vctrlMe.wb_cpsr := ifields.s;
 
						if ifields.rd = X"F" then
							vctrlMe.wb_pc_sel := MeALUresult;			-- branch
						else
							-- write back to reg as long as it's not TST, TEQ, CMP, CMN          
							vctrlWb.wb_we := not (ifields.opcode(3) and not ifields.opcode(2));
						end if;
					end if;
				when "001"  =>
					if ctrl_i.inst(24 downto 23) = "10" and ctrl_i.inst (21 downto 20) = "00" then 
						---------------------------------------------------------------------
						-- UNDEFINED INSTRUCTION
						---------------------------------------------------------------------
						null;   -- dummy instruction
					elsif ctrl_i.inst(24 downto 23) = "10" and ctrl_i.inst (21 downto 20) = "10" then 
						---------------------------------------------------------------------
						-- MOVE IMMEDIATE TO STATUS REGISTER
						---------------------------------------------------------------------
						null;   -- dummy instruction
					else 
						-----------------------------------------------------------------------
						-- DATA PROCESSING IMMEDIATE
						-----------------------------------------------------------------------
						vctrlEx.sh_type := styp_immrot;
						vctrlMe.wb_cpsr := ifields.s;
						
						if ifields.rd = X"F" then
							vctrlMe.wb_pc_sel := MeALUresult;		-- branch
						else
							-- write back to reg as long as it's not TST, TEQ, CMP, CMN          
							vctrlWb.wb_we := not (ifields.opcode(3) and not ifields.opcode(2));
						end if;
					end if;
				when "010"  =>
					-------------------------------------------------------------------------
					-- LOAD/STORE IMMEDIATE OFFSET
					-------------------------------------------------------------------------
					vctrlEx.sh_type := styp_none;
					vctrlEx.op2_sel := ExOP2IMM12;
					decode_loadstore_bits(ctrl_i.thread_state, ifields, vDEtoReg, vctrlEx, vctrlMe, vctrlWb, nextstate);
					
					if ctrl_i.thread_state = "01" and ifields.rd = X"F"  and ifields.LS_l = '1' then
						vctrlMe.wb_pc_sel := MeRdVal;
					end if;
				when "011"  =>
					if ctrl_i.inst(4) = '0' then
						-----------------------------------------------------------------------
						-- LOAD/STORE REGISTER OFFSET
						-----------------------------------------------------------------------
						vctrlEx.sh_type := styp_simm;
						decode_loadstore_bits(ctrl_i.thread_state, ifields, vDEtoReg, vctrlEx, vctrlMe, vctrlWb, nextstate);
						
						if ctrl_i.thread_state = "01" and ifields.rd = X"F"  and ifields.LS_l = '1' then
							vctrlMe.wb_pc_sel := MeRdVal;
						end if;
					else
						if ctrl_i.inst(24 downto 20) = "11111" and ctrl_i.inst(7 downto 5) = "111" then 
							------------------------------------------------------------------------
							-- ARCHITECTURALLY UNDEFINED
							------------------------------------------------------------------------
							null;
						else
							-----------------------------------------------------------------------
							-- MEDIA INSTRUCTIONS
							-----------------------------------------------------------------------
							null;
						end if;
					end if;
				when "100"  =>
					-------------------------------------------------------------------------
					-- LOAD/STORE MULTIPLE
					-------------------------------------------------------------------------
					if ctrl_i.thread_state /= "01" then 
						-- use the accumulated currentAddr as base address
						vDEtoReg.addr1ValMux := ctrl_i.lsMult.valid;
						
						if ctrl_i.lsMult.valid = '1' then	-- have already started executing this instruction
							vlsMult.RegList := ctrl_i.lsMult.RegList;
						end if;
						
						if ifields.reglist /= X"0000" then	-- if reglist isn't X"0000", i.e., there is a list of registers
							vlsMultexec := '1';            
						end if;

						if ifields.LS_u = '1' then				-- add or subtract offset
							vctrlEx.alu_op := ALU_OP_ADD;
						else
							vctrlEx.alu_op := ALU_OP_SUB;
						end if;

						vctrlEx.op2_sel := ExOp2VAL4;			-- always increment or decrement by 4
						vctrlMe.en := vlsMultexec;
						vctrlMe.we := vlsMultexec and not ifields.LS_l;
 
						-- FIXME: Store PC is currently not implemented
  
						vctrlMe.addr_src := not ifields.LS_p;  -- post-index addressing
						vctrlWb.wb_we := vlsMultexec and ifields.LS_l;
						vctrlWb.wb_sel := WbMemData;
						get_reg_from_reglist(vlsMult.RegList, ifields.LS_u, vctrlWb.wb_addr, vlsMult.RegList);
						vDEtoReg.addr3 := vctrlWb.wb_addr;

						if vlsMult.RegList = X"0000" then		-- all registers will be serviced by the next cycle
							vlsMultdone := '1';
						end if;
						
						-- the valid bit is set if the instruction executes and bitmask isn't all cleared
						vlsMult.valid := vlsMultexec and not vlsMultdone;

						-- hold the pc if it's a valid execution and one of the following conditions occur:
						-- 1) instruction not done
						-- 2) instruction is done, but it needs to update base register
						-- 3) instruction is done, it doesn't need to update base register, but
						--    it needs to load to pc and it's a decrement address mode, in which
						--    the value is the first register value to be loaded, so we need an
						--    extra cycle to read it back and store it in the pc
						vctrlMe.hold_pc := vlsMultexec and ((not vlsMultdone) or ifields.LS_w or (not ifields.LS_u and ifields.LS_l and ifields.reglist(15)));

						-- increment the next state, unless we're stalled for dram access
						if (vlsMultexec and (vlsMultdone and (ifields.LS_w  or ((not ifields.LS_u) and ifields.LS_l and ifields.reglist(15))))) = '1' and ctrl_i.thread_state = "00" then 
							nextstate := "01";
						else
							nextstate := ctrl_i.thread_state;
						end if;
					else
						-- second state of multi-cycle instruction
						vDEtoReg.addr1ValMux := '1';	-- use the accumulated currentAddr as base
						vctrlMe.addr_src := '1';		-- select the accumulated currentAddr to store back
						vctrlWb.wb_we := ifields.LS_w;
						vctrlWb.wb_addr := ifields.rn;
						vctrlWb.wb_sel := WbALUresult;
						
						-- Check if load to PC
						if ifields.reglist(15) = '1' and ifields.LS_l = '1' then  
							vDEtoReg.addr3 := X"F";		-- load the previously stored pc address from register file
							vctrlMe.wb_pc_sel := MeRdVal;
						end if;
					end if;
				when "101"  =>
					-------------------------------------------------------------------------
					-- BRANCH AND BRANCH WITH LINK
					-------------------------------------------------------------------------
					vctrlEx.op1_sel := ExOp1PC;
					vctrlEx.op2_sel := ExOp2SIMM24;
					vctrlEx.alu_op := ALU_OP_ADD;
					vctrlMe.wb_pc_sel := MeALUresult;	-- update with results of ALU

					if ifields.B_l = '1' then         -- If there is a link
						vctrlWb.wb_we := '1';
						vctrlWb.wb_addr := X"E";       -- write back address is r14
						vctrlWb.wb_sel := WbPC4;
					end if;
				when "110"  => null;	--TODO: Add in decoding for coprocessor and software interrupt
				when "111"  =>
					if ctrl_i.inst(24) = '0' then 
						if ctrl_i.inst(4) = '0' then 
							---------------------------------------------------------------------
							-- COPROCESSOR DATA PROCESSING
							---------------------------------------------------------------------
							if ctrl_i.inst(11 downto 8) = X"D" then	-- Timer access is coprocessor 13 (D)
								case ctrl_i.thread_state is
									when "00" =>
										case ifields.opcode1 is 
											when X"0" => vctrlWb.wb_we := '1';						-- get thread id
															 vctrlWb.wb_sel := WbThreadID;
											when X"1" => --mutex
												case ifields.opcode2 is
													when "000" => vctrlEx.test_and_clear := '1';	-- release lock
													when "001" => vctrlEx.test_and_set := '1';	-- get lock
													when others => null;
												end case; 
											when X"2" => -- exception on expire enable
												-- data from rn loaded to regc (addr1ValMux must be 0)
												-- data from rm loaded to regd
												vctrlEx.deadline_enable := '1';
											when X"3" => vctrlEx.deadline_disable := '1';		-- exception on expire disable
											when X"4" => -- delay_until
												-- data from rn getting to alu op1 (through regc, addr1ValMux must be 0)
												vctrlEX.op2_sel := ExOp2TIMER; -- ns_h goes to op2 of alu
												
												-- data from rm getting to timer_adder a
												vctrlEx.alu_cc_sel := alu_cc_timer_adder; -- use carry from timer_adder
												vctrlEx.alu_op := ALU_OP_SBC;
												vctrlMe.cTime := '1'; -- PC held until cond_code is zero or negative.
											when X"8" => -- get_time
												-- To utilize existing hardware, ns_h is moved through op2 of the alu and is automatically stored in
												-- lsMult.currentAddr, storing the value until the next thread cycle.
												vctrlEx.alu_op := ALU_OP_MOV;
												vctrlEX.op2_sel := ExOp2TIMER; -- ns_h goes to op2 of alu
												
												-- The first cycle of get_time passes ns_l through ns_word registers into rn
												vctrlWb.wb_we := '1';
												vctrlWb.wb_addr := ifields.rm;
												vctrlWb.wb_sel := WbTimer;
												vctrlMe.hold_pc := '1';
												nextstate := "01";
											when X"9" => vctrlWb.wb_we := '1';		-- get exception pc
															 vctrlWb.wb_sel := WbExceptionPC;
											when X"F" => -- instruction and cycle counters
												case ifields.opcode2 is
													when "000" => vctrlEx.reset_count := '1';	-- reset both inst and cycle counter                     
													when "001" => -- write instruction counter to rd
														-- inst count is moved through op2 of alu and stored in lsMult.currentAddr so it can 
														-- be stored in the next cycle in rn
														-- ns_word is used to pass cycle counter through to be stored in rm
														vctrlEx.alu_op := ALU_OP_MOV;
														vctrlEx.op2_sel := ExOp2InstCount;
														vctrlWb.wb_we := '1';
														vctrlWb.wb_addr := ifields.rm;
														vctrlWb.wb_sel := WbTimer;
														vctrlMe.hold_pc := '1';
														nextstate := "01";
													when others => null;
												end case;
											when others => null;
										end case;
									when "01" =>
										case ifields.opcode1 is 
											when X"8" => -- 2nd thread cycle of get_time
												-- ns_h from last thread cycle is passed through ns_word registers into rd
												-- TODO hw restriction of registers?
												vctrlEx.ns_word_sel := ns_h_src;
												vctrlWb.wb_we := '1';
												vctrlWb.wb_addr := ifields.rn;
												vctrlWb.wb_sel := WbTimer;
												nextstate := "00";
											when X"F" => -- write cycle counter to rd
												vctrlEx.ns_word_sel := ns_h_src;
												vctrlWb.wb_we := '1';
												vctrlWb.wb_addr := ifields.rn;
												vctrlWb.wb_sel := WbTimer;
												nextstate := "00";
											when others => null;
										end case;
									when others => null;
								end case;            
							elsif ctrl_i.inst(11 downto 8) = X"C" then		-- PSR access is coprocessor 12 (C)
								case ctrl_i.thread_state is
									when "00" =>
										case ifields.opcode1 is 
											when X"0" => vctrlWb.wb_we := '1';	-- get SPSR
															 vctrlWb.wb_sel := WbSPSR;
											when X"1" => vctrlWb.wb_we := '1';	-- get CPSR
															 vctrlWb.wb_sel := WbCPSR;
											when X"2" => -- set CPSR
												-- data from rn loaded to regc (addr1ValMux must be 0)
												-- data from rm loaded to regd
												vctrlEx.cpsr_set := '1';
											when others => null;
										end case;
									when others => null;
								end case;
							elsif ctrl_i.inst(11 downto 8) = X"9" then		-- Divider is coprocessor 9 (9)
								case ctrl_i.thread_state is
									when "00" =>
										case ifields.opcode1 is 
											when X"0" =>
												-- div:
												-- data from rn loaded to regc (addr1ValMux must be 0)
												-- data from rm loaded to regd
												-- lpm_divide has a latency of 2 thread cycles (8 clock cycles)
												-- an additional thread cycle to write the result back to the destination register
												-- use result from divider instead of alu when result is available in the mem stage
												vctrlMe.hold_pc := '1';
												nextstate := "01";
											when others => null;
										end case;
									when "01" =>
										case ifields.opcode1 is 
											when X"0" =>
												vctrlMe.hold_pc := '1';
												nextstate := "10";
											when others => null;
										end case;
									when "10" =>
										case ifields.opcode1 is 
											when X"0" =>
												vctrlWb.wb_we := '1';
												vctrlWb.wb_sel := WbDiv;			-- default write back from ALU result
												vctrlWb.wb_addr := ifields.rd;
												nextstate := "00";
											when others => null;
										end case;
									when others => null;
								end case;
							end if;
						else
							---------------------------------------------------------------------
							-- COPROCESSOR REGISTER PROCESSING
							---------------------------------------------------------------------
							null;
						end if;
					else
						-----------------------------------------------------------------------
						-- SOFTWARE INTERRUPT
						-----------------------------------------------------------------------
						null;
					end if;
				when others => null;
			end case;
		end if;               -- if bypass

		vlsMult.hold_pc := vctrlMe.hold_pc;
		
		ctrl_o.DEtoReg <= vDEtoReg;
		ctrl_o.ctrlEx <= vctrlEx;
		ctrl_o.ctrlMe <= vctrlMe;
		ctrl_o.ctrlWb <= vctrlWb; 
		ctrl_o.lsMult <= vlsMult;
		ctrl_o.next_state <= nextstate;
	end process controller;
end architecture rtl;

