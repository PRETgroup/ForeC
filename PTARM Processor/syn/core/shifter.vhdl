library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.arm_defs.all;

--Source code adapted from:
--http://skdec.sourceforge.net/build_html/vhdl/arm/libs/armshiefter.html#aas_shieft

entity shifter is
port (
  inst  : in std_logic_vector(INST_ROTATE_U downto INST_IMMEDIATE_D);
  shiftOp   : in shifter_op;
  shiftType   : in shifter_type;
  data1 : in std_logic_vector(31 downto 0);
  data2 : in std_logic_vector(31 downto 0);
  carry : in std_logic;
  shiftout      : out std_logic_vector(31 downto 0);
  shiftcarryout : out std_logic);
end shifter;

architecture rtl of shifter is
  type shift_src is (shiftin_00,shiftin_32,shiftin_33,shiftin_prev);  
begin  -- rtl
-- purpose: A shifter for the ARM core
-- type   : combinational
-- inputs : inst, shiftOp, shiftType, data1, data2, carry
-- outputs: shiftout, shiftcarryout
shifter: process (inst, shiftOp, shiftType, data1, data2, carry)
  variable op1 : std_logic_vector(31 downto 0);
  variable op2 : std_logic_vector(4 downto 0);                        
  variable shiftin : std_logic_vector(64 downto 0);
  variable carryout : std_logic;
  variable carryoutsrc : shift_src;
