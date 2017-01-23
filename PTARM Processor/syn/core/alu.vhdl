library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

--Source code adapted from:
--http://skdec.sourceforge.net/build_html/vhdl/arm/libs/armshiefter.html#aas_shieft

entity alu is
generic (
  DATAWIDTH : integer := 32);
port (
  opcode : in std_logic_vector(3 downto 0);
  op1, op2 : in std_logic_vector(DATAWIDTH-1 downto 0); 
  cc_in : in cond_code;
  cc_out : out cond_code;
  shiftcarry : in std_logic;
  results : out std_logic_vector(DATAWIDTH-1 downto 0));
end alu;

architecture rtl of alu is

  type alu_src_sel is (alu_src_logic, alu_src_adder);

  procedure adder(
  op1   : in std_logic_vector(DATAWIDTH-1 downto 0);
  op2   : in std_logic_vector(DATAWIDTH-1 downto 0);
  carry : in std_logic_vector(0 downto 0);
  sum   : out std_logic_vector(DATAWIDTH-1 downto 0)) is
  begin
    sum := std_logic_vector(unsigned(op1) + unsigned(op2) + unsigned(carry));
  end;
  
begin  -- rtl
  
-- purpose: Arithmetic Logic Unit
-- type   : combinational
-- inputs : opcode, op1, op2, carry_in
-- outputs: carry_out, results
alu: process (opcode, op1, op2, cc_in, shiftcarry)
  variable src : alu_src_sel;
  variable adder_result, logic_result, final_result : std_logic_vector(DATAWIDTH-1 downto 0) := (others => '0');
  variable log_AND, log_EOR, log_ORR : std_logic_vector(DATAWIDTH-1 downto 0);  -- logic cmds
  variable log_MOV, log_BIC, log_MVN : std_logic_vector(DATAWIDTH-1 downto 0);  --  move cmds
  variable t_op1, t_op2 : std_logic_vector(DATAWIDTH-1 downto 0);
  variable use_carry, is_sub, neg_c, use_shiftcarry : std_logic := '0';
  variable c_in : std_logic_vector(0 downto 0);
  variable alu_cc, newcpsr: cond_code;
  variable u_mask : std_logic_vector(3 downto 0);  -- n, z, c, v
begin

  c_in(0) := cc_in.c;
  is_sub := '0';
  use_carry := '0';
  u_mask := X"0";                       -- used to control which condition code
                                        -- to update
  neg_c := '0';
  use_shiftcarry := '0';
  adder_result := (others => '0');
  logic_result := (others => '0');
  t_op1 := (others => '0');
  t_op2 := (others => '0');

  -----------------------------------------------------------------------------
  -- LOGIC FUNCTIONS
  -----------------------------------------------------------------------------
  
  log_AND := op1 and op2;
  log_EOR := op1 xor op2;
  log_ORR := op1 or op2;
  log_MOV := op2;
  log_BIC := op1 and not op2;
  log_MVN := not op2;

  -----------------------------------------------------------------------------
  -- ALU CONTROL
  -----------------------------------------------------------------------------
  case opcode is
      when ALU_OP_AND => src := alu_src_logic; logic_result := log_AND;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_EOR => src := alu_src_logic; logic_result := log_EOR;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_SUB => src := alu_src_adder; is_sub := '1'; 
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111"; neg_c := '1';
      when ALU_OP_RSB => src := alu_src_adder; is_sub := '1'; 
                         t_op1 := op2;
                         t_op2 := op1;
                         u_mask := "1111"; neg_c := '1';
      when ALU_OP_ADD => src := alu_src_adder;
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111";
      when ALU_OP_ADC => src := alu_src_adder; use_carry := '1';
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111";
      when ALU_OP_SBC => src := alu_src_adder; use_carry := '1'; is_sub := '1'; c_in := not c_in; 
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111"; neg_c := '1';
      when ALU_OP_RSC => src := alu_src_adder; use_carry := '1'; is_sub := '1'; c_in := not c_in; 
                         t_op2 := op1;
                         t_op1 := op2;
                         u_mask := "1111"; neg_c := '1';
      when ALU_OP_TST => src := alu_src_logic; logic_result := log_AND;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_TEQ => src := alu_src_logic; logic_result := log_EOR;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_CMP => src := alu_src_adder; is_sub := '1'; 
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111"; neg_c := '1';
      when ALU_OP_CMN => src := alu_src_adder; 
                         t_op1 := op1;
                         t_op2 := op2;
                         u_mask := "1111";
      when ALU_OP_ORR => src := alu_src_logic; logic_result := log_ORR;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_MOV => src := alu_src_logic; logic_result := log_MOV;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_BIC => src := alu_src_logic; logic_result := log_BIC;
                         u_mask := "1110"; use_shiftcarry := '1';
      when ALU_OP_MVN => src := alu_src_logic; logic_result := log_MVN;
                         u_mask := "1110"; use_shiftcarry := '1';
      when others => null;
  end case;

  -----------------------------------------------------------------------------
  -- ALU ADDER
  -----------------------------------------------------------------------------
  if use_carry = '0' then
    c_in := "0";
  end if;
    
  if is_sub = '1' then
    t_op2 := not t_op2;
    c_in := not c_in;
  end if;                    

  adder(t_op1, t_op2, c_in, adder_result);


  -----------------------------------------------------------------------------
  -- LOGIC or ADDER MUX
  -----------------------------------------------------------------------------
  case src is
    when alu_src_adder => final_result := adder_result;
    when others => final_result := logic_result;
  end case;

  -----------------------------------------------------------------------------
  -- ALU CONDITION CODES 
  -----------------------------------------------------------------------------
  if is_sub = '1' then 
    -- If it's a subtraction, since the t_op2 has been flipped in line 137, we need to
    -- unflip them here, so t_op2 has been negated in the following operations
    alu_cc.c :=                         ((not t_op1(31)) and not t_op2(31)) or 	 -- Carry
                                           (final_result(31) and ((not t_op1(31)) or  (not t_op2(31))));
    alu_cc.v := (     t_op1(31)  and (t_op2(31)) and (not final_result(31))) or -- Overflow
                   ((not t_op1(31)) and   (not   t_op2(31))  and  final_result(31));
  else
    alu_cc.c :=                               (t_op1(31) and t_op2(31)) or 	 -- Carry
                                                 ((not final_result(31)) and (t_op1(31) or  t_op2(31)));
    alu_cc.v := (    t_op1(31)  and      t_op2(31) and not final_result(31)) or 	 -- Overflow
                   ((not t_op1(31)) and (not t_op2(31)) and    final_result(31));
  end if;
  
  if final_result = X"00000000" then
    alu_cc.z := '1';
  else
    alu_cc.z := '0';
  end if;

  alu_cc.n := final_result(31);
  
  -----------------------------------------------------------------------------
  -- Updating condition codes
  -----------------------------------------------------------------------------
  newcpsr := cc_in;

  if u_mask(3) = '1' then               -- n
    newcpsr.n := alu_cc.n;
  end if;
  if u_mask(2) = '1' then               -- z
    newcpsr.z := alu_cc.z;
  end if;
  if u_mask(1) = '1' then               -- c
    if use_shiftcarry = '1' then
      newcpsr.c := shiftcarry;
    else
      if neg_c = '1' then 
        newcpsr.c := not alu_cc.c;
      else
        newcpsr.c := alu_cc.c;      
      end if;
    end if;
  end if;
  if u_mask(0) = '1' then               -- v
    newcpsr.v := alu_cc.v;
  end if;

  results <= final_result;
  cc_out <= newcpsr;
end process alu;

end rtl;