begin
  
  carryoutsrc := shiftin_prev;
  carryout := carry;
  
  op1 := data1;
  op2 := (others => '0');
  shiftin := (others => '0');
  shiftin(32 downto 1) := data1;
  
  --                                       data1  data2   value   shiftval
  -- adm_DAPRAMxLDSTAM_DAPRAM_immrot:        -      -      imm      imm 
  -- adm_DAPRAMxLDSTAM_DAPRAMxLDSTAM_simm:   -     use    data1     imm
  -- adm_DAPRAMxLDSTAM_DAPRAM_sreg:         use    use    data1    data2
  -- adm_DAPRAMxLDSTAM_DAPRAM_none:          -     use    data1      0
  
  case shiftType is
    when styp_immrot  => -- (special msr case also)
      
      --  64  63               33  32 31          1  0
      -- +---+---+---------------+===+=============+---+
      -- |           op1         |       op1       | 0 |
      -- +---+---+---------------+ccc+=============+---+
      --         |    op1            |                   <<  1 (>>1) 
      --                      |       op1       |        << 31 (>>31)
      
      op1 := (others => '0');
      op1(7 downto 0) := inst(INST_IMMEDIATE_U downto INST_IMMEDIATE_D);
      
      shiftin := (others => '0');
      shiftin(32 downto 1) := op1;
      shiftin(64 downto 33) := op1;
      op2 := inst(INST_ROTATE_U downto INST_ROTATE_D) & "0";
      
      carryoutsrc := shiftin_32;

      if op2 = "00000" then -- == 0
        carryoutsrc := shiftin_prev;
        carryout := carry;
      end if;
      
    when styp_simm =>

      shiftin := (others => '0');
      shiftin(32 downto 1) := data1;
      
      case shiftOp  is 
        when sOp_slsl =>
          
          --$(del)
          --if shift_imm == 0 then /* Register Operand */
          --  shifter_operand = Rm
          --  shifter_carry_out = C Flag
          --else /* shift_imm > 0 */
          --  shifter_operand = Rm Logical_Shift_Left shift_imm
          --  shifter_carry_out = Rm[32 - shift_imm]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | c |           op1         |    000      | 0 |
          -- +---+---+------------ccc+===+=============+---+
          --       c |    op1            |                   << 31 (>>0)
          --                       c |       op1       |     << 0 (>>31)
            
          shiftin := (others => '0');
          shiftin(64) := carry;
          shiftin(63 downto 32) := data1;
          op2 := not inst(INST_SHIFTAMOUNT_U downto INST_SHIFTAMOUNT_D);
          
          carryoutsrc := shiftin_33;
       
          -- if shift_imm == 0, shifter_carry_out = C flag
          if inst(INST_SHIFTAMOUNT_U downto INST_SHIFTAMOUNT_D) = "00000" then
            carryoutsrc := shiftin_prev;
            carryout := carry;
          end if;

        when sOp_slsr =>
          
          --$(del)
          --if shift_imm == 0 then
          --  shifter_operand = 0
          --  shifter_carry_out = Rm[31]
          --else /* shift_imm > 0 */
          --  shifter_operand = Rm Logical_Shift_Right shift_imm
          --  shifter_carry_out = Rm[shift_imm - 1]
          --$(/del)
          
          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | 0 | 0 |    000        |        op1      | c |
          -- +---+---+---------------+===+=============+ccc+
          --                         |     op1         |     >> 0
          --                                       |op1|     >> 31 
          
          shiftin := (others => '0');
          shiftin(0) := carry;
          shiftin(32 downto 1) := data1;
          op2 := inst(INST_SHIFTAMOUNT_U downto INST_SHIFTAMOUNT_D);

          carryoutsrc := shiftin_00;
          
        when sOp_sasr =>
          --$(del)
          --if shift_imm == 0 then
          --  if Rm[31] == 0 then
          --    shifter_operand = 0
          --    shifter_carry_out = Rm[31]
          --  else /* Rm[31] == 1 */
          --    shifter_operand = 0xFFFFFFFF
          --    shifter_carry_out = Rm[31]
          --else /* shift_imm > 0 */
          --  shifter_operand = Rm Arithmetic_Shift_Right <shift_imm>
          --  shifter_carry_out = Rm[shift_imm - 1]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | s | s |    sss        |        op1      | c |
          -- +---+---+---------------+===+=============+ccc+
          --                           s |    op1      |     >> 1
          --                                  sss  |op1|     >> 31 
          --                                  000      | 0   >> 0 (s=0)
          --                                  111      | 1   >> 0 (s=1)
          if data1(31) = '1' then
            shiftin(64 downto 33) := (others => '1');
          else
            shiftin(64 downto 33) := (others => '0');
          end if;
          shiftin(0) := carry;
          shiftin(32 downto 1) := data1;
          op2 := inst(INST_SHIFTAMOUNT_U downto INST_SHIFTAMOUNT_D);
          
          if op2 = "00000" then
            if data1(31) = '1' then
              shiftin(32 downto 0) := (others => '1');
            else
              shiftin(32 downto 0) := (others => '0');
            end if;
          end if;
          
          carryoutsrc := shiftin_00;
      
        when sOp_sror =>
          
          --$(del)
          --if shift_imm == 0 then
          --  sOp_srrx case
          --else /* shift_imm > 0 */
          --  shifter_operand = Rm Rotate_Right shift_imm
          --  shifter_carry_out = Rm[shift_imm - 1]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- |           op1         |       op1       | 0 |
          -- +---+---+---------------+ccc+=============+---+
          --         |    op1            |                   <<  1 (>>1) 
          --                      |       op1       |        << 31 (>>31)

          shiftin := (others => '0');
          shiftin(64 downto 33) := data1;
          shiftin(32 downto 1) := data1;
          op2 := inst(INST_SHIFTAMOUNT_U downto INST_SHIFTAMOUNT_D);
          
          carryoutsrc := shiftin_32;
          
        when sOp_srrx =>
      
          --$(del)
          --shifter_operand = (C Flag Logical_Shift_Left 31) OR (Rm Logical_Shift_Right 1)
          --shifter_carry_out = Rm[0]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- |           000         | c |    op1-1        |
          -- +---+---+---------------+===+=============+ccc+
          --                                                 : rrx 
          
          shiftin(31 downto 0) := data1;
          shiftin(32) := carry;
          op2 := (others => '0');
          
          carryoutsrc := shiftin_00;
          
        when sOp_snone =>
          op2 := (others => '0');
        when others => null;
      end case;


      
    when styp_sreg =>

      shiftin := (others => '0');
      shiftin(32 downto 1) := data1;

      case shiftOp  is 
        when sOp_slsl =>
      
          --$(del)
          --if Rs[7:0] == 0 then
          --  shifter_operand = Rm
          --  shifter_carry_out = C Flag
          --else if Rs[7:0] < 32 then
          --  shifter_operand = Rm Logical_Shift_Left Rs[7:0]
          --  shifter_carry_out = Rm[32 - Rs[7:0]]
          --else if Rs[7:0] == 32 then
          --  shifter_operand = 0
          --  shifter_carry_out = Rm[0]
          --else /* Rs[7:0] > 32 */
          --  shifter_operand = 0
          --  shifter_carry_out = 0
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | c |           op1         |    000      | 0 |
          -- +---+---+------------ccc+===+=============+---+
          --       c |    op1            |                   << 31 (>>0)
          --                       c |       op1       |     << 0 (>>31)
            
          shiftin := (others => '0');
          shiftin(64) := carry;
          shiftin(63 downto 32) := data1;
          op2 := not data2(4 downto 0);
          
          carryoutsrc := shiftin_33;
          
          if not (data2(7 downto 5) = "000") then -- >= 32
            shiftin := (others => '0');
            if data2(7 downto 0) = "00100000" then  -- == 32
              carryoutsrc := shiftin_prev;
              carryout := data1(0);
            end if;
          end if;
          
        when sOp_slsr =>

          --$(del)
          --if Rs[7:0] == 0 then
          --  shifter_operand = Rm
          --  shifter_carry_out = C Flag
          --else if Rs[7:0] < 32 then
          --  shifter_operand = Rm Logical_Shift_Right Rs[7:0]
          --  shifter_carry_out = Rm[Rs[7:0] - 1]
          --else if Rs[7:0] == 32 then
          --  shifter_operand = 0
          --  shifter_carry_out = Rm[31]
          --else /* Rs[7:0] > 32 */
          --  shifter_operand = 0
          --  shifter_carry_out = 0
          --$(/del)
      
          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | 0 | 0 |    000        |        op1      | c |
          -- +---+---+---------------+===+=============+ccc+
          --                         |     op1         |     >> 0
          --                                       |op1|     >> 31 
          
          shiftin := (others => '0');
          shiftin(0) := carry;
          shiftin(32 downto 1) := data1;
          op2 := data2(4 downto 0);

          carryoutsrc := shiftin_00;
          
          if not (data2(7 downto 5) = "000") then -- >= 32
            shiftin := (others => '0');
            if data2(7 downto 0) = "00100000" then  -- == 32
              carryoutsrc := shiftin_prev;
              carryout := data1(31);
            end if;
          end if;
          
        when sOp_sasr =>
          --$(del)
          --if Rs[7:0] == 0 then
          --  shifter_operand = Rm
          --  shifter_carry_out = C Flag
          --else if Rs[7:0] < 32 then
          --  shifter_operand = Rm Arithmetic_Shift_Right Rs[7:0]
          --  shifter_carry_out = Rm[Rs[7:0] - 1]
          --else /* Rs[7:0] >= 32 */
          --  if Rm[31] == 0 then
          --    shifter_operand = 0
          --    shifter_carry_out = Rm[31]
          --  else /* Rm[31] == 1 */
          --    shifter_operand = 0xFFFFFFFF
          --    shifter_carry_out = Rm[31]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- | s | s |    sss        |        op1      | c |
          -- +---+---+---------------+===+=============+ccc+
          --                           s |    op1      |     >> 1
          --                                  sss  |op1|     >> 31 
          --                                  000      | 0   >> 0 (s=0)
          --                                  111      | 1   >> 0 (s=1)
          if data1(31) = '1' then
            shiftin(64 downto 33) := (others => '1');
          else
            shiftin(64 downto 33) := (others => '0');
          end if;
          shiftin(0) := carry;
          shiftin(32 downto 1) := data1;
          op2 := data2(4 downto 0);
          
          if not (data2(7 downto 5) = "000") then -- >= 32
            if data1(31) = '1' then
              shiftin(32 downto 0) := (others => '1');
            else
              shiftin(32 downto 0) := (others => '0');
            end if;
          end if;
          
          carryoutsrc := shiftin_00;
      
        when sOp_sror =>
      
          --$(del)
          --if Rs[7:0] == 0 then
          --  shifter_operand = Rm
          --  shifter_carry_out = C Flag
          --else if Rs[4:0] == 0 then
          --  shifter_operand = Rm 
          --  shifter_carry_out = Rm[31]
          --else /* Rs[4:0] > 0 */
          --  shifter_operand = Rm Rotate_Right Rs[4:0]
          --  shifter_carry_out = Rm[Rs[4:0] - 1]
          --$(/del)

          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- |           op1         |       op1       | 0 |
          -- +---+---+---------------+ccc+=============+---+
          --         |    op1            |                   <<  1 (>>1) 
          --                      |       op1       |        << 31 (>>31)

          shiftin := (others => '0');
          shiftin(64 downto 33) := data1;
          shiftin(32 downto 1) := data1;
          op2 := data2(4 downto 0);
          
          carryoutsrc := shiftin_32;
          
          if data2(7 downto 0) = "00000000" then -- == 0
            carryoutsrc := shiftin_prev;
            carryout := carry;
          end if;
          
        when sOp_srrx =>
      
          --$(del)
          --shifter_operand = (C Flag Logical_Shift_Left 31) OR (Rm Logical_Shift_Right 1)
          --shifter_carry_out = Rm[0]
          --$(/del)
          
          --  64  63               33  32 31          1  0
          -- +---+---+---------------+===+=============+---+
          -- |           000         | c |    op1-1        |
          -- +---+---+---------------+===+=============+ccc+
          --                                                 : rrx
          
          op2 := (others => '0');
          shiftin(31 downto 0) := carry & shiftin(31 downto 1);
          
        when sOp_snone =>
        when others => null;
      end case;
      
    when styp_none =>
      
      shiftin := (others => '0');
      shiftin(32 downto 1) := data1;
      
    when others => 
  end case;
  
  -- shifter
  if op2 (4) = '1' then
    shiftin(48 downto 0) := shiftin(64 downto 16);
  end if;
  if op2 (3) = '1' then
    shiftin(40 downto 0) := shiftin(48 downto 8);
  end if;
  if op2 (2) = '1' then
    shiftin(36 downto 0) := shiftin(40 downto 4);
  end if;
  if op2 (1) = '1' then
    shiftin(34 downto 0) := shiftin(36 downto 2);
  end if;
  if op2 (0) = '1' then
    shiftin(32 downto 0) := shiftin(33 downto 1);
  end if;

  -- carry out select
  case carryoutsrc is
    when shiftin_00   => carryout := shiftin(0);
    when shiftin_33   => carryout := shiftin(33);
    when shiftin_32   => carryout := shiftin(32);
    when shiftin_prev => 
    when others => null;
  end case;
    
  shiftout <= shiftin(32 downto 1);
  shiftcarryout <= carryout;

end process shifter;

end rtl;


